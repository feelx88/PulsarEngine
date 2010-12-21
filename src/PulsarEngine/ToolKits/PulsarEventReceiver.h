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

#ifndef __pulsareventreceiver__
#define __pulsareventreceiver__

#include <IEventReceiver.h> // Base class: irr::IEventReceiver
#include "IToolKit.h"
#include "ScriptToolKit.h"
#include "../ICallback.h"

namespace pulsar
{

class PulsarEventReceiver : public irr::IEventReceiver, public IToolKit
{

public:

	/**
	 * @brief Standard constructor.
	 */
	PulsarEventReceiver();

	/**
	 * @brief Standard destructor.
	 */
	~PulsarEventReceiver();

	/**
	 * @brief Get the ToolKit's name.
	 *
	 * @return String containing "EventReceiver".
	 **/
	virtual String getToolKitClassName();
	
	/**
	 * @brief Initialization method.
	 * @param initParam Not used.
	 */
	void init( Value initParam );

	/**
	 * @brief Get the current state of the selected key.
	 * @param key Key code of the key.
	 * @return True if pressed, false otherwise.
	 */
	bool keyState( irr::EKEY_CODE key );

	/**
	 * @brief Returns the x coordinate of the mouse cursor.
	 * @return The x coordinate of the mouse cursor.
	 */
	int getMouseX();

	/**
	 * @brief Returns the y coordinate of the mouse cursor.
	 * @return The y coordinate of the mouse cursor.
	 */
	int getMouseY();

	/**
	 * @brief Get the mouse movement delta along the x axis.
	 * @return The movement delta along the x axis.
	 */
	int getMouseMoveX();

	/**
	 * @brief Get the mouse movement delta along the y axis.
	 * @return The movement delta along the y axis.
	 */
	int getMouseMoveY();

	/**
	 * @brief Get the state of the selected mouse button.
	 * @param iButton Index of the button to be queried.
	 * @return True if the button is pressed, false otherwise.
	 */
	bool getMouseButtonState( int iButton );

	/**
	 * @brief Get the movement delta of the mouse wheel.
	 * @return Positive if the wheel is scrolled up, negatice on down and 0 if
	 * not moved.
	 */
	int getMouseWheelDelta();

	/**
	 * @brief Show/hide the system mouse cursor.
	 * @param bShow True to show, false to hide the cursor.
	 */
	void showMouse( bool bShow = true );

	/**
	 * @brief Set the position of the mouse cursor.
	 * @param iX X coordinate to place the cursor.
	 * @param iY Y coordinate to place the cursor.
	 */
	void setMousePosition( int iX, int iY );

	/**
	 * @brief Lock the system mouse cursor in the middle of the window.
	 * @param bLock True to lock, false to unlock.
	 */
	void lockMouse( bool bLock = true );

	/**
	 * @brief Adds a callback which gets called when a button is pressed.
	 * @param cb The Callback to call.
	 */
	void addKeyPressedCallback( irr::EKEY_CODE key, ICallback *cb );

	/**
	 * @brief Clears all callbacks of the sepcified key.
	 * @param key Key which callbacks should get deleted.
	 */
	void clearKeyPressedCallbacks( irr::EKEY_CODE key );

	/**
	 * @brief irr::EventReceiver::OnEvent()
	 * Override this method to process events on your own.
	 * @param evt
	 */
	bool OnEvent( const irr::SEvent &evt );

protected:

	irr::IrrlichtDevice *m_pDevice;
	irr::gui::IGUIEnvironment *m_pGUI;

	ScriptToolKit *m_pScriptToolKit;

	int m_iScreenWidth, m_iScreenHeight;

	bool m_bKeyStates[irr::KEY_KEY_CODES_COUNT];
	int m_iMouseX, m_iMouseY, m_iOldMouseX, m_iOldMouseY, m_iMouseMoveX, m_iMouseMoveY;
	int m_iMouseWheelDelta;
	int m_iMouseButtonStates;
	bool m_bMouseLocked;

	irr::gui::IGUIWindow *m_pConsoleWindow;
	irr::gui::IGUIListBox *m_pConsoleOutput;
	irr::gui::IGUIEditBox *m_pConsoleInput;
	irr::gui::IGUIButton *m_pConsoleSendButton;
	unsigned int m_iCurOutputLine;

	std::multimap<irr::EKEY_CODE, ICallback*> m_Callbacks;

};

}

#endif // __pulsareventreceiver__
