#pragma once
#include "axmol.h"
#include "Bird.h";
#include "Pipe.h"

class GameLayer : public ax::Layer {

public:
	GameLayer();

	bool init();

	void addPipes();
	void update(float dt);
	bool checkCollision(Bird* bird);
	bool hitGround(Bird* bird);
	void stop();
	int getScore();

private:
	float speed;
	float pipe_distance;
	float pipe_width;
	int score;
	ax::Size visibleSize;
	ax::Point origin;
	float point_x;
	ax::Sprite* land;
	std::vector<Pipe*> pipes;

};
