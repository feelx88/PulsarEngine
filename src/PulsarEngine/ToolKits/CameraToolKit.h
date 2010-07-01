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
