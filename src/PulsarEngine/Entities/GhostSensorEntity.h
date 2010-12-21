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

#ifndef __ghostsensorentity__
#define __ghostsensorentity__

#include "SensorEntity.h" // Base class: pulsar::SensorEntity
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace pulsar
{

class GhostSensorEntity : public pulsar::SensorEntity
{

public:
	GhostSensorEntity( unsigned int id = 0,
		Vector pos = Vector(), Vector rot = Vector() );
	virtual ~GhostSensorEntity();

	virtual void setPosition( Vector pos );
	virtual Vector getPosition();

	virtual void setRotation( Vector rot );
	virtual Vector getRotation();

	virtual bool isEntityTriggering(Entity* pE);
	virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);

	void setOnEnterCallback( ICallback *onEnterCallback );
	void setOnLeaveCallback( ICallback *onLeaveCallback );

protected:
	virtual void createSensor();
	btGhostObject *m_pSensor;

	ICallback *m_onEnterCallback, *m_onLeaveCallback;
};

}

#endif // __ghostsensorentity__
