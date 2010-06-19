#include "Entity.h"
#include "PulsarEngine.h"
#include "EntityToolKit.h"

using namespace pulsar;

#include "Irrlicht_using.h"

IrrlichtDevice *Entity::s_pDevice = 0;
btDynamicsWorld *Entity::s_pWorld = 0;
EntityToolKit *Entity::s_pEntityToolKit = 0;

std::map<String, btCollisionShape*> Entity::s_mShapePool;

std::map<btCollisionObject*, Entity*> Entity::s_colEntityRelations;
std::map<ISceneNode*, Entity*> Entity::s_nodeEntityRelations;

Entity::Entity( unsigned int iID, Vector position, Vector rotation )
	: IObject(), m_iID( 0 )
{
	setClassName( "Entity" );
	m_pConfig = new ConfigStorage();
	m_pConfig->setCopy<Vector>( "Position", position );
	m_pConfig->setCopy<Vector>( "Rotation", rotation );

	getWorld()->addAction( this );

	if( !this->s_pEntityToolKit )
		this->s_pEntityToolKit = dynamic_cast<EntityToolKit*>(
			PulsarEngine::getInstance()->getToolKit( "Entity" ) );

	this->m_iID = this->s_pEntityToolKit->addEntity( iID, this );
}

Entity::~Entity()
{
	this->getWorld()->removeAction( this );
	delete this->m_pConfig;
	this->s_pEntityToolKit->deleteEntity( this->m_iID );
}

void Entity::loadFromValues( ConfigStorage *pConf )
{
	this->m_pConfig->append( pConf );
}

void Entity::loadFromFile( String sFileName, String sNodeName )
{
	m_pConfig->parseXMLFile( sFileName, sNodeName );
}

Entity *Entity::getEntity( btCollisionObject *colObject )
{
	return s_colEntityRelations[colObject];
}

Entity *Entity::getEntity( ISceneNode *sceneNode )
{
	return s_nodeEntityRelations[sceneNode];
}

vector3df Entity::convert( btVector3 in )
{
	return vector3df( in.getX(), in.getY(), in.getZ() );
}

btVector3 Entity::convert( vector3df in )
{
	return btVector3( in.X, in.Y, in.Z );
}

IrrlichtDevice *Entity::getDevice()
{
	if( !this->s_pDevice )
		this->s_pDevice = PulsarEngine::getInstance()->getIrrlichtDevice();

	return this->s_pDevice;
}

btDynamicsWorld *Entity::getWorld()
{
	if( !this->s_pWorld )
		this->s_pWorld = PulsarEngine::getInstance()->getBulletWorld();

	return this->s_pWorld;
}

btCollisionShape* Entity::getFromShapePool( String sName, Vector size )
{
	String poolString =
		sName + ":" +
		String( size.X ) + ";" +
		String( size.Y ) + ";" +
		String( size.Z );
	btCollisionShape *shape = s_mShapePool[poolString];

	if( shape )
	{
		std::cout << "Getting from ShapePool: " << poolString << std::endl;
		return shape;
	}

	if( sName == "$Sphere" )
		shape = new btSphereShape( size.X );
	else if( sName == "$Box" )
		shape = new btBoxShape( convert( size / 2 ) );
	else if( sName == "$Cone" )
		shape = new btConeShape( size.X, size.Y );
	else if( sName == "$Cylinder" )
		shape = new btCylinderShape( convert( size/2 ) );
	else if( sName == "$Capsule" )
		shape = new btCapsuleShape( size.X, size.Y );
	else
		shape = new btSphereShape( 1 );

	s_mShapePool[poolString] = shape;

	std::cout << "Adding to ShapePool: " << poolString << std::endl;

	return shape;
}
