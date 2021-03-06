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

#ifndef __pulsarengine__
#define __pulsarengine__

#include "IObject.h"

//Engine includes
#include "ValueFactory.h"
#include "StandardConverters.h"
#include "ConfigStorage.h"

#include "Entities/Entity.h"
#include "Entities/GraphicalEntity.h"
#include "Entities/DynamicEntity.h"
#include "Entities/SensorEntity.h"
#include "Entities/GhostSensorEntity.h"

#include "StandardCallbacks.h"

#include "ToolKits/IToolKit.h"
#include "ToolKits/PulsarEventReceiver.h"
#include "ToolKits/ScriptToolKit.h"
#include "ToolKits/EntityToolKit.h"
#include "ToolKits/ConstraintToolKit.h"
#include "ToolKits/CameraToolKit.h"

/** 
 * @namespace pulsar
 * @brief Main namespace.
 * 
 * Everything related to the Engine is in this namespace.
 */
namespace pulsar
{

/**
 * @class PulsarEngine
 * @brief Main class.
 * 
 * This class manages everything related to the engine.
 */
class PulsarEngine : public IObject, public btActionInterface
{

public:
	
	static PulsarEngine *getInstance();

	~PulsarEngine();

	void init( String sConfigFileName );

	//IEventReceiver OnEvent()
	bool OnEvent( const irr::SEvent &evt );

	void setGravity( Vector direction );

	irr::IrrlichtDevice *getIrrlichtDevice()
	{
		return m_pDevice;
	}

	btDynamicsWorld *getBulletWorld()
	{
		return m_pBulletWorld;
	}

	bool run();
	void beginDrawing();
	void endDrawing();

	int getScreenWidth()
	{
		return m_iScreenWidth;
	}

	int getScreenHeight()
	{
		return m_iScreenHeight;
	}

	void showConsoleWindow( bool = true );
	irr::gui::IGUIWindow *getConsoleWindow()
	{
		return m_pConsoleWindow;
	}

	void setSimulationState( bool bSimulate )
	{
		if ( m_bSimulate != bSimulate )
			log( bSimulate ? String( "Simulation started!" )
				: String( "Simulation stopped!" ) );

		m_bSimulate = bSimulate;
	}

	void addToolKit( IToolKit *pToolKit );

	template <class T>
	T *getToolKit()
	{
		return dynamic_cast<T*>( m_mToolKits[typeid( T ).name()] );
	}

	void log( Value sValue );

	ConfigStorage *getConfig()
	{
		return m_pMainConfiguration;
	}

	static btVector3 convert( Vector vec )
	{
		return Entity::convert( vec );
	}

	static Vector convert( btVector3 vec )
	{
		return Entity::convert( vec );
	}

	void updateAction( btCollisionWorld *collisionWorld, btScalar deltaTimeStep );

	//unused
	void debugDraw( btIDebugDraw* ){};

protected:

	PulsarEngine();

	void loadConfig( String sConfigFileName );

	static PulsarEngine *s_pInstance;

	void initIrrlicht();
	void initConsole();
	void initLua();
	void initBullet();
	void initOpenAL();
	void initStandardToolKits();

	void registerTypes();

	//Irrlicht members
	irr::IrrlichtDevice *m_pDevice;
	irr::video::IVideoDriver *m_pVideoDriver;
	irr::scene::ISceneManager *m_pSceneManager;
	irr::gui::IGUIEnvironment *m_pGUI;
	irr::ITimer *m_pTimer;

	PulsarEventReceiver *mEventReceiver;

	int m_iScreenWidth, m_iScreenHeight;

	bool m_bKeyStates[irr::KEY_KEY_CODES_COUNT];
	int m_iMouseX, m_iMouseY, m_iOldMouseX, m_iOldMouseY, m_iMouseMoveX, m_iMouseMoveY;
	int m_iMouseWheelDelta;
	int m_iMouseButtonStates;
	bool m_bMouseLocked;

	//Console
	irr::gui::IGUIWindow *m_pConsoleWindow;
	irr::gui::IGUIListBox *m_pConsoleOutput;
	irr::gui::IGUIEditBox *m_pConsoleInput;
	irr::gui::IGUIButton *m_pConsoleSendButton;
	unsigned int m_iCurOutputLine;

	//bullet members
	btDiscreteDynamicsWorld *m_pBulletWorld;
	bool m_bSimulate;

	//needed to let Irrlicht Calculate it's fps
	unsigned int m_iStartTime;
	unsigned int m_GameLoopTime;

	ConfigStorage *m_pMainConfiguration;

	std::map<String, IToolKit*> m_mToolKits;
};

}

#include "LuaBinding.h"

#endif // __pulsarengine__
