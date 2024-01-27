#include "main.h"

int main(int argc, char* argv[])
{
    Engine engine;

    engine.initialize();

    engine.gameLoop();

    engine.shutdown();

    return engine.ReturnState();
}