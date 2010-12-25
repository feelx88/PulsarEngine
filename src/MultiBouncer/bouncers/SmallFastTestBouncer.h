#ifndef SMALLFASTTESTBOUNCER_H
#define SMALLFASTTESTBOUNCER_H

#include "../../home/feelx/devel/PulsarEngine/src/MultiBouncer/IBouncer.h"
#include "../../PulsarEngine/Entities/DynamicEntity.h"

class SmallFastTestBouncer : public IBouncer
{

public:
	virtual void spawn(Vector position, Vector rotation);
	virtual void startAction(int num);
	virtual void jump();
	virtual void move(bool up, bool down, bool left, bool right);
	SmallFastTestBouncer();
	virtual ~SmallFastTestBouncer();

private:
	pulsar::DynamicEntity *mBody;
	Vector mDirection;
};

#endif // SMALLFASTTESTBOUNCER_H
