#ifndef __sensorentity__
#define __sensorentity__

#include "Entity.h" // Base class: pulsar::Entity
#include <set>

namespace pulsar
{

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

	void setCallback( ICallback *pCB )
	{
		m_Callback = pCB;
	}

protected:

	virtual void createSensor() = 0;
	ICallback *m_Callback;

	std::set<Entity*> m_TriggeringEntities;

};

}

#endif // __sensorentity__
