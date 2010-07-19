#include "MultiBouncerGame.h"

#include "../PulsarEngine/Irrlicht_using.h"

#include <boost/filesystem.hpp>

using namespace pulsar;
using namespace boost;

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
	//Check for folders
	if( !filesystem::exists( "bouncers" ) )
	{
		std::cout << "Directory bouncers does not exist!" << std::endl;
		exit( EXIT_FAILURE );
	}
	if( !filesystem::exists( "maps" ) )
	{
		std::cout << "Directory maps does not exist!" << std::endl;
		exit( EXIT_FAILURE );
	}
	
	//Read bouncer and map file names
	filesystem::directory_iterator end;
	for( filesystem::directory_iterator x( "bouncers" ); x != end; x++ )
		m_BouncerFiles.push_back( x->string().c_str() );
	for( filesystem::directory_iterator x( "maps" ); x != end; x++ )
		m_BouncerFiles.push_back( x->string().c_str() );
	
	//Get gui environment
	IGUIEnvironment *gui = m_Engine->getIrrlichtDevice()->getGUIEnvironment();
	
	m_MainMenu = gui->addWindow( 
		recti( 0, 0, m_Engine->getScreenWidth(), m_Engine->getScreenHeight() ),
		false, L"MainMenu" );
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	ConfigStorage *input = m_Engine->getConfig()->getSubSection( "Input" );

	ConfigStorage *p = new ConfigStorage( true );
	p->parseXMLFile( "maps/testmap.xml" );
	p->setAlwaysGetRecursive();

	PulsarEventReceiver *evt =
		m_Engine->getToolKit<PulsarEventReceiver>( "EventReceiver" );

	m_Engine->setSimulationState( true );

	while( m_Engine->run() )
	{
		m_Engine->beginDrawing();

		m_Engine->endDrawing();
	}

	return EXIT_SUCCESS;
}
