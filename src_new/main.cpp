#include <iostream>

#include <core/scene/archetype.hpp>

int main(int argc, char* argv[])
{
    std::cout << ax::archetype<std::string, int, double>::contains<int>() << std::endl;
    std::cout << ax::archetype<std::string, int, double>::contains<>() << std::endl;

    return 0;
}