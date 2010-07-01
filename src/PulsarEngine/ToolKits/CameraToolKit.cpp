#include "CameraToolKit.h"
#include "../PulsarEngine.h"
#include "../Irrlicht_using.h"

namespace pulsar
{

CameraToolKit::CameraToolKit() : IToolKit()
{
	setClassName( "CameraToolKit" );
}

CameraToolKit::~CameraToolKit()
{
}

void CameraToolKit::init( Value initParam )
{
	PulsarEngine *pEngine = PulsarEngine::getInstance();
	this->m_pSceneManager = pEngine->getIrrlichtDevice()->getSceneManager();
}

void CameraToolKit::tickUpdate()
{
}

void pulsar::CameraToolKit::addCamera( unsigned int iID )
{
	if( !getCamera( iID ) )
		this->m_mCameras[iID] = this->m_pSceneManager->addCameraSceneNode();
}

void pulsar::CameraToolKit::addCamera( unsigned int iID, irr::scene::ICameraSceneNode* pCam )
{
	if( !getCamera( iID ) )
		this->m_mCameras[iID] = pCam;
}

irr::scene::ICameraSceneNode *pulsar::CameraToolKit::getCamera( unsigned int iID )
{
	return this->m_mCameras[iID];
}

void CameraToolKit::setCameraPosition( unsigned int iID, vector3df position )
{
	ICameraSceneNode *pCamera = getCamera( iID );

	if ( pCamera )
		pCamera->setPosition( position );
}

void CameraToolKit::setCameraTarget( unsigned int iID, vector3df target )
{
	ICameraSceneNode *pCamera = getCamera( iID );

	if ( pCamera )
		pCamera->setTarget( target );
}

void CameraToolKit::setCameraUpVector( unsigned int iID, Vector up )
{
	ICameraSceneNode *pCamera = getCamera( iID );

	if ( pCamera )
		pCamera->setUpVector( up );
}

}
