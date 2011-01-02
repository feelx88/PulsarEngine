#ifndef SMALLFASTTESTBOUNCER_H
#define SMALLFASTTESTBOUNCER_H

#include "../../home/feelx/devel/PulsarEngine/src/MultiBouncer/IBouncer.h"
#include "../../PulsarEngine/Entities/DynamicEntity.h"

class SmallFastTestBouncer : public IBouncer
{

public:
	SmallFastTestBouncer( int num );
	virtual ~SmallFastTestBouncer();
	
	virtual void spawn(Vector position, Vector rotation);
	virtual void startAction(int num);
	virtual void jump();
	virtual void move(bool up, bool down, bool left, bool right);

	virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep);

	static void addTeamBluePoint();
	static void addTeamRedPoint();
	static void resetPoints();
private:
	pulsar::DynamicEntity *mBody;
	bool mTurbo;
	int mTurboPoints;
	unsigned int mJumpTime, mTurboTime;
	irr::scene::IBillboardSceneNode *mJumpBar, *mTurboBar, *mPlayerNum;
};

#endif // SMALLFASTTESTBOUNCER_H
