#include "MultiBouncerGame.h"

using namespace pulsar;

MultiBouncerGame::MultiBouncerGame() : m_Engine( 0 )
{
	init();
}

MultiBouncerGame::~MultiBouncerGame()
{
	delete m_Engine;
}

void MultiBouncerGame::init()
{
	m_Engine = PulsarEngine::getInstance();
	m_Engine->init( "config.xml" );

	m_Engine->getIrrlichtDevice()->getSceneManager()->addLightSceneNode( 0, Vector( 0, 100, 0 ) );

	CameraToolKit *pCam = dynamic_cast<CameraToolKit*>( m_Engine->getToolKit( "Camera" ) );
	pCam->addCamera( 1 );
	pCam->setCameraPosition( 1, Vector( 0, 10, -50 ) );
	pCam->setCameraTarget( 1, Vector( 0, 0, 0 ) );
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	m_Engine->setSimulationState( true );

	while( m_Engine->run() )
	{
		m_Engine->beginDrawing();
		m_Engine->endDrawing();
	}

	return EXIT_SUCCESS;
}
