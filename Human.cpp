#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;


///srand(time(NULL));

class Human{
public:
    int xPos,yPos;
    Texture pText;
    Sprite player;

    void start(int pX,int pY)
    {
        player.setTexture(pText);
        player.setPosition(pX,pY);


        xPos = pX;
        yPos = pY;
    }



    void moveDown()
    {
        if(((yPos)+32) != 0 && tiles[((yPos)+32)/32][(xPos)/32] != '#')
        {
            (player).move(0.0f, 32.0f);
            yPos+=32;
            cout << "Down" << endl;
        }
        cout << xPos << " " << yPos << endl;
    }

    void moveUp()
    {
        if(((yPos)-32) != 0 && tiles[((yPos)-32)/32][(xPos)/32] != '#')
        {
            (player).move(0.0f, -32.0f);
            yPos-=32;
            cout << "Up" << endl;

        }
        cout << xPos << " " << yPos << endl;
    }

    void moveLeft()
    {
        if(((xPos)-32) != 0 && tiles[((yPos))/32][(xPos-32)/32] != '#')
        {
            (player).move(-32.0f, 0.0f);
            xPos-=32;
            cout << "Left" << endl;
        }
        cout << xPos << " " << yPos << endl;
    }

    void moveRight()
    {
        if(((xPos)+32) != 0 && tiles[((yPos))/32][(xPos+32)/32] != '#')
        {
            (player).move(32.0f, 0.0f);
            xPos+=32;
            cout << "Right" << endl;
        }
        cout << xPos << " " << yPos << endl;
    }

};

class Hero : public Human
{
public:
    int health;

    void heroStart(int phealth)
    {
        health = phealth;
    }
};





class Enemy : public Human
{
private:
    int moveNow;
public:
    Enemy()
    {
        moveNow = 0;
    }
    void randomMove(int choice)
    {

        if(moveNow)
        {
            switch(choice)
            {
            case 0: moveUp(); break;
            case 1: moveRight(); break;
            case 2: moveDown(); break;
            case 3: moveLeft(); break;
            }
            moveNow = 0;
        }
        else
        {
            moveNow = 1;
        }
    }
};



