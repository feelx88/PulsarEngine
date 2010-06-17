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
