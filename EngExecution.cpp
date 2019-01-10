#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <windows.h>
#include <string>
#include <cstdlib>
#include "MapGen.cpp"
#include "Human.cpp"

using namespace std;
using namespace sf;

Hero hero;

///srand(time(NULL));

Enemy enemy1,enemy2;

int coinsTaken = 0;

bool keyTaken = false;

bool Level1Passed = false;



SoundBuffer coinSound_buffer;
Sound coinSound;


SoundBuffer keySound_buffer;
Sound keySound;

SoundBuffer damagedSound_buffer;
Sound damagedSound;





Music Level1Theme;

Music GameOver;

Music Level1Complete;


int timeCount = 180;

int score = 0;



int cnt = 1;



Font gameFont;


RenderWindow window(VideoMode(800,645),"Maze Game!");

class Eng : public mapGen
{
public:

    void Update(char grid[20][20])
    {
        Texture blockTxt;
        blockTxt.loadFromFile("52575.png");
        Sprite blocks;
        blocks.setTexture(blockTxt);

        Texture floorTxt;
        floorTxt.loadFromFile("15849.png");
        Sprite floors;
        floors.setTexture(floorTxt);

        Texture coinTxt;
        coinTxt.loadFromFile("52581.png");
        Sprite coins;
        coins.setTexture(coinTxt);


        int randomChoice1 = rand()%4, randomChoice2 = rand()%4;

        enemy1.randomMove(randomChoice1);
        enemy2.randomMove(randomChoice2);


        if(enemy1.xPos == hero.xPos && enemy1.yPos == hero.yPos)
        {
            hero.health-=10;
            damagedSound.play();
        }
        if(enemy2.xPos == hero.xPos && enemy2.yPos == hero.yPos)
        {
            hero.health-=10;
            damagedSound.play();
        }



        if(tiles[(hero.yPos)/32][(hero.xPos)/32] == 'c')
        {
            tiles[(hero.yPos)/32][(hero.xPos)/32] = '.';
            coinSound.play();
            score+=20;
            ///Sleep(150);
        }

        if(tiles[(hero.yPos)/32][(hero.xPos)/32] == 'k')
        {
            tiles[(hero.yPos)/32][(hero.xPos)/32] = '.';
            keyTaken = true;
            keySound.play();
            ///Sleep(150);
        }

        if(tiles[(hero.yPos)/32][(hero.xPos)/32] == 'x' && keyTaken)
        {
            Level1Passed = true;
        }



        for(int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                if(tiles[i][j] == '#')
                {
                    blocks.setPosition(Vector2f(32*j,32*i));
                    window.draw(blocks);
                }
                else
                {
                    floors.setPosition(Vector2f(32*j,32*i));
                    window.draw(floors);
                    if(tiles[i][j] == 'c')
                    {
                        coins.setPosition(Vector2f(32*j,32*i));
                        window.draw(coins);
                    }
                    else if (tiles[i][j] == 'x')
                    {
                        Texture doorTxt;
                        doorTxt.loadFromFile("door.png");
                        Sprite door;
                        door.setTexture(doorTxt);
                        door.setPosition(Vector2f(32*j,32*i));
                        window.draw(door);
                    }
                    else if(tiles[i][j] == 'k')
                    {
                        Texture keyTxt;
                        keyTxt.loadFromFile("key.png");
                        Sprite key;
                        key.setTexture(keyTxt);
                        key.setPosition(Vector2f(33.5*j,32*i));
                        window.draw(key);
                    }
                }
            }
        }
        window.draw(hero.player);
        window.draw(enemy1.player);
        window.draw(enemy2.player);
    }

    void gameLoop()
    {



        if(!damagedSound_buffer.loadFromFile("Damaged.wav"))
        {
            cout << "Failed to load Damaged sound" << endl;
        }

        if(!coinSound_buffer.loadFromFile("CoinSound2.wav"))
        {
            cout << "Failed to load coin sound 2" << endl;
        }

        if(!keySound_buffer.loadFromFile("KeyPickup.wav"))
        {
            cout << "Failed to load key pikcup sound" << endl;
        }



        damagedSound.setBuffer(damagedSound_buffer);
        coinSound.setBuffer(coinSound_buffer);
        keySound.setBuffer(keySound_buffer);






        if(!Level1Theme.openFromFile("ZeldaTheme.ogg"))
        {
            cout << "Music file didnt load correctly";
        }
        Level1Theme.play();

        if(!Level1Complete.openFromFile("Level1Complete.ogg"))
        {
            cout << "Failed to load level complete theme" << endl;
        }

        if(!GameOver.openFromFile("GameOver.ogg"))
        {
            cout << "Failed to load game over theme" << endl;
        }


        if(!gameFont.loadFromFile("pixelfont.ttf"))
        {
            cout << "Failed to load font!!" << endl;
        }

        Text heroHealthCount_text;

        Text timeCount_text;

        Text scoreCount_text;

        Text keyTaken_text;

        Text levelPassed_text;

        Text gameOver_text;
        //("Level Passed!!!", levelPassed_font, 30);


        levelPassed_text.setString("Level Passed!!!");
        levelPassed_text.setFont(gameFont);
        levelPassed_text.setCharacterSize(50);

        levelPassed_text.setColor(Color(255,255,0));


        levelPassed_text.setPosition(130,300);



        timeCount_text.setFont(gameFont);
        timeCount_text.setCharacterSize(20);
        timeCount_text.setPosition(650,500);

        scoreCount_text.setFont(gameFont);
        scoreCount_text.setCharacterSize(20);
        scoreCount_text.setPosition(650,200);
        scoreCount_text.setFillColor(Color::Yellow);


        keyTaken_text.setFont(gameFont);
        keyTaken_text.setCharacterSize(20);
        keyTaken_text.setPosition(650,300);
        keyTaken_text.setFillColor(Color::Magenta);


        heroHealthCount_text.setFont(gameFont);
        heroHealthCount_text.setCharacterSize(20);

        heroHealthCount_text.setPosition(650,100);






        gameOver_text.setString("GAME OVER");
        gameOver_text.setFont(gameFont);
        gameOver_text.setCharacterSize(50);
        gameOver_text.setFillColor(Color::Red);
        gameOver_text.setStyle(Text::Bold | Text::Underlined | Text::Italic);

        gameOver_text.setPosition(130,300);



        (enemy1.pText).loadFromFile("enemy1.png");
        enemy1.start(32,15*32);

        (enemy2.pText).loadFromFile("enemy1.png");
        enemy2.start(13*32,18*32);


        (hero.pText).loadFromFile("65156.png");
        hero.start(32,32);
        hero.heroStart(100);
        while(window.isOpen())
        {
            Event evnt;
            while(window.pollEvent(evnt))
            {
                if(evnt.type == Event::Closed)
                {
                    window.close();
                }
            }
            window.clear();
            Update(tiles);

            if(cnt%5 == 0)
            {
                timeCount--;
            }
            cnt++;


            heroHealthCount_text.setString("Health: " + to_string(hero.health));///displays live count for hero's health
            timeCount_text.setString("Time: " + to_string(timeCount));
            scoreCount_text.setString("Score: " + to_string(score));

            if(keyTaken)
                keyTaken_text.setString("Key: Yes");
            else
                keyTaken_text.setString("Key: No");


            window.draw(heroHealthCount_text);
            window.draw(timeCount_text);
            window.draw(scoreCount_text);
            window.draw(keyTaken_text);


            if(Level1Passed)
            {
                window.draw(hero.player);
                window.draw(levelPassed_text);
                Level1Theme.stop();
            }

            if(hero.health == 0 || timeCount == 0)
            {
                window.draw(hero.player);
                window.draw(gameOver_text);
                Level1Theme.stop();
            }


            if(Keyboard::isKeyPressed(Keyboard::Key::Down))
            {
                hero.moveDown();
            }
            else if(Keyboard::isKeyPressed(Keyboard::Key::Up))
            {
                hero.moveUp();
            }
            else if(Keyboard::isKeyPressed(Keyboard::Key::Left))
            {
                hero.moveLeft();
            }
            else if(Keyboard::isKeyPressed(Keyboard::Key::Right))
            {
                hero.moveRight();
            }

            window.display();

            if(hero.health == 0 || timeCount == 0)
            {
                GameOver.play();
                Sleep(4685);
                window.close();
            }

            if(Level1Passed)
            {
                Level1Complete.play();
                Sleep(6500);
                window.close();
            }
            Sleep(100);
        }
    }


    void startGame()
    {
        gameLoop();
    }

};
