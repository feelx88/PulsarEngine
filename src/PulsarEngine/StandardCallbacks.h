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

	void onTrigger( Entity* entity )
	{
		DynamicEntity *dyn = dynamic_cast<DynamicEntity*>( entity );
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
