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

#ifndef __standardcallbacks__
#define __standardcallbacks__

#include "ICallback.h"

namespace pulsar
{

namespace StandardCallbacks
{

struct ApplyImpulseCallback : public ICallback
{
	ApplyImpulseCallback( Vector direction, Vector offset = Vector() )
		: m_Direction( direction ), m_Offset( offset )
	{
	}

	void onTrigger( Value *val )
	{
		DynamicEntity *dyn = val->getAs<DynamicEntity*>();
		if( dyn )
		{
			dyn->applyImpulse( m_Direction, m_Offset );
		}
	}

protected:
	Vector m_Direction, m_Offset;
};

}

}

#endif // __standardcallbacks__
