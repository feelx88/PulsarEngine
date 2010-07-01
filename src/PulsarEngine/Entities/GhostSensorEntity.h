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
