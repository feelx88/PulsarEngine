#ifndef __standardtypes__
#define __standardtypes__

#include "ValueFactory.h"
#include "ConfigStorage.h"
#include "Entities/DynamicEntity.h"
#include "StandardCallbacks.h"

#include <lua.h>
#include <lauxlib.h>

namespace pulsar
{

namespace StandardConverters
{

//Int
struct IntConverter : public IValueConverter
{
	void *parseString( String sStr )
	{
		if( sStr == "" )
			return 0;

		return static_cast<void*>(
		           new int( boost::lexical_cast<int>( sStr.c_str() ) ) );
	}

	String toString( void *pOb )
	{
		if( pOb )
			return String( *static_cast<int*>( pOb ) );
		return "";
	}

	void *parseValues( ConfigStorage *pConf )
	{
		String sStr = pConf->get<String>( "Value" );
		return static_cast<void*>(
		           new int( boost::lexical_cast<int>( sStr.c_str() ) ) );
	}
};

//Float
struct FloatConverter : public IValueConverter
{
	void *parseString( String sStr )
	{
		if( sStr == "" )
			return 0;

		return static_cast<void*>(
		           new float( boost::lexical_cast<float>( sStr.c_str() ) ) );
	}

	String toString( void *pOb )
	{
		if( pOb )
			return String( *static_cast<float*>( pOb ) );
		return "";
	}

	void *parseValues( ConfigStorage *pConf )
	{
		String sStr = pConf->get<String>( "Value" );
		return static_cast<void*>(
		           new int( boost::lexical_cast<float>( sStr.c_str() ) ) );
	}
};

//Bool
struct BoolConverter : public IValueConverter
{
	void *parseString( String sStr )
	{
		if( sStr == "" )
			return 0;

		return static_cast<void*>( new bool( sStr == "True" ) );
	}

	String toString( void *pOb )
	{
		if( pOb )
			return ( *static_cast<bool*>( pOb ) ) ? "True" : "False";
		return "";
	}

	void *parseValues( ConfigStorage *pConf )
	{
		String sStr = pConf->get<String>( "Value" );
		return static_cast<void*>(
		           new bool( sStr == "True" ? true : false ) );
	}
};

//String
struct StringConverter : public IValueConverter
{
	void *parseString( String sStr )
	{
		return static_cast<void*>( new String( sStr ) );
	}

	String toString( void *pOb )
	{
		if( pOb )
			return String( *static_cast<String*>( pOb ) );
		return "";
	}

	void *parseValues( ConfigStorage *pConf )
	{
		String sStr = pConf->get<String>( "Value" );
		return static_cast<void*>(
		           new String( sStr ) );
	}
};

//Vector
struct VectorConverter : public IValueConverter
{
	void *parseString( String sStr )
	{
		if( sStr == "" )
			return 0;

		Vector vec = parseStringToVector( sStr );

		return static_cast<void*>( new Vector( vec ) );
	}

	String toString( void *pOb )
	{
		if( pOb )
		{
			Vector vec = *static_cast<Vector*>( pOb );
			return String( vec.X ) + "," + String( vec.Y ) + "," + String( vec.Z );
		}
		return "";
	}

	void *parseValues( ConfigStorage *pConf )
	{
		float x = pConf->get<float>( "X" );
		float y = pConf->get<float>( "Y" );
		float z = pConf->get<float>( "Z" );
		return static_cast<void*>( new Vector( x, y, z ) );
	}

	ConfigStorage *toValues( void *pOb )
	{
		if( !pOb )
			return 0;
		Vector v = *static_cast<Vector*>( pOb );
		ConfigStorage *pConf = new ConfigStorage();
		pConf->setSectionLabel( "Vector" );
		pConf->set<float>( "X", v.X );
		pConf->set<float>( "Y", v.Y );
		pConf->set<float>( "Z", v.Z );
		return pConf;
	}
};

struct LuaIntConverter : public IValueConverter
{
	LuaIntConverter( lua_State *state )
	{
		m_State = state;
	}
	
	void *parseString( String str )
	{
		lua_getglobal( m_State, str.c_str() );
		return new int( luaL_checkinteger( m_State, 1 ) );
	}
	
	//TODO: toString
	
private:
	lua_State *m_State;
};

//std::vector
struct StringListConverter : public IValueConverter
{
    virtual void* parseString( String sInput )
    {
	    std::vector<String> *splitted = new std::vector<String>();
	    sInput.split<std::vector<String> >( *splitted, "," );
	    return static_cast<void*>( splitted );
    }
    
    virtual String toString( void* pOb )
    {
	    if( !pOb )
		    return "";
	    
	    std::vector<String> splitted = *static_cast<std::vector<String>* >( pOb );
	    String result = "";
	    int splittedSize = splitted.size();
	    
	    for( unsigned int x = 0; x < splittedSize; x++ )
	    {
		    result += splitted.at( x );
		    if( x < splittedSize - 1 )
			result += ",";
	    }
	    
	    return result;
    }
};

//Entity
template <class T>
struct EntityTypesConverter : public IValueConverter
{
	void *parseValues( ConfigStorage *pConf )
	{
		if( !pConf )
			return 0;

		T *pE = new T( pConf->get<int>( "ID", 0 ) );
		
		if( pConf->varExists( "File" ) )
		{
			pE->loadFromFile( pConf->get<String>( "File" ) );
			pE->loadFromValues( pConf );
		}
		else
			pE->loadFromValues( pConf );

		return static_cast<void*>( pE );
	}
};

//SensorEntity
template <class T>
struct SensorEntityTypesConverter : public IValueConverter
{
	void *parseValues( ConfigStorage *pConf )
	{
		if( !pConf )
			return 0;

		T *pE = new T( pConf->get<int>( "ID", 0 ) );
		if( pConf->varExists( "File" ) )
		{
			pE->loadFromFile( pConf->get<String>( "File" ) );
			pE->loadFromValues( pConf );
		}
		else
			pE->loadFromValues( pConf );

		if( pConf->varExists( "Callback" ) )
		{
			pE->setCallback( &pConf->get<ICallback>( "Callback" ) );
		}

		return static_cast<void*>( pE );
	}
};

//ApplyImpulseCallback
struct ApplyImpulseCallbackConverter : public IValueConverter
{
	void *parseValues( ConfigStorage *pConf )
	{
		if( !pConf )
			return 0;

		StandardCallbacks::ApplyImpulseCallback *cb = new
			StandardCallbacks::ApplyImpulseCallback(
				pConf->get<Vector>( "Direction", Vector() ),
				pConf->get<Vector>( "Offset", Vector() ) );

		return static_cast<void*>( cb );
	}
};

}

}

#endif // __standardtypes__
