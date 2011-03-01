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

#include "EntityToolKit.h"
#include "../PulsarEngine.h"
#include "../Irrlicht_using.h"

namespace pulsar
{

EntityToolKit::EntityToolKit() : IToolKit()
{
	setClassName( "EntityToolKit" );
	setName( "Entity" );
}

EntityToolKit::~EntityToolKit()
{
}

String EntityToolKit::getToolKitClassName()
{
	return typeid( *this ).name();
}

void EntityToolKit::init( Value initParam )
{
	this->m_pBulletWorld = PulsarEngine::getInstance()->getBulletWorld();
	this->m_pSceneManager =
		PulsarEngine::getInstance()->getIrrlichtDevice()->getSceneManager();
}

void EntityToolKit::tickUpdate()
{
	int collisionPairCount = mCollisionPairs.size();

	if( collisionPairCount == 0 )
		return;
	
	for ( int x = 0; x < m_pBulletWorld->getDispatcher()->getNumManifolds(); x++)
	{
		btPersistentManifold* manifold =
			m_pBulletWorld->getDispatcher()->getManifoldByIndexInternal( x );

		btCollisionObject *ob0 =
			static_cast<btCollisionObject*>( manifold->getBody0() );
		btCollisionObject *ob1 =
			static_cast<btCollisionObject*>( manifold->getBody1() );

		for( int x = 0; x < collisionPairCount; x++ )
		{
			CollisionPairCallbackStorage *storage = mCollisionPairs.at( x );
			if( ( storage->mObject0 == ob0 && storage->mObject1 == ob1 ) ||
				( storage->mObject0 == ob1 && storage->mObject1 == ob0 ) )
				storage->mCallback->onTrigger( new Value( manifold, "btPersistentManifold" ) );
		}
	}
}

unsigned int EntityToolKit::addEntity( Entity *pEntity )
{
	unsigned int iID  = 1;
	//If the map is not empty, get the highest id +1 for the Entity
	if( !this->m_mEntities.empty() )
	{
		std::map<unsigned int, Entity*>::iterator x = this->m_mEntities.end();
		x--;
		iID = x->first;
		iID++;
	}

	this->m_mEntities[iID] = pEntity;
	return iID;
}

unsigned int EntityToolKit::addEntity( unsigned int iID, Entity *pEntity )
{
	//If id is 0 (auto assign) or an Entity with this id already exists,
	//generate a new id and return it
	if( iID == 0 || this->m_mEntities[iID] )
		return addEntity( pEntity );

	//otherwise add the Entity and return the chosen id
	this->m_mEntities[iID] = pEntity;
	return iID;
}

void EntityToolKit::deleteEntity( unsigned int iID )
{
	this->m_mEntities.erase( iID );
}

Entity *pulsar::EntityToolKit::getEntity( unsigned int iID )
{
	return this->m_mEntities[iID];
}

CollisionPairCallbackStorage* EntityToolKit::addCollisionCallback( Entity* entity0,
	Entity* entity1, ICallback* callback )
{
	btCollisionObject *ob0 = entity0->getCollisionObject();
	btCollisionObject *ob1 = entity1->getCollisionObject();
	
	CollisionPairCallbackStorage *storage =
		new CollisionPairCallbackStorage( ob0, ob1, callback );

	mCollisionPairs.push_back( storage );

	return storage;
}

void EntityToolKit::removeCollisionCallback( CollisionPairCallbackStorage* callbackStorage )
{
	for( int x = 0; x < mCollisionPairs.size(); x++ )
	{
		if( mCollisionPairs.at( x ) == callbackStorage )
			mCollisionPairs.erase( mCollisionPairs.begin() + x );
	}
}


bool EntityToolKit::rayHitsEntity( Entity* pE, Vector from, Vector to )
{
	if( pE->isDynamic() )
	{
		btCollisionWorld::ClosestRayResultCallback callback( Entity::convert( from ), Entity::convert( to ) );
		m_pBulletWorld->rayTest( Entity::convert( from ), Entity::convert( to ), callback );
		if( callback.hasHit() && callback.m_collisionObject ==  pE->getCollisionObject() )
			return true;
	}
	else
	{
		Vector vtmp;
		irr::core::triangle3df ttmp;
		//TODO: re-add
		/*if( m_pSceneManager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay( line3df( from, to ), vtmp, ttmp )
			== pE->getSceneNode() )*/
			return true;
	}
	return false;
}

Entity* EntityToolKit::getEntityInRay( Vector from, Vector to )
{
	//TODO: search for userdata pointer in irrlicht scene nodes
	return 0;
}

DynamicEntity* EntityToolKit::getDynamicEntityInRay( Vector from, Vector to )
{
	//Entity* pE = 0;
	btCollisionWorld::ClosestRayResultCallback callback( Entity::convert( from ), Entity::convert( to ) );
	m_pBulletWorld->rayTest( Entity::convert( from ), Entity::convert( to ), callback );
	if( callback.hasHit() )
		return static_cast<ContactPointStorage*>( callback.m_collisionObject->getUserPointer() )->getEntity();
	return 0;
}

}
