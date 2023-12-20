#include "Bird.h"
#include "Paths.h"
#include "iostream"

bool Bird::init()
{
	if (!ax::Sprite::init())
	{
		return false;
	}
	
	visibleSize = ax::Director::getInstance()->getVisibleSize();
	velocity = 0.0f;
	gravity =18.0f;
	state = State::Normal;
	
	auto animation = ax::Animation::create();

	//Randomize between the bird variants
	auto which = rand() % 3;
	for (int i = 0; i < 3; ++i)
	{
		//Set the sprite frames,which would be 3 for our use case
		auto image_name = ax::StringUtils::format(IMAGES_DIR"bird%d_%d.png", which, i);
		animation->addSpriteFrameWithFile(image_name);
	}
	//Set animation properties
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);

	//Create the animation
	normalAnimation = ax::Animate::create(animation);
	runAction(normalAnimation);

	//Create the fall animation/action
	fallAnimation = ax::RotateTo::create(0.6f, 90.0f);
	fallAnimation->retain();

	flyAnimation = ax::Sequence::create(
		ax::EaseOut::create(ax::RotateTo::create(0.15f, 0), 0.4f),
		ax::EaseIn::create(ax::RotateTo::create(0.25f, -30), 0.4f),
		// RotateTo::create(0.15f, 0),
		// RotateTo::create(0.25f, -30),
		nullptr
	);
	flyAnimation->retain();
	
	this->create(IMG_BIRD0_1);
	return true;
}

void Bird::update(float dt)
{
	float y = getPositionY() - velocity * dt;
	//Ensure that the bird never goes beyond the height of the screen/display
	if (y > visibleSize.height) {
		y = visibleSize.height;
	}
	setPositionY(y);

	//If true the bird should appear as if it's falling 
	if (velocity < 0 && velocity + gravity >= 0) {
		fall();
	}
	AXLOG("Y\t%f\tVelocity\t%f\tGravity\t%f\tdt\t%f\tVelocity + Gravity = %f", y, velocity, gravity, dt, velocity + gravity);

	//Incrementally increase the velocity of the bird too ensure that it gets affected by gravity
	velocity += gravity;
}


void Bird::flyUp() {
	//Initial value of the bird's velocity
	velocity = -360.0f;
	//Run fly animation and update the bird's state to State::FlyingUp;
	if (state != State::FlyingUp) {
		if (state == State::Falling) {

			//stop the fallAnimation action
			stopAction(fallAnimation);
		}
		runAction(flyAnimation);
		state = State::FlyingUp;
	}
}





void Bird::fall() {
	
	if (state == State::FlyingUp) {
		//stop the flyAnimation action
		stopAction(flyAnimation);

		//Run fallAnimation and update the bird's state to State::Falling;
		runAction(fallAnimation);
		state = State::Falling;
	}
}


void Bird::die() {
	//Stop all actions that the bird is performing
	stopAllActions();
}