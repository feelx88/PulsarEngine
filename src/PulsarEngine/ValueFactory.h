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
    along with The PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __valuefactory__
#define __valuefactory__

#include "IObject.h"

namespace pulsar
{

class ConfigStorage;

/**
 * @struct IValueConverter
 * @author Felix Müller
 * @date 02.05.2010
 * @file ValueFactory.h
 * @brief Interface which defines conversion functions for registering types as
 * Value. If reading and/or writing to a ConfigStorage xml file is needed, at
 * least one out of the parseX/toX method pair has to be implemented.
 */
struct IValueConverter : public IObject
{
	virtual String toString( void *pOb )
	{
		return String();
	}

	virtual void *parseString( String sInput )
	{
		return 0;
	}

	virtual ConfigStorage *toValues( void *pOb )
	{
		return 0;
	}

	virtual void *parseValues( ConfigStorage *pConfig )
	{
		return 0;
	}
};

class Value : public IObject
{
	private:

	struct ValueGeneratorBase
	{
		virtual void *parseString( String sParseString ) = 0;
		virtual String toString( void *pOb ) = 0;
		virtual void *parseValues( ConfigStorage *pData ) = 0;
		virtual ConfigStorage *toValues( void *pOb ) = 0;
		virtual void destruct( void* pOb ) = 0;
		virtual void *copy( void *pOb ) = 0;
	};

	template <class T>
	class ValueGenerator : public ValueGeneratorBase, public IObject
	{
	public:

		ValueGenerator( String sTypeName, IValueConverter *pConverter = 0 )
			: IObject(), m_sTypeName( sTypeName ), m_pConverter( pConverter )
		{
			setInfo( P_VALUEGENERATOR, String( P_VALUEGENERATOR ) + sTypeName );
		}

		void* parseString( String sParseString )
		{
			if( m_pConverter )
				return m_pConverter->parseString( sParseString );
		}

		String toString( void* pOb )
		{
			if( m_pConverter )
				return m_pConverter->toString( pOb );
			return String();
		}

		void* parseValues( ConfigStorage *pData )
		{
			if( m_pConverter )
				return m_pConverter->parseValues( pData );
			return 0;
		}

		ConfigStorage *toValues( void* pOb )
		{
			if( m_pConverter )
				return m_pConverter->toValues( pOb );
			return 0;
		}

		void destruct( void* pOb )
		{
			if( pOb )
			{
				T *pT = static_cast<T*>( pOb );
				delete pT;
			}
		}

		void *copy( void *pOb )
		{
			if( pOb )
			{
				T *newOb = static_cast<T*>( pOb );
				return static_cast<void*>( new T( *newOb ) );
			}
			return 0;
		}

	private:
		String m_sTypeName;
		IValueConverter *m_pConverter;

	};

public:

	template <class T>
	Value( T& val ) : m_Generated( false )
	{
		setClassName( P_VALUE );
		m_Value = static_cast<void*>( &val );
		m_sTypeName = getTypeName<T>();
		m_pGenerator = getGenerator( m_sTypeName );
	}

	template <class T>
	Value( const T& val ) : m_Generated( false )
	{
		setClassName( P_VALUE );
		m_Value = static_cast<void*>( new T( val ) );
		m_sTypeName = getTypeName<T>();
		m_pGenerator = getGenerator( m_sTypeName );
	}

	Value( void *val, String sTypeName ) : m_Generated( false )
	{
		setClassName( P_VALUE );
		m_Value = val;
		m_sTypeName = sTypeName;
		m_pGenerator = getGenerator( m_sTypeName );
	}

	Value() : m_pGenerator( 0 ), m_Value( 0 ), m_Generated( false )
	{
		setClassName( P_VALUE );
		m_sTypeName = "Nil";
	}

	Value *copy()
	{
		m_Generated = true;
		if( m_pGenerator )
			return new Value( this->m_pGenerator->copy( m_Value ), m_sTypeName );
		else
			return new Value( m_Value, m_sTypeName );//TODO: copy
	}

	~Value()
	{
		if( m_Value && m_pGenerator && m_Generated )
			m_pGenerator->destruct( m_Value );
	}

	String getTypeName()
	{
		return m_sTypeName;
	}

	template <class T>
	T &getAs()
	{
		if( !m_Value )
			throw "No valid Value!";
		return *static_cast<T*>( m_Value );
	}

	template <class T>
	void set( T& val )
	{
		if( m_sTypeName == "Nil" )
			m_sTypeName = getTypeName<T>();
		else if( getTypeName<T>() != m_sTypeName )
			throw "Invalid Conversion!";

		if( m_Value && m_Generated )
		{
			if( m_pGenerator )
				m_pGenerator->destruct( m_Value );
			else
				delete static_cast<T*>( m_Value );
		}

		m_Value = static_cast<void*>( &val );
		m_Generated = false;
	}

	template <class T>
	void set( const T& val )
	{
		if( m_sTypeName == "Nil" )
			m_sTypeName = getTypeName<T>();
		else if( getTypeName<T>() != m_sTypeName )
			throw "Invalid Conversion!";

		if( m_Value && m_Generated )
		{
			if( m_pGenerator )
				m_pGenerator->destruct( m_Value );
			else
				delete static_cast<T*>( m_Value );
		}

		m_Value = static_cast<void*>( new T( val ) );

		m_Generated = true;
	}

	template <class T>
	Value operator=( T &val )
	{
		set( val );
		return *this;
	}

	template <class T>
	Value operator=( const T& val )
	{
		set( val );
		return *this;
	}

	String toString()
	{
		if( m_pGenerator )
			return m_pGenerator->toString( m_Value );
		return "";
	}

	void parseString( String sParseString )
	{
		if( m_pGenerator )
		{
			if( m_Value && m_Generated )
				m_pGenerator->destruct( m_Value );
			m_Value = m_pGenerator->parseString( sParseString );
			m_Generated = true;
		}
	}

	ConfigStorage *toValues()
	{
		if( m_pGenerator )
			return m_pGenerator->toValues( m_Value );
		return 0;
	}

	void parseValues( ConfigStorage *pData )
	{
		if( m_pGenerator )
		{
			if( m_Value && m_Generated )
				m_pGenerator->destruct( m_Value );
			m_Value = m_pGenerator->parseValues( pData );
			m_Generated = true;
		}
	}

	void setAutoDestroy( bool autoDestroy )
	{
		m_Generated = autoDestroy;
	}

	template <class T>
	static String getTypeName()
	{
		std::map<String, String>::iterator x =
			m_mTypeAliases.find( typeid( T ).name() );
		if( x != m_mTypeAliases.end() )
			return x->second;
		else if( String( typeid( T ).name() ).find( "P" ) )
			return "Unknown*";
		else
			return "Unknown";
	}

	static bool isSupported( String sTypeName )
	{
		for( std::multimap<String, String>::iterator x = m_mTypeAliases.begin();
			x != m_mTypeAliases.end(); x++ )
		{
			if( x->second == sTypeName )
				return true;
		}
		return false;
	}

	template <class T>
	static void registerType( String sTypeName, IValueConverter *pConverter = 0 )
	{
		ValueGeneratorBase *gen = new ValueGenerator<T>( sTypeName, pConverter );
		m_mGenerators.insert( std::make_pair( sTypeName, gen ) );
		m_mTypeAliases.insert(
			std::make_pair( typeid( T ).name(), sTypeName ) );
	}

	static ValueGeneratorBase *getGenerator( String sTypeName )
	{
		std::map<String, ValueGeneratorBase*>::iterator x =
			m_mGenerators.find( sTypeName );

		if( x != m_mGenerators.end() )
			return x->second;
		return 0;
	}

private:

	void *m_Value;

	bool m_Generated;

	String m_sTypeName;
	ValueGeneratorBase *m_pGenerator;

	static std::map<String, ValueGeneratorBase*> m_mGenerators;
	static std::multimap<String, String> m_mTypeAliases;
};

}

#endif // __valuefactory__
