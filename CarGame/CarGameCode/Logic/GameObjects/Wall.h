#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Game;

class Wall {
private:
    Game* game_;
    Point2D<double> pos_;
    int w_, h_;
    Texture* texture_;

    void drawTexture(Texture* texture); //mirar car.h para explicacion de por que es privado
public:
    Wall(Game* g);
    ~Wall();

    void draw();
    void update();

    void setDimension(int width, int height);

    double getX() { return pos_.getX(); };
    double getY() { return pos_.getY(); };
    int getWidth() { return w_; };
    int getHeight() { return h_; };

    void setPosition(double x, double y);

    SDL_Rect getCollider();
};