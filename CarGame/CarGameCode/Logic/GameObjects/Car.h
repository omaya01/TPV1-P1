//
// Created by eys on 21/8/21.
//

#ifndef CARGAME_CAR_H
#define CARGAME_CAR_H


class Game;

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Car {

private:

    const double ACCELERATION = 1.3;
    const double DECELERATION = 0.9;
    const int VSPEED = 5;
    const int MAX_SPEED = 10;
    const int INITIAL_POWER = 3;

    Point2D<double> pos;
    int w, h;
    Game *game;
    Texture *texture;
    bool debug_ = false;

    //variables para movimiento
    double vel_ = 0;
    int vmove = 0;
    int hmove = 0;
    //no se si es lo correcto pero como la otra es constante y no la puedo cambiar pues toca crear otra
    int power_ = INITIAL_POWER;

    //metodos que he puesto privados porque creo que estan mejor siendo privados
    void drawTexture(Texture* texture); //en este caso no creo que este tenga sentido que sea publico porque claramente es un metodo de herencia
public:
    Car(Game *game);
    ~Car();

    void draw();
    void update();

    void setDimension(int width, int height);

    double getX() {return pos.getX();};
    double getY() {return pos.getY();};
    int getWidth() {return w;};
    int getHeight() {return h;};
    double getVel() { return vel_; }
    int getPower() { return power_; }

    void setPosition(double x, double y);

    SDL_Rect getCollider();

    void gotHit();

    void switchDebug() { debug_ = !debug_; }

    //para cambiar la posicion
    void upNdown(int i);
    void accelerateNdecelerate(int i);
};


#endif //CARGAME_CAR_H
