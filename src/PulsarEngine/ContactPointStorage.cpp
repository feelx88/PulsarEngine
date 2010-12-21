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

#include "ContactPointStorage.h"
#include "Entities/DynamicEntity.h"
namespace pulsar
{

ContactPointStorage::ContactPointStorage( DynamicEntity *pEntity ) :
	IObject(), m_pEntity( pEntity ),
	m_pBody( dynamic_cast<btRigidBody*>( pEntity->getCollisionObject() ) )
{
}

ContactPointStorage::~ContactPointStorage()
{
	clearContactPoints();
}

void ContactPointStorage::addContactPoint( btRigidBody* pBody, Vector posA, Vector posB )
{
	Vector x[2] = { posA, posB };

	m_mContactPoints.insert( std::make_pair( pBody, x ) );
}

bool ContactPointStorage::contactWithOtherBody( btRigidBody *pBody )
{
	for( std::multimap<btRigidBody*, Vector*>::iterator x = m_mContactPoints.begin();
		x != m_mContactPoints.end(); x++ )
	{
		if( pBody == x->first )
			return true;
	}
	return false;
}

int ContactPointStorage::countContactsWithBody( btRigidBody* pBody )
{
	int count = 0;
	for( std::multimap<btRigidBody*, Vector*>::iterator x = m_mContactPoints.begin();
		x != m_mContactPoints.end(); x++ )
	{
		if( pBody == x->first )
			count++;
	}
	return count;
}

Vector ContactPointStorage::getContactPointSelf( btRigidBody* pBody, int iIndex )
{
	std::multimap<btRigidBody*, Vector*>::iterator x;
	for( x = m_mContactPoints.begin(); x != m_mContactPoints.end() && iIndex; x++ )
	{
		if( pBody == x->first )
			iIndex--;
	}

	return x->second[0];
}

Vector ContactPointStorage::getContactPointOther( btRigidBody* pBody, int iIndex )
{
	std::multimap<btRigidBody*, Vector*>::iterator x;
	for( x = m_mContactPoints.begin(); x != m_mContactPoints.end() && iIndex; x++ )
	{
		if( pBody == x->first )
			iIndex--;
	}

	return x->second[1];
}

void ContactPointStorage::clearContactPoints()
{
	m_mContactPoints.clear();
}

}
