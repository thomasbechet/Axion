#include <iostream>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Utility/ThreadPool.hpp>

int main(int argc, char* argv[])
{
    ax::Vector4d vec = ax::Vector4d(0.0, 1.0, 0.0, 1.0);
    ax::Matrix4d mat = ax::Matrix4d::rotateX(-ax::PI / 2.0);
    vec = mat * vec;

    std::cout << vec << std::endl;

    return 0;
}