#include "ScriptToolkit.h"

using namespace pulsar;

ScriptToolkit::ScriptToolkit()
{
	setClassName( P_SCRIPTTOOLKIT );
}

ScriptToolkit::~ScriptToolkit()
{
	m_pLuaState = 0;
	m_mScriptStack.clear();
	m_iIDCounter = 0;
}

void ScriptToolkit::init( Value initParam )
{
	if( initParam.getClassName() == P_LUASTATE )
		m_pLuaState = &initParam.getAs<lua_State>();
	else
		throw "Not a lua_State!"; //TODO: Add ValueTypeException
}

void ScriptToolkit::update()
{
	std::map<int, String>::iterator x = m_mScriptStack.begin();
	for( ; x != m_mScriptStack.end(); x++ )
		executeString( x->second );
}

void ScriptToolkit::executeString( String sString )
{
	luaL_dostring( m_pLuaState, sString.c_str() );
}

void ScriptToolkit::executeFile( String sFileName )
{
	luaL_dofile( m_pLuaState, sFileName.c_str() );
}

int ScriptToolkit::addTickScript( String sScript )
{
	m_iIDCounter++;
	m_mScriptStack.insert( std::make_pair( m_iIDCounter, sScript ) );
}

void ScriptToolkit::removeTickScript( int iID )
{
	m_mScriptStack.erase( iID );
}

void ScriptToolkit::clearScriptStack()
{
	m_mScriptStack.clear();
}

