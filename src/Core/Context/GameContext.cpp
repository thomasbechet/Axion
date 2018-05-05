#include <Core/Context/GameContext.hpp>

using namespace ax;

void GameContext::start()
{
    onStart();
}
void GameContext::stop()
{
    onStop();
}