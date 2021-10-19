//
// Created by eys on 20/8/21.
//

#include "Game.h"

Game::Game(string name, int width, int height, int roadLength) {
    this->name = name;
    this->roadLength = roadLength;
    this->width = width;
    this->height = height;
    doExit = false;
    font = new Font("../Images/Monospace.ttf", 12);
}

void Game::startGame() {
    car = new Car(this);
    car->setDimension(CAR_WIDTH, CAR_HEIGHT);
    car->setPosition(car->getWidth(), height/ 2.0);
}

string Game::getGameName() {
    return name;
}

Game::~Game() {
    cout << "[DEBUG] deleting game" << endl;

    // puesto para que no deje basura
    delete car;
    delete font;
    delete textureContainer;
}

void Game::update(){
    car->update();
}

void Game::draw(){
    switch (currentState_)
    {
    case MENU:
        drawMenu();
        break;
    case RUNNING:
        car->draw();
        drawInfo();
        break;
    case GAMEOVER:
        
        break;
    }
}

void Game::drawInfo() {
    int x = font->getSize() / 2;
    int y = font->getSize() / 2;

    SDL_Rect rect = {0, 0, getWindowWidth(),
                     int(font->getSize() * 1.8)};
    Box(rect, BLACK).render(renderer);

    string s = "Pos: " + to_string(int(car->getX())) + " "
               + to_string(int(car->getY())) + "  " + 
        "Distance: " + to_string(roadLength-(int)car->getX())+ "  " +
        "Speed: " + to_string((int) car->getVel()) + "  " +
        "Power: " + to_string(car->getPower()) + "  " +
        "Time: " + to_string(SDL_GetTicks()/1000) + "  " +
        "Obstacles: ";
    renderText(s, x, y);
}
void Game::drawMenu() {
    string s1 = "Welcome to Super Cars";
    string s2 = "Level: " + to_string(level_);
    string s3 = "Press space to start";
    string s4 = "Press [h] for help";

    int x = width / 2 - (s1.length()/2)*font->getSize();
    int y = height / 2 - font->getSize() * 2;
    
    renderText(s1, x, y);
    renderText(s2, x, y + font->getSize());
    renderText(s3, x, y + font->getSize()*2);
    renderText(s4, x, y + font->getSize()*3);
}
void Game::drawGameOver(bool i) {
    
}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

int Game::getWindowWidth(){
    return width;
}

int Game::getWindowHeight() {
    return height;
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::setRenderer(SDL_Renderer *_renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if(renderer == nullptr)
        throw string("Renderer is null");

    textureContainer = new TextureContainer(renderer);
}

void Game::renderText(string text, int x, int y, SDL_Color color){
    font->render(renderer, text.c_str(), x, y, color);
}

bool Game::doQuit() {
    return isUserExit();
}

Texture *Game::getTexture(TextureName name) {
    return textureContainer->getTexture(name);
}

Point2D<int> Game::getOrigin() {
    return {int(-(car->getX() - car->getWidth())), 0};
}

void Game::carUpNdown(int i) {
    car->upNdown(i);
}

void Game::carAccNdec(int i) {
    car->accelerateNdecelerate(i);
}