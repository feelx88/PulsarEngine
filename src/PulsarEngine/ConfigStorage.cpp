#include "ConfigStorage.h"

#include <fstream>

#include "Irrlicht_using.h"
namespace pulsar
{

ConfigStorage::ConfigStorage( bool bAllowDuplicates )
	: IObject(),
		m_bAllowDuplicates( bAllowDuplicates ), m_sSectionLabel ( "Section" ),
		m_bAlwaysGetRecursive( false )
{
	setClassName( P_CONFIGSTORAGE );
}

ConfigStorage::~ConfigStorage()
{
	for( ValueMap::iterator x = m_mValues.begin(); x != m_mValues.end(); x++ )
		delete x->second;
	m_mValues.clear();

	for( std::map<String, ConfigStorage*>::iterator x = m_mSubSections.begin();
		x != m_mSubSections.end(); x++ )
		delete x->second;
	m_mSubSections.clear();
}

ConfigStorage *ConfigStorage::setValue( String sName, Value *value )
{
	String sOperation = "Adding: ";
	if( !m_bAllowDuplicates && varExists( sName ) )
	{
		m_mValues.erase( sName );
		sOperation = "Changing: ";
	}

	m_mValues.insert( std::make_pair( sName, value ) );

	String sConverted = value->toString();
	if( sConverted != "" )
		sConverted = String( " = " ) + sConverted;

	std::cout << sOperation.c_str() << sName.c_str()<< " ("
		<< value->getTypeName() << ")"
		<< sConverted << std::endl;

	this->m_qReadQueue.push_back( sName );
	return this;
}

ConfigStorage *ConfigStorage::deleteValue( String sName )
{
	ValueMap::iterator x = m_mValues.find( sName );
	if( x != m_mValues.end() )
	{
		delete x->second;
		m_mValues.erase( sName );
		std::cout << "Deleting: " << sName.c_str() << std::endl;
	}
	return this;
}

bool ConfigStorage::varExists( String sName )
{
	if( m_mValues.find( sName ) != m_mValues.end() )
		return true;

	for( std::map<String, ConfigStorage*>::iterator x = this->m_mSubSections.begin();
		x != this->m_mSubSections.end(); x++ )
	{
		if( x->second->varExists( sName ) )
			return true;
	}

	return false;
}

ConfigStorage *ConfigStorage::append( ConfigStorage *pConf )
{
	for( ValueMap::iterator x = pConf->m_mValues.begin();
		x != pConf->m_mValues.end(); x++ )
	{
		Value *val = x->second->copy();
		setValue( x->first, val );
	}
	return this;
}

ConfigStorage *ConfigStorage::parseXMLFile( String sFileName, String sSubSectionName )
{
	IrrXMLReader *pXML = createIrrXMLReader( sFileName.c_str() );

	if( !pXML )
		return this;

	if( sSubSectionName != "" )
	{
		this->m_sNodeName = sSubSectionName;

		bool bSearching = true;
		while( pXML->read() && bSearching )
		{
			if( pXML->getNodeType() == EXN_ELEMENT )
			{
				if( String( pXML->getAttributeValueSafe( "Name" ) ) == sSubSectionName )
				{
					this->m_sSectionLabel = pXML->getNodeName();
					break;
				}
			}
		}
	}

	parseXMLReader( pXML );

	return this;
}

ConfigStorage *ConfigStorage::addSubSection( String sName, ConfigStorage *pSubSection )
{
	Value *val = new Value( pSubSection );
	setValue( sName, val );
	this->m_mSubSections[sName] = pSubSection;

	return this;
}

ConfigStorage *ConfigStorage::getSubSection( String sName )
{
	std::map<String, ConfigStorage*>::iterator x =
		m_mSubSections.find( sName );

	if( x != m_mSubSections.end() )
		return x->second;

	return this;
}

String ConfigStorage::toXMLString( int iLevel )
{
	String out = "";

	String sTab = "";

	for( int x = 0; x < iLevel; x++ )
	{
		sTab += "\t";
	}

	for( std::deque<String>::iterator z = this->m_qReadQueue.begin();
		z != this->m_qReadQueue.end(); z++ )
	{
		ValueMap::iterator x = this->m_mValues.find( *z );
		if( x == this->m_mValues.end() )
			continue;

		if( x->second->getTypeName() == "ConfigStorage" )
		{
			ConfigStorage *pConf = x->second->getAs<ConfigStorage*>();

			out += sTab + "<" + pConf->m_sSectionLabel
				+ " Name=\"" + x->first + "\">\n";

			out += pConf->toXMLString( iLevel + 1 );

			out += sTab + "</" + pConf->m_sSectionLabel + ">\n";
		}
		else if( x->second->toString() == "" )
		{
			ConfigStorage *pConf = x->second->toValues();

			out += sTab + "<" + pConf->m_sSectionLabel
				+ " Name=\"" + x->first + "\">\n";

			out += pConf->toXMLString( iLevel + 1 );

			out += sTab + "</" + pConf->m_sSectionLabel + ">\n";
		}
		else
		{
			String sType = x->second->getTypeName();
			out += sTab + "<" + sType + " Name=\"" + x->first + "\""
				+ ">" + x->second->toString() + "</" + sType + ">\n";
		}
	}
	return out;
}

void ConfigStorage::saveToFile( String sFileName, bool bAppend )
{
	std::ofstream out( sFileName.c_str(),
		( bAppend ? std::ios::out | std::ios::app : std::ios::out ) );

	if( !bAppend )
		out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";

	out << toXMLString().c_str();

}

void ConfigStorage::parseXMLReader( irr::io::IrrXMLReader *pXML )
{
	bool bElementOpened = false;
	String sCurrentNodeName = "";
	String sCurrentNodeType = "";

	while( pXML->read() )
	{
		if( pXML->getNodeType() == EXN_ELEMENT_END ) //</foo>
		{
			if( bElementOpened )
				bElementOpened = false;
			else
				return;
		} //node type element_end

		if( pXML->getNodeType() == EXN_TEXT ) //<...>foo</...>
		{
			if( bElementOpened )
			{
				String sNodeData = pXML->getNodeData();
				sNodeData.trim(); //Because it could be a whitespace

				if( sNodeData != "" ) //<Int ...>17</Int>
				{
					Value *val = new Value( 0, sCurrentNodeType );
					val->parseString( sNodeData );
					setValue( sCurrentNodeName, val );
				}
				else //<Entity ...><...><...></Entity>
				{
					ConfigStorage *pConf = new ConfigStorage();
					pConf->parseXMLReader( pXML );

					Value *val = new Value( 0, sCurrentNodeType );
					val->parseValues( pConf );
					setValue( sCurrentNodeName, val );

					bElementOpened = false;

					delete pConf;
				}
			}
		} //node type text

		if( pXML->getNodeType() == EXN_ELEMENT ) //<foo ...>
		{
			sCurrentNodeName = pXML->getAttributeValueSafe( "Name" );
			sCurrentNodeType = pXML->getNodeName();

			if( sCurrentNodeName != "" ) //Prevent nameless tags
			{
				Value *val = 0;

				if( pXML->isEmptyElement() ) //<foo ... />
				{
					ConfigStorage *pConf = new ConfigStorage();

					String sType = "";
					String sAttrName = "";
					String sAttrValue = "";
					int iDelimPos = -1;

					for( unsigned int x = 0; x < pXML->getAttributeCount(); x++ )
					{
						sAttrName = pXML->getAttributeName( x );
						sAttrValue = pXML->getAttributeValue( x );

						iDelimPos = sAttrValue.find( ":" );

						if( iDelimPos > 0 )
						{
							sType = sAttrValue.subString( 0, iDelimPos );
							sAttrValue = sAttrValue.subString(
								iDelimPos, sAttrValue.size() - iDelimPos );
						}
						else
							sType = "String";

						Value val( 0, sType );
						val.parseString( sAttrValue );
						pConf->set( sAttrName, val );
					}

					val = new Value( 0, sCurrentNodeType );
					val->parseValues( pConf );

					setValue( sCurrentNodeName, val );

					delete pConf;
				}
				else //!empty
				{
					if( Value::isSupported( sCurrentNodeType ) ) //<Int>...</Int>
					{
						bElementOpened = true;
					}
					else //<Section>...</Section>
					{
						ConfigStorage *pConf = new ConfigStorage();
						pConf->parseXMLReader( pXML );

						pConf->setNodeName( sCurrentNodeName );
						pConf->setSectionLabel( sCurrentNodeType );

						addSubSection( sCurrentNodeName, pConf );
					}
				} //empty
			} //current node name = ""
		} //node type element
	} //read()
}

Vector parseStringToVector( String sVector )
{
	int iFirst, iLast;
	float fX = 0.0f;
	float fY = 0.0f;
	float fZ = 0.0f;
	iFirst = sVector.findFirst( ',' );
	iLast = sVector.findLast( ',' );
	if( iFirst == iLast )
	{
		fX = boost::lexical_cast<float>( sVector.subString( 0, iFirst ).c_str() );
		fY = boost::lexical_cast<float>( sVector.subString( iFirst + 1, sVector.size() - iFirst ).c_str() );
	}
	else
	{
		fX = boost::lexical_cast<float>( sVector.subString( 0, iFirst ).c_str() );
		fY = boost::lexical_cast<float>( sVector.subString( iFirst + 1, iLast - iFirst - 1 ).c_str() );
		fZ = boost::lexical_cast<float>( sVector.subString( iLast + 1, sVector.size() - iLast ).c_str() );
	}

	return vector3df( fX, fY, fZ );
}

}
