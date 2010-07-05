#ifndef __iobject__
#define __iobject__

//Load standard headers
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <map>
#include <deque>

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
		s_mObjects.push_back( this );
	}

	virtual ~IObject()
	{
		s_mObjects.erase(
			std::find( s_mObjects.begin(), s_mObjects.end(), this ) );
		m_sName = "";
		m_sClassName = "";
	}

	String getClassName()
	{
		return m_sClassName;
	}

	String getName()
	{
		return m_sName;
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

	void setInfo( String sClassName, String sName )
	{
		setClassName( sClassName );
		setName( sName );
	}

	String m_sClassName;
	String m_sName;

	static std::deque<IObject*> s_mObjects;
};

}
#endif // __iobject__
