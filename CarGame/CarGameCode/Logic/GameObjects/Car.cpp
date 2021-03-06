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
    if (debug_) {
        Box(c, RED).render(game->getRenderer());
        SDL_Rect aux;
        aux.w = 10; aux.h = 10;
        aux.x = w - (aux.w / 2);
        aux.y = getY() - (aux.h / 2);
        Box(aux, BLUE).render(game->getRenderer());
    }
}


SDL_Rect Car::getCollider(){
    return { int(getX() - getWidth() + game->getOrigin().getX()), //he cambiado la cuenta porque el rectangulo que esto devolvia estaba mal
        //basicamente se movia lejos de la imagen del coche y he comprobado que dicho movimiento no coincide con el movimiento que tendria si se quedase con la imagen
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