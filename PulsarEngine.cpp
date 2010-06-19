#include "PulsarEngine.h"

using namespace pulsar;

//use irrlicht namespaces
#include "Irrlicht_using.h"

PulsarEngine *PulsarEngine::s_pInstance = 0;

PulsarEngine *S_PULSARENGINE = 0;
lua_State *S_LUASTATE = 0;

std::vector<String> LuaBinding::s_vCommands;


PulsarEngine *PulsarEngine::getInstance()
{
	if( !s_pInstance )
		s_pInstance = new PulsarEngine();

	return s_pInstance;

}

PulsarEngine::PulsarEngine() : IObject(), m_bSimulate( false )
{
	setInfo( P_PULSARENGINE, P_PULSARENGINE, 1 );

	//intialise the value factory
	registerTypes();
}

PulsarEngine::~PulsarEngine()
{
	m_pDevice->drop();
	delete m_pBulletWorld;

	for( std::map<String, IToolKit*>::iterator x = m_mToolKits.begin();
		x != m_mToolKits.end(); x++ )
		delete x->second;
	m_mToolKits.clear();

	delete m_pMainConfiguration;
}

void PulsarEngine::init( String sConfigFileName )
{
	//Load configuration
	loadConfig( sConfigFileName );

	//initialise everything
	initIrrlicht();
	initConsole();
	initLua();
	initBullet();
	initOpenAL();

	//initialize standard ToolKits
	initStandardToolKits();
}

IToolKit *PulsarEngine::getToolKit( String sName )
{
	std::map<String, IToolKit*>::iterator x = this->m_mToolKits.find( sName );
	if( x != this->m_mToolKits.end() )
		return x->second;
	else
		return 0;
}

void PulsarEngine::loadConfig( String sConfigFileName )
{
	m_pMainConfiguration = new ConfigStorage();

	m_pMainConfiguration->parseXMLFile( sConfigFileName );
	m_pMainConfiguration->setAlwaysGetRecursive();
	//m_pMainConfiguration->saveToFile( sConfigFileName );
}

void PulsarEngine::initIrrlicht()
{
	SIrrlichtCreationParameters parameters;
	parameters.AntiAlias = m_pMainConfiguration->get<int>( "AntiAlias", 0 );
	parameters.Bits = m_pMainConfiguration->get<int>( "ColorDepth", 16 );
	parameters.DeviceType = EIDT_BEST;
	parameters.Doublebuffer = m_pMainConfiguration->get<bool>( "DoubleBuffer", true );

	String sDriver = m_pMainConfiguration->get<String>( "Driver", "Software" );

	if ( sDriver == "Software" )
		parameters.DriverType = EDT_BURNINGSVIDEO;
	else
		parameters.DriverType = EDT_OPENGL;

	parameters.Fullscreen = m_pMainConfiguration->get<bool>( "Fullscreen", false );

	parameters.Stencilbuffer = m_pMainConfiguration->get<bool>( "StencilBuffer", false );

	parameters.Vsync = m_pMainConfiguration->get<bool>( "VSync", false );

	parameters.WindowSize = dimension2di(
		m_pMainConfiguration->get<int>( "ScreenWidth", 640 ),
		m_pMainConfiguration->get<int>( "ScreenHeight", 480 ) );

	m_iScreenWidth = parameters.WindowSize.Width;
	m_iScreenHeight = parameters.WindowSize.Height;

	PulsarEventReceiver *pEvt = new PulsarEventReceiver();
	parameters.EventReceiver = pEvt;

	m_pDevice = createDeviceEx( parameters );

	if ( !m_pDevice )
	{
		throw( "Irrlicht could not be initialised!" );
		exit( EXIT_FAILURE );
	}

	m_pVideoDriver = m_pDevice->getVideoDriver();

	m_pSceneManager = m_pDevice->getSceneManager();
	m_pGUI = m_pDevice->getGUIEnvironment();
	m_pTimer = m_pDevice->getTimer();
	m_pTimer->start();

	//add the event receiver as ToolKit
	addToolKit( "EventReceiver", pEvt );

	//Initialize the irrlicht toolkits
	EntityToolKit *pEntTK = new EntityToolKit();
	addToolKit( "Entity", pEntTK );

	ConstraintToolKit *pConstTK = new ConstraintToolKit();
	addToolKit( "Constraint", pConstTK );

	CameraToolKit *pCamTK = new CameraToolKit();
	addToolKit( "Camera", pCamTK );
}

void PulsarEngine::initConsole()
{
	int iWidth = m_pMainConfiguration->get<int>( "ConsoleWidth", 300 );
	int iHeight = m_pMainConfiguration->get<int>( "ConsoleHeight", 200 );
	String sName = m_pMainConfiguration->get<String>( "ConsoleTitle", "Console" );
	m_pConsoleWindow = m_pGUI->addWindow( rect<s32>( 0, 0, iWidth, iHeight ), false, stringw( sName ).c_str() );
	m_pConsoleOutput = m_pGUI->addListBox( rect<s32>( 5, 25, iWidth - 5, iHeight - 30 ), m_pConsoleWindow, -1, true );
	m_pConsoleInput = m_pGUI->addEditBox( L"", rect<s32>( 5, iHeight - 25, iWidth - 50, iHeight - 5 ), true, m_pConsoleWindow );
	m_pConsoleSendButton = m_pGUI->addButton( rect<s32>( iWidth - 45, iHeight - 25, iWidth - 5, iHeight - 5 ),
	                       m_pConsoleWindow, -1, L"OK" );

	m_pConsoleOutput->setAutoScrollEnabled( true );
	m_pConsoleWindow->getCloseButton()->setVisible( false );
}

void PulsarEngine::initLua()
{
	IToolKit *toolkit = new ScriptToolKit();

	addToolKit( "Script", toolkit );
}

void PulsarEngine::initBullet()
{
	//copied from BasicDemo.cpp
	///collision configuration contains default setup for memory, collision setup
	btCollisionConfiguration *pCollisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher *pDispatcher = new btCollisionDispatcher( pCollisionConfiguration );

	btBroadphaseInterface *pBroadphase = new btDbvtBroadphase();

	//Needed for btGhostObjects to work
	pBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(
		new btGhostPairCallback() );

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver *pSolver = new btSequentialImpulseConstraintSolver();

	m_pBulletWorld = new btDiscreteDynamicsWorld( pDispatcher, pBroadphase, pSolver, pCollisionConfiguration );

	m_pBulletWorld->addAction( (btActionInterface*)this );
}

void PulsarEngine::initOpenAL()
{
}

void PulsarEngine::initStandardToolKits()
{
	getToolKit( "EventReceiver" )->init( Value() );
	getToolKit( "Script" )->init( Value() );
	getToolKit( "Entity" )->init( Value() );
	getToolKit( "Constraint" )->init( Value() );
	getToolKit( "Camera" )->init( Value() );

	//Load Pulsar definitions for lua
	dynamic_cast<ScriptToolKit*>( getToolKit( "Script" ) )
		->executeFile( "pulsar_defs.lua" );
}

void PulsarEngine::registerTypes()
{
	Value::registerType<Value*>( "ValuePtr", 0 );

	//Register types with converters
	Value::registerType<int>( P_INTEGER, new StandardTypes::IntConverter() );
	Value::registerType<float>( P_FLOAT, new StandardTypes::FloatConverter() );
	Value::registerType<bool>( P_BOOL, new StandardTypes::BoolConverter() );
	Value::registerType<String>( P_STRING, new StandardTypes::StringConverter() );
	Value::registerType<Vector>( P_VECTOR, new StandardTypes::VectorConverter() );

	Value::registerType<ConfigStorage*>( "ConfigStorage", 0 );

	//Register Standard Entitys
	Value::registerType<GraphicalEntity>( "GraphicalEntity",
		new StandardTypes::EntityTypesConverter<GraphicalEntity>() );
	Value::registerType<DynamicEntity>( "DynamicEntity",
		new StandardTypes::EntityTypesConverter<DynamicEntity>() );
	Value::registerType<GhostSensorEntity>( "GhostSensorEntity",
		new StandardTypes::EntityTypesConverter<GhostSensorEntity>() );

}

void PulsarEngine::setGravity( irr::core::vector3df direction )
{
	m_pBulletWorld->setGravity( btVector3( direction.X, direction.Y, direction.Z ) );
}

bool PulsarEngine::run()
{
	if( !m_iStartTime || !m_GameLoopTime )
	{
		if( m_pTimer )
			m_iStartTime = m_GameLoopTime = m_pTimer->getRealTime();
	}

	if ( m_pDevice )
		return m_pDevice->run();
	else
		return false;
}

void PulsarEngine::beginDrawing()
{
	m_pVideoDriver->beginScene();
	m_pSceneManager->drawAll();
	m_pGUI->drawAll();

	for( std::map<String, IToolKit*>::iterator x = m_mToolKits.begin();
		x != m_mToolKits.end(); x++ )
		x->second->update();
}

void PulsarEngine::endDrawing()
{
	m_pVideoDriver->endScene();

	unsigned int curTime = m_pTimer->getRealTime();

	if ( m_bSimulate )
		m_pBulletWorld->stepSimulation( (float)( curTime - m_iStartTime ) / 1000.0f, 15 );

	m_iStartTime = curTime;

	int dt = m_pTimer->getRealTime() - m_GameLoopTime;
	while( dt >= 32 )
	{
		dt -= 32;
		m_GameLoopTime += 32;
	}

	m_iOldMouseX = m_iMouseX;
	m_iOldMouseY = m_iMouseY;
}

void PulsarEngine::showConsoleWindow( bool bVisible )
{
	m_pConsoleWindow->setVisible( bVisible );
}

void PulsarEngine::addToolKit( String sName, IToolKit *pToolKit )
{
	this->m_mToolKits.insert( std::make_pair( sName, pToolKit ) );
}

void PulsarEngine::log( Value sValue )
{
	m_pConsoleOutput->addItem( stringw( sValue.toString() ).c_str() );
	m_pDevice->getLogger()->log( sValue.toString().c_str() );
}

void PulsarEngine::updateAction( btCollisionWorld *collisionWorld, btScalar deltaTimeStep )
{
	for( std::map<String, IToolKit*>::iterator x = m_mToolKits.begin();
		x != m_mToolKits.end(); x++ )
		x->second->tickUpdate();

	/*for ( int x = 0; x < m_pBulletWorld->getDispatcher()->getNumManifolds(); x++)
	{
		btPersistentManifold* pManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal( x );
		btCollisionObject* pBody0 = static_cast<btCollisionObject*>( pManifold->getBody0() );
		btCollisionObject* pBody1 = static_cast<btCollisionObject*>( pManifold->getBody1() );

		if( !pBody0 || !pBody1 )
			continue;

		for ( int y = 0;  y < pManifold->getNumContacts(); y++)
		{
			btManifoldPoint& pt = pManifold->getContactPoint( y );
			static_cast<ContactPointStorage*>( pBody0->getUserPointer() )->addContactPoint( pBody1,
				Vector( pt.getPositionWorldOnA().getX(), pt.getPositionWorldOnA().getY(), pt.getPositionWorldOnA().getZ() ),
				Vector( pt.getPositionWorldOnB().getX(), pt.getPositionWorldOnB().getY(), pt.getPositionWorldOnB().getZ() ) );
			static_cast<ContactPointStorage*>( pBody1->getUserPointer() )->addContactPoint( pBody0,
				Vector( pt.getPositionWorldOnA().getX(), pt.getPositionWorldOnA().getY(), pt.getPositionWorldOnA().getZ() ),
				Vector( pt.getPositionWorldOnA().getX(), pt.getPositionWorldOnA().getY(), pt.getPositionWorldOnA().getZ() ) );
		}
	}*/
}
