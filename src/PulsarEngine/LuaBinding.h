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

#ifndef __luabinding__
#define __luabinding__

#define S_PULSARENGINE LuaBinding::s_pEngine
#define S_LUASTATE LuaBinding::s_pState

#define PULSAR "Pulsar"
#define PULSAREVENTRECEIVER "PulsarEventReceiver"
#define SCRIPTTOOLKIT "ScriptToolKit"
#define ENTITYTOOLKIT "EntityToolKit"
#define CONSTRAINTTOOLKIT "ConstraintToolKit"
#define CAMERATOOLKIT "CameraToolKit"
#define ENTITY "Entity"
#define DYNAMICENTITY "DynamicEntity"
#define CONFIGSTORAGE "ConfigStorage"
#define VECTOR "Vector"

namespace pulsar
{

class LuaBinding
{

public:
	static void registerAll()
	{
		S_PULSARENGINE = PulsarEngine::getInstance();

		S_LUASTATE =
			S_PULSARENGINE->getToolKit<ScriptToolKit>()->getLuaState();

		luaL_Reg pulsar[] =
		{
			{ "log", pulsar_log },

			{ "getConfig", pulsar_getConfig },

			{ "getEventReceiver", pulsar_getEventReceiver },
			{ "getScriptToolKit", pulsar_getScriptToolKit },
			{ "getEntityToolKit", pulsar_getEntityToolKit },
			{ "getConstraintToolKit", pulsar_getConstraintToolKit },
			{ "getCameraToolKit", pulsar_getCameraToolKit },

			{ "run", pulsar_run },
			{ "beginDrawing", pulsar_beginDrawing },
			{ "endDrawing", pulsar_endDrawing },

			{ "showConsoleWindow", pulsar_showConsoleWindow },

			{ "setSimulationState", pulsar_setSimulationState },
			{ "setGravity", pulsar_setGravity },

			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, PULSAR, pulsar );

		//PulsarEventReceiver
		luaL_reg eventReceiver[] =
		{
			{ "keyState", evt_keyState },
			{ "getMouseX", evt_getMouseX },
			{ "getMouseY", evt_getMouseY },
			{ "getMouseMoveX", evt_getMouseMoveX },
			{ "getMouseMoveY", evt_getMouseMoveY },
			{ "getMouseButtonState", evt_getMouseButtonState },
			{ "getMouseWheelDelta", evt_getMouseWheelDelta },
			{ "showMouse", evt_showMouse },
			{ "setMousePosition", evt_setMousePosition },
			{ "lockMouse", evt_lockMouse },
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, PULSAREVENTRECEIVER, eventReceiver );
		luaL_newmetatable( S_LUASTATE, PULSAREVENTRECEIVER );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		//ScriptToolKit
		luaL_reg scriptToolKit[] =
		{
			{ "addTickScript", stk_addTickScript },
			{ "removeTickScript", stk_removeTickScript },
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, SCRIPTTOOLKIT, scriptToolKit );
		luaL_newmetatable( S_LUASTATE, SCRIPTTOOLKIT );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		//EntityToolKit
		luaL_reg entityToolKit[] =
		{
			//TODO: { "addEntity", etk_addEntity },
			{ "addEntity", etk_addEntity },
			/*TODO: { "createEntity", etk_createEntity },
			{ "createDynamicEntity", etk_createDynamicEntity },
			{ "createEntityFromFile", etk_createEntityFromFile },
			{ "createDynamicEntityFromFile", etk_createDynamicEntityFromFile },*/
			{ "getEntity", etk_getEntity },

			{ "rayHitsEntity", etk_rayHitsEntity },
			{ "getEntityInRay", etk_getEntityInRay },
			{ "getDynamicEntityInRay", etk_getDynamicEntityInRay },
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, ENTITYTOOLKIT, entityToolKit );
		luaL_newmetatable( S_LUASTATE, ENTITYTOOLKIT );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		//ConstraintToolKit
		luaL_reg constraintToolKit[] =
		{
			//TODO:
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, CONSTRAINTTOOLKIT, constraintToolKit );
		luaL_newmetatable( S_LUASTATE, CONSTRAINTTOOLKIT );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		//CameraToolKit
		luaL_reg cameraToolKit[] =
		{
			{ "addCamera", camtk_addCamera },
			{ "setCameraPosition", camtk_setCameraPosition },
			{ "setCameraTarget", camtk_setCameraTarget },
			{ "setCameraUpVector", camtk_setCameraUpVector },
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, CAMERATOOLKIT, cameraToolKit );
		luaL_newmetatable( S_LUASTATE, CAMERATOOLKIT );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		//Config
		luaL_Reg config[] =
		{
			{ "new", confstore_new },
			{ "parseXMLFile", confstore_parseXMLFile },

			{ "setBool", confstore_setBool },
			{ "setInt", confstore_setInt },
			{ "setFloat", confstore_setFloat },
			{ "setString", confstore_setString },
			{ "setVector", confstore_setVector },

			{ "getBool", confstore_getBool },
			{ "getInt", confstore_getInt },
			{ "getFloat", confstore_getFloat },
			{ "getString", confstore_getString },
			{ "getVector", confstore_getVector },

			{ "deleteValue", confstore_deleteValue },
			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, CONFIGSTORAGE, config );
		luaL_newmetatable( S_LUASTATE, CONFIGSTORAGE );

		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__call" );
		lua_pushcfunction( S_LUASTATE, confstore_new );
		lua_rawset( S_LUASTATE, -3 );

		//Vector
		luaL_Reg vector[] =
		{
			{ "new", vector_new },
			{ "set", vector_set },
			{ "zero", vector_zero },

			{ "getX", vector_getX },
			{ "getY", vector_getY },
			{ "getZ", vector_getZ },

			{ "add", vector_add },
			{ "sub", vector_sub },
			{ "mul", vector_mul },
			{ "div", vector_div },
			{ "dot", vector_dot },
			{ "cross", vector_cross },

			{ "normalize", vector_normalize },

			{ 0, 0 }
		};

		//{
		luaL_register( S_LUASTATE, VECTOR, vector );
		luaL_newmetatable( S_LUASTATE, VECTOR );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__call" );
		lua_pushcfunction( S_LUASTATE, vector_new );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__add" );
		lua_pushcfunction( S_LUASTATE, vector_add );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__sub" );
		lua_pushcfunction( S_LUASTATE, vector_sub );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__mul" );
		lua_pushcfunction( S_LUASTATE, vector_mul );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__div" );
		lua_pushcfunction( S_LUASTATE, vector_div );
		lua_rawset( S_LUASTATE, -3 );

		lua_pushliteral( S_LUASTATE, "__gc" );
		lua_pushcfunction( S_LUASTATE, vector_gc );
		lua_rawset( S_LUASTATE, -3 );
		//}

		//Entity
		luaL_Reg dynamicEntity[] =
		{
			{ "new", dynamicentity_new },

			{ "loadFromValues", dynamicentity_loadFromValues },
			{ "loadFromFile", dynamicentity_loadFromFile },
			{ "loadSceneNodeFromFile", dynamicentity_loadSceneNodeFromFile },
			{ "createSceneNodeFromPrimitive", dynamicentity_createSceneNodeFromPrimitive },
			{ "createRigidBodyFromPrimitive", dynamicentity_createRigidBodyFromPrimitive },

			{ "getPosition", dynamicentity_getPosition },
			{ "getRotation", dynamicentity_getRotation },
			{ "getDirection", dynamicentity_getDirection },

			{ "getConfig", dynamicentity_getConfig },
			{ "updateParameters", dynamicentity_updateParams },

			{ "applyImpulse", dynamicentity_applyImpulse },
			{ "applyTorqueImpulse", dynamicentity_applyTorqueImpulse },

			{ "applyForce", dynamicentity_applyForce },
			{ "applyTorque", dynamicentity_applyTorque },

			{ "warp", dynamicentity_warp },
			{ "reposition", dynamicentity_reposition },

			{ "setRotation", dynamicentity_setRotation },

			{ "collidesWith", dynamicentity_collidesWith },

			{ 0, 0 }
		};

		luaL_register( S_LUASTATE, DYNAMICENTITY, dynamicEntity );
		luaL_newmetatable( S_LUASTATE, DYNAMICENTITY );
		lua_pushliteral( S_LUASTATE, "__index" );
		lua_pushvalue( S_LUASTATE, -3 );
		lua_rawset( S_LUASTATE, -3 );

		lua_pop( S_LUASTATE, 3 );
	}

	//{ Helper methods

	template< class T >
	static T* toPointer( lua_State *pS, int index, String sTypeName )
	{

		 T* x = *( T** )luaL_checkudata( pS, index, sTypeName.c_str() );
		 if( !x )
			throw String( "Nullpointer! (" ) + sTypeName + " expected)";
		 return x;
	}

	template< class T >
	static void pushPointer( lua_State *pS, T* pT, String sTableName )
	{
		if( !pT )
			lua_pushnil( pS );
		else
		{
			T** ppT = ( T** )lua_newuserdata( pS, sizeof( T* ) );
			*ppT = pT;

			if ( sTableName != "" )
			{
				luaL_getmetatable( pS, sTableName.c_str() );
				lua_setmetatable( pS, -2 );
			}
		}
	}

	//}

	//{ Pulsar bindings

	static int pulsar_log( lua_State *pS )
	{
		if ( lua_isnumber( pS, 1 ) )
			S_PULSARENGINE->log( String( lua_tonumber( pS, 1 ) ) );
		else
			S_PULSARENGINE->log( lua_tostring( pS, 1 ) );

		return 0;
	}

	static int pulsar_getConfig( lua_State *pS )
	{
		LuaBinding::pushPointer<ConfigStorage>( pS, S_PULSARENGINE->getConfig(),
			CONFIGSTORAGE );

		return 1;
	}

	static int pulsar_getEventReceiver( lua_State *pS )
	{
		LuaBinding::pushPointer<PulsarEventReceiver>( pS,
			S_PULSARENGINE->getToolKit<PulsarEventReceiver>(),
			PULSAREVENTRECEIVER );
		return 1;
	}

	static int pulsar_getScriptToolKit( lua_State *pS )
	{
		LuaBinding::pushPointer<ScriptToolKit>( pS,
			S_PULSARENGINE->getToolKit<ScriptToolKit>(),
			SCRIPTTOOLKIT );
		return 1;
	}

	static int pulsar_getEntityToolKit( lua_State *pS )
	{
		LuaBinding::pushPointer<EntityToolKit>( pS,
			S_PULSARENGINE->getToolKit<EntityToolKit>(),
			ENTITYTOOLKIT );
		return 1;
	}

	static int pulsar_getConstraintToolKit( lua_State *pS )
	{
		LuaBinding::pushPointer<ConstraintToolKit>( pS,
			S_PULSARENGINE->getToolKit<ConstraintToolKit>(),
			CONSTRAINTTOOLKIT );
		return 1;
	}

	static int pulsar_getCameraToolKit( lua_State *pS )
	{
		LuaBinding::pushPointer<CameraToolKit>( pS,
			S_PULSARENGINE->getToolKit<CameraToolKit>(),
			CAMERATOOLKIT );
		return 1;
	}

	static int pulsar_run( lua_State *pS )
	{
		lua_pushboolean( pS, S_PULSARENGINE->run() );
		return 1;
	}

	static int pulsar_beginDrawing( lua_State *pS )
	{
		S_PULSARENGINE->beginDrawing();
		return 0;
	}

	static int pulsar_endDrawing( lua_State *pS )
	{
		S_PULSARENGINE->endDrawing();
		return 0;
	}

	static int pulsar_showConsoleWindow( lua_State* pS )
	{
		if( lua_gettop( pS ) > 0 )
			S_PULSARENGINE->showConsoleWindow( static_cast<bool>( lua_toboolean( pS, 1 ) ) );
		else
			S_PULSARENGINE->showConsoleWindow();

		return 0;
	}

	static int camtk_addCamera( lua_State *pS )
	{
		CameraToolKit *pCam = toPointer<CameraToolKit>( pS, 1, CAMERATOOLKIT );
		pCam->addCamera( luaL_checkint( pS, 2 ) );
		return 0;
	}

	static int camtk_setCameraPosition( lua_State *pS )
	{
		CameraToolKit *pCam = toPointer<CameraToolKit>( pS, 1, CAMERATOOLKIT );
		pCam->setCameraPosition( luaL_checkint( pS, 2 ),
			*LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) );

		return 0;
	}

	static int camtk_setCameraTarget( lua_State *pS )
	{
		CameraToolKit *pCam = toPointer<CameraToolKit>( pS, 1, CAMERATOOLKIT );
		pCam->setCameraTarget( luaL_checkint( pS, 2 ),
			*LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) );

		return 0;
	}

	static int camtk_setCameraUpVector( lua_State *pS )
	{
		CameraToolKit *pCam = toPointer<CameraToolKit>( pS, 1, CAMERATOOLKIT );

		pCam->setCameraUpVector( luaL_checkint( pS, 2 ),
			*LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) );

		return 0;
	}

	static int pulsar_setSimulationState( lua_State *pS )
	{
		S_PULSARENGINE->setSimulationState( (bool)lua_toboolean( pS, 1 ) );
		return 0;
	}

	static int pulsar_setGravity( lua_State *pS )
	{
		S_PULSARENGINE->setGravity( *LuaBinding::toPointer<Vector>( pS, 1, VECTOR ) );

		return 0;
	}

	//}

	//{ ScriptToolKit bindings

	static int stk_addTickScript( lua_State *pS )
	{
		ScriptToolKit *pStk = toPointer<ScriptToolKit>( pS, 1, SCRIPTTOOLKIT );
		int iID = pStk->addTickScript( luaL_checkstring( pS, 2 ) );

		lua_pushinteger( S_LUASTATE, iID );
		return 1;
	}

	static int stk_removeTickScript( lua_State *pS )
	{
		ScriptToolKit *pStk = toPointer<ScriptToolKit>( pS, 1, SCRIPTTOOLKIT );
		pStk->removeTickScript( luaL_checkinteger( pS, 2 ) );
		return 0;
	}

	//}

	//{ EntityToolKit bindings

	static int etk_addEntity( lua_State *pS )
	{
		EntityToolKit *pEtk = toPointer<EntityToolKit>( pS, 1, ENTITYTOOLKIT );
		if( lua_gettop( pS ) > 2 )
		{
			lua_pushinteger( pS,
				pEtk->addEntity( luaL_checkint( pS, 2 ), toPointer<Entity>( pS, 3, ENTITY) ) );
			return 1;
		}
		else
		{
			lua_pushinteger( pS,
				pEtk->addEntity( toPointer<Entity>( pS, 2, ENTITY) ) );
			return 1;
		}
	}

	static int etk_getEntity( lua_State *pS )
	{
		EntityToolKit *pEtk = toPointer<EntityToolKit>( pS, 1, ENTITYTOOLKIT );
		pushPointer<Entity>( pS, pEtk->getEntity( luaL_checkint( pS, 2 ) ),
			ENTITY );

		return 1;
	}

	static int etk_rayHitsEntity( lua_State *pS )
	{
		EntityToolKit *pEtk = toPointer<EntityToolKit>( pS, 1, ENTITYTOOLKIT );
		Entity *pE = LuaBinding::toPointer<Entity>( pS, 2, ENTITY );
		Vector v1 = *LuaBinding::toPointer<Vector>( pS, 3, VECTOR );
		Vector v2 = *LuaBinding::toPointer<Vector>( pS, 4, VECTOR );
		lua_pushboolean( pS, pEtk->rayHitsEntity( pE, v1, v2 ) );

		return 1;
	}

	static int etk_getEntityInRay( lua_State *pS )
	{
		EntityToolKit *pEtk = toPointer<EntityToolKit>( pS, 1, ENTITYTOOLKIT );
		Vector v1 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		Vector v2 = *LuaBinding::toPointer<Vector>( pS, 3, VECTOR );
		LuaBinding::pushPointer<Entity>( pS, pEtk->getEntityInRay( v1, v2 ), ENTITY );

		return 1;
	}

	static int etk_getDynamicEntityInRay( lua_State *pS )
	{
		EntityToolKit *pEtk = toPointer<EntityToolKit>( pS, 1, ENTITYTOOLKIT );
		Vector v1 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		Vector v2 = *LuaBinding::toPointer<Vector>( pS, 3, VECTOR );
		Entity *pE = pEtk->getDynamicEntityInRay( v1, v2 );
		if( pE )
			LuaBinding::pushPointer<Entity>( pS, pE, ENTITY );
		else
			lua_pushnil( pS );

		return 1;
	}

	//}

	//{ PulsarEventReceiver bindings

	static int evt_keyState( lua_State *pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushboolean( pS,
			pEvt->keyState(( irr::EKEY_CODE )luaL_checkinteger( pS, 2 ) ) );

		return 1;
	}

	static int evt_getMouseX( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushinteger( pS, pEvt->getMouseX() );
		return 1;
	}

	static int evt_getMouseY( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushinteger( pS, pEvt->getMouseY() );
		return 1;
	}

	static int evt_getMouseMoveX( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushinteger( pS, pEvt->getMouseMoveX() );
		return 1;
	}

	static int evt_getMouseMoveY( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushinteger( pS, pEvt->getMouseMoveY() );
		return 1;
	}

	static int evt_showMouse( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		if( lua_gettop( pS ) )
			pEvt->showMouse( static_cast<bool>( lua_toboolean( pS, 2 ) ) );
		else
			pEvt->showMouse();

		return 0;
	}

	static int evt_setMousePosition( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		pEvt->setMousePosition( luaL_checkinteger( pS, 2), luaL_checkinteger( pS, 3 ) );
		return 0;
	}

	static int evt_getMouseButtonState( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushboolean( pS, pEvt->getMouseButtonState( luaL_checkinteger( pS, 2 ) ) );
		return 1;
	}

	static int evt_getMouseWheelDelta( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		lua_pushinteger( pS, pEvt->getMouseWheelDelta() );
		return 1;
	}

	static int evt_lockMouse( lua_State* pS )
	{
		PulsarEventReceiver *pEvt = toPointer<PulsarEventReceiver>( pS, 1,
			PULSAREVENTRECEIVER );
		if( lua_gettop( pS ) > 1 )
			pEvt->lockMouse( lua_toboolean( pS, 2 ) );
		else
			pEvt->lockMouse();
		return 0;
	}

	//}

	//{ ConfigStorage bindings

	static int confstore_new( lua_State *pS)
	{
		ConfigStorage *pConf = new ConfigStorage();
		pushPointer<ConfigStorage>( pS, pConf, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_parseXMLFile( lua_State *pS )
	{
		ConfigStorage *pConf = toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		pConf->parseXMLFile( luaL_checkstring( pS, 2 ),
			lua_gettop( pS ) > 2 ? luaL_checkstring( pS, 3 ) : "" );

		pushPointer<ConfigStorage>( pS, pConf, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_setBool( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		pC->set<bool>( luaL_checkstring( pS, 2 ), (bool)lua_toboolean( pS, 3 ) );

		pushPointer<ConfigStorage>( pS, pC, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_setInt( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		pC->set<int>( luaL_checkstring( pS, 2 ), luaL_checkinteger( pS, 3 ) );

		pushPointer<ConfigStorage>( pS, pC, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_setFloat( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		pC->set<float>( luaL_checkstring( pS, 2 ), luaL_checknumber( pS, 3 ) );

		pushPointer<ConfigStorage>( pS, pC, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_setString( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE);
		pC->set<String>( luaL_checkstring( pS, 2 ), luaL_checkstring( pS, 3 ) );

		pushPointer<ConfigStorage>( pS, pC, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_setVector( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );

		pC->set<Vector>( luaL_checkstring( pS, 2 ), *LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) );

		pushPointer<ConfigStorage>( pS, pC, CONFIGSTORAGE );

		return 1;
	}

	static int confstore_getBool( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		lua_pushboolean( pS, pC->get<bool>( luaL_checkstring( pS, 2 ) ) );

		return 1;
	}

	static int confstore_getInt( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		lua_pushinteger( pS, pC->get<int>( luaL_checkstring( pS, 2 ) ) );

		return 1;
	}

	static int confstore_getFloat( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		lua_pushnumber( pS, pC->get<float>( luaL_checkstring( pS, 2 ) ) );

		return 1;
	}

	static int confstore_getString( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		lua_pushstring( pS, pC->get<String>( luaL_checkstring( pS, 2 ) ).c_str() );

		return 1;
	}

	static int confstore_getVector( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>(
			pS, 1, CONFIGSTORAGE );

		Vector *pV = new Vector(
			pC->get<Vector>( luaL_checkstring( pS, 2 ) ) );
		LuaBinding::pushPointer<Vector>( pS, pV, VECTOR );

		return 1;
	}

	static int confstore_deleteValue( lua_State *pS )
	{
		ConfigStorage *pC = LuaBinding::toPointer<ConfigStorage>( pS, 1, CONFIGSTORAGE );
		pC->deleteValue( luaL_checkstring( pS, 2 ) );
		return 0;
	}

	//}

	//{ Vector

	static int vector_new( lua_State *pS )
	{
		if( lua_gettop( pS ) == 3 )
			LuaBinding::pushPointer<Vector>( pS,
				new Vector( luaL_checknumber( pS, 1 ), luaL_checknumber( pS, 2 ), luaL_checknumber( pS, 3 ) ), VECTOR );
		else
			LuaBinding::pushPointer<Vector>( pS,
				new Vector( luaL_checknumber( pS, 2 ), luaL_checknumber( pS, 3 ), luaL_checknumber( pS, 4 ) ), VECTOR );

		return 1;
	}

	static int vector_gc( lua_State* pS )
	{
		try
		{
			Vector* pV = LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
			delete pV;
		}
		catch( String &s )
		{
			S_PULSARENGINE->log( s );
		}
		return 0;
	}

	static int vector_set( lua_State *pS )
	{
		Vector* pV = LuaBinding::toPointer<Vector>( pS, 1, VECTOR );

		pV->set( luaL_checknumber( pS, 2 ), luaL_checknumber( pS, 3 ), luaL_checknumber( pS, 4 ) );

		return 0;
	}

	static int vector_zero( lua_State *pS )
	{
		LuaBinding::pushPointer<Vector>( pS, new Vector( 0.0f ), VECTOR );
		return 1;
	}

	static int vector_getX( lua_State *pS )
	{
		Vector* pV = LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		lua_pushnumber( pS, pV->X );
		return 1;
	}

	static int vector_getY( lua_State *pS )
	{
		Vector* pV = LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		lua_pushnumber( pS, pV->Y );
		return 1;
	}

	static int vector_getZ( lua_State *pS )
	{
		Vector* pV = LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		lua_pushnumber( pS, pV->Z );
		return 1;
	}

	static int vector_add( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		LuaBinding::pushPointer<Vector>( pS, new Vector( pV1 + pV2 ), VECTOR );
		return 1;
	}

	static int vector_sub( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		LuaBinding::pushPointer<Vector>( pS, new Vector( pV1 - pV2 ), VECTOR );
		return 1;
	}

	static int vector_mul( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );

		if( !lua_isnumber( pS, 2 ) )
		{
			Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
			LuaBinding::pushPointer<Vector>( pS, new Vector( pV1 * pV2 ), VECTOR );
		}
		else
		{
			LuaBinding::pushPointer<Vector>( pS, new Vector( pV1 * luaL_checknumber( pS, 2 ) ), VECTOR );
		}
		return 1;
	}

	static int vector_div( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		LuaBinding::pushPointer<Vector>( pS, new Vector( pV1 / pV2 ), VECTOR );
		return 1;
	}

	static int vector_dot( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		lua_pushnumber( pS, pV1.dotProduct( pV2 ) );
		return 1;
	}

	static int vector_cross( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		Vector pV2 = *LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		LuaBinding::pushPointer<Vector>( pS, new Vector( pV1.crossProduct( pV2 ) ), VECTOR );
		return 1;
	}

	static int vector_normalize( lua_State *pS )
	{
		Vector pV1 = *LuaBinding::toPointer<Vector>( pS, 1, VECTOR );
		LuaBinding::pushPointer<Vector>( pS, new Vector( pV1.normalize() ), VECTOR );
		return 1;
	}

	//}

	//{ DynamicEntity Bindings

	static int dynamicentity_new( lua_State *pS )
	{
		unsigned int iID = lua_gettop( pS ) > 0 ?
			luaL_checknumber( pS, 1 ) : 0;
		float fMass = lua_gettop( pS ) > 1 ?
			luaL_checknumber( pS, 2 ) : 0;
		Vector *pos = lua_gettop( pS ) > 2 ?
			toPointer<Vector>( pS, 3, VECTOR ) : new Vector();
		Vector *rot = lua_gettop( pS ) > 3 ?
			toPointer<Vector>( pS, 4, VECTOR ) : new Vector();

		Entity *pE = new DynamicEntity( iID, fMass, *pos, *rot );

		pushPointer( pS, pE, DYNAMICENTITY );
		return 1;
	}

	static int dynamicentity_loadFromValues( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );
		ConfigStorage *pConf = toPointer<ConfigStorage>( pS, 2, CONFIGSTORAGE );

		pE->loadFromValues( pConf );

		return 0;
	}

	static int dynamicentity_loadFromFile( lua_State *pS )
	{
		DynamicEntity* pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		String sNodeName = lua_gettop( pS ) > 2 ? lua_tostring( pS, 3 ) : "";

		pE->loadFromFile( lua_tostring( pS, 2 ), sNodeName );

		return 0;
	}

	static int dynamicentity_loadSceneNodeFromFile( lua_State* pS )
	{
		try
		{
			DynamicEntity* pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
				DYNAMICENTITY );
			String sFileName = luaL_checkstring( pS, 2 );
			pE->loadSceneNodeFromFile( sFileName );
		}
		catch( String &s )
		{
			S_PULSARENGINE->log( s );
		}
		return 0;
	}

	static int dynamicentity_createSceneNodeFromPrimitive( lua_State* pS )
	{
		try
		{
			DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
				DYNAMICENTITY );
			Entity::E_PULSARENTITYPRIMITIVE prim =
				static_cast<Entity::E_PULSARENTITYPRIMITIVE>(
				luaL_checkinteger( pS, 2 ) );
			Vector size = *LuaBinding::toPointer<Vector>( pS, 3, VECTOR );
			pE->createSceneNodeFromPrimitive( prim, size );
		}
		catch( String &s )
		{
			S_PULSARENGINE->log( s );
		}

		return 0;
	}

	static int dynamicentity_createRigidBodyFromPrimitive( lua_State* pS )
	{
		try
		{
			DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
				DYNAMICENTITY );
			Entity::E_PULSARENTITYPRIMITIVE prim =
				static_cast<Entity::E_PULSARENTITYPRIMITIVE>( luaL_checkinteger( pS, 2 ) );
			Vector size = *LuaBinding::toPointer<Vector>( pS, 3, VECTOR );
			pE->createRigidBodyFromPrimitive( prim, size );
		}
		catch( String &s )
		{
			S_PULSARENGINE->log( s );
		}

		return 0;
	}

	static int dynamicentity_getDirection( lua_State *pS )
	{
		DynamicEntity* pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *dir = ( lua_gettop( pS ) > 1 ) ?
			LuaBinding::toPointer<Vector>( pS, 2, VECTOR ) : new Vector();

		LuaBinding::pushPointer<Vector>( pS,
			new Vector( pE->getDirection( *dir ) ), VECTOR );

		return 1;
	}

	static int dynamicentity_getConfig( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		LuaBinding::pushPointer<ConfigStorage>( pS, pE->getConfig(), CONFIGSTORAGE );

		return 1;
	}

	static int dynamicentity_updateParams( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );
		pE->updateParameters();
		return 0;
	}

	static int dynamicentity_applyImpulse( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *direction = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		Vector *offset = lua_gettop( pS ) > 2 ?
			LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) : new Vector();

		pE->applyImpulse( *direction, *offset );

		return 0;
	}

	static int dynamicentity_applyTorqueImpulse( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *direction = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		pE->applyTorqueImpulse( *direction );

		return 0;
	}

	static int dynamicentity_applyForce( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *direction = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		Vector *offset = lua_gettop( pS ) > 2 ?
			LuaBinding::toPointer<Vector>( pS, 3, VECTOR ) : new Vector();

		pE->applyForce( *direction, *offset );

		return 0;
	}

	static int dynamicentity_applyTorque( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *direction = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );
		pE->applyTorque( *direction );

		return 0;
	}

	static int dynamicentity_warp( lua_State* pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *pos = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		pE->warp( *pos );

		return 0;
	}

	static int dynamicentity_reposition( lua_State* pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		Vector *pos = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		pE->reposition( *pos );

		return 0;
	}

	static int dynamicentity_setRotation( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );
		Vector *rot = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		pE->setRotation( *rot );

		return 0;
	}

	static int dynamicentity_setPosition( lua_State *pS )
	{
		Entity *pE = LuaBinding::toPointer<Entity>( pS, 1, ENTITY );
		Vector *pos = LuaBinding::toPointer<Vector>( pS, 2, VECTOR );

		pE->setPosition( *pos );

		return 0;
	}

	static int dynamicentity_getRotation( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		LuaBinding::pushPointer<Vector>( pS, new Vector( pE->getRotation() ), VECTOR );

		return 1;
	}

	static int dynamicentity_getPosition( lua_State *pS )
	{
		DynamicEntity *pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );

		LuaBinding::pushPointer<Vector>( pS, new Vector( pE->getPosition() ), VECTOR );

		return 1;
	}

	static int dynamicentity_collidesWith( lua_State *pS )
	{
		DynamicEntity* pE = LuaBinding::toPointer<DynamicEntity>( pS, 1,
			DYNAMICENTITY );
		DynamicEntity* pE2 = LuaBinding::toPointer<DynamicEntity>( pS, 2,
			DYNAMICENTITY );

		bool col = pE->collidesWith( pE2 );

		lua_pushboolean( pS, col );

		return 1;
	}

	//}

private:

	static PulsarEngine *s_pEngine;
	static lua_State *s_pState;
	static std::vector<String> s_vCommands;
};

}

#endif // __luabinding__
