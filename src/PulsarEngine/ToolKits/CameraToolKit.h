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

#ifndef __cameratoolkit__
#define __cameratoolkit__

#include "IToolKit.h" // Base class: pulsar::IToolKit
#include "../Entities/Entity.h"

namespace pulsar
{

class CameraToolKit : public pulsar::IToolKit
{

public:
	CameraToolKit();
	virtual ~CameraToolKit();

	/**
	 * @brief Initializes the ToolKit.
	 * @param initParam Not used.
	 */
	virtual void init( Value initParam );

	/**
	 * @brief Updates the position of the cameras if they are attached to an
	 * Entity.
	 */
	virtual void tickUpdate();

	/**
	 * @brief Get the ToolKit's name.
	 *
	 * @return String containing "Camera".
	 **/
	virtual String getToolKitClassName();
	
	/**
	 * @brief Adds an existing ICameraSceneNode to the ToolKit.
	 * @param iID ID of the camera.
	 * @param pCam Pointer to the ICameraSceneNode.
	 */
	void addCamera( unsigned int iID, irr::scene::ICameraSceneNode* pCam );

	/**
	 * @brief Add a new camera to the ToolKit.
	 * @param iID ID of the camera.
	 */
	void addCamera( unsigned int iID );

	/**
	 * @brief Get an ICameraSceneNode stored in the ToolKit.
	 * @param iID ID of the camera.
	 * @return The ICameraSceneNode if exists, 0 otherwise.
	 */
	irr::scene::ICameraSceneNode *getCamera( unsigned int iID );

	void setCameraPosition( unsigned int iID, Vector position );

	void setCameraTarget( unsigned int iID, Vector target );

	void setCameraUpVector( unsigned int iID, Vector up );

private:

	irr::scene::ISceneManager *m_pSceneManager;

	std::map<unsigned int, irr::scene::ICameraSceneNode*> m_mCameras;
	std::map<unsigned int, Entity*> m_mAttachedEntities;
};

}

#endif // __cameratoolkit__
