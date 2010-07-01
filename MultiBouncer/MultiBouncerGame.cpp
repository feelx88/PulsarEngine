#include "MultiBouncerGame.h"

#include "Irrlicht_using.h"

using namespace pulsar;

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
	CameraToolKit *cam =
		dynamic_cast<CameraToolKit*>( m_Engine->getToolKit( "Camera" ) );
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

	ConfigStorage *p = new ConfigStorage();
	p->parseXMLFile( "bouncers/StandardBouncer.xml" );
	delete p;

	m_Engine->setSimulationState( true );

	while( m_Engine->run() )
	{
		m_Engine->beginDrawing();

		m_Engine->endDrawing();
	}

	return EXIT_SUCCESS;
}