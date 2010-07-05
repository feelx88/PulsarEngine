#ifndef __icallback__
#define __icallback__

namespace pulsar
{

class Value;

/**
 * @class ICallback
 * @author Felix Müller
 * @date 09.06.2010
 * @file ICallback.h
 * @brief Generic Callback Interface.
 */
struct ICallback : public IObject
{
	/**
	 * @brief This method gets called if an Entity activates the sensor.
	 * @param val Value which can hold needed parameters
	 */
	virtual void onTrigger( Value *val ) = 0;

	virtual ~ICallback(){};
};

}

#endif //__icallback__
