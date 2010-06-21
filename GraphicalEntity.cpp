#include "GraphicalEntity.h"

#include "Irrlicht_using.h"

using namespace pulsar;

GraphicalEntity::GraphicalEntity( unsigned int iID, Vector pos, Vector rot )
	: Entity( iID, pos, rot ), m_pSceneNode( 0 )
{
	setClassName( "GraphicalEntity" );
}

GraphicalEntity::~GraphicalEntity()
{
	if( this->m_pSceneNode )
		this->m_pSceneNode->remove();
}

void GraphicalEntity::loadFromValues( ConfigStorage *pConf )
{
	Entity::loadFromValues( pConf );
	createSceneNode();
}

void GraphicalEntity::loadFromFile( String sFileName, String sNodeName )
{
	Entity::loadFromFile( sFileName, sNodeName );
	createSceneNode();
}

void GraphicalEntity::loadSceneNodeFromFile( String sModelFileName )
{
	m_pConfig->set<String>( "ModelFileName", sModelFileName );

	createSceneNode();
}

void GraphicalEntity::createSceneNodeFromPrimitive(
	E_PULSARENTITYPRIMITIVE primType, vector3df size )
{
	switch( primType ) //TODO: Add all primitives
	{
		case EPEP_BOX:
		{
			m_pConfig->set<String>( "Shape", "$Box" );
			break;
		}
		case EPEP_SPHERE:
		{
			m_pConfig->set<String>( "Shape", "$Sphere" );
			break;
		}
		default:
			return;
	}

	m_pConfig->set<Vector>( "Size", size );

	createSceneNode();
}


void GraphicalEntity::setPosition( vector3df pos )
{
	if( !m_pSceneNode )
		return;

	m_pSceneNode->setPosition( pos );
}

Vector GraphicalEntity::getPosition()
{
	if( !m_pSceneNode )
		return Vector();

	return m_pSceneNode->getPosition();
}

void GraphicalEntity::setRotation( vector3df rot )
{
	if( !m_pSceneNode )
		return;

	m_pSceneNode->setRotation( rot );
}

Vector GraphicalEntity::getRotation()
{
	if( !m_pSceneNode )
		return Vector();

	return m_pSceneNode->getRotation();
}

Vector GraphicalEntity::getDirection( vector3df direction )
{
	if( !m_pSceneNode )
		return direction;

	return m_pSceneNode->getRotation().rotationToDirection( direction );
}

void GraphicalEntity::createSceneNode()
{
	if( this->m_pSceneNode )
		this->m_pSceneNode->remove();

	String sPrimtive = m_pConfig->get<String>( "Shape", "" );

	//Primitive?
	if( sPrimtive != "" && !m_pConfig->varExists( "ModelFileName" ) )
	{
		if( sPrimtive == "$Box" )
			m_pSceneNode = getSceneManager()->addCubeSceneNode( 1.0f );
		else if( sPrimtive == "$Sphere" )
			m_pSceneNode = getSceneManager()->addSphereSceneNode( 1.0f, 64 );

		if( m_pSceneNode )
			m_pSceneNode->setScale( m_pConfig->get<Vector>( "Size", Vector( 1.0f ) ) );
	}
	else
	{
		m_pSceneNode = getSceneManager()->addAnimatedMeshSceneNode( getSceneManager()->getMesh(
			m_pConfig->get<String>( "ModelFileName", "" ) ) );
	}

	setPosition( m_pConfig->get<Vector>( "Position", Vector() ) );
	setRotation( m_pConfig->get<Vector>( "Rotation", Vector() ) );
}
