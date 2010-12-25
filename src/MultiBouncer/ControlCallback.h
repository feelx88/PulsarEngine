#ifndef CONTROLCALLBACK_H
#define CONTROLCALLBACK_H

#include "../PulsarEngine/ICallback.h"
#include "IBouncer.h"

/**
 * @class ControlCallback
 * @brief Callback for controlling bouncers.
 **/
class ControlCallback : public pulsar::ICallback
{
public:
	
	/**
	 * @brief Enum for the actions a bouncer can do.
	 **/
	enum CCB_ACTION
	{
		UP = 1,
		DOWN,
		LEFT,
		RIGHT,
		JUMP,
		ACTION1,
		ACTION2
	};
	
	/**
	 * @brief Constructor for a specific action.
	 *
	 * @param action Action to perform if triggered.
	 **/
	ControlCallback( CCB_ACTION action );
	
	/**
	 * @brief Standard destructor.
	 **/
	virtual ~ControlCallback();
	
	/**
	 * @brief Set the bouncer to control through the callback.
	 *
	 * @param bouncer Bouncer to control.
	 **/
	void setBouncer( IBouncer *bouncer );
	
	virtual void onTrigger( pulsar::Value* val );
	
private:
	CCB_ACTION mAction;
	IBouncer* mBouncer;
};

#endif // CONTROLCALLBACK_H
