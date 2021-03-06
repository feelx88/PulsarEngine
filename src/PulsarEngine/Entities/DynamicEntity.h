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
    along with the PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __dynamicentity__
#define __dynamicentity__

#include "GraphicalEntity.h"

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
};

}

#endif // __dynamicentity__
