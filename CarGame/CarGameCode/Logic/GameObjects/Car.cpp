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
    pos = Point2D<double>(getX() + vel, getY());
}

Car::~Car(){};

void Car::draw() {
    drawTexture(game->getTexture(carTexture));
}


void Car::drawTexture(Texture *texture) {
    int dX = game->getOrigin().getX();
    int dY = game->getOrigin().getY();

    SDL_Rect c = getCollider();
    SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h};
    texture->render(textureBox);
}


SDL_Rect Car::getCollider(){
    return { int(getX() - getWidth()),
             int(getY() - getHeight()/2),
             getWidth(),
             getHeight()};
}

// no muy seguro de esto, es mejor esto o hacerlo directamente en game con un set position???
void Car::upNdown(int i) {
    Point2D<double> p(pos.getX(), pos.getY() + (VSPEED * i));
    pos = p;
}

void Car::accelerate() {
    vel *= ACCELERATION;
    if (vel > MAX_SPEED)vel = MAX_SPEED;
}

void Car::decelerate() {
    vel *= DECELERATION;
    if (vel < 1)vel = 1; //no viene el minimo pero no creo que haga falta porner una variable constante para ello, o si, no se
}