#pragma once

//Bird class contains Faby's core mechanics
#include "axmol.h"

class Bird : public ax::Sprite {

public:
	bool init();

	void update(float dt);
	void flyUp();
	void fall();
	void die();

private:
	enum class State {Normal,FlyingUp,Falling};

	ax::Action* normalAnimation;
	ax::Action* flyAnimation;
	ax::Action* fallAnimation;

	State state;
	ax::Size visibleSize;
	float velocity;
	float gravity;
};