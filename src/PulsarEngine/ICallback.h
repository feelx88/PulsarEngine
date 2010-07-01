#ifndef __icallback__
#define __icallback__

namespace pulsar
{

class Entity;

/**
 * @class ICallback
 * @author Felix Müller
 * @date 09.06.2010
 * @file ICallback.h
 * @brief Generic Callback Interface.
 */
struct ICallback
{
	/**
	 * @brief This method gets called if an Entity activates the sensor.
	 * @param pE The triggering Entity.
	 */
	virtual void onTrigger( Entity *pE ) = 0;
};

}

#endif //__icallback__
