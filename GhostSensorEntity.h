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

protected:
	virtual void createSensor();
	btGhostObject *m_pSensor;
};

}

#endif // __ghostsensorentity__
