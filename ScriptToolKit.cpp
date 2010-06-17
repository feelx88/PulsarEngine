#include "ScriptToolKit.h"
#include "PulsarEngine.h"

using namespace pulsar;

ScriptToolKit::ScriptToolKit() : IToolKit()
{
	setClassName( "ScriptToolKit" );
}

ScriptToolKit::~ScriptToolKit()
{
	m_pLuaState = 0;
	m_mScriptStack.clear();
	m_iIDCounter = 0;
}

void ScriptToolKit::init( Value initParam )
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs( m_pLuaState );

	LuaBinding::registerAll();

	m_pConsoleWindow = PulsarEngine::getInstance()->getConsoleWindow();
}

void ScriptToolKit::tickUpdate()
{
	for( std::map<int, String>::iterator x = m_mScriptStack.begin();
		x != m_mScriptStack.end(); x++ )
		executeString( x->second );
}

void ScriptToolKit::executeString( String sString )
{
	luaL_dostring( m_pLuaState, sString.c_str() );
}

void ScriptToolKit::executeFile( String sFileName )
{
	luaL_dofile( m_pLuaState, sFileName.c_str() );
}

int ScriptToolKit::addTickScript( String sScript )
{
	m_iIDCounter++;
	m_mScriptStack.insert( std::make_pair( m_iIDCounter, sScript ) );
	return m_iIDCounter;
}

void ScriptToolKit::removeTickScript( int iID )
{
	m_mScriptStack.erase( iID );
}

void ScriptToolKit::clearScriptStack()
{
	m_mScriptStack.clear();
}

