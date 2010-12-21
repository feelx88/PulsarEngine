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

#ifndef __graphicalentity__
#define __graphicalentity__

#include "Entity.h" // Base class: pulsar::Entity

namespace pulsar
{

/**
 * @class GraphicalEntity
 * @author Felix Müller
 * @date 31.05.2010
 * @file GraphicalEntity.h
 * @brief Class which represents a single graphical Object with no physical
 * properities, e.g. for skydomes or stationary particle systems.
 */
class GraphicalEntity : public Entity
{

public:
	GraphicalEntity( unsigned int iID = 0, Vector pos = Vector(), Vector rot = Vector() );
	~GraphicalEntity();

	virtual void loadFromValues( ConfigStorage *pConf );
	virtual void loadFromFile( String sFileName, String sNodeName = "" );

	virtual void loadSceneNodeFromFile( String sModelFileName );
	virtual void createSceneNodeFromPrimitive(
		E_PULSARENTITYPRIMITIVE primType, Vector size );

	virtual void setTexture( String sName ){};

	irr::scene::ISceneNode *getSceneNode()
	{
		return m_pSceneNode;
	}

	virtual void setPosition( Vector pos );
	virtual Vector getPosition();

	virtual void setRotation( Vector rot );
	virtual Vector getRotation();

	virtual Vector getDirection( Vector direction = Vector( 0.0f, 0.0f, 1.0f ) );

protected:

	void createSceneNode();

	irr::scene::ISceneNode *m_pSceneNode;

};

}

#endif // __graphicalentity__
