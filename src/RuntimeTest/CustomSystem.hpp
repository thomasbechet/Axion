#pragma once

#include <Core/System/System.hpp>

class CustomSystem : public ax::System
{
public:
    static std::string name(){return "CustomSystem";}

private:
    void onUpdate() override
    {
        std::cout << "RIP" << std::endl;
    }
};

class CustomSystem2 : public ax::System
{
public:
    static std::string name(){return "CustomSystem2";}

private:
    void onUpdate() override
    {
        std::cout << "RIP" << std::endl;
    }
};

class CustomSystem3 : public ax::System
{
public:
    static std::string name(){return "CustomSystem3";}

private:
    void onUpdate() override
    {
        std::cout << "RIP" << std::endl;
    }
};