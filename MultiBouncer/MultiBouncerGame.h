#ifndef __multibouncergame__
#define __multibouncergame__

#include "PulsarEngine.h"

struct MultiBouncerGame
{
	MultiBouncerGame();
	~MultiBouncerGame();

	int run();

private:

	void init();
	void initGUI();

	irr::gui::IGUITab *m_MainMenu;

	pulsar::PulsarEngine *m_Engine;
};

#endif // __multibouncergame__
