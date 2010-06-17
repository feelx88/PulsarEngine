#include "IObject.h"

using namespace pulsar;

unsigned int IObject::s_iIDCounter = 8192;
std::map<unsigned int, IObject*> IObject::s_mObjects;
std::stack<unsigned int> IObject::s_Unused;

std::ostream& operator<<( std::ostream& out, String str )
{
	out << str.c_str();
	return out;
}
