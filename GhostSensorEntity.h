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

	void setOnEnterCallback( SensorCallback *onEnterCallback );
	void setOnLeaveCallback( SensorCallback *onLeaveCallback );

protected:
	virtual void createSensor();
	btGhostObject *m_pSensor;

	SensorCallback *m_onEnterCallback, *m_onLeaveCallback;
};

}

#endif // __ghostsensorentity__
