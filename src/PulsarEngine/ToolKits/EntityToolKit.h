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

#ifndef __EntityToolKit__
#define __EntityToolKit__

#include "IToolKit.h" // Base class: pulsar::IToolKit
#include "../Entities/Entity.h"
#include "../Entities/DynamicEntity.h"
#include "../ValueFactory.h"
#include "../StandardConverters.h"

namespace pulsar
{

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
};

}

#endif // __EntityToolKit__
