#include "ConstraintToolKit.h"
#include "PulsarEngine.h"

using namespace pulsar;

ConstraintToolKit::ConstraintToolKit() : IToolKit()
{
	setClassName( "ConstraintToolKit" );
}

ConstraintToolKit::~ConstraintToolKit()
{
}

void ConstraintToolKit::init( Value initValue )
{
}

btPoint2PointConstraint *ConstraintToolKit::connectWithPoint2Point( unsigned int iID, Entity *pEntity1,
	Entity *pEntity2, Vector pos1, Vector pos2 )
{
	if( !pEntity1->isDynamic() || !pEntity2->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody *pBody1 = static_cast<btRigidBody*>( pEntity1->getCollisionObject() );
	btRigidBody *pBody2 = static_cast<btRigidBody*>( pEntity2->getCollisionObject() );

	btVector3 p1 = PulsarEngine::convert( pos1 );
	btVector3 p2 = PulsarEngine::convert( pos2 );

	btPoint2PointConstraint *pP2P = new btPoint2PointConstraint( *pBody1, *pBody2,
		p1, p2 );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pP2P );
	m_mConstraints.insert( std::make_pair( iID, pP2P ) );

	return pP2P;
}

btHingeConstraint *ConstraintToolKit::connectWithHinge( unsigned int iID, Entity *pEntity1, Entity *pEntity2,
	Vector pos1, Vector pos2, Vector hingeAxis1, Vector hingeAxis2 )
{
	if( !pEntity1->isDynamic() || !pEntity2->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );
	btRigidBody &pBody2 = *static_cast<btRigidBody*>( pEntity2->getCollisionObject() );

	btVector3 p1 = PulsarEngine::convert( pos1 );
	btVector3 p2 = PulsarEngine::convert( pos2 );
	btVector3 ha1 = PulsarEngine::convert( hingeAxis1 );
	btVector3 ha2 = PulsarEngine::convert( hingeAxis2 );

	btHingeConstraint *pHinge = new btHingeConstraint( pBody1, pBody2,
		p1, p2, ha1, ha2 );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pHinge );
	m_mConstraints.insert( std::make_pair( iID, pHinge ) );

	return pHinge;
}

btSliderConstraint *ConstraintToolKit::connectWithSlider( unsigned int iID, Entity *pEntity1, Entity *pEntity2,
				Vector pos1, Vector pos2, Vector dir1, Vector dir2 )
{
	if( !pEntity1->isDynamic() || !pEntity2->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );
	btRigidBody &pBody2 = *static_cast<btRigidBody*>( pEntity2->getCollisionObject() );

	btTransform t1( btQuaternion( dir1.Y, dir1.X, dir1.Z ), PulsarEngine::convert( pos1 ) );
	btTransform t2( btQuaternion( dir2.Y, dir2.X, dir2.Z ), PulsarEngine::convert( pos2 ) );

	btSliderConstraint *pSlider = new btSliderConstraint( pBody1, pBody2, t1, t2, false );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pSlider );
	m_mConstraints.insert( std::make_pair( iID, pSlider ) );

	return pSlider;
}

btGeneric6DofConstraint *ConstraintToolKit::connectWith6DOF( unsigned int iID, Entity *pEntity1, Entity *pEntity2,
	Vector pos1, Vector pos2, Vector dir1, Vector dir2 )
{
	if( !pEntity1->isDynamic() || !pEntity2->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );
	btRigidBody &pBody2 = *static_cast<btRigidBody*>( pEntity2->getCollisionObject() );

	btTransform t1( btQuaternion( dir1.Y, dir1.X, dir1.Z ), PulsarEngine::convert( pos1 ) );
	btTransform t2( btQuaternion( dir2.Y, dir2.X, dir2.Z ), PulsarEngine::convert( pos2 ) );

	btGeneric6DofConstraint *p6DOF = new btGeneric6DofConstraint( pBody1, pBody2,
		t1, t2, false );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( p6DOF );
	m_mConstraints.insert( std::make_pair( iID, p6DOF ) );

	return p6DOF;
}

btPoint2PointConstraint *ConstraintToolKit::lockWithPoint2Point( unsigned int iID, Entity *pEntity1, Vector pos1 )
{
	if( !pEntity1->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );

	btVector3 p1 = PulsarEngine::convert( pos1 );

	btPoint2PointConstraint *pP2P = new btPoint2PointConstraint( pBody1, p1 );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pP2P );
	m_mConstraints.insert( std::make_pair( iID, pP2P ) );

	return pP2P;
}

btHingeConstraint *ConstraintToolKit::lockWithHinge( unsigned int iID, Entity *pEntity1, Vector pos1,
	Vector hingeAxis1 )
{
	if( !pEntity1->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );

	btVector3 p1 = PulsarEngine::convert( pos1 );
	btVector3 ha1 = PulsarEngine::convert( hingeAxis1 );

	btHingeConstraint *pHinge = new btHingeConstraint( pBody1, p1, ha1 );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pHinge );
	m_mConstraints.insert( std::make_pair( iID, pHinge ) );

	return pHinge;
}

btSliderConstraint *ConstraintToolKit::lockWithSlider( unsigned int iID, Entity *pEntity1, Vector pos1, Vector dir1 )
{
	if( !pEntity1->isDynamic() || getConstraint( iID ) )
		return 0;

	btRigidBody &pBody1 = *static_cast<btRigidBody*>( pEntity1->getCollisionObject() );

	btTransform t1( btQuaternion( dir1.Y, dir1.X, dir1.Z ), PulsarEngine::convert( pos1 ) );

	btSliderConstraint *pSlider = new btSliderConstraint( pBody1, t1, false );

	btDynamicsWorld *pBullet= PulsarEngine::getInstance()->getBulletWorld();

	pBullet->addConstraint( pSlider );
	m_mConstraints.insert( std::make_pair( iID, pSlider ) );

	return pSlider;
}


