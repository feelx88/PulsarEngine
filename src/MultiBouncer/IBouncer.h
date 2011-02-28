#ifndef _IBOUNCER_H_
#define _IBOUNCER_H_

#include "../PulsarEngine/IObject.h"
#include "../PulsarEngine/ToolKits/PulsarEventReceiver.h"
#include "../PulsarEngine/PulsarEngine.h"

/**
 * @class IBouncer
 * @brief Base class for Bouncers.
 **/
class IBouncer : public pulsar::IObject, public btActionInterface
{
public:
	/**
	 * @brief Standard constructor.
	 *
	 **/
	IBouncer() : IObject()
	{
		mEventReceiver =
			static_cast<pulsar::PulsarEventReceiver*>( pulsar::PulsarEngine::getInstance()->
			getIrrlichtDevice()->getEventReceiver() );
	};
	
	/**
	 * @brief Standard destructor.
	 *
	 **/
	virtual ~IBouncer(){};
	
	/**
	 * @brief Move the Bouncer in the specified direction on its local axis.
	 *
	 * @param up Move up?
	 * @param down Move down?
	 * @param left Move left?
	 * @param right Move right?
	 **/
	virtual void move( bool up, bool down, bool left, bool right ) = 0;
	
	/**
	 * @brief Let the bouncer jump.
	 * 
	 **/
	virtual void jump() = 0;
	
	/**
	 * @brief Let the bouncer start the specified action.
	 *
	 * @param num Number of the action to start.
	 **/
	virtual void startAction( int num ) = 0;
	
	/**
	 * @brief Spawn the bouncer at the specified position / rotation.
	 *
	 * @param position The initial position of the bouncer.
	 * @param rotation The initial rotation of the bouncer.
	 **/
	virtual void spawn( Vector position, Vector rotation ) = 0;

	void setControls( irr::EKEY_CODE up, irr::EKEY_CODE down, irr::EKEY_CODE left,
		irr::EKEY_CODE right, irr::EKEY_CODE jump, irr::EKEY_CODE action1,
		irr::EKEY_CODE action2 )
	{
		mKeys[0] = up;
		mKeys[1] = down;
		mKeys[2] = left;
		mKeys[3] = right;
		mKeys[4] = jump;
		mKeys[5] = action1;
		mKeys[6] = action2;
	}

	virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep)
	{
		if( mEventReceiver->keyState( mKeys[0] ) )
			move( true, false, false, false );
		if( mEventReceiver->keyState( mKeys[1] ) )
			move( false, true, false, false );
		if( mEventReceiver->keyState( mKeys[2] ) )
			move( false, false, true, false );
		if( mEventReceiver->keyState( mKeys[3] ) )
			move( false, false, false, true );
		if( mEventReceiver->keyState( mKeys[4] ) )
			jump();
		if( mEventReceiver->keyState( mKeys[5] ) )
			startAction( 1 );
		if( mEventReceiver->keyState( mKeys[6] ) )
			startAction( 2 );
	};
	
	virtual void debugDraw(btIDebugDraw* debugDrawer){};

protected:
	irr::ITimer *mTimer;

	pulsar::PulsarEventReceiver *mEventReceiver;
	irr::EKEY_CODE mKeys[7];
};

#endif //_IBOUNCER_H_