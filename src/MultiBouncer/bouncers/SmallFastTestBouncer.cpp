#include "SmallFastTestBouncer.h"
#include "../../PulsarEngine/ConfigStorage.h"
#include "../../PulsarEngine/PulsarEngine.h"

using namespace pulsar;

SmallFastTestBouncer::SmallFastTestBouncer() : mDirection( Vector() )
{
	//Create the body
	ConfigStorage bodyConf;

	bodyConf.set<String>( "Shape", "$Box" );
	bodyConf.set<Vector>( "Size", Vector( 3.f, 1.f, 2.f ) );
	bodyConf.set<float>( "Mass", 50.f );
	bodyConf.set<Vector>( "LinearVelocityLimit", Vector( 20.f, 20.f, 20.f ) );

	mBody = new DynamicEntity();
	mBody->loadFromValues( &bodyConf );

	irr::IrrlichtDevice *dev = PulsarEngine::getInstance()->getIrrlichtDevice();

	mJumpBar = dev->getSceneManager()->addBillboardSceneNode(
		mBody->getSceneNode(), irr::core::dimension2df( 3, 0.4 ),
		Vector( 0, 3, 0 ), -1, irr::video::SColor( 255, 255, 0, 0 ),
		irr::video::SColor( 255, 255, 0, 0 ) );
	
	mTimer = dev->getTimer();
	mJumpTime = mTimer->getRealTime();

	PulsarEngine::getInstance()->getBulletWorld()->addAction( this );
}

SmallFastTestBouncer::~SmallFastTestBouncer()
{
	mJumpBar->remove();
	delete mBody;
	PulsarEngine::getInstance()->getBulletWorld()->removeAction( this );
}

void SmallFastTestBouncer::spawn(Vector position, Vector rotation)
{
	mBody->setPosition( position );
	mBody->setRotation( rotation );
}

void SmallFastTestBouncer::startAction(int num)
{
	if( num == 1 )
		mBody->applyImpulse( mDirection * 10 );
}

void SmallFastTestBouncer::jump()
{
	if( mTimer->getRealTime() - mJumpTime > 5000 )
	{
		mBody->applyImpulse( Vector( 0, 500, 0 ) );
		mJumpTime = mTimer->getRealTime();
	}
}

void SmallFastTestBouncer::move(bool up, bool down, bool left, bool right)
{
	float x = left ? -1.f : 0.f + right ? 1.f : 0.f;
	float z = down ? -1.f : 0.f + up ? 1.f : 0.f;

	if( x + z > 1.f )
		x = z = 0.5f;

	mDirection.set( x, 0, z );
	
	mBody->applyImpulse( mDirection );
}

void SmallFastTestBouncer::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	float scale = (float)( mTimer->getRealTime() - mJumpTime ) / 5000.f;
	if( scale < 1.f )
	{
		mJumpBar->setSize( irr::core::dimension2df( scale * 3, 0.4f ) );
		mJumpBar->setColor( irr::video::SColor( 255, 255, 0, 0 ) );
	}
	else
		mJumpBar->setColor( irr::video::SColor( 255, 0, 255, 0 ) );
}