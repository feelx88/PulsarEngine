#include "ValueFactory.h"

using namespace pulsar;

std::map<String, Value::ValueGeneratorBase*> Value::m_mGenerators;
std::multimap<String, String> Value::m_mTypeAliases;