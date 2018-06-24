#pragma once

#include <Core/System/System.hpp>

class CustomSystem : public ax::System
{
public:
    static std::string name(){return "CustomSystem";}

private:
    void tick() override
    {
        std::cout << "RIP" << std::endl;
    }
};