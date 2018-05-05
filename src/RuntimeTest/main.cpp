#include <iostream>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>

int main(int argc, char* argv[])
{
    ax::Vector4f vec = ax::Vector4f(0.0f, 0.0f, 0.0f, 1.0f);

    ax::Transform trans = ax::Transform();
    trans.setTranslation(ax::Vector3f(1.0f, 0.0f, 1.0f));
    trans.setScale(ax::Vector3f(1.0f, 2.0f, 2.0f));

    vec = trans.matrix() * vec;

    std::cout << vec << std::endl;

    return 0;
}