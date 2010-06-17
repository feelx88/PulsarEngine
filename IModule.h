#ifndef __imodule__
#define __imodule__

#include "IObject.h"

namespace pulsar
{

class IModule : public IObject
{

	public:

	/**
	 * @brief Enum for the call position of the module's update() method.
	 */
	enum E_PULSARMODULECALLPLACE
	{
		EPMCP_RUN = 0,
		ECMCP_BEGINDRAWING,
		ECMCP_ENDDRAWING,
		ECMCP_PHYSICSTICK
	};

	private:

	/**
	 * @brief Standard constructor.
	 */
	IModule() : IObject( "IModule", "" )
	{
	}

	public:

	/**
	 * @brief Get the instance of a module.
	 * @return a newly created module instance if none exists, otherwise the
	 * already constructed.
	 */
	virtual static IModule *getInstance() = 0;

	/**
	 * @brief Standard destructor.
	 */
	virtual ~IModule()
	{
		if( m_pConfig )
			delete m_pConfig;
	}

	/**
	 * @brief Initialize the Module, alternatively with the given ConfigStorage
	 * @param pConfig ConfigStorage to use if needed
	 */
	virtual void init( ConfigStorage *pConfig = 0 )
	{
		m_pConfig = pConfig;
	}

	/**
	 * @brief Main callback method which gets called at a specified position in
	 * the Engine loop. This position is set by the getCallPlace method.
	 */
	virtual void update() = 0;

	/**
	 * @brief Get the position at which this module runs its update method.
	 * @return the position of the update() call.
	 */
	virtual E_PULSARMODULECALLPLACE getCallPlace() = 0;

	/**
	 * @brief Calls a module method.
	 * @param sName Name of the method to call.
	 * @param pParameters Parameters needed by the method.
	 */
	virtual void callMethod( String sName, ConfigStorage* pParameters = 0 ) = 0;

	/**
	 * @brief Check if a method exists.
	 * @param sName Name of the method to check for.
	 * @return True if the method exists, false otherwise.
	 */
	virtual bool queryMethod( String sName ) = 0;

	protected:

	ConfigStorage *m_pConfig;

	static IModule *s_pInstance;

};

}

#endif // __imodule__
