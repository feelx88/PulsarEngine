#ifndef __itoolkit__
#define __itoolkit__

#include "../IObject.h" // Base class: pulsar::IObject
#include "../ValueFactory.h"

namespace pulsar
{

/**
 * @class IToolKit
 * @author Felix Müller
 * @date 29.04.2010
 * @file IToolKit.h
 * @brief Base class for toolkits
 */
class IToolKit : public pulsar::IObject
{
	public:

	/**
	 * @brief Standard constructor.
	 */
	IToolKit(){};

	/**
	 * @brief Standard destructor.
	 */
	virtual ~IToolKit(){};

	/**
	 * @brief Initialization method.
	 * @param initParam If needed, an additional parameter can be passed packed
	 * in this Value.
	 */
	virtual void init( Value initParam ) = 0;

	/**
	 * @brief Update method for toolkits which need to do something regularly.
	 * This method is called at the end of every PulsarEngine::beginDrawing().
	 */
	virtual void update(){};

	/**
	 * @brief Update method for something that has to be updated every internal
	 * tick of the physics Engine.
	 */
	virtual void tickUpdate(){};

};

}

#endif // __itoolkit__
