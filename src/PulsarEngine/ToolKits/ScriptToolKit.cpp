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

#include "ScriptToolKit.h"
#include "../PulsarEngine.h"

namespace pulsar
{

ScriptToolKit::ScriptToolKit() : IToolKit()
{
	setClassName( "ScriptToolKit" );
}

ScriptToolKit::~ScriptToolKit()
{
	m_pLuaState = 0;
	m_iIDCounter = 0;
}

String ScriptToolKit::getToolKitClassName()
{
	return typeid( *this ).name();
}

void ScriptToolKit::init( Value initParam )
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs( m_pLuaState );

	luaL_dostring( m_pLuaState, "TickScripts = {}" );
	luaL_loadstring( m_pLuaState,
		"if next( TickScripts ) then \
		for y, x in pairs( TickScripts ) do x() end end" );
	lua_setglobal( m_pLuaState, "Pulsar.executeTickScripts" );

	LuaBinding::registerAll();

	m_pConsoleWindow = PulsarEngine::getInstance()->getConsoleWindow();
}

void ScriptToolKit::tickUpdate()
{
	lua_getglobal( m_pLuaState, "Pulsar.executeTickScripts" );
	lua_call( m_pLuaState, 0, 0 );
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

	lua_getglobal( m_pLuaState, "TickScripts" );
	lua_pushinteger( m_pLuaState, m_iIDCounter );
	luaL_loadstring( m_pLuaState, sScript.c_str() );
	lua_settable( m_pLuaState, -3 );

	return m_iIDCounter;
}

void ScriptToolKit::removeTickScript( int iID )
{
	lua_getglobal( m_pLuaState, "TickScripts" );
	lua_pushinteger( m_pLuaState, iID );
	lua_pushnil( m_pLuaState );
	lua_settable( m_pLuaState, -3 );
}

void ScriptToolKit::clearScriptStack()
{
	executeString( "TickScripts = {}" );
}

}
