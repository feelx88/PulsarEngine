#include "SmallFastTestBouncer.h"
#include "../../PulsarEngine/ConfigStorage.h"
#include "../../PulsarEngine/PulsarEngine.h"

using namespace pulsar;

SmallFastTestBouncer::SmallFastTestBouncer( int num ) : mTurbo( false ),
	mTurboPoints( 3 ), mDirection( Vector() ), mMoveTime( 0.f ), mTurboTime( 0.f )
{
	//Create the body
	ConfigStorage bodyConf;

	bodyConf.set<String>( "Shape", "$Box" );
	bodyConf.set<Vector>( "Size", Vector( 3.f, 1.f, 3.f ) );
	bodyConf.set<float>( "Mass", 50.f );
	bodyConf.set<Vector>( "LinearVelocityLimit", Vector( 20.f, 20.f, 20.f ) );
	bodyConf.set<float>( "AngularFactor", 0.f );
	bodyConf.set<String>( "ModelFileName", "models/sftbouncer/sftbouncer.x" );

	mBody = new DynamicEntity( 0, 50.f );
	mBody->loadFromValues( &bodyConf );

	static_cast<irr::scene::IAnimatedMeshSceneNode*>( mBody->getSceneNode() )
		->addShadowVolumeSceneNode();

	irr::IrrlichtDevice *dev = PulsarEngine::getInstance()->getIrrlichtDevice();

	mJumpBar = dev->getSceneManager()->addBillboardSceneNode(
		0, irr::core::dimension2df( 3, 0.4 ),
		Vector( 0, 3, 0 ), -1, irr::video::SColor( 255, 255, 0, 0 ),
		irr::video::SColor( 255, 255, 0, 0 ) );

	mTurboBar = dev->getSceneManager()->addBillboardSceneNode(
		0, irr::core::dimension2df( 3, 0.4 ),
		Vector( 0, 3, 0 ), -1, irr::video::SColor( 255, 255, 0, 0 ),
		irr::video::SColor( 255, 255, 0, 0 ) );

	irr::video::SColor col( 255, num % 2 ? 255 : 0, 0, num % 2 ? 0 : 255 );
	mPlayerNum = dev->getSceneManager()->addBillboardTextSceneNode(
		dev->getGUIEnvironment()->getSkin()->getFont(),
		irr::core::stringw( num ).c_str(), 0, irr::core::dimension2df( 2, 2 ),
		Vector(), -1, col, col );
	
	mTimer = dev->getTimer();
	mJumpTime = mTimer->getRealTime() - 2000;

	PulsarEngine::getInstance()->getBulletWorld()->addAction( this );
}

SmallFastTestBouncer::~SmallFastTestBouncer()
{
	mJumpBar->remove();
	mTurboBar->remove();
	mPlayerNum->remove();
	delete mBody;
	PulsarEngine::getInstance()->getBulletWorld()->removeAction( this );
}

void SmallFastTestBouncer::spawn(Vector position, Vector rotation)
{
	mBody->setPosition( position );
	mBody->setRotation( rotation );

	mBody->getConfig()->set<Vector>( "Position", position );
}

void SmallFastTestBouncer::startAction(int num)
{
	mTurbo = true;
}

void SmallFastTestBouncer::jump()
{
	if( mTimer->getRealTime() - mJumpTime > 2000 )
	{
		mBody->applyImpulse( Vector( 0, 500, 0 ) );
		mJumpTime = mTimer->getRealTime();
	}
}

void SmallFastTestBouncer::move(bool up, bool down, bool left, bool right)
{
	float full = mTurbo && mTurboPoints > 0 ? 25.0f : 10.0f;
	float x = left ? -full : 0.f + right ? full : 0.f + mDirection.X;
	float z = down ? -full : 0.f + up ? full : 0.f + mDirection.Z;

	if( x > full )
		x = full;
	if( z > full )
		z = full;
	
	mDirection.set( x, 0, z );
	mBody->applyImpulse( mDirection );
}

void SmallFastTestBouncer::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	IBouncer::updateAction( collisionWorld, deltaTimeStep );
	mDirection.set( 0.f, 0.f, 0.f );
		
	float jumpScale = (float)( mTimer->getRealTime() - mJumpTime ) / 2000.f;
	if( jumpScale < 1.f )
	{
		mJumpBar->setSize( irr::core::dimension2df( jumpScale * 3, 0.4f ) );
		mJumpBar->setColor( irr::video::SColor( 255, 255, 0, 0 ) );
	}
	else
		mJumpBar->setColor( irr::video::SColor( 255, 0, 255, 0 ) );

	float turboScale = mTurboPoints / 3.f;
	if( turboScale < 0.5f )
	{
		mTurboBar->setSize( irr::core::dimension2df( turboScale * 3, 0.4f ) );
		mTurboBar->setColor( irr::video::SColor( 255, 255, 0, 0 ) );
	}
	else
		mTurboBar->setColor( irr::video::SColor( 255, 0, 255, 0 ) );

	mJumpBar->setPosition( mBody->getPosition() + Vector( 0, 4, 0 ) );
	mTurboBar->setPosition( mBody->getPosition() + Vector( 0, 4.9, 0 ) );
	mPlayerNum->setPosition( mBody->getPosition() + Vector( -2.2, 4, 0 ) );

	if( mTurbo )
	{
		if( mTurboTime >= 1.f && mTurboPoints > 0 )
		{
			mTurboPoints--;
			mTurboTime = 0.f;
		}
		else
			mTurboTime += deltaTimeStep;
	}
	else
	{
		if( mTurboTime >= 1.f && mTurboPoints <= 3 )
		{
			mTurboPoints++;
			mTurboTime = 0.f;
		}
	}
	
	mTurbo = false;
}