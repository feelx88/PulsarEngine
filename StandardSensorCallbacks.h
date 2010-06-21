#ifndef __standardsensorcallbacks__
#define __standardsensorcallbacks__

#include "SensorEntity.h"

namespace pulsar
{

namespace StandardSensorCallbacks
{

struct ApplyImpulseSensorCallback : public SensorCallback
{
	ApplyImpulseSensorCallback( Vector direction, Vector offset = Vector() )
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
};

}

#endif // __standardsensorcallbacks__
