#ifndef _IBOUNCER_H_
#define _IBOUNCER_H_

#include "../PulsarEngine/IObject.h"

/**
 * @class IBouncer
 * @brief Base class for Bouncers.
 **/
class IBouncer : public pulsar::IObject
{
public:
	/**
	 * @brief Standard constructor.
	 *
	 **/
	IBouncer() : IObject(){};
	
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
};

#endif //_IBOUNCER_H_