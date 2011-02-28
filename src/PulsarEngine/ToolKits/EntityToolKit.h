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

#ifndef __EntityToolKit__
#define __EntityToolKit__

#include "IToolKit.h" // Base class: pulsar::IToolKit
#include "../Entities/Entity.h"
#include "../Entities/DynamicEntity.h"
#include "../ValueFactory.h"
#include "../StandardConverters.h"

#include <deque>
#include <utility>

namespace pulsar
{

/**
 * @struct CollisionPairCallbackStorage
 * @author Felix Müller
 * @date 27.02.2011
 * @file EntityToolkit.h
 * @brief Struct to save Collision pairs and their callbacks.
**/
struct CollisionPairCallbackStorage
{
	CollisionPairCallbackStorage( btCollisionObject *ob0, btCollisionObject *ob1, ICallback *cb )
		: mObject0( ob0 ), mObject1( ob1 ), mCallback( cb ){};
		
	btCollisionObject *mObject0;
	btCollisionObject *mObject1;
	ICallback *mCallback;
};

/**
 * @class EntityToolKit
 * @author Felix Müller
 * @date 04.05.2010
 * @file EntityToolKit.h
 * @brief Toolkit which manages adding, removing and manipulation of Entitys.
 */
class EntityToolKit : public pulsar::IToolKit
{

public:

	/**
	 * @brief Standard Constructor.
	 */
	EntityToolKit();

	/**
	 * @brief Standard destructor.
	 */
	virtual ~EntityToolKit();

	/**
	 * @brief Get the ToolKit's name.
	 *
	 * @return String containing "Entity".
	 **/
	virtual String getToolKitClassName();
	
	/**
	 * @brief Initializes the toolkit.
	 * @param initParam Not used.
	 */
	void init( Value initParam );

	virtual void tickUpdate();

	unsigned int createEntity( ConfigStorage *pData );

	void createEntity( unsigned int iID, ConfigStorage *pData );

	/**
	 * @brief Add an Entity to the toolkit.
	 * @param pEntity Entity to be added.
	 * @return ID of the newly created Entity.
	 */
	unsigned int addEntity( Entity *pEntity );

	/**
	 * @brief Add an Entity to the toolkit.
	 * @param iID ID of the Entity.
	 * @param pEntity Entity to be added.
	 */
	unsigned int addEntity( unsigned int iID, Entity *pEntity );

	/**
	 * @brief Delete the Entity with the given ID.
	 * @param iID ID of the Entity.
	 */
	void deleteEntity( unsigned int iID );

	/**
	 * @brief Get the Entity with the given ID.
	 * @param iID ID of the Entity.
	 * @return The Entity with the given ID, or 0 if it does not exist.
	 */
	Entity *getEntity( unsigned int iID );

	/**
	 * @brief Get the total number of Entities.
	 * @return The total number of Entities.
	 */
	int getNumEntities()
	{
		return m_mEntities.size();
	}

	/**
	 * @brief Add a collision callback.
	 * Its onTrigger-method gets called if entity0 and entity1 are in contact
	 * with each other. The parameter of the onTrigger method is the
	 * btPersistentManifold of the collision.
	 *
	 * @param entity0 First Entity to test for contact.
	 * @param entity1 Second Entity to test for contact.
	 * @param callback Collision callback.
	 * @return Pointer to the created CollisionPairCallbackStorage, can be
	 * used to remove the callback.
	**/
	CollisionPairCallbackStorage *addCollisionCallback( Entity *entity0,
		Entity *entity1, ICallback *callback );

	/**
	 * @brief Remove the given Callback.
	 *
	 * @param callbackStorage Callback to remove.
	 **/
	void removeCollisionCallback( CollisionPairCallbackStorage *callbackStorage );

	/**
	 * @brief Test if the ray with the specified endpoints hits the specified
	 * Entity.
	 * @param pEntity Entity to test for.
	 * @param from Start point of the ray.
	 * @param to End point of the ray.
	 * @return True if the Entity got hit, false otherwise.
	 */
	bool rayHitsEntity( Entity* pEntity, Vector from, Vector to );

	Entity* getEntityInRay( Vector from, Vector to ); //TODO:

	/**
	 * @brief Get the first DynamicEntity in the ray with the specified end
	 * points.
	 * @param from Start point of the ray.
	 * @param to End point of the ray.
	 * @return A pointer to the DynamicEntity which got hit, 0 if nothing was
	 * hit.
	 */
	DynamicEntity* getDynamicEntityInRay( Vector from, Vector to );

protected:

	std::map<unsigned int, Entity*> m_mEntities;
	btDynamicsWorld *m_pBulletWorld;
	irr::scene::ISceneManager *m_pSceneManager;

	std::vector<CollisionPairCallbackStorage*> mCollisionPairs;
};

}

#endif // __EntityToolKit__
