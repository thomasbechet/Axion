#include <Core/Builder/ComponentFactories.hpp>

#include <iostream>

using namespace ax;

IComponentFactory& ComponentFactories::get(const std::string& identifier)
{
    return *m_factories.at(identifier).get();
}