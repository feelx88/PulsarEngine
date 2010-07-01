#include "MultiBouncer/MultiBouncerGame.h"

int main( int argc, char **argv )
{
	MultiBouncerGame *game = new MultiBouncerGame();
	return game->run();
}

/*
#include "PulsarEngine.h"
#include <iostream>

#include "Irrlicht_using.h"

using namespace pulsar;
*/
/*
Test entities:
<?xml version="1.0" encoding="UTF-8"?>

<Section Name="Extras">
	<DynamicEntity Name="Dyn1">
		<Float Name="Mass">15.000000</Float>
		<Vector Name="Position">
			<Float Name="X">2.2232</Float>
			<Float Name="Y">5.234</Float>
			<Float Name="Z">10.5</Float>
		</Vector>
		<String Name="Shape">$Sphere</String>
		<String Name="ModelFileName">models/testship1/testship1.b3d</String>
		<Vector Name="Size">
			<Float Name="X">2.000000</Float>
			<Float Name="Y">2.000005</Float>
			<Float Name="Z">2.000000</Float>
		</Vector>
	</DynamicEntity>
	<DynamicEntity Name="Ramp">
		<Float Name="Mass">0</Float>
		<Vector Name="Rotation">50,0,0</Vector>
		<String Name="Shape">$Box</String>
		<Vector Name="Size">5,5,0.5</Vector>
	</DynamicEntity>
	<GhostSensorEntity Name="AntigravSensor">
		<String Name="Shape">$Box</String>
		<Vector Name="Size">5,10,5</Vector>
		<Vector Name="Position">0,10,0</Vector>
		<ApplyImpulseCallback Name="OnTrigger">
			<Vector Name="Direction">0,3,0</Vector>
		</ApplyImpulseCallback>
	</GhostSensorEntity>
	<GhostSensorEntity Name="LeftSensor">
		<String Name="Shape">$Box</String>
		<Vector Name="Size">5,20,50</Vector>
		<Vector Name="Position">-25,10,0</Vector>
		<ApplyImpulseCallback Name="OnEnter">
			<Vector Name="Direction">300,0,0</Vector>
		</ApplyImpulseCallback>
	</GhostSensorEntity>
	<GhostSensorEntity Name="RightSensor">
		<String Name="Shape">$Box</String>
		<Vector Name="Size">5,20,50</Vector>
		<Vector Name="Position">25,10,0</Vector>
		<ApplyImpulseCallback Name="OnEnter">
			<Vector Name="Direction">-300,0,0</Vector>
		</ApplyImpulseCallback>
	</GhostSensorEntity>
	<GhostSensorEntity Name="FrontSensor">
		<String Name="Shape">$Box</String>
		<Vector Name="Size">50,20,5</Vector>
		<Vector Name="Position">0,10,25</Vector>
		<ApplyImpulseCallback Name="OnEnter">
			<Vector Name="Direction">0,0,-300</Vector>
		</ApplyImpulseCallback>
	</GhostSensorEntity>
	<GhostSensorEntity Name="BackSensor">
		<String Name="Shape">$Box</String>
		<Vector Name="Size">50,20,5</Vector>
		<Vector Name="Position">0,10,-25</Vector>
		<ApplyImpulseCallback Name="OnEnter">
			<Vector Name="Direction">0,0,300</Vector>
		</ApplyImpulseCallback>
	</GhostSensorEntity>
</Section>
*/
/*
int main( int argc, char **argv )
{
	//Initialize the Engine with the configuration file config.cml
	PulsarEngine *pEngine = PulsarEngine::getInstance();
	pEngine->init( "config.xml" );

	//add a light
	//TODO: light managemenet
	pEngine->getIrrlichtDevice()->getSceneManager()->addLightSceneNode( 0, vector3df( 0, 100, 0 ) );

	//execute script if it should be used
	if( pEngine->getConfig()->get<bool>( "ScriptOnly", false ) )
	{
		dynamic_cast<ScriptToolKit*>( pEngine->getToolKit( "Script" ) )->
			executeFile( "main.lua" );
		delete pEngine;
		return 0;
	}

	//get the toolkits
	ScriptToolKit *pScript =
		dynamic_cast<ScriptToolKit*>( pEngine->getToolKit( "Script" ) );
	PulsarEventReceiver *pEvent =
		dynamic_cast<PulsarEventReceiver*>( pEngine->getToolKit( "EventReceiver" ) );
	EntityToolKit *pEntity =
		dynamic_cast<EntityToolKit*>( pEngine->getToolKit( "Entity" ) );
	ConstraintToolKit *pConstraint =
		dynamic_cast<ConstraintToolKit*>( pEngine->getToolKit( "Constraint" ) );
	CameraToolKit *pCam =
		dynamic_cast<CameraToolKit*>( pEngine->getToolKit( "Camera" ) );

	//add a camera
	pCam->addCamera( 1 );
	pCam->setCameraPosition( 1, Vector( 0, 15, -40 ) );

	Value running = true;

	//add a floor and a falling box
	DynamicEntity *pE1 = new DynamicEntity();
	pE1->createRigidBodyFromPrimitive( Entity::EPEP_BOX, Vector( 50, 1, 50 ) );
	pE1->createSceneNodeFromPrimitive( Entity::EPEP_BOX, Vector( 50, 1, 50 ) );

	DynamicEntity *pE2 = new DynamicEntity( 0, 10, Vector( 0, 15, 0 ), Vector( 45, 0, 0 ) );
	pE2->createRigidBodyFromPrimitive( Entity::EPEP_BOX, Vector( 1, 5, 5 ) );
	pE2->createSceneNodeFromPrimitive( Entity::EPEP_BOX, Vector( 1, 5, 5 ) );

	DynamicEntity *pE3 = new DynamicEntity();
	DynamicEntity *pE4 = new DynamicEntity();
	DynamicEntity *pE5 = new DynamicEntity();
	DynamicEntity *pE6 = new DynamicEntity();

	//Create 4 spheres from a ConfigStorage

	ConfigStorage *pConf = new ConfigStorage();
	pConf->set<float>( "Mass", 10 )
		->set<Vector>( "Position", Vector( 2, 25, 0 ) )
		->set<String>( "ModelFileName", "models/testship1/testship1.b3d" )
		->set<String>( "CollisionShape", "$Sphere" )
		->set<Vector>( "Size", Vector( 2, 2, 2 ) );

	pE3->loadFromValues( pConf );
	pConf->set<Vector>( "Position", Vector( 2, 25, 5 ) );
	pE4->loadFromValues( pConf );
	pConf->set<Vector>( "Position", Vector( 2, 25, 10 ) );
	pE5->loadFromValues( pConf );
	pConf->set<Vector>( "Position", Vector( 2, 25, -5 ) );
	pE6->loadFromValues( pConf );

	delete pConf;

	ConfigStorage p;
	p.parseXMLFile( "../main.cpp", "Extras" );

	//start simulation
	pEngine->setSimulationState( true );

	float angle = 180.0f;

	//main loop
	while( pEngine->run() && running.getAs<bool>() )
	{
		pEngine->beginDrawing();

		//exit if escape is pressed
		if( pEvent->keyState( KEY_ESCAPE ) )
			running = false;

		//test other stuff
		if( pEvent->keyState( KEY_KEY_X ) )
			pE2->applyForce( Vector( 0, 100, 0 ) );

		//rotate camera
		angle += 0.0005f;
		if( angle > 360.0f )
			angle = 0.0f;

		pCam->setCameraPosition( 1, Vector( sin( angle ) * 20, 15, cos( angle ) * 20  ) );
		pCam->setCameraTarget( 1, Vector() );

		pEngine->endDrawing();
	}

	delete pEngine;

	return 0;
}
*/
