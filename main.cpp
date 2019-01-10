#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "EngExecution.cpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


int main()
{
    srand(time(NULL));
    Eng game;
    game.generateMap("Maze.txt");
    game.Update(tiles);
    game.startGame();

    return 0;
}
