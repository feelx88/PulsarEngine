#include "MultiBouncerGame.h"

#include "../PulsarEngine/Irrlicht_using.h"

using namespace pulsar;
using namespace boost;

#include "ControlCallback.h"

#define TEXT_SCORE_ZERO ( L"0 : 0" )

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
	//TODO: Light management
	m_Engine->getIrrlichtDevice()->getSceneManager()->
		addLightSceneNode( 0, Vector( 0, 60, -50 ) );

	//Add a camera
	CameraToolKit *cam = m_Engine->getToolKit<CameraToolKit>();
	cam->addCamera( ID_CAMERA_PRIMARY );
	cam->setCameraPosition( ID_CAMERA_PRIMARY, Vector( 0, 20, -50 ) );
	cam->setCameraTarget( ID_CAMERA_PRIMARY, Vector( 0, 0, 0 ) );
}

void MultiBouncerGame::initGUI()
{	
	//TODO: Filesystem tools
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
	//TODO: Add a better method for gui management
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
	m_PlayerCounter->getEditBox()->setTextAlignment( irr::gui::EGUIA_CENTER, 
		irr::gui::EGUIA_CENTER );
	m_PlayerCounter->setDecimalPlaces( 0 );
	m_PlayerCounter->setRange( 1.f, 32.f );
	m_PlayerCounter->setValue( 2.f );
	
	//Create ingame gui
	
	//Upper window for scores etc.
	mScoreWindow = gui->addWindow( recti( 0, 0, W, 50 ) );
	mScoreWindow->setDraggable( false );
	mScoreWindow->setDrawTitlebar( false );
	mScoreWindow->getCloseButton()->setVisible( false );
	
	mScoreCounter = gui->addStaticText( TEXT_SCORE_ZERO, 
		recti( W4, 0, 3 * W4, 50 ), false, false, mScoreWindow );
	mScoreCounter->setTextAlignment( irr::gui::EGUIA_CENTER, 
		irr::gui::EGUIA_CENTER );
	mScoreCounter->setOverrideColor( SColor( 255, 255, 255, 255 ) );
	
	//undefine sizes
	#undef W
	#undef H
	#undef W2
	#undef H2
	#undef W4
	#undef H4
	
	//hide all windows
	m_MainMenu->setVisible( false );
	mScoreWindow->setVisible( false );
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	ConfigStorage *input = m_Engine->getConfig()->getSubSection( "Input" );
	
	PulsarEventReceiver *evt = m_Engine->getToolKit<PulsarEventReceiver>();
	
	ScriptToolKit *scriptTK = m_Engine->getToolKit<ScriptToolKit>();
	lua_State *lua = scriptTK->getLuaState();
	
	int numPlayerControls = 0;
	ControlCallback *callback[32][7];
	
	//Fill the controls
	//TODO: Maybe a KeyCodeConverter for <KeyCode> elements?
	for( int x = 0; x < 32; x++ )
	{
		String playerUpString = "PlayerUp-";
		String playerDownString = "PlayerDown-";
		String playerLeftString = "PlayerLeft-";
		String playerRightString = "PlayerRight-";
		String playerJumpString = "PlayerJump-";
		String playerAction1String = "PlayerAction1-";
		String playerAction2String = "PlayerAction2-";
		playerUpString += x + 1;
		playerDownString += x + 1;
		playerLeftString += x + 1;
		playerRightString += x + 1;
		playerJumpString += x + 1;
		playerAction1String += x + 1;
		playerAction2String += x + 1;
		
		try
		{
			playerUpString = input->get<String>( playerUpString );
			playerDownString = input->get<String>( playerDownString );
			playerLeftString = input->get<String>( playerLeftString );
			playerRightString = input->get<String>( playerRightString );
			playerJumpString = input->get<String>( playerJumpString );
			playerAction1String = input->get<String>( playerAction1String );
			playerAction2String = input->get<String>( playerAction2String );

			callback[x][0] = new ControlCallback( ControlCallback::UP );
			callback[x][1] = new ControlCallback( ControlCallback::DOWN );
			callback[x][2] = new ControlCallback( ControlCallback::LEFT );
			callback[x][3] = new ControlCallback( ControlCallback::RIGHT );
			callback[x][4] = new ControlCallback( ControlCallback::JUMP );
			callback[x][5] = new ControlCallback( ControlCallback::ACTION1 );
			callback[x][6] = new ControlCallback( ControlCallback::ACTION2 );
			
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerUpString ),
				callback[x][0] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerDownString),
				callback[x][1] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerLeftString ),
				callback[x][2] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerRightString ),
				callback[x][3] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerJumpString ),
				callback[x][4] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerAction1String ),
				callback[x][5] );
			evt->addKeyPressedCallback(
				scriptTK->getPulsarKeyCode( playerAction2String ),
				callback[x][6] );
		}
		catch( ValueNotFoundException *e )
		{
			std::cout << "Ok, there are only " << --x << " player's"
				<< " keys defined, stop checking now.\n";
			break;
		}
		
		numPlayerControls++;
	}
	
	//Create a callback for the quit key
	struct : public ICallback {
		virtual void onTrigger( Value* val ){
			exit( EXIT_SUCCESS );
		}
	} exitCallback;

	EKEY_CODE exitKey = scriptTK->getPulsarKeyCode( 
		input->get<String>( "Exit", "ESCAPE" ) );
	
	evt->addKeyPressedCallback( exitKey, &exitCallback );
	
	bool running = true;
	
	//Loop until the game is cancelled
	while( m_Engine->run() && running )
	{
		//Show menu
		m_MainMenu->setVisible( true );
		mScoreWindow->setVisible( false );
		
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
				m_PlayerCounter->setRange( 1.f, std::min(
					numPlayerControls, 
					m_MapData.at( selection )->get<int>( "MaxPlayers" ) ) );
			
			prevSelection = selection;
			
			m_Engine->endDrawing();
		}
		
		//Hide menu
		m_MainMenu->setVisible( false );
		mScoreWindow->setVisible( true );
		
		//Get the selected file names
		String selectedMap = m_MapFiles.at( m_MapList->getSelected() ).string().c_str();
		
		//Load the map
		ConfigStorage map( true );
		map.parseXMLFile( selectedMap );
		map.setAlwaysGetRecursive();
		
		int numPlayers = (int)m_PlayerCounter->getValue();
		
		int numGoals = map.get<int>( "GoalCount", 2 );
		int numBalls = map.get<int>( "BallCount", 1 );
		
		IBouncer *players[numPlayers];
		Value::createStandardGenerator<SmallFastTestBouncer>();

		for( int x = 0; x < numPlayers; x++ )
		{
			players[x] = new SmallFastTestBouncer();
			for( int y = 0; y < 7; y++ )
				callback[x][y]->setBouncer( players[x] );

			Value *player = new Value( *(SmallFastTestBouncer*)players[x] );
			player->setAutoDestroy( true );
			map.setValue( "Player", player );
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
			
			Value *val = new Value( *goalEntity[x] );
			val->setAutoDestroy( true );
			map.setValue( "Goal", val );
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
			conf.set<float>( "Restitution", 1.f );
			conf.set<float>( "Friction", 0.95f );
			
			ballEntity[x] = new DynamicEntity( 0, map.get<float>( "BallMass", 10.0f ) );
			ballEntity[x]->loadFromValues( &conf );
			
			Value *val = new Value( *ballEntity[x] );
			val->setAutoDestroy( true );
			map.setValue( "Ball", val );
		}
		
		//Start simulation
		m_Engine->setSimulationState( true );

		//Standard loop again
		while( m_Engine->run() )
		{
			m_Engine->beginDrawing();
			
			if( evt->keyState( KEY_F12 ) )
				break;

			m_Engine->endDrawing();
		}
		
		//Stop simulation
		m_Engine->setSimulationState( false );
	}

	return EXIT_SUCCESS;
}
