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

#include "ScriptToolKit.h"
#include "../PulsarEngine.h"

namespace pulsar
{

ScriptToolKit::ScriptToolKit() : IToolKit(), m_iIDCounter( 0 ), mTickStackSize( 0 )
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
	
	//Load Pulsar definitions
	//luaL_dofile( m_pLuaState, "pulsar_defs.lua" );
	executeFile( "pulsar_defs.lua" );
	
	//Get Pulsar-*
	lua_getglobal( m_pLuaState, "Pulsar" );
	
	//Set Pulsar.TickScripts = {}
	lua_newtable( m_pLuaState );
	lua_setfield( m_pLuaState, -2, "TickScripts" );
	
	//Set Pulsar.executeTickScripts() = ...
	luaL_loadstring( m_pLuaState,
		"if next( Pulsar.TickScripts ) then \
		for y, x in pairs( Pulsar.TickScripts ) do x() end end" );
	lua_setfield( m_pLuaState, -2, "executeTickScripts" );
	
	//Pop Pulsar.*
	lua_pop( m_pLuaState, 1 );
	
	LuaBinding::registerAll();
	
	m_pConsoleWindow = PulsarEngine::getInstance()->getConsoleWindow();
}

void ScriptToolKit::tickUpdate()
{
	if( mTickStackSize )
		return;
	
	//Get Pulsar.*
	lua_getglobal( m_pLuaState, "Pulsar" );
	
	//Get Pulsar.TickScripts
	lua_getfield( m_pLuaState, -1, "executeTickScripts" );
	
	//Call Pulsar.executeTickScripts
	lua_pcall( m_pLuaState, 0, LUA_MULTRET, 0 );
	
	//Clear Stack
	lua_pop( m_pLuaState, 1 );
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
	mTickStackSize++;

	lua_getglobal( m_pLuaState, "Pulsar" );
	lua_getfield( m_pLuaState, -1, "TickScripts" );
	lua_pushinteger( m_pLuaState, m_iIDCounter );
	luaL_loadstring( m_pLuaState, sScript.c_str() );
	lua_settable( m_pLuaState, -3 );
	
	lua_pop( m_pLuaState, 2 );

	return m_iIDCounter;
}

void ScriptToolKit::removeTickScript( int iID )
{
	mTickStackSize--;
	lua_getglobal( m_pLuaState, "Pulsar" );
	lua_getfield( m_pLuaState, -1, "TickScripts" );
	
	lua_pushinteger( m_pLuaState, iID );
	lua_pushnil( m_pLuaState );
	lua_settable( m_pLuaState, -3 );
	
	lua_pop( m_pLuaState, 2 );
}

void ScriptToolKit::clearScriptStack()
{
	mTickStackSize = 0;
	executeString( "Pulsar.TickScripts = {}" );
}

irr::EKEY_CODE ScriptToolKit::getPulsarKeyCode( String keyName )
{
	lua_getglobal( m_pLuaState, "Pulsar" );
	lua_getfield( m_pLuaState, -1, "Key" );
	lua_getfield( m_pLuaState, -1, keyName.c_str() );
	irr::EKEY_CODE key = (irr::EKEY_CODE)lua_tointeger( m_pLuaState, -1 );
	lua_pop( m_pLuaState, 3 );
	return key;
}

}
