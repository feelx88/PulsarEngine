#include "MultiBouncerGame.h"

#include "../PulsarEngine/Irrlicht_using.h"

using namespace pulsar;

enum
{
	ID_CAMERA_PRIMARY = 1
};

MultiBouncerGame::MultiBouncerGame() : m_Engine( 0 )
{
	init();
	initGUI();
}

MultiBouncerGame::~MultiBouncerGame()
{
	delete m_Engine;
}

void MultiBouncerGame::init()
{
	m_Engine = PulsarEngine::getInstance();
	m_Engine->init( "config.xml" );

	//Add a light, complicated version...
	m_Engine->getIrrlichtDevice()->getSceneManager()->
		addLightSceneNode( 0, Vector( 0, 100, 0 ) );

	//Add a camera
	CameraToolKit *cam = m_Engine->getToolKit<CameraToolKit>( "Camera" );
	cam->addCamera( ID_CAMERA_PRIMARY );
	cam->setCameraPosition( ID_CAMERA_PRIMARY, Vector( 0, 10, -50 ) );
	cam->setCameraTarget( ID_CAMERA_PRIMARY, Vector( 0, 0, 0 ) );
}

void MultiBouncerGame::initGUI()
{
	IGUIEnvironment *gui = m_Engine->getIrrlichtDevice()->getGUIEnvironment();
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	ConfigStorage *input = m_Engine->getConfig()->getSubSection( "Input" );

	ConfigStorage *p = new ConfigStorage( true );
	//p->parseXMLFile( "bouncers/StandardBouncer.xml" );
	p->setAlwaysGetRecursive();

	PulsarEventReceiver *evt =
		m_Engine->getToolKit<PulsarEventReceiver>( "EventReceiver" );
		
	DynamicEntity *lol = new DynamicEntity( 10.f );
	lol->loadFromFile( "bouncers/StandardBouncer.xml" );
	std::cout << lol->getConfig()->countVars( "Mass" ) << std::endl;

	m_Engine->setSimulationState( true );

	while( m_Engine->run() )
	{
		m_Engine->beginDrawing();

		m_Engine->endDrawing();
	}

	return EXIT_SUCCESS;
}
