#ifndef __multibouncergame__
#define __multibouncergame__

#include "../PulsarEngine/PulsarEngine.h"

struct MultiBouncerGame
{
	MultiBouncerGame();
	~MultiBouncerGame();

	int run();

private:

	enum
	{
		ID_CAMERA_PRIMARY = 1
	};

	void init();
	void initGUI();

	irr::gui::IGUITab *m_MainMenu;

	pulsar::PulsarEngine *m_Engine;
};

#endif // __multibouncergame__
