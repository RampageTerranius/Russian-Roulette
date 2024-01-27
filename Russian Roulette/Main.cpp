#include "main.h"

int main(int argc, char* argv[])
{
    Engine engine;
    engine.GameLoop();

    return engine.ReturnState();
}