#pragma once
#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Game;

class Meta {
protected:
    Game* game_;
    Point2D<double> pos_;
    int w_, h_;
    Texture* texture_;
public:
    Meta(Game* g);
    ~Meta();

    void draw();
    void update();
    void drawTexture(Texture* texture);

    void setDimension(int width, int height);

    double getX() { return pos_.getX(); };
    double getY() { return pos_.getY(); };
    int getWidth() { return w_; };
    int getHeight() { return h_; };

    void setPosition(double x, double y);

    SDL_Rect getCollider();
};