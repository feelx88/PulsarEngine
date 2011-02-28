#include "MultiBouncerGame.h"

#include "../PulsarEngine/Irrlicht_using.h"

using namespace pulsar;
using namespace boost;

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

	//Add the reconnect button
	mReconnectButton = gui->addButton( recti( 10, 10, 410, 60 ),
		m_MainMenu, -1, L"(Re)connect wiimotes" );
	mReconnectButton->setVisible( m_Engine->getConfig()->get<bool>( "UseWiimotes", false ) );
	
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

EKEY_CODE*** MultiBouncerGame::loadControls( ConfigStorage* input,
	ScriptToolKit* scriptTK )
{
	int numPlayerControls = 0;
	EKEY_CODE **codes = new EKEY_CODE*[32];
	for( int x = 0; x < 32; x++ )
		codes[x] = new EKEY_CODE[7];

	//Fill the controls
	//TODO: Maybe a KeyCodeConverter for <KeyCode> elements?
	for( int x = 0; x < 32; x++ )
	{
		String sectionName = "Player";
		sectionName += x + 1;

		try
		{
			ConfigStorage *section = input->getSubSection( sectionName );

			codes[x][0] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Up" ) );
			codes[x][1] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Down" ) );
			codes[x][2] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Left" ) );
			codes[x][3] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Right" ) );
			codes[x][4] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Jump" ) );
			codes[x][5] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Action1" ) );
			codes[x][6] = scriptTK->getPulsarKeyCode(
				section->get<String>( "Action2" ) );
		}
		catch( ValueNotFoundException *e )
		{
			std::cout << "Ok, there are only " << x << " player's"
				<< " keys defined, stop checking now.\n";
			break;
		}

		numPlayerControls++;
	}
	codes[numPlayerControls][0] = KEY_KEY_CODES_COUNT;
	return &codes;
}

wiimote** MultiBouncerGame::connectWiimotes( int& connected )
{
	wiimote **wiimotes;
	connected = 0;
	wiimotes = wiiuse_init( 32 );
	int found = wiiuse_find( wiimotes, 32, 5 );
	connected = wiiuse_connect( wiimotes, 32 );

	for( int x = 0; x < found; x++ )
	{
		wiiuse_set_leds( wiimotes[x], ( x + 1 ) * 16 % 64 );
		wiiuse_rumble( wiimotes[x], 1 );
		usleep( 200000 );
		wiiuse_rumble( wiimotes[x], 0 );
	}

	return wiimotes;
}

int MultiBouncerGame::run()
{
	if( !m_Engine )
		return EXIT_FAILURE;

	ConfigStorage *input = m_Engine->getConfig()->getSubSection( "Input" );
	
	PulsarEventReceiver *evt = m_Engine->getToolKit<PulsarEventReceiver>();
	
	ScriptToolKit *scriptTK = m_Engine->getToolKit<ScriptToolKit>();
	lua_State *lua = scriptTK->getLuaState();

	bool useWiimotes = m_Engine->getConfig()->get<bool>( "UseWiimotes", false);
	
	EKEY_CODE **codes = 0;
	wiimote **wiimotes = 0;
	int connectedWiimotes = 0;

	int maxPlayers = 0;
	
	if( !useWiimotes )
	{
		codes = *loadControls( input, scriptTK );
		for( ; maxPlayers < 32; maxPlayers++ )
		{
			if( codes[maxPlayers][0] == KEY_KEY_CODES_COUNT )
				break;
		}
	}

	//Callbacks for the goals
	struct : public ICallback {
		void onTrigger( Value* entity ) {
			for( int x = 0; balls[x] != 0; x++ )
			{
				if( entity->getAs<Entity*>()->getID() ==
					balls[x]->getID() )
				{
					points++;
					balls[x]->reset();
				}
			}
		}
		int points;
		DynamicEntity **balls;
	} redGoalCallback;

	struct : public ICallback {
		void onTrigger( Value* entity ) {
			for( int x = 0; balls[x] != 0; x++ )
			{
				if( entity->getAs<Entity*>()->getID() ==
					balls[x]->getID() )
				{
					points++;
					balls[x]->reset();
				}
			}
		}
		int points;
		DynamicEntity **balls;
	} blueGoalCallback;

	struct : public ICallback {
		void onTrigger(Value* val){
			static_cast<DynamicEntity*>( val->getAs<Entity*>() )->reset();
		}
	} borderCallback;

	bool running = true;

	//Create a callback for the quit key
	struct : public ICallback {
		virtual void onTrigger( Value* val ){
			*running = false;
		}
		bool *running;
	} exitCallback;
	exitCallback.running = &running;

	EKEY_CODE exitKey = scriptTK->getPulsarKeyCode(
		input->get<String>( "Exit", "ESCAPE" ) );

	evt->addKeyPressedCallback( exitKey, &exitCallback );
	
	//Loop until the game is cancelled
	while( m_Engine->run() && running )
	{
		//Show menu
		m_MainMenu->setVisible( true );
		mScoreWindow->setVisible( false );

		//Reset points
		redGoalCallback.points = 0;
		blueGoalCallback.points = 0;
		
		//Store selected MapName
		int prevSelection = -1;
		
		//Standard loop
		while( m_Engine->run() && running )
		{
			m_Engine->beginDrawing();
			
			int selection = m_MapList->getSelected();
			
			//Exit loop if everything is selected
			if( m_OkButton->isPressed() && selection > -1 )
				break;
			
			//If a new Map gets selected, change the max player limit
			if( selection > -1 && prevSelection != selection && maxPlayers > 0 )
				m_PlayerCounter->setRange( 1.f, std::min( maxPlayers, 
					m_MapData.at( selection )->get<int>( "MaxPlayers" ) ) );

			if( mReconnectButton->isPressed() )
			{
				wiimotes = connectWiimotes( connectedWiimotes );
				maxPlayers = connectedWiimotes;
			}
			
			prevSelection = selection;
			
			m_Engine->endDrawing();
		}

		if( !running )
			break;
		
		//Hide menu
		m_MainMenu->setVisible( false );
		mScoreWindow->setVisible( true );
		
		//Get the selected file names
		String selectedMap = m_MapFiles.at( m_MapList->getSelected() ).string().c_str();
		
		//Load the map
		ConfigStorage map( true );
		map.parseXMLFile( selectedMap, "Map" );
		map.setAlwaysGetRecursive();

		std::vector<ILightSceneNode*> lights;

		//Add lights, complicated version...
		//TODO: Light management
		for( int x = 0; x < map.countVars( "Light" ); x++ )
		{
			ConfigStorage *light = map.getSubSection( "Data" )->getSubSectionN( x, "Light" );
			
			SColor lightColor( 128, light->get<int>( "ColorR", 255 ),
				light->get<int>( "ColorG", 255 ),
				light->get<int>( "ColorB", 255 ) );
			ILightSceneNode *node = m_Engine->getIrrlichtDevice()->getSceneManager()->
				addLightSceneNode( 0, light->get<Vector>( "Position" ),
					lightColor, light->get<float>( "Radius" ) );
			node->getLightData().SpecularColor.set( 0,0,0 );

			lights.push_back( node );
		}
		
		//Add a camera
		CameraToolKit *cam = m_Engine->getToolKit<CameraToolKit>();
		cam->addCamera( ID_CAMERA_PRIMARY );
		cam->setCameraPosition( ID_CAMERA_PRIMARY,
			map.getSubSection( "Data" )->getSubSection( "Camera" )->get<Vector>( "Position" ) );
		cam->setCameraTarget( ID_CAMERA_PRIMARY,
			map.getSubSection( "Data" )->getSubSection( "Camera" )->get<Vector>( "Target" ) );
		
		int numPlayers = (int)m_PlayerCounter->getValue();

		IBouncer *players[numPlayers];
		Value::createStandardGenerator<SmallFastTestBouncer>();

		for( int x = 0; x < numPlayers; x++ )
		{
			players[x] = new SmallFastTestBouncer( x + 1 );
			players[x]->setControls( codes[x][0], codes[x][1], codes[x][2],
				codes[x][3], codes[x][4], codes[x][5], codes[x][6] );

			Value *player = new Value( *(SmallFastTestBouncer*)players[x] );
			player->setAutoDestroy( true );
			map.setValue( "Player", player );

			if( x % 2 )
				players[x]->spawn( map.getN<Vector>( x / 2, "RedTeamSpawn" ), Vector() );
			else
				players[x]->spawn( map.getN<Vector>( x / 2, "BlueTeamSpawn" ), Vector() );
		}

		for( int x = 0; x < map.countVars( "RedGoal" ); x++ )
		{
			map.getN<GhostSensorEntity>( x, "RedGoal" ).
				setOnEnterCallback( &redGoalCallback );
		}

		for( int x = 0; x < map.countVars( "BlueGoal" ); x++ )
		{
			map.getN<GhostSensorEntity>( x, "BlueGoal" ).
				setOnEnterCallback( &blueGoalCallback );
		}

		//Create Balls
		int numBalls = map.countVars( "Ball" );
		DynamicEntity *ballEntity[numBalls + 1];
		
		for( int x = 0; x < numBalls; x++ )
		{
			ballEntity[x] = &map.getN<DynamicEntity>( x, "Ball" );
		}

		ballEntity[numBalls] = 0;

		redGoalCallback.balls = ballEntity;
		blueGoalCallback.balls = ballEntity;

		//Create borders
		for( int x = 0; x < map.countVars( "Border" ); x++ )
			map.getN<GhostSensorEntity>( x, "Border" ).setOnEnterCallback( &borderCallback );
		
		//Start simulation
		m_Engine->setSimulationState( true );

		bool toMenu = false;

		int sleeptime = 0;
		
		//Standard loop again
		while( m_Engine->run() && !toMenu && running )
		{
			m_Engine->beginDrawing();
			
			if( evt->keyState( KEY_F12 ) )
				toMenu = true;

			if( evt->keyState( KEY_F5 ) )
				sleeptime = 0;
			if( evt->keyState( KEY_F6 ) )
				sleeptime = 40000;

			usleep(sleeptime);
			
			String points( redGoalCallback.points );
			points += " : ";
			points += blueGoalCallback.points;
			points += " FPS: ";
			points += m_Engine->getIrrlichtDevice()->getVideoDriver()->getFPS();
			mScoreCounter->setText( irr::core::stringw( points ).c_str() );

			if( useWiimotes )
			{
				wiiuse_poll( wiimotes, 32 );
				for( int x = 0; x < numPlayers; x++ )
				{
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_B ) )
						players[x]->jump();
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_ONE ) )
						players[x]->startAction( 1 );
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_TWO ) )
						players[x]->startAction( 2 );
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_HOME ) )
						toMenu = true;
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_DOWN ) )
						players[x]->move( false, false, false, true );
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_UP ) )
						players[x]->move( false, false, true, false );
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_RIGHT ) )
						players[x]->move( true, false, false, false );
					if( IS_PRESSED( wiimotes[x], WIIMOTE_BUTTON_LEFT ) )
						players[x]->move( false, true, false, false );
				}
			}

			m_Engine->endDrawing();
		}
		
		//Stop simulation
		m_Engine->setSimulationState( false );

		for( std::vector<ILightSceneNode*>::iterator x = lights.begin(); x != lights.end(); x++ )
			( *x )->remove();
	}

	for( int x = 0; x < 32; x++ )
		delete[] codes[x];
	delete[] codes;
	
	wiiuse_cleanup( wiimotes, 32 );

	return EXIT_SUCCESS;
}
