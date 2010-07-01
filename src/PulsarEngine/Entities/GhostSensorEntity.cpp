#include "GhostSensorEntity.h"
#include "../Irrlicht_using.h"

using namespace pulsar;

GhostSensorEntity::GhostSensorEntity( unsigned int id, Vector pos, Vector rot )
	: SensorEntity( id, pos, rot ), m_pSensor( 0 ), m_onEnterCallback( 0 ),
		m_onLeaveCallback( 0 )
{
	setClassName( "GhostSensorEntity" );
}

GhostSensorEntity::~GhostSensorEntity()
{
	if( this->m_pSensor )
	{
		getWorld()->removeCollisionObject( this->m_pSensor );
		s_colEntityRelations.erase( this->m_pSensor );
	}

	delete this->m_pSensor;
}

void GhostSensorEntity::setPosition( Vector pos )
{
	if( !this->m_pSensor )
		return;

	btTransform transform = this->m_pSensor->getWorldTransform();
	transform.setOrigin( convert( pos ) );
	m_pSensor->setWorldTransform( transform );
}

Vector GhostSensorEntity::getPosition()
{
	if( !this->m_pSensor )
		return Vector();

	return convert( this->m_pSensor->getWorldTransform().getOrigin() );
}

void GhostSensorEntity::setRotation( Vector rot )
{
	if( !this->m_pSensor )
		return;

	btTransform transform( btQuaternion( degToRad( rot.Y ), degToRad( rot.X ),
		degToRad( rot.Z ) ), convert( getPosition() ) );
	m_pSensor->setWorldTransform( transform );
}

Vector GhostSensorEntity::getRotation()
{
	if( !this->m_pSensor )
		return Vector();

	btTransform transform;
	this->m_pSensor->getWorldTransform();
	quaternion quat( -transform.getRotation().getX(),
		-transform.getRotation().getY(),
		-transform.getRotation().getZ(),
		transform.getRotation().getW() );
	return quat.getMatrix().getRotationDegrees();
}

bool GhostSensorEntity::isEntityTriggering(Entity* pE)
{
	if( !this->m_pSensor )
		return false;

	for( int x = 0; x < this->m_pSensor->getNumOverlappingObjects(); x++ )
	{
		if( pE->getCollisionObject() &&
			this->m_pSensor->getOverlappingObject( x ) == pE->getCollisionObject() )
			return true;
	}
	return false;
}

void GhostSensorEntity::updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
{
	if( !this->m_pSensor )
		return;

	std::set<Entity*> currentTriggers;

	for( int x = 0; x < this->m_pSensor->getNumOverlappingObjects(); x++ )
	{
		Entity *entity = getEntity( this->m_pSensor->getOverlappingObject( x ) );
		if( entity )
		{
			currentTriggers.insert( entity );

			if( this->m_Callback )
				this->m_Callback->onTrigger( entity );

			if( m_TriggeringEntities.find( entity ) == m_TriggeringEntities.end()
				&& this->m_onEnterCallback )
				this->m_onEnterCallback->onTrigger( entity );

			m_TriggeringEntities.erase( entity );
		}
	}

	for( std::set<Entity*>::iterator x = m_TriggeringEntities.begin();
		x != m_TriggeringEntities.end(); x++ )
	{
		if( this->m_onLeaveCallback )
			this->m_onLeaveCallback->onTrigger( *x );
	}

	m_TriggeringEntities.swap( currentTriggers );
}

void GhostSensorEntity::setOnEnterCallback( ICallback *onEnterCallback )
{
	this->m_onEnterCallback = onEnterCallback;
}

void GhostSensorEntity::setOnLeaveCallback( ICallback *onLeaveCallback )
{
	this->m_onLeaveCallback = onLeaveCallback;
}

void GhostSensorEntity::createSensor()
{
	if( this->m_pSensor )
	{
		getWorld()->removeCollisionObject( this->m_pSensor );
		delete this->m_pSensor;
	}

	this->m_pSensor = new btGhostObject();
	this->m_pSensor->setCollisionFlags( btCollisionObject::CF_NO_CONTACT_RESPONSE );

	this->m_pSensor->setCollisionShape( getFromShapePool(
		this->m_pConfig->get<String>( "Shape", "" ),
		this->m_pConfig->get<Vector>( "Size", Vector( 1.0f ) ) ) );

	setPosition( this->m_pConfig->get<Vector>( "Position", Vector() ) );
	setRotation( this->m_pConfig->get<Vector>( "Rotation", Vector() ) );

	if( this->m_pConfig->varExists( "OnTrigger" ) )
		this->setCallback(
			&this->m_pConfig->get<ICallback>( "OnTrigger" ) );
	if( this->m_pConfig->varExists( "OnEnter" ) )
		this->setOnEnterCallback(
			&this->m_pConfig->get<ICallback>( "OnEnter" ) );
	if( this->m_pConfig->varExists( "OnLeave" ) )
		this->setOnLeaveCallback(
			&this->m_pConfig->get<ICallback>( "OnLeave" ) );

	getWorld()->addCollisionObject( this->m_pSensor );

	s_colEntityRelations[this->m_pSensor] = this;
}
