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
