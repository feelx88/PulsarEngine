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
	 * @brief Get the associated lua_State.
	 * @return The used lua_State or 0 if not set.
	 */
	lua_State *getLuaState()
	{
		return m_pLuaState;
	}

protected:

	std::map<int, String> m_mScriptStack;
	int m_iIDCounter;
	lua_State *m_pLuaState;
	irr::gui::IGUIWindow *m_pConsoleWindow;

};

}

#endif // __scripttoolkit__
