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

#ifndef __icallback__
#define __icallback__

#include "IObject.h"

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
