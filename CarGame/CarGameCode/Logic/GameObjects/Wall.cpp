#include "Wall.h"

Wall::Wall(Game* g) {
	game_ = g;
	texture_ = nullptr;
}

Wall::~Wall() {

}

void Wall::draw() {
	drawTexture(game_->getTexture(carTexture));
}

void Wall::update() {

}

void Wall::drawTexture(Texture* t) {
	int dX = game_->getOrigin().getX();
	int dY = game_->getOrigin().getY();

	SDL_Rect c = getCollider();
	SDL_Rect textureBox = { c.x + dX, c.y + dY, c.w, c.h };
	texture->render(textureBox);
}

void Wall::setDimension(int width, int height) {
	w_ = width;
	h_ = height;
}

void Wall::setPosition(double x, double y) {
	pos_ = Point2D<double>(x, y);
}