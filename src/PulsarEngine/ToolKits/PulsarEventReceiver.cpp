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

#include "PulsarEventReceiver.h"
#include "../Irrlicht_using.h"
#include "../PulsarEngine.h"

namespace pulsar
{

PulsarEventReceiver::PulsarEventReceiver()
{
	setClassName( "PulsarEventReceiver" );
	setName( "EventReceiver" );
	
	//clear key codes
	for ( int x = 0; x < KEY_KEY_CODES_COUNT; x++ )
		m_bKeyStates[x] = false;

	this->m_iMouseMoveX = this->m_iMouseMoveY = this->m_iMouseWheelDelta = 0;
	this->m_iMouseX = this->m_iMouseY = this->m_iMouseButtonStates = 0;
}

PulsarEventReceiver::~PulsarEventReceiver()
{
}

String PulsarEventReceiver::getToolKitClassName()
{
	return typeid( *this ).name();
}

void PulsarEventReceiver::init( Value initParam )
{
	PulsarEngine *pEngine = PulsarEngine::getInstance();
	this->m_pDevice = pEngine->getIrrlichtDevice();
	this->m_pGUI = this->m_pDevice->getGUIEnvironment();
	this->m_pScriptToolKit = pEngine->getToolKit<ScriptToolKit>();

	this->m_iScreenWidth = pEngine->getScreenWidth();
	this->m_iScreenHeight = pEngine->getScreenHeight();

	this->m_pConsoleWindow = pEngine->getConsoleWindow();

	list<IGUIElement*> childList = this->m_pConsoleWindow->getChildren();
	for( list<IGUIElement*>::Iterator x = childList.begin();
		x != childList.end(); x++ )
	{
		switch( static_cast<IGUIElement*>( *x )->getType() )
		{
			case EGUIET_BUTTON:
			{
				this->m_pConsoleSendButton = static_cast<IGUIButton*>( *x );
				break;
			}

			case EGUIET_EDIT_BOX:
			{
				this->m_pConsoleInput = static_cast<IGUIEditBox*>( *x );
				break;
			}

			case EGUIET_LIST_BOX:
			{
				this->m_pConsoleOutput = static_cast<IGUIListBox*>( *x );
				break;
			}

			default:
				break;
		}
	}

}

bool PulsarEventReceiver::keyState( irr::EKEY_CODE key )
{
	if ( key > 0 && key < KEY_KEY_CODES_COUNT )
		return m_bKeyStates[key];

	return false;
}

int PulsarEventReceiver::getMouseX()
{
	return m_iMouseX;
}

int PulsarEventReceiver::getMouseY()
{
	return m_iMouseY;
}

int PulsarEventReceiver::getMouseMoveX()
{
	return m_iMouseMoveX;
}

int PulsarEventReceiver::getMouseMoveY()
{
	return m_iMouseMoveY;
}

bool PulsarEventReceiver::getMouseButtonState( int iButton )
{
	return m_iMouseButtonStates &= ( 1 << iButton );
}

int PulsarEventReceiver::getMouseWheelDelta()
{
	return m_iMouseWheelDelta;
}

void PulsarEventReceiver::showMouse( bool bShow )
{
	m_pDevice->getCursorControl()->setVisible( bShow );
}

void PulsarEventReceiver::setMousePosition( int iX, int iY )
{
	m_pDevice->getCursorControl()->setPosition( iX, iY );
}

void PulsarEventReceiver::lockMouse( bool bLock )
{
	//setMousePosition( 50, 50 );
	m_bMouseLocked = bLock;
	/*if( bLock )
	{
		m_iMouseX = m_iOldMouseX = 50;
		m_iMouseY = m_iOldMouseY = 50;
	}*/
}

void PulsarEventReceiver::addKeyPressedCallback( irr::EKEY_CODE key, ICallback *cb )
{
	m_Callbacks.insert( std::make_pair( key, cb ) );
}

void PulsarEventReceiver::clearKeyPressedCallbacks( irr::EKEY_CODE key )
{
	m_Callbacks.erase( key );
}

bool PulsarEventReceiver::OnEvent( const SEvent &evt )
{
	if ( evt.EventType == EET_KEY_INPUT_EVENT )
	{
		m_bKeyStates[evt.KeyInput.Key] = evt.KeyInput.PressedDown;

		if ( m_pGUI->getFocus() == m_pConsoleInput )
		{
			if ( evt.KeyInput.Key == KEY_RETURN && !evt.KeyInput.PressedDown && String( m_pConsoleInput->getText() ).size() )
			{
				if ( String( m_pConsoleInput->getText() ) == "exit" )
					exit( 0 );

				this->m_pScriptToolKit->
					executeString( String( m_pConsoleInput->getText() ) );

				PulsarEngine::getInstance()->log( String( m_pConsoleInput->getText() ) );

				m_pConsoleInput->setText( L"" );

				m_iCurOutputLine = -1;
			} //ConsoleInput

			if ( evt.KeyInput.Key == KEY_UP && !evt.KeyInput.PressedDown )
				m_pConsoleInput->setText( m_pConsoleOutput->getListItem( --m_iCurOutputLine ) );

			if ( evt.KeyInput.Key == KEY_DOWN && !evt.KeyInput.PressedDown )
				m_pConsoleInput->setText( m_pConsoleOutput->getListItem( ++m_iCurOutputLine ) );

			if ( m_iCurOutputLine <= 0 )
				m_iCurOutputLine = 0;

			if ( m_iCurOutputLine >= m_pConsoleOutput->getItemCount() )
				m_iCurOutputLine = m_pConsoleOutput->getItemCount();
		}
	} //EET_INPUT_EVENT

	if( evt.EventType == EET_MOUSE_INPUT_EVENT )
	{
		if( !m_bMouseLocked )
		{
			m_iOldMouseX = m_iMouseX;
			m_iOldMouseY = m_iMouseY;
			m_iMouseX = evt.MouseInput.X;
			m_iMouseY = evt.MouseInput.Y;
			m_iMouseMoveX = m_iMouseX - m_iOldMouseX;
			m_iMouseMoveY = m_iMouseY - m_iOldMouseY;
		}
		else
		{
			m_iOldMouseX = m_iMouseX;
			m_iOldMouseY = m_iMouseY;
			m_iMouseX = evt.MouseInput.X;
			m_iMouseY = evt.MouseInput.Y;
			m_iMouseMoveX = evt.MouseInput.X - m_iScreenWidth / 2;
			m_iMouseMoveY = evt.MouseInput.Y - m_iScreenHeight / 2;
			if( m_iMouseX != m_iScreenWidth / 2 && m_iMouseX != m_iScreenHeight / 2 )
			{
				setMousePosition( m_iScreenWidth / 2, m_iScreenHeight / 2 );
			}
		}
		m_iMouseWheelDelta = evt.MouseInput.Wheel;
		m_iMouseButtonStates = evt.MouseInput.ButtonStates;
	} //EET_MOUSE_INPUT_EVENT

	if ( evt.EventType == EET_GUI_EVENT )
	{
		if ( evt.GUIEvent.Caller == m_pConsoleOutput && evt.GUIEvent.EventType == EGET_LISTBOX_CHANGED )
		{
			m_pConsoleInput->setText( m_pConsoleOutput->getListItem( m_pConsoleOutput->getSelected() ) );
			m_pConsoleOutput->setSelected( -1 );
		} // ConsoleOutput

		if ( evt.GUIEvent.Caller == m_pConsoleSendButton && evt.GUIEvent.EventType == EGET_BUTTON_CLICKED
			&& String( m_pConsoleInput->getText() ).size() )
		{
			if ( String( m_pConsoleInput->getText() ) == "exit" )
				exit( 0 );

			this->m_pScriptToolKit->
				executeString( String( m_pConsoleInput->getText() ) );

			PulsarEngine::getInstance()->log( String( m_pConsoleInput->getText() ) );

			m_pConsoleInput->setText( L"" );

			m_iCurOutputLine = -1;
		} //ConsoleSendButton
	} //EET_GUI_EVENT

	return false;
}

void PulsarEventReceiver::callCallbacks()
{
	for( int x = 0; x < irr::KEY_KEY_CODES_COUNT; x++ )
	{
		if( m_bKeyStates[(EKEY_CODE)x] )
		{
			//Process the Callbacks
			std::pair<std::multimap<irr::EKEY_CODE, ICallback*>::iterator,
				std::multimap<irr::EKEY_CODE, ICallback*>::iterator> keyCB
				= m_Callbacks.equal_range( (EKEY_CODE)x );

			if( keyCB.first != m_Callbacks.end() )
			{
				for( std::multimap<irr::EKEY_CODE, ICallback*>::iterator cur = keyCB.first;
					cur != keyCB.second; cur++ )
					(*cur).second->onTrigger( 0 );
			}
		}
	}
}

}
