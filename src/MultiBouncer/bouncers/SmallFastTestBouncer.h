#ifndef SMALLFASTTESTBOUNCER_H
#define SMALLFASTTESTBOUNCER_H

#include "../IBouncer.h"
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
	unsigned int mJumpTime;
	irr::scene::IBillboardSceneNode *mJumpBar, *mTurboBar, *mPlayerNum;

	float mMoveTime, mTurboTime;

	Vector mDirection;
};

#endif // SMALLFASTTESTBOUNCER_H
