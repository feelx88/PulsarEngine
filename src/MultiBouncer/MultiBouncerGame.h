#ifndef __multibouncergame__
#define __multibouncergame__

#include "../PulsarEngine/PulsarEngine.h"

#include <boost/filesystem.hpp>

#include "bouncers/SmallFastTestBouncer.h"
#include <wiiuse.h>

class MultiBouncerGame
{
public:
	MultiBouncerGame();
	~MultiBouncerGame();
	
	int run();

private:

	void init();
	void initGUI();
	irr::EKEY_CODE ***loadControls( pulsar::ConfigStorage *input,
		pulsar::ScriptToolKit *scriptTK );
	wiimote **connectWiimotes( int &connected );
	
	//Menu gui items
	irr::gui::IGUIWindow *m_MainMenu;
	irr::gui::IGUIListBox *m_MapList;
	irr::gui::IGUIButton *m_OkButton, *mReconnectButton;
	irr::gui::IGUISpinBox *m_PlayerCounter;
	
	//Ingame gui items
	irr::gui::IGUIWindow *mScoreWindow;
	irr::gui::IGUIStaticText *mScoreCounter;
	
	std::vector<boost::filesystem::path> m_MapFiles;
	std::vector<pulsar::ConfigStorage*> m_MapData;

	pulsar::PulsarEngine *m_Engine;
	
	int mWinWidth, mWindHeight;
};

#endif // __multibouncergame__
