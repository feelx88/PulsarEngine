 /*
    Copyright 2010 Felix Müller

    This file is part of the PulsarEngine.

    The PulsarEngine is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The PulsarEngine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with The PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DynamicEntity.h"

using namespace pulsar;

#include "../Irrlicht_using.h"

DynamicEntity::DynamicEntity( unsigned int iID, float fMass, vector3df pos,
	vector3df rot ) : GraphicalEntity( iID, pos, rot ), m_pRigidBody( 0 )
{
	setClassName( "DynamicEntity" );
	m_pConfig->setCopy<float>( "Mass", fMass );
	m_pConfig->set<bool>( "Dynamic", true );
}

DynamicEntity::~DynamicEntity()
{
	if( this->m_pRigidBody )
	{
		getWorld()->removeRigidBody( m_pRigidBody );
		s_colEntityRelations.erase( this->m_pRigidBody );
	}
	delete m_pRigidBody;
	delete m_pContactPoints;
}

void DynamicEntity::loadFromValues( ConfigStorage *pConf )
{
	GraphicalEntity::loadFromValues( pConf );
	createRigidBody();
}

void DynamicEntity::loadFromFile( String sFileName, String sNodeName )
{
	GraphicalEntity::loadFromFile( sFileName, sNodeName );

	createRigidBody();
}

void DynamicEntity::loadRigidBodyFromFile( String sFileName )
{
	//TODO: Model loading
	m_pCollisionShape = new btBoxShape( btVector3( 1.0f, 1.0f, 1.0f ) );

	if( m_pConfig->get<String>( "ModelFileName" ) != sFileName )
		m_pConfig->setCopy<String>( "CollisionModelFileName", sFileName );

	createRigidBody();
}

void DynamicEntity::createRigidBodyFromCollisionShape( btCollisionShape *pShape )
{
	m_pCollisionShape = pShape;

	createRigidBody();
}

void DynamicEntity::createRigidBodyFromPrimitive(
	Entity::E_PULSARENTITYPRIMITIVE primType, irr::core::vector3df size )
{

	switch ( primType )
	{

		case Entity::EPEP_BOX:
		{
			m_pConfig->set<String>( "CollisionShape", "$Box" );
			break;
		}

		case Entity::EPEP_SPHERE:
		{
			m_pConfig->set<String>( "CollisionShape", "$Sphere" );
			break;
		}

		default:
			return;
	}

	m_pConfig->setCopy<Vector>( "Size", size );

	createRigidBody();
}

void DynamicEntity::createRigidBodyFromCompoundShape( String sFileName,
	String sSectionName )
{
	//TODO: File loading
	createRigidBody();
}

void DynamicEntity::applyImpulse( vector3df direction, vector3df offset )
{
	if( !m_pRigidBody )
		return;

	m_pRigidBody->activate();
	m_pRigidBody->applyImpulse( convert( direction ), convert( offset ) );
}

void DynamicEntity::applyTorqueImpulse( irr::core::vector3df direction )
{
	if( !m_pRigidBody )
		return;

	m_pRigidBody->activate();
	m_pRigidBody->applyTorqueImpulse( convert( direction ) );
}

void DynamicEntity::applyForce( Vector direction, Vector offset )
{
	if( !this->m_pRigidBody )
		return;

	m_pRigidBody->activate();
	this->m_pRigidBody->applyForce( convert( direction ), convert( offset ) );
}

void DynamicEntity::applyTorque( Vector direction )
{
	if( !this->m_pRigidBody )
		return;

	m_pRigidBody->activate();
	this->m_pRigidBody->applyTorque( convert( direction ) );
}

void DynamicEntity::warp( irr::core::vector3df pos )
{
	if( !this->m_pRigidBody )
		return;

	btTransform trans;
	m_pRigidBody->getMotionState()->getWorldTransform( trans );
	trans.setOrigin( convert( pos ) );
	delete this->m_pRigidBody->getMotionState();
	m_pRigidBody->setMotionState( new btDefaultMotionState( trans ) );
	m_pRigidBody->activate();
}

void DynamicEntity::reposition( irr::core::vector3df pos )
{
	warp( pos );
	m_pRigidBody->setLinearVelocity( btVector3( 0.0f, 0.0f, 0.0f ) );
	m_pRigidBody->setAngularVelocity( btVector3( 0.0f, 0.0f, 0.0f ) );
	m_pRigidBody->activate();
}

void DynamicEntity::setRotation( irr::core::vector3df rot )
{
	if( !this->m_pRigidBody )
		return;

	btTransform trans( btQuaternion( degToRad( rot.Y ), degToRad( rot.X ),
		degToRad( rot.Z ) ), convert( getPosition() ) );
	delete this->m_pRigidBody->getMotionState();
	m_pRigidBody->setMotionState( new btDefaultMotionState( trans ) );
}

Vector DynamicEntity::getPosition()
{
	if( !this->m_pRigidBody )
		return Vector();

	btTransform trans;
	m_pRigidBody->getMotionState()->getWorldTransform( trans );
	return convert( trans.getOrigin() );
}

Vector DynamicEntity::getRotation()
{
	if( !this->m_pRigidBody )
		return Vector();

	btTransform trans;
	m_pRigidBody->getMotionState()->getWorldTransform( trans );
	quaternion quat( -trans.getRotation().getX(),
		-trans.getRotation().getY(),
		-trans.getRotation().getZ(),
		trans.getRotation().getW() );
	return quat.getMatrix().getRotationDegrees();
}

void DynamicEntity::updateParameters()
{
	if( !this->m_pRigidBody )
		return;

	m_pRigidBody->setMassProps( m_pConfig->get<float>( "Mass", 0.0f ),
		convert( m_pConfig->get<Vector>( "Inertia", Vector() ) ) );

	m_pRigidBody->setGravity( convert( m_pConfig->get<Vector>( "LocalGravity",
		convert( getWorld()->getGravity() ) ) ) );

	m_pRigidBody->setDamping( m_pConfig->get<float>( "LinearDamping", 0.0f ),
		m_pConfig->get<float>( "AngularDamping", 0.0f ) );
	m_pRigidBody->setLinearFactor(
		convert( m_pConfig->get<Vector>( "LinearFactor", vector3df( 1.0f ) ) ) );
	m_pRigidBody->setAngularFactor(
		convert( m_pConfig->get<Vector>( "AngularFactor", vector3df( 1.0f ) ) ) );
	m_pRigidBody->setSleepingThresholds(
		m_pConfig->get<float>( "LinearSleepingThreshold", 0.8f ),
		m_pConfig->get<float>( "AngularSleepingThreshold", 1.0f ) );
	m_pRigidBody->setLinearVelocity(
		convert( m_pConfig->get<Vector>( "LinearVelocity", Vector() ) ) );
	m_pRigidBody->setAngularVelocity(
		convert( m_pConfig->get<Vector>( "AngularVelocity", Vector() ) ) );

	m_bLinearVelocityLimitEnabled = m_pConfig->varExists( "LinearVelocityLimit" );
	m_bAngularVelocityLimitEnabled = m_pConfig->varExists( "AngularVelocityLimit" );
	m_fLinearVelocityLimit = m_pConfig->get<float>( "LinearVelocityLimit", 0.0f );
	m_fAngularVelocityLimit = m_pConfig->get<float>( "AngularVelocityLimit", 0.0f );

	if( m_pConfig->get<bool>( "DisableSleeping", false ) )
		m_pRigidBody->setActivationState( DISABLE_DEACTIVATION );
	else
		m_pRigidBody->setActivationState( 1 );
}

void DynamicEntity::updateAction( btCollisionWorld *collisionWorld, btScalar deltaTimeStep )
{
	if( !this->m_pRigidBody || !this->m_pSceneNode )
		return;

	m_pSceneNode->setPosition( getPosition() );
	m_pSceneNode->setRotation( getRotation() );

	if( m_bLinearVelocityLimitEnabled )
	{
		btVector3 linVel = m_pRigidBody->getLinearVelocity();
		if( linVel.length2() > m_fLinearVelocityLimit * m_fLinearVelocityLimit )
			m_pRigidBody->setLinearVelocity(
					m_fLinearVelocityLimit * ( linVel / linVel.length() ) );
	}

	if( m_bAngularVelocityLimitEnabled )
	{
		btVector3 angVel = m_pRigidBody->getAngularVelocity();
		if( angVel.length2() > m_fAngularVelocityLimit * m_fAngularVelocityLimit )
			m_pRigidBody->setAngularVelocity(
				m_fAngularVelocityLimit * ( angVel / angVel.length() ) );
	}
}

void DynamicEntity::freeze( bool bFreeze )
{
	if( !this->m_pRigidBody )
		return;

	//Only (un)freeze one time
	if( bFreeze == m_pConfig->get<bool>( "Frozen" ) )
		return;

	m_pConfig->setCopy( "Frozen", bFreeze );

	btVector3 linvel = m_pRigidBody->getLinearVelocity();
	btVector3 angvel = m_pRigidBody->getAngularVelocity();

	m_pConfig->set( "Position", getPosition() );
	m_pConfig->set( "Rotation", getRotation() );

	getWorld()->removeRigidBody( m_pRigidBody );

	createRigidBody();
	m_pRigidBody->setLinearVelocity( linvel );
	m_pRigidBody->setAngularVelocity( angvel );
}

void DynamicEntity::reset()
{
	if( !this->m_pRigidBody )
		return;

	setRotation( m_pConfig->get<Vector>( "Rotation" ) );
	reposition( m_pConfig->get<Vector>( "Position" ) );
	m_pRigidBody->setActivationState( true );
	updateParameters();
}

bool DynamicEntity::collidesWith( DynamicEntity* pOther )
{
	if( !this->m_pRigidBody )
		return false;

	btRigidBody* pBody = dynamic_cast<btRigidBody*>( pOther->getCollisionObject() );
	return static_cast<ContactPointStorage*>(
		m_pRigidBody->getUserPointer() )->contactWithOtherBody( pBody );
}

void DynamicEntity::createRigidBody()
{
	if( this->m_pRigidBody )
	{
		getWorld()->removeRigidBody( this->m_pRigidBody );
		delete this->m_pRigidBody;
	}

	String shapeString = this->m_pConfig->varExists( "CollisionShape" ) ?
		m_pConfig->get<String>( "CollisionShape", "" ) :
		m_pConfig->get<String>( "Shape", "" );

	Vector size = m_pConfig->get<Vector>( "Size", Vector( 1.0f ) );

	m_pCollisionShape = getFromShapePool( shapeString, size );

	btTransform trans(
		btQuaternion(
			degToRad( m_pConfig->get<Vector>( "Rotation", Vector() ).Y ),
			degToRad( m_pConfig->get<Vector>( "Rotation", Vector() ).X ),
			degToRad( m_pConfig->get<Vector>( "Rotation", Vector() ).Z ) ),
		convert( m_pConfig->get<Vector>( "Position" ) ) );

	btMotionState *pState = new btDefaultMotionState( trans );
	btVector3 inertia( 0.0f, 0.0f, 0.0f );

	float fMass = m_pConfig->get<bool>( "Frozen", false ) ?
		0.0f : m_pConfig->get<float>( "Mass", 0.0f );

	m_pCollisionShape->calculateLocalInertia( fMass, inertia );

	m_pConfig->set<Vector>( "Inertia", convert( inertia ) );

	btRigidBody::btRigidBodyConstructionInfo info( fMass, pState,
		m_pCollisionShape, inertia );

	info.m_restitution = m_pConfig->get<float>( "Restitution", 0.0f );
	info.m_friction = m_pConfig->get<float>( "Friction", 0.5f );

	m_pRigidBody = new btRigidBody( info );

	getWorld()->addRigidBody( m_pRigidBody );

	this->s_colEntityRelations[this->m_pRigidBody] = this;

	updateParameters();

	m_pContactPoints = new ContactPointStorage( this );
	m_pRigidBody->setUserPointer( static_cast<void*>( m_pContactPoints ) );
}
