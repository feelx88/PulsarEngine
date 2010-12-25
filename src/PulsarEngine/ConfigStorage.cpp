 /*
    Copyright 2010 Felix Müller

    This file is part of the PulsarEngine.

    The PulsarEngine is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The PulsarEngine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with the PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ConfigStorage.h"

#include <fstream>

#include "Irrlicht_using.h"
namespace pulsar
{

ConfigStorage::ConfigStorage( bool bAllowDuplicates )
	: IObject(), m_bAllowDuplicates( bAllowDuplicates ), 
	m_sSectionLabel ( "Section" ), m_bAlwaysGetRecursive( false ), m_FilterEnabled( false ),
	m_noSubSections( false )
{
	setClassName( P_CONFIGSTORAGE );
	m_FilterStrings.push_back( m_sSectionLabel );
}

ConfigStorage::~ConfigStorage()
{
	clear();
}

ConfigStorage& ConfigStorage::addTypeFilter( String typeName )
{
	m_FilterEnabled = true;
	m_FilterStrings.push_back( typeName );
	return *this;
}

void ConfigStorage::setTypeFilterStatus( bool status )
{
	m_FilterEnabled = status;
}

Value *ConfigStorage::getValueN( int index, String name )
{
	ValueMap::iterator x = m_mValues.find( name );
	if( x != m_mValues.end() )
	{
		std::advance( x, index );
		return x->second;
	}
	else
		return 0;
}

Value *ConfigStorage::getValue( String name )
{
	return getValueN( 0, name );
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

ConfigStorage *ConfigStorage::deleteValueN( int index, String sName )
{
	ValueMap::iterator x = m_mValues.find( sName );
	if( x != m_mValues.end() )
	{
		std::advance( x, index );
		delete x->second;
		m_mValues.erase( sName );
		std::cout << "Deleting: " << sName.c_str() << std::endl;
	}
	return this;
}

ConfigStorage* ConfigStorage::deleteValue( String sName )
{
	deleteValueN( 0, sName );
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
		setValue( x->first, x->second );
	}
	return this;
}

ConfigStorage *ConfigStorage::appendCopy( ConfigStorage *pConf )
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

int ConfigStorage::countVars( String sName )
{
	int count = 0;
	count += m_mValues.count( sName );
	
	for( std::multimap<String, ConfigStorage*>::iterator x = m_mSubSections.begin();
		x != m_mSubSections.end(); x++ )
		count += x->second->countVars( sName );
	
	return count;
}

ConfigStorage *ConfigStorage::addSubSection( String sName, ConfigStorage *pSubSection )
{
	if( pSubSection )
	{
		if( m_noSubSections )
			append( pSubSection );
		else
		{
			Value *val = new Value( *pSubSection );
			setValue( sName, val );
			this->m_mSubSections.insert( std::make_pair( sName, pSubSection ) );
		}
	}

	return this;
}

ConfigStorage *ConfigStorage::getSubSection( String sName )
{
	std::map<String, ConfigStorage*>::iterator x =
		m_mSubSections.find( sName );

	if( x != m_mSubSections.end() )
		return x->second;

	return 0;
}

void ConfigStorage::setNoSubSections( bool enabled )
{
	m_noSubSections = enabled;
}

String ConfigStorage::toXMLString( int iLevel )
{
	String out = "";

	if( iLevel == 0 )
		out += "<?xml version=\"1.0\"?>\n\n";

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

			if( pConf )
			{
				out += sTab + "<" + pConf->m_sSectionLabel
					+ " Name=\"" + String( x->first ) + "\">\n";

				out += pConf->toXMLString( iLevel + 1 );

				out += sTab + "</" + pConf->m_sSectionLabel + ">\n";
			}
		}
		else if( x->second->toString() == "" )
		{
			ConfigStorage *pConf = x->second->toValues();

			if( pConf )
			{
				out += sTab + "<" + pConf->m_sSectionLabel
					+ " Name=\"" + String( x->first ) + "\">\n";

				out += pConf->toXMLString( iLevel + 1 );

				out += sTab + "</" + pConf->m_sSectionLabel + ">\n";
			}
		}
		else
		{
			String sType = x->second->getTypeName();
			out += sTab + "<" + sType + " Name=\"" + String( x->first ) + "\""
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
		out << "<?xml version=\"1.0\"?>\n\n";

	out << toXMLString().c_str();

}

void ConfigStorage::parseXMLReader( irr::io::IrrXMLReader *pXML )
{
	bool bElementOpened = false;
	String sCurrentNodeName = "";
	String sCurrentNodeType = "";
	irr::io::EXML_NODE nodeType = EXN_NONE;

	while( pXML->read() )
	{
		bool validNode = m_FilterEnabled ? std::count( m_FilterStrings.begin(), 
			m_FilterStrings.end(), sCurrentNodeType ) : true;
		
		nodeType = pXML->getNodeType();
			
		if( nodeType == EXN_ELEMENT_END ) //</foo>
		{
			if( bElementOpened )
				bElementOpened = false;
			else
				return;
		} //node type element_end

		if( nodeType == EXN_TEXT ) //<...>foo</...>
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
				else if( validNode )//<Entity ...><...><...></Entity>
				{
					ConfigStorage pConf( m_bAllowDuplicates );
					pConf.setAlwaysGetRecursive( m_bAlwaysGetRecursive );
					pConf.parseXMLReader( pXML );

					Value *val = new Value( 0, sCurrentNodeType );
					val->parseValues( &pConf );
					setValue( sCurrentNodeName, val );

					bElementOpened = false;
				}
			}
		} //node type text

		if( nodeType == EXN_ELEMENT ) //<foo ...>
		{
			sCurrentNodeName = pXML->getAttributeValueSafe( "Name" );
			sCurrentNodeType = pXML->getNodeName();
		
			if( sCurrentNodeName != "" ) //Prevent nameless tags
			{
				Value *val = 0;

				if( pXML->isEmptyElement() && validNode ) //<foo ... />
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

						Value tmp( 0, sType );
						tmp.parseString( sAttrValue );
						pConf->set( sAttrName, tmp );
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
						ConfigStorage *pConf = new ConfigStorage( m_bAllowDuplicates );
						pConf->setAlwaysGetRecursive( m_bAlwaysGetRecursive );
						
						pConf->m_FilterStrings = m_FilterStrings;
						pConf->m_FilterEnabled = m_FilterEnabled;
						
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
