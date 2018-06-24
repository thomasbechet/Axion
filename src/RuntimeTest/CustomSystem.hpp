#pragma once

#include <Core/System/MonothreadSystem.hpp>

class CustomSystem : public ax::MonothreadSystem
{
public:
    static std::string name(){return "CustomSystem";}

private:

};