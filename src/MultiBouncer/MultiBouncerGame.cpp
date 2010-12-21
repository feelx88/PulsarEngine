#include "MultiBouncerGame.h"

#include "../PulsarEngine/Irrlicht_using.h"

using namespace pulsar;
using namespace boost;

enum
{
	ID_CAMERA_PRIMARY = 1,
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
	
	mWinWidth = m_Engine->getScreenWidth();
	mWindHeight = m_Engine->getScreenHeight();

	//Add a light, complicated version...
	m_Engine->getIrrlichtDevice()->getSceneManager()->
		addLightSceneNode( 0, Vector( 0, 100, 0 ) );

	//Add a camera
	CameraToolKit *cam = m_Engine->getToolKit<CameraToolKit>();
	cam->addCamera( ID_CAMERA_PRIMARY );
	cam->setCameraPosition( ID_CAMERA_PRIMARY, Vector( 0, 10, -50 ) );
	cam->setCameraTarget( ID_CAMERA_PRIMARY, Vector( 0, 0, 0 ) );
}

void MultiBouncerGame::initGUI()
{	
	//Clear file names
	m_MapFiles.clear();
	
	if( !filesystem::exists( "maps" ) )
	{
		std::cout << "Directory maps does not exist!" << std::endl;
		exit( EXIT_FAILURE );
	}
	
	//Read bouncer and map file names
	filesystem::directory_iterator end;
	for( filesystem::directory_iterator x( "maps" ); x != end; x++ )
		m_MapFiles.push_back( x->path() );
	
	for( unsigned int x = 0; x < m_MapFiles.size(); x++ )
	{
		ConfigStorage *conf = new ConfigStorage();
		conf->parseXMLFile( m_MapFiles.at( x ).string().c_str(), "Data" );
		m_MapData.push_back( conf );
	}
	
	//Get gui environment
	IGUIEnvironment *gui = m_Engine->getIrrlichtDevice()->getGUIEnvironment();
	
	//some defines for easier size definitions
#define W mWinWidth
#define H mWindHeight
#define W2 (W/2)
#define H2 (H/2)
#define W4 (W/4)
#define H4 (H/4)
	
	//Add main menu window
	m_MainMenu = gui->addWindow( 
		recti( 20, 20, W - 20, H - 20 ),
		false, L"MainMenu" );
	m_MainMenu->getCloseButton()->setVisible( false );
	m_MainMenu->setDraggable( false );
	m_MainMenu->setDrawTitlebar( false );
	
	//Add the bouncer list
	m_MapList = gui->addListBox( recti( W4, H4, 3 * W4, 3 * H4 ), 
		m_MainMenu, -1, true );
	for( unsigned int x = 0; x < m_MapFiles.size(); x++ )
		m_MapList->addItem( stringw( 
		m_MapData.at( x )->get<String>( "MapName", "No Name!" ) ).c_str() );
	
	m_OkButton = gui->addButton( recti( W4, 3 * H4 + 10, W2 - 5, 3 * H4 + 60 ), 
		m_MainMenu, -1, L"Start" );
	
	m_PlayerCounter = gui->addSpinBox( L"Spieleranzahl:", 
		recti( W2 + 4, 3 * H4 + 10, 3 * W4, 3 * H4 + 60 ), true, m_MainMenu );
	m_PlayerCounter->setDecimalPlaces( 0 );
	m_PlayerCounter->setRange( 1.f, 32.f );
	m_PlayerCounter->setValue( 2.f );
	
	//undefine sizes
#undef W
#undef H
#undef W2
#undef H2
#undef W4
#undef H4
	
	m_MainMenu->setVisible( false );
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	ConfigStorage *input = m_Engine->getConfig()->getSubSection( "Input" );
	
	std::vector<EKEY_CODE> leftKeys, rightKeys;
	
	lua_State *lua = m_Engine->getToolKit<ScriptToolKit>()->getLuaState();
	
	//Fill the controls
	for( int x = 1; x <= 32; x++ )
	{
		String playerLeftString = "PlayerLeft";
		String playerRightString = "PlayerRight";
		playerLeftString += x;
		playerRightString += x;
		
		int left = m_Engine->getToolKit<ScriptToolKit>()->getPulsarKeyCode( 
			input->get<String>( playerLeftString, "KEY_F11" ) );
		int right = m_Engine->getToolKit<ScriptToolKit>()->getPulsarKeyCode( 
			input->get<String>( playerRightString, "KEY_F11" ) );
		
		std::cout << playerLeftString << ": " << left << std::endl
			<< playerRightString << ": " << right << std::endl;
		
		leftKeys.push_back( (EKEY_CODE)left );
		rightKeys.push_back( (EKEY_CODE)right );
	}
	
	PulsarEventReceiver *evt =
		m_Engine->getToolKit<PulsarEventReceiver>();
	
	//Create a callback for the quit key
	struct : public ICallback {
		virtual void onTrigger( Value* val ){
			exit( EXIT_SUCCESS );
		}
	} exitCallback;
	
	EKEY_CODE exitKey = m_Engine->getToolKit<ScriptToolKit>()->
		getPulsarKeyCode( input->get<String>( "Exit", "ESCAPE" ) );
	
	evt->addKeyPressedCallback( exitKey, &exitCallback );
	
	bool running = true;
	
	//Loop until the game is cancelled
	
	while( m_Engine->run() && running )
	{
		//Show menu
		m_MainMenu->setVisible( true );
		
		//Store selected MapName
		int prevSelection = -1;
		
		//Standard loop
		while( m_Engine->run() )
		{
			m_Engine->beginDrawing();
			
			int selection = m_MapList->getSelected();
			
			//Exit loop if everything is selected
			if( m_OkButton->isPressed() && selection > -1 )
				break;
			
			//If a new Map gets selected, change the max player limit
			if( selection > -1 && prevSelection != selection )
				m_PlayerCounter->setRange( 1.f, m_MapData.at( selection )->get<int>( "MaxPlayers" ) );
			
			prevSelection = selection;
			
			m_Engine->endDrawing();
		}
		
		//Hide menu
		m_MainMenu->setVisible( false );
		
		//Get the selected file names
		String selectedMap = m_MapFiles.at( m_MapList->getSelected() ).string().c_str();
		
		//Load the map
		ConfigStorage map( true );
		map.parseXMLFile( selectedMap );
		map.setAlwaysGetRecursive();
		
		int maxPlayers = map.get<int>( "MaxPlayers", 2 );
		int numPlayers = (int)m_PlayerCounter->getValue();
		
		int numGoals = map.get<int>( "NumGoals", 2 );
		int numBalls = map.get<int>( "NumBalls", 1 );
		
		//Create the players
		DynamicEntity *playerEntity[numPlayers];
		
		for( int x = 0; x < numPlayers; x++ )
		{
			String posString = "PlayerPosition";
			posString += ( x + 1 );
			
			ConfigStorage conf;
			conf.set<String>( "Shape", "$Box" );
			conf.set<Vector>( "Size", Vector( 3, 1, 1 ) );
			conf.set<Vector>( "Position", map.get<Vector>( posString, Vector() ) );
			
			playerEntity[x] = new DynamicEntity( 0, 10.0f );
			playerEntity[x]->loadFromValues( &conf );
		}
		
		//Create goals
		GhostSensorEntity *goalEntity[numGoals];
		
		for( int x = 0; x < numGoals; x++ )
		{
			String posString = "GoalPosition";
			posString += ( x + 1 );
			
			ConfigStorage conf;
			conf.set<String>( "Shape", "$Box" );
			conf.set<Vector>( "Size", 
					  map.get<Vector>( "GoalSize", Vector( 5, 5, 1 ) ) );
			conf.set<Vector>( "Position", map.get<Vector>( posString, Vector() ) );
			
			goalEntity[x] = new GhostSensorEntity();
			goalEntity[x]->loadFromValues( &conf );
		}
		
		//Create Balls
		DynamicEntity *ballEntity[numBalls];
		
		for( int x = 0; x < numBalls; x++ )
		{
			String posString = "BallPosition";
			posString += ( x + 1 );
			
			ConfigStorage conf;
			conf.set<String>( "Shape", "$Sphere" );
			conf.set<Vector>( "Size", map.get<Vector>( "BallSize", Vector( 0.5f ) ) );
			conf.set<Vector>( "Position", map.get<Vector>( posString, Vector() ) );
			conf.set<float>( "Restitution", 2.f );
			
			ballEntity[x] = new DynamicEntity( 0, map.get<float>( "BallMass", 10.0f ) );
			ballEntity[x]->loadFromValues( &conf );
		}
		
		//TODO Make working
		/*
		
		//Create the players
		ConfigStorage player[numPlayers];
		DynamicEntity *playerEntity[numPlayers];
		
		for( int x = 0; x < numPlayers; x++ )
		{
			String posString = "PlayerPosition";
			posString += ( x + 1 );
			
			player[x].setAlwaysGetRecursive();
			player[x].parseXMLFile( selectedBouncer );
			
			playerEntity[x] = &player[x].get<DynamicEntity>( "Bouncer" );
			playerEntity[x]->reposition( map.get<Vector>( posString, Vector() ) );
		}
		
		//Create the goals
		int goalCount = map.get<int>( "GoalCount", 2 );
		
		ConfigStorage goal[goalCount];
		
		for( int x = 0; x < goalCount; x++ )
		{
			String posString = "GoalPosition";
			posString += ( x + 1 );
			
			goal[x].parseXMLFile( selectedGoal );
			goal[x].setAlwaysGetRecursive();
			
			if( goal[x].varExists( "GoalParts" ) )
			{
				std::vector<String> partNames = 
					goal[x].get<std::vector<String> >( "GoalParts" );
					
				for( int y = 0; y < partNames.size(); y++ )
				{
					DynamicEntity &goalPart = goal[x].get<DynamicEntity>( partNames.at( y ) );
					goalPart.reposition( 
						map.get<Vector>( posString, Vector() ) + goalPart.getPosition() );
				}
			}
			else
				goal[x].get<DynamicEntity>( "Goal" ).reposition( 
					map.get<Vector>( posString, Vector() ) );
		}
		
		//Load the balls
		int ballCount = map.get<int>( "BallCount", 1 );
		Confi&player[x].get<DynamicEntity>( "Bouncer" );gStorage ball[ballCount];
		DynamicEntity *ballEntity[ballCount];
		
		for( int x = 0; x < ballCount; x++ )
		{
			String posString = "BallPosition";
			posString += ( x + 1 );
			
			String forceString = "BallStartingForce";
			forceString += ( x + 1 );
			
			ball[x].parseXMLFile( selectedBall );
			ball[x].setAlwaysGetRecursive();
			
			ballEntity[x] = &ball[x].get<DynamicEntity>( "Ball" );
			ballEntity[x]->reposition( map.get<Vector>( posString, Vector() ) );
			ballEntity[x]->applyForce( map.get<Vector>( forceString, Vector() ) );
		}
		*/
		//Start simulation
		m_Engine->setSimulationState( true );

		//Standard loop again
		while( m_Engine->run() )
		{
			m_Engine->beginDrawing();
			
			//Control the players
			for( int x = 0; x < numPlayers; x++ )
			{
				if( evt->keyState( leftKeys.at( x ) ) )
					playerEntity[x]->applyForce( Vector( -100, 0, 0 ) );
					
				if( evt->keyState( rightKeys.at( x ) ) )
					playerEntity[x]->applyForce( Vector( 100, 0, 0 ) );
			}
			
			if( evt->keyState( KEY_F12 ) )
				break;

			m_Engine->endDrawing();
		}
		
		//Delete Entities
		for( int x = 0; x < numPlayers; x++ )
			delete playerEntity[x];
		
		//Stop simulation
		m_Engine->setSimulationState( false );
	}

	return EXIT_SUCCESS;
}
