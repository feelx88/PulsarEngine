#ifndef __scripttoolkit__
#define __scripttoolkit__

#include "IToolKit.h" // Base class: pulsar::IToolKit

namespace pulsar
{

/**
 * @class ScriptToolkit
 * @author Felix Müller
 * @date 29.04.2010
 * @file ScriptToolkit.h
 * @brief Toolkit class for managing script related tasks.
 */
class ScriptToolkit : public pulsar::IToolKit
{
	public:

	/**
	 * @brief Standard constructor.
	 */
	ScriptToolkit();

	/**
	 * @brief Standard destructor.
	 */
	virtual ~ScriptToolkit();

	/**
	 * @brief Initialization function which needs a lua_State.
	 * @param initParam lua_State packed in a Value.
	 */
	virtual void init( Value initParam );

	/**
	 * @brief Method which runs the tick scripts stack.
	 */
	virtual void update();

	/**
	 * @brief Execute a given String in the lua vm.
	 * @param sString String to be processed.
	 */
	void executeString( String sString );

	/**
	 * @brief Execute a given File in the lua vm.
	 * @param sString File name of the file to be processed.
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

	protected:

	std::map<int, String> m_mScriptStack;
	int m_iIDCounter;
	lua_State *m_pLuaState;

};

}

#endif // __scripttoolkit__
