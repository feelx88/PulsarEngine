#ifndef __multibouncergame__
#define __multibouncergame__

#include "../PulsarEngine/PulsarEngine.h"

struct MultiBouncerGame
{
	MultiBouncerGame();
	~MultiBouncerGame();

	int run();

private:

	void init();
	void initGUI();

	std::vector<String> m_BouncerFiles;
	std::vector<String> m_MapFiles;
	
	irr::gui::IGUIWindow *m_MainMenu;

	pulsar::PulsarEngine *m_Engine;
};

#endif // __multibouncergame__
