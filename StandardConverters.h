#ifndef __standardtypes__
#define __standardtypes__


#include "ValueFactory.h"
#include "ConfigStorage.h"
#include "DynamicEntity.h"
#include "StandardCallbacks.h"

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

//*Entity
template <class T>
struct EntityTypesConverter : public IValueConverter
{
	void *parseValues( ConfigStorage *pConf )
	{
		if( !pConf )
			return 0;

		T *pE = new T( pConf->get<int>( "ID", 0 ) );
		pE->loadFromValues( pConf );

		return static_cast<void*>( pE );
	}
};

//*SensorEntity
template <class T>
struct SensorEntityTypesConverter : public IValueConverter
{
	void *parseValues( ConfigStorage *pConf )
	{
		if( !pConf )
			return 0;

		T *pE = new T( pConf->get<int>( "ID", 0 ) );
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
