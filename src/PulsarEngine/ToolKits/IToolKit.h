 /*
    Copyright 2010 Felix Müller

    This file is part of the PulsarEngine.

    The PulsarEngine is free software: you can redistribute it and/or modify
    it under the terms of the Lesser GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The PulsarEngine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    Lesser GNU General Public License for more details.

    You should have received a copy of the Lesser GNU General Public License
    along with the PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	 * @brief This method returns the name of the ToolKit.
	 * This name is used internally in the engine to save its ToolKits.
	 * @sa PulsarEngine::getToolKit
	 *
	 **/
	virtual String getToolKitClassName() = 0;

	/**
	 * @brief Initialization method.
	 * @param initParam If needed, an additional parameter can be passed 
	 * packed in this Value.
	 */
	virtual void init( Value initParam ) = 0;

	/**
	 * @brief Update method for toolkits which need to do something regularly.
	 * This method is called at the end of every PulsarEngine::beginDrawing().
	 */
	virtual void update(){};

	/**
	 * @brief Update method for something that has to be updated every 
	 * internal tick of the physics Engine.
	 */
	virtual void tickUpdate(){};

};

}

#endif // __itoolkit__
