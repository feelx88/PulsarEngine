#ifndef __iobject__
#define __iobject__

//Load standard headers
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <map>

#include <irrlicht.h>

typedef irr::core::stringc String;
typedef irr::core::vector3df Vector;

//cout operator for irrlicht strings
std::ostream& operator<<( std::ostream& out, String str );

//Bullet includes
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

//lua includes
extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

//Boost includes
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

//Type name defines
#define P_INTEGER "Int"
#define P_FLOAT "Float"
#define P_BOOL "Bool"
#define P_STRING "String"
#define P_VECTOR "Vector"

#define P_VALUEGENERATOR "ValueGenerator"
#define P_VALUE "Value"
#define P_PULSARENGINE "PulsarEngine"
#define P_CONFIGSTORAGE "ConfigStorage"
#define P_ENTITY "Entity"
#define P_SCRIPTTOOLKIT "ScriptToolkit"
#define P_LUASTATE "lua_StatePointer"
#define P_IRRLICHTDEVICE "IrrlichtDevicePointer"

namespace pulsar
{

class IObject
{
public:

	IObject()
	{
		if( s_Unused.empty() )
			m_iObjectID = ++s_iIDCounter;
		else
		{
			m_iObjectID = s_Unused.top();
			s_Unused.pop();
		}

		s_mObjects.insert( std::make_pair( m_iObjectID, this ) );
	}

	virtual ~IObject()
	{
		if( m_iObjectID >= 8192 )
			s_Unused.push( m_iObjectID );

		m_sName = "";
		m_sClassName = "";
		m_iObjectID = -1;
	}

	String getClassName()
	{
		return String( "IObject" );
	}

	String getName()
	{
		return m_sName;
	}

	unsigned int getObjectID()
	{
		return m_iObjectID;
	}

	static IObject *getByObjectID( int iID )
	{
		std::map<unsigned int, IObject*>::iterator x = s_mObjects.find( iID );
		if( x != s_mObjects.end() )
			return x->second;
		return 0;
	}

protected:

	void setClassName( String sClassName )
	{
		m_sClassName = sClassName;
	}

	void setName( String sName )
	{
		m_sName = sName;
	}

	void setObjectID( unsigned int iID )
	{
		if( iID > 0 )
		{
			if( m_iObjectID >= 8192 )
				s_Unused.push( m_iObjectID );

			s_mObjects.erase( iID );

			m_iObjectID = iID;
			s_mObjects.insert( std::make_pair( m_iObjectID, this ) );
		}
	}

	void setInfo( String sClassName, String sName, unsigned int iID = 0 )
	{
		setClassName( sClassName );
		setName( sName );
		setObjectID( iID );
	}

	String m_sClassName;
	String m_sName;
	unsigned int m_iObjectID;

	static std::map<unsigned int, IObject*> s_mObjects;
	static std::stack<unsigned int> s_Unused;

	static unsigned int s_iIDCounter;
};

}
#endif // __iobject__
