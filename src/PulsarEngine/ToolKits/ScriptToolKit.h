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

#ifndef __scripttoolkit__
#define __scripttoolkit__

#include "IToolKit.h" // Base class: pulsar::IToolKit

namespace pulsar
{

class PulsarEngine;

/**
 * @class ScriptToolkit
 * @author Felix Müller
 * @date 29.04.2010
 * @file ScriptToolkit.h
 * @brief Toolkit class for managing script related tasks.
 */
class ScriptToolKit : public pulsar::IToolKit
{
	public:

	/**
	 * @brief Standard constructor.
	 */
	ScriptToolKit();

	/**
	 * @brief Standard destructor.
	 */
	virtual ~ScriptToolKit();
	
	/**
	 * @brief Get the ToolKit's name.
	 *
	 * @return String containing "Script".
	 **/
	virtual String getToolKitClassName();

	/**
	 * @brief Initialization function.
	 * @param initParam Not needed.
	 */
	virtual void init( Value initParam );

	/**
	 * @brief Method which runs the tick scripts stack.
	 */
	virtual void tickUpdate();

	/**
	 * @brief Execute a given String in the lua vm.
	 * @param sString String to be processed.
	 */
	void executeString( String sString );

	/**
	 * @brief Execute a given File in the lua vm.
	 * @param sFileName File name of the file to be processed.
	 */
	void executeFile( String sFileName );

	/**
	 * @brief Add a script String to the tick scripts stack.
	 * @param sScript Script to be placed on the stack.
	 * @return The id of the script which is used to delete it later.
	 */
	int addTickScript( String sScript );

	/**
	 * @brief Removes the script with the given ID from the tick scripts stack.
	 * @param iID ID of the script string to be removed.
	 */
	void removeTickScript( int iID );

	/**
	 * @brief Clears the tick scripts stack.
	 */
	void clearScriptStack();
	
	/**
	 * @brief Get the value of a key code string.
	 * Only Values from Pulsar.* defined in pulsar_defs.lua are checked.
	 *
	 * @param keyname Name of the key.
	 * @return The code of the specified key.
	 **/
	irr::EKEY_CODE getPulsarKeyCode( String keyName );

	/**
	 * @brief Get the associated lua_State.
	 * @return The used lua_State or 0 if not set.
	 */
	lua_State *getLuaState()
	{
		return m_pLuaState;
	}

protected:

	int m_iIDCounter, mTickStackSize;
	lua_State *m_pLuaState;
	irr::gui::IGUIWindow *m_pConsoleWindow;

};

}

#endif // __scripttoolkit__
