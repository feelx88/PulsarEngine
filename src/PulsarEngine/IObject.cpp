#include "IObject.h"

using namespace pulsar;

std::deque<IObject*> IObject::s_mObjects;

std::ostream& operator<<( std::ostream& out, String str )
{
	out << str.c_str();
	return out;
}
