//
// Created by eys on 20/8/21.
//

#ifndef CARGAME_GAME_H
#define CARGAME_GAME_H

#include <iostream>
#include <string>
#include <vector>

#include "../View/TextureContainer.h"
#include "../View/Texture.h"
#include "../View/Box.h"
#include "../View/Font.h"

#include "GameObjects/Car.h"
#include "GameObjects/Wall.h"
#include "GameObjects/Meta.h"

enum state_ {MENU, RUNNING, GAMEOVER};

using namespace std;

class Game{


private:
    string name;
    bool doExit;
    bool help_ = false;
    bool victory_ = false;
    int roadLength;
    int width, height;
    Car *car = nullptr;
    int distance_;
    float time_;
    Meta* goal_ = nullptr;

    int nObstacles_;
    vector<Wall*> obstacles_; //a futuro cambiar esto a gameobjects
    
    TextureContainer *textureContainer;
    SDL_Renderer* renderer = nullptr;
    Font *font;

    state_ currentState_ = MENU;

    int level_ = 0;

    void createObstacles();
    void clearObstacles();

    void drawInfo();
    void drawMenu();
    void drawGameOver();
public:
    const unsigned int CAR_WIDTH = 100;
    const unsigned  int CAR_HEIGHT = 50;
    
    const unsigned int WALL_WIDTH = 50;
    const unsigned int WALL_HEIGHT = 50;

    Game(string name, int width, int height, int roadLength, int obstacles);
    ~Game();

    void startGame();
    void update();
    void draw();

    void setUserExit();
    bool isUserExit();
    bool doQuit();

    int getWindowWidth();
    int getWindowHeight();

    Point2D<int> getOrigin();

    string getGameName();

    void setRenderer(SDL_Renderer *renderer);
    void loadTextures();
    Texture *getTexture(TextureName name);
    SDL_Renderer *getRenderer();
    void renderText(string text, int x, int y, SDL_Color color={0,0,0}); //no estoy seguro de si esto deberia ser privado o no, creo que si tho

    void changeState(state_ s);
    void switchHelp() { help_ = !help_; }
    void vic(bool i) { victory_ = i; }

    SDL_Rect getCarColl() { return car->getCollider(); }
    void gotHit(Wall *w);

    //metodos para coche
    void carUpNdown(int i);
    void carAccNdec(int i);

};


#endif //CARGAME_GAME_H
