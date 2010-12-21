#ifndef __multibouncergame__
#define __multibouncergame__

#include "../PulsarEngine/PulsarEngine.h"

#include <boost/filesystem.hpp>

struct MultiBouncerGame
{
	MultiBouncerGame();
	~MultiBouncerGame();

	int run();

private:

	void init();
	void initGUI();
	
	pulsar::DynamicEntity *createBouncer();
	pulsar::DynamicEntity *createGoal();
	pulsar::DynamicEntity *createBall();
	
	irr::gui::IGUIWindow *m_MainMenu;
	irr::gui::IGUIListBox *m_MapList;
	irr::gui::IGUIButton *m_OkButton;
	irr::gui::IGUISpinBox *m_PlayerCounter;
	
	std::vector<boost::filesystem::path> m_MapFiles;
	std::vector<pulsar::ConfigStorage*> m_MapData;

	pulsar::PulsarEngine *m_Engine;
	
	int mWinWidth, mWindHeight;
};

#endif // __multibouncergame__
