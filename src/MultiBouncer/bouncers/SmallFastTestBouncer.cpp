#include "SmallFastTestBouncer.h"
#include "../../PulsarEngine/ConfigStorage.h"

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
}

SmallFastTestBouncer::~SmallFastTestBouncer()
{

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
	else
		mBody->setRotation( Vector() );
}

void SmallFastTestBouncer::jump()
{
	float y = static_cast<btRigidBody*>( mBody->getCollisionObject() )->
		getLinearVelocity().getY();
	if( y < 0.1 && y > -0.1 )
		mBody->applyImpulse( Vector( 0, 100, 0 ) );
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
