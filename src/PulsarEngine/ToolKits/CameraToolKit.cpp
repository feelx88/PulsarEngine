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

String CameraToolKit::getToolKitClassName()
{
	return typeid( *this ).name();
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
