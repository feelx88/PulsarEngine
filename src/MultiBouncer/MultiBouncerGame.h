#ifndef __multibouncergame__
#define __multibouncergame__

#include "../PulsarEngine/PulsarEngine.h"

#include <boost/filesystem.hpp>

#include "bouncers/SmallFastTestBouncer.h"

class MultiBouncerGame
{
public:
	MultiBouncerGame();
	~MultiBouncerGame();

	static void addTeamBluePoint();
	static void addTeamRedPoint();
	static void resetPoints();
	
	int run();

private:

	void init();
	void initGUI();
	
	//Menu gui items
	irr::gui::IGUIWindow *m_MainMenu;
	irr::gui::IGUIListBox *m_MapList;
	irr::gui::IGUIButton *m_OkButton;
	irr::gui::IGUISpinBox *m_PlayerCounter;
	
	//Ingame gui items
	irr::gui::IGUIWindow *mScoreWindow;
	irr::gui::IGUIStaticText *mScoreCounter;
	
	std::vector<boost::filesystem::path> m_MapFiles;
	std::vector<pulsar::ConfigStorage*> m_MapData;

	pulsar::PulsarEngine *m_Engine;
	
	int mWinWidth, mWindHeight;

	static pulsar::DynamicEntity **sBall;
	
	static int sTeamRedPoints, sTeamBluePoints;
};

#endif // __multibouncergame__
