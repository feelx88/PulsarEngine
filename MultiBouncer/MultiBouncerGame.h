#ifndef __multibouncergame__
#define __multibouncergame__

#include "PulsarEngine.h"

struct MultiBouncerGame
{
	MultiBouncerGame();
	~MultiBouncerGame();

	void init();

	int run();

private:
	pulsar::PulsarEngine *m_Engine;
};

#endif // __multibouncergame__
