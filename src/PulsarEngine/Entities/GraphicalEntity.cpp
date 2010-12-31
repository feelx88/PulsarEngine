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

#include "GraphicalEntity.h"

#include "../Irrlicht_using.h"

#include "../PulsarEngine.h"

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
			m_pConfig->set<String>( "Shape", "$Box" );
			break;
		case EPEP_SPHERE:
			m_pConfig->set<String>( "Shape", "$Sphere" );
			break;
		case EPEP_EMPTY:
			m_pConfig->set<String>( "Shape", "$Empty" );
			break;
		
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

	int parentID = m_pConfig->get<int>( "Parent", 0 );
	ISceneNode *parent = 0;

	if( parentID )
	{
		GraphicalEntity *e = dynamic_cast<GraphicalEntity*> (
			PulsarEngine::getInstance()->getToolKit<EntityToolKit>()
			->getEntity( parentID ) );
		if( e )
			parent = e->getSceneNode();
	}

	//Primitive?
	if( sPrimtive != "" && !m_pConfig->varExists( "ModelFileName" ) )
	{
		IAnimatedMesh *mesh = 0;
		if( sPrimtive == "$Box" )
			 mesh = new SAnimatedMesh( getSceneManager()->
				getGeometryCreator()->createCubeMesh(
				m_pConfig->get<Vector>( "Size", Vector( 1.0f ) ) ) );
		else if( sPrimtive == "$Sphere" )
			mesh = new SAnimatedMesh( getSceneManager()->
				getGeometryCreator()->createSphereMesh(
				m_pConfig->get<Vector>( "Size", Vector( 1.0f ) ).X ));
		else if( sPrimtive == "$Empty" )
			m_pSceneNode = getSceneManager()->addDummyTransformationSceneNode();

		if( mesh )
			m_pSceneNode = getSceneManager()->addAnimatedMeshSceneNode( mesh );
	}
	else
	{
		m_pSceneNode = getSceneManager()->addAnimatedMeshSceneNode( getSceneManager()->getMesh(
			m_pConfig->get<String>( "ModelFileName", "" ) ) );
	}

	if( m_pSceneNode )
	{
		if( parent )
			m_pSceneNode->setParent( parent );

		if( m_pConfig->get<bool>( "CastShadows", false ) && sPrimtive != "$Empty" )
		{
			IAnimatedMeshSceneNode *node =
				static_cast<IAnimatedMeshSceneNode*>( m_pSceneNode );
				
			if( node )
				node->addShadowVolumeSceneNode();
		}

		m_pSceneNode->setScale( m_pConfig->get<Vector>( "Scale", Vector( 1.0f ) ) );
	}
	
	setPosition( m_pConfig->get<Vector>( "Position", Vector() ) );
	setRotation( m_pConfig->get<Vector>( "Rotation", Vector() ) );
}
