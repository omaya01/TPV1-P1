#include "../Game.h"

Meta::Meta(Game* g) {
	game_ = g;
	texture_ = nullptr;
}

Meta::~Meta() {}

void Meta::draw() {
	drawTexture(game_->getTexture(goalTexture));
}

void Meta::update() {
	if ((-game_->getOrigin().getX()) + game_->getWindowWidth()+w_ > pos_.getX()) { //calculo para saber cuando se tiene que empezar a dibujar
		draw();
	}
	if (SDL_HasIntersection(&getCollider(), &game_->getCarColl())) {
		game_->vic(true);
		game_->changeState(GAMEOVER);
	}
}

void Meta::drawTexture(Texture* t) {
	int dX = game_->getOrigin().getX();
	int dY = game_->getOrigin().getY();

	SDL_Rect c = getCollider();
	SDL_Rect textureBox = { c.x, c.y + dY, c.w, c.h };
	t->render(textureBox);
	//SDL_RenderDrawRect(game_->getRenderer(), &c);
}

void Meta::setDimension(int width, int height) {
	w_ = width;
	h_ = height;
}

void Meta::setPosition(double x, double y) {
	pos_ = Point2D<double>(x, y);
}

SDL_Rect Meta::getCollider() {
	return { int(getX() - getWidth() + game_->getOrigin().getX()), //mirar car.cpp para explicacion de por que la cuenta esta cambiada
			 int(getY() - getHeight() / 2),
			 getWidth(),
			 getHeight() };
}