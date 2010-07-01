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
