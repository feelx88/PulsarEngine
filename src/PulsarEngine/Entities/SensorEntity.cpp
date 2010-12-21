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

#include "SensorEntity.h"

using namespace pulsar;

SensorEntity::SensorEntity( unsigned int iID, Vector pos, Vector rot )
	: Entity( iID, pos, rot ), m_Callback( 0 )
{
}

void SensorEntity::loadFromFile( String sFileName, String sNodeName )
{
	Entity::loadFromFile( sFileName, sNodeName );
	createSensor();
}

void SensorEntity::loadFromValues( ConfigStorage* pConf )
{
	Entity::loadFromValues( pConf );
	createSensor();
}
