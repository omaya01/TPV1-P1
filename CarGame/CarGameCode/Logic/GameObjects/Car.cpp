//
// Created by eys on 21/8/21.
//

#include "Car.h"
#include "../Game.h"

Car::Car(Game *game){
    this->game = game;
    texture = nullptr;

}

void Car::setDimension(int width, int height){
    w = width;
    h = height;
};

void  Car::setPosition(double x, double y){
    pos = Point2D<double>(x, y);
};

// cambiado para trabajar con variable privada vel (creada por mi), supongo que esto esta bien porque si no como narices hago para cambiar la velocidad de actualizacion
void Car::update() {
    int vspeedaux = 0;
    switch (vmove)
    {
    case 0:
        break;
    case -1:
        vspeedaux = -VSPEED;
        if (pos.getY() - VSPEED - (h / 2) <= 0) {
            vspeedaux = 0;
            vmove = 0;
        }
        break;
    case 1:
        vspeedaux = VSPEED;
        if (pos.getY() + VSPEED + (h / 2) >= game->getWindowHeight()) {
            vspeedaux = 0;
            vmove = 0;
        }
        break;
    }

    switch (hmove)
    {
    case 0:
        break;
    case 1:
        vel_ *= ACCELERATION;
        if (vel_ > MAX_SPEED) {
            vel_ = MAX_SPEED;
            hmove = 0;
        }
        else if (vel_ == 0) {
            vel_ = 1;
            hmove = 0;
        }
        break;
    case -1:
        vel_ *= DECELERATION;
        if (vel_ < 1) {
            vel_ = 1;
            hmove = 0;
        }
        break;
    }

    pos = Point2D<double>(getX() + vel_, getY() + vspeedaux);    
}

Car::~Car(){};

void Car::draw() {
    drawTexture(game->getTexture(carTexture));
}


void Car::drawTexture(Texture *texture) {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x , c.y + dY, c.w, c.h};
    texture->render(textureBox);
    SDL_RenderDrawRect(game->getRenderer(), &c);
}


SDL_Rect Car::getCollider(){
    return { int(getX() - getWidth() + game->getOrigin().getX()),
             int(getY() - getHeight()/2),
             getWidth(),
             getHeight()};
}

void Car::gotHit() {
    if (power_ - 1 == 0) {
        game->vic(false);
        game->changeState(GAMEOVER);
    }
    else power_--;
    vel_=0;
}

void Car::upNdown(int i) {
    vmove = i;
}

void Car::accelerateNdecelerate(int i) {
    hmove = i;
}