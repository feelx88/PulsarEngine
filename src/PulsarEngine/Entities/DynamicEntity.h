#ifndef __dynamicentity__
#define __dynamicentity__

#include "GraphicalEntity.h"
#include "../ContactPointStorage.h"

namespace pulsar
{

class DynamicEntity : public GraphicalEntity
{

public:
	DynamicEntity( unsigned int iID = 0, float fMass = 0.0f, Vector pos = Vector(), Vector rot = Vector() );
	virtual ~DynamicEntity();

	void loadFromValues( ConfigStorage *pConf );
	void loadFromFile( String sFileName, String sNodeName = "" );

	void loadRigidBodyFromFile( String sFileName );
	void createRigidBodyFromCollisionShape( btCollisionShape *pShape );
	void createRigidBodyFromPrimitive( Entity::E_PULSARENTITYPRIMITIVE primtype, Vector size );
	void createRigidBodyFromCompoundShape( String sFileName, String sSectionName = "" );

	void applyImpulse( Vector direction, Vector offset = Vector() );
	void applyTorqueImpulse( Vector direction );

	void applyForce( Vector direction, Vector offset = Vector() );
	void applyTorque( Vector direction );

	void warp( Vector pos );
	void reposition( Vector pos );

	//override for Entity
	void setPosition( Vector pos )
	{
		warp( pos );
	}

	void setRotation( Vector rot );

	Vector getPosition();
	Vector getRotation();

	void updateParameters();

	void freeze( bool bFreeze = true );

	void reset();

	bool collidesWith( DynamicEntity* );

	ContactPointStorage* getContactPointStorage()
	{
		return m_pContactPoints;
	}

	virtual btCollisionObject *getCollisionObject()
	{
		return m_pRigidBody;
	}

	bool isDynamic()
	{
		return true;
	}

	virtual void updateAction( btCollisionWorld* collisionWorld,
		btScalar deltaTimeStep );

	void debugDraw( btIDebugDraw* ){};

protected:

	void createRigidBody();

	btCollisionShape *m_pCollisionShape;
	btRigidBody *m_pRigidBody;

	float m_fLinearVelocityLimit, m_fAngularVelocityLimit;
	bool m_bLinearVelocityLimitEnabled, m_bAngularVelocityLimitEnabled;

	bool m_bFrozen;

	ContactPointStorage* m_pContactPoints;
};

}

#endif // __dynamicentity__
