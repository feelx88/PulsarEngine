#ifndef __entity__
#define __entity__

#include "../IObject.h"
#include "../ICallback.h"
#include "../ConfigStorage.h"
#include <irrlicht.h>

namespace pulsar
{

class EntityToolKit;

class Entity : public IObject, public btActionInterface
{

public:
	enum E_PULSARENTITYPRIMITIVE
	{
		EPEP_EMPTY = 0,
		EPEP_BOX,
		EPEP_SPHERE,
		EPEP_CONE,
		EPEP_CYLINDER
	};

	Entity( unsigned int iID = 0, Vector position = Vector(),
		Vector rotation = Vector() );
	virtual ~Entity();

	virtual void loadFromValues( ConfigStorage *pConf ) = 0;
	virtual void loadFromFile( String sFileName, String sNodeName = "" ) = 0;

	virtual void setPosition( Vector pos ) = 0;
	virtual Vector getPosition() = 0;

	virtual void setRotation( Vector rot ) = 0;
	virtual Vector getRotation() = 0;

	virtual irr::scene::ISceneNode *getSceneNode()
	{
		return 0;
	}

	virtual btCollisionObject *getCollisionObject()
	{
		return 0;
	}

	static Entity *getEntity( btCollisionObject *colObject );
	static Entity *getEntity( irr::scene::ISceneNode *sceneNode );

	ConfigStorage *getConfig()
	{
		return m_pConfig;
	}

	virtual bool isDynamic()
	{
		return false;
	}

	unsigned int getID()
	{
		return m_iID;
	}

	virtual void updateAction( btCollisionWorld *collisionWorld, btScalar deltaTimeStep ){};
	virtual void debugDraw( btIDebugDraw*){};

	static Vector convert( const btVector3 &in );
	static btVector3 convert( const Vector &in );

protected:

	irr::scene::ISceneManager *getSceneManager()
	{
		return getDevice()->getSceneManager();
	}

	irr::IrrlichtDevice *getDevice();
	btDynamicsWorld *getWorld();

	bool m_bSelfGeneratedConfig; //Used to avoid memory leaks
	ConfigStorage *m_pConfig;

	static btCollisionShape* getFromShapePool( String sName, Vector size = Vector() );

	static std::map<btCollisionObject*, Entity*> s_colEntityRelations;
	static std::map<irr::scene::ISceneNode*, Entity*> s_nodeEntityRelations;

	unsigned int m_iID;

private:
	static irr::IrrlichtDevice *s_pDevice;
	static btDynamicsWorld *s_pWorld;
	static std::map<String, btCollisionShape*> s_mShapePool;

	static EntityToolKit *s_pEntityToolKit;
};

}

#endif // __entity__
