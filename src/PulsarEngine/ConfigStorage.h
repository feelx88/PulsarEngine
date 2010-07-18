#ifndef __ConfigStorage__
#define __ConfigStorage__

#include "IObject.h"
#include "ValueFactory.h"
#include <irrlicht.h>
#include <deque>

namespace pulsar
{
Vector parseStringToVector( String sVector );

struct ValueNotFoundException
{
	ValueNotFoundException( String name )
	{
		std::cout << "Value not found: " << name << std::endl;
	}
};

class ConfigStorage : public IObject
{

public:

	typedef std::multimap<String, Value*> ValueMap;

	ConfigStorage( bool bAllowDuplicates = false );
	~ConfigStorage();

	/**
	 * @brief Clears the ConfigStorage.
	 */
	void clear()
	{
		for( ValueMap::iterator x = m_mValues.begin(); x != m_mValues.end(); x++ )
		{
			if( x->second )
				delete x->second;
		}
		m_mValues.clear();

		for( std::map<String, ConfigStorage*>::iterator x = m_mSubSections.begin();
			x != m_mSubSections.end(); x++ )
		{
			if( x->second )
				delete x->second;
		}
		m_mSubSections.clear();
	}
	
	ConfigStorage& addTypeFilter( String typeName );
	void setTypeFilterStatus( bool status );

	template <class T>
	T& get( String sName )
	{
		if( m_bAlwaysGetRecursive )
			return getRecursive<T>( sName );

		ValueMap::iterator x = m_mValues.find( sName );
		if( x != m_mValues.end() )
		{
			return x->second->getAs<T>();
		}
		throw new ValueNotFoundException( sName );
	}

	template <class T>
	T &getRecursive( String sName )
	{
		ValueMap::iterator x = m_mValues.find( sName );
		if( x != m_mValues.end() )
		{
			return x->second->getAs<T>();
		}

		for( std::map<String, ConfigStorage*>::iterator x = m_mSubSections.begin();
			x != m_mSubSections.end(); x++ )
		{
			if( x->second->varExists( sName ) )
				return x->second->getRecursive<T>( sName );
		}
		throw new ValueNotFoundException( sName );
	}

	template <class T>
	T &get( String sName, T &standard )
	{
		try
		{
			return get<T>( sName );
		}
		catch( ValueNotFoundException* )
		{
			return standard;
		}
	}

	template <class T>
	const T& get( String sName, const T& standard )
	{
		try
		{
			return get<T>( sName );
		}
		catch( ValueNotFoundException* )
		{
			return standard;
		}
	}

	template <class T>
	T &getRecursive( String sName, T& standard )
	{
		try
		{
			return getRecursive<T>( sName );
		}
		catch( ValueNotFoundException* )
		{
			return standard;
		}
	}

	template <class T>
	T& getRecursive( String sName, const T& standard )
	{
		try
		{
			return getRecursive<T>( sName );
		}
		catch( ValueNotFoundException* )
		{
			return const_cast<T&>( standard );
		}
	}

	template <class T>
	ConfigStorage *set( String sName, T &value )
	{
		String sOperation = "Adding: ";
		if( !m_bAllowDuplicates && varExists( sName ) )
		{
			m_mValues.erase( sName );
			sOperation = "Changing: ";
		}

		Value *val = new Value( value );//0, Value::getTypeName<T>() );
		//val->set( value );

		m_mValues.insert( std::make_pair( sName, val ) );

		String sConverted = val->toString();
		if( sConverted != "" )
			sConverted = String( " = " ) + sConverted;

		std::cout << sOperation.c_str() << sName.c_str() << " ("
			<< val->getTypeName() << ")" << sConverted << std::endl;

		this->m_qReadQueue.push_back( sName );
		return this;
	}

	template <class T>
	ConfigStorage *setCopy( String sName, T &value )
	{
		String sOperation = "Adding: ";
		if( !m_bAllowDuplicates && varExists( sName ) )
		{
			deleteValue( sName );
			sOperation = "Changing: ";
		}

		Value *val = new Value( *new T( value ) );//0, Value::getTypeName<T>() );
		/*T *tmp = new T( value );
		val->set( *tmp );*/
		val->setAutoDestroy( true );

		m_mValues.insert( std::make_pair( sName, val ) );

		String sConverted = val->toString();
		if( sConverted != "" )
			sConverted = String( " = " ) + sConverted;

		std::cout << sOperation.c_str() << sName.c_str() << " ("
			<< val->getTypeName() << ")" << sConverted << std::endl;

		this->m_qReadQueue.push_back( sName );
		return this;
	}

	template <class T>
	ConfigStorage *set( String sName, const T& value )
	{
		String sOperation = "Adding: ";
		if( !m_bAllowDuplicates && varExists( sName ) )
		{
			deleteValue( sName );
			sOperation = "Changing: ";
		}

		Value *val = new Value( 0, Value::getTypeName<T>() );
		val->set<T>( value );

		m_mValues.insert( std::make_pair( sName, val ) );

		String sConverted = val->toString();
		if( sConverted != "" )
			sConverted = String( " = " ) + sConverted;

		std::cout << sOperation.c_str() << sName.c_str() << " ("
			<< val->getTypeName() << ")" << sConverted << std::endl;

		this->m_qReadQueue.push_back( sName );
		return this;
	}

	ConfigStorage *setValue( String sName, Value *value );

	ConfigStorage *deleteValue( String sName );

	bool varExists( String sName );

	ConfigStorage *append( ConfigStorage *pConf );

	ConfigStorage *appendCopy( ConfigStorage *pConf );

	ConfigStorage *parseXMLFile( String sFileName, String sSubSectionName = "" );

	String toXMLString( int iLevel = 0 );

	void saveToFile( String sFileName, bool bAppend = false );

	int countVars( String sName );

	ConfigStorage *addSubSection( String sName, ConfigStorage *pSubSection );

	ConfigStorage *getSubSection( String sName );
	
	void setNoSubSections( bool enabled = true );

	int getNumSubSections()
	{
		return m_mSubSections.size();
	}

	void setNodeName( String sName )
	{
		m_sNodeName = sName;
	}

	void setSectionLabel( String sLabel )
	{
		m_sSectionLabel = sLabel;
		m_FilterStrings.push_back( m_sSectionLabel );
	}

	void setAlwaysGetRecursive( bool bAlwaysRecursive = true )
	{
		m_bAlwaysGetRecursive = bAlwaysRecursive;
	}

private:

	void parseXMLReader( irr::io::IrrXMLReader *pXML );

	ValueMap m_mValues;

	std::deque<String> m_qReadQueue;

	std::multimap<String, ConfigStorage*> m_mSubSections;
	
	bool m_FilterEnabled;
	std::deque<String> m_FilterStrings;
	
	bool m_noSubSections;

	bool m_bAllowDuplicates;
	bool m_bAlwaysGetRecursive;
	String m_sSectionLabel, m_sNodeName;
};
}

#endif // __ConfigStorage__
