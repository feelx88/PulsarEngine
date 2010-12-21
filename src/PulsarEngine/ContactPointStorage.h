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

#ifndef __contactpointstorage__
#define __contactpointstorage__

#include "IObject.h"

namespace pulsar
{
	class DynamicEntity;

	class ContactPointStorage : public IObject
	{

		public:
			ContactPointStorage( DynamicEntity* pEntity );
			~ContactPointStorage();

			void addContactPoint( btRigidBody* pOtherBody, Vector posSelf, Vector posOther );

			bool contactWithOtherBody( btRigidBody* pBody );

			int countContactsWithBody( btRigidBody* pBody );

			Vector getContactPointSelf( btRigidBody* pOtherBody, int iIndex );
			Vector getContactPointOther( btRigidBody* pOtherBody, int iIndex );

			void clearContactPoints();

			DynamicEntity* getEntity()
			{
				return m_pEntity;
			}

		private:
			DynamicEntity *m_pEntity;
			btRigidBody* m_pBody;
			
			std::multimap<btRigidBody*, Vector*> m_mContactPoints;

	};
}

#endif // __contactpointstorage__
