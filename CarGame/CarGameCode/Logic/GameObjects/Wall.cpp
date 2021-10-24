#include "../Game.h"

Wall::Wall(Game* g) {
	game_ = g;
	texture_ = nullptr;
}

Wall::~Wall() {}

void Wall::draw() {
	drawTexture(game_->getTexture(rockTexture));
}

void Wall::update() {
	if ( (-game_->getOrigin().getX())+ game_->getWindowWidth()+w_ > pos_.getX()) { //calculo para saber cuando se tiene que empezar a dibujar dibujar
		draw();
	}

	if (SDL_HasIntersection(&getCollider(), &game_->getCarColl())) {
		game_->gotHit(this);
	}
}

void Wall::drawTexture(Texture* t) {
	int dX = game_->getOrigin().getX();
	int dY = game_->getOrigin().getY();

	SDL_Rect c = getCollider();
	SDL_Rect textureBox = { c.x, c.y + dY, c.w, c.h };
	t->render(textureBox);
	//SDL_RenderDrawRect(game_->getRenderer(), &c);
}

void Wall::setDimension(int width, int height) {
	w_ = width;
	h_ = height;
}

void Wall::setPosition(double x, double y) {
	pos_ = Point2D<double>(x, y);
}

SDL_Rect Wall::getCollider() {
	return { int(getX() - getWidth()+game_->getOrigin().getX()),//mirar car.cpp para explicacion de por que el calculo esta cambiado
			 int(getY() - getHeight()/2),
			 getWidth(),
			 getHeight() };
}