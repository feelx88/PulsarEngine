#ifndef __sensorentity__
#define __sensorentity__

#include "Entity.h" // Base class: pulsar::Entity
#include <set>

namespace pulsar
{

/**
 * @class SensorCallback
 * @author Felix Müller
 * @date 09.06.2010
 * @file SensorEntity.h
 * @brief Callback class for SensorEntities.
 */
struct SensorCallback
{
	/**
	 * @brief This method gets called if an Entity activates the sensor.
	 * @param pE The triggering Entity.
	 */
	virtual void onTrigger( Entity *pE ) = 0;
};

class SensorEntity : public pulsar::Entity
{

public:

	SensorEntity( unsigned int iID = 0, Vector pos = Vector(), Vector rot = Vector() );

	virtual bool isDynamic()
	{
		return false;
	}

	virtual void loadFromFile( String sFileName, String sNodeName );
	virtual void loadFromValues( ConfigStorage* pConf );

	virtual bool isEntityTriggering( Entity *pE ) = 0;

	void setCallback( SensorCallback *pCB )
	{
		m_Callback = pCB;
	}

protected:

	virtual void createSensor() = 0;
	SensorCallback *m_Callback;

	std::set<Entity*> m_TriggeringEntities;

};

}

#endif // __sensorentity__
