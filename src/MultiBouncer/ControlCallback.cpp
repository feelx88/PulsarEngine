#include "ControlCallback.h"

using namespace pulsar;

ControlCallback::ControlCallback( ControlCallback::CCB_ACTION action ) :
	ICallback(), mAction( action ), mBouncer( 0 )
{
}

ControlCallback::~ControlCallback()
{
	mAction = (CCB_ACTION)0;
	mBouncer = 0;
}

void ControlCallback::onTrigger(Value* val)
{
	if( mBouncer )
	{
		switch( mAction )
		{
			case UP:
				mBouncer->move( true, false, false, false );
				break;
			case DOWN:
				mBouncer->move( false, true, false, false );
				break;
			case LEFT:
				mBouncer->move( false, false, true, false );
				break;
			case RIGHT:
				mBouncer->move( false, false, false, true );
				break;
			case JUMP:
				mBouncer->jump();
				break;
			case ACTION1:
				mBouncer->startAction( 1 );
				break;
			case ACTION2:
				mBouncer->startAction( 2 );
				break;
			default:
				break;
		}
	}
	else
		std::cout << "Fired but no bouncer... Action " << mAction << std::endl;
}

void ControlCallback::setBouncer(IBouncer* bouncer)
{
	mBouncer = bouncer;
}