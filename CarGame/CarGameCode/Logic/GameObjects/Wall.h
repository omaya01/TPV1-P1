#pragma once

#include "../../Utils/Vector2D.h"
#include "../../View/Texture.h"
#include "../../View/Box.h"

class Wall {
protected:
    Point2D<double> pos;
    int w, h;
    Texture* texture;
public:

};