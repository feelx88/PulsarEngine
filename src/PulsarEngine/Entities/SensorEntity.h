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
    along with The PulsarEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

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

	virtual void loadFromFile( String sFileName, String sNodeName = "" );
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
