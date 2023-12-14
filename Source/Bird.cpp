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
	gravity = 18.0f;
	state = State::Normal;
	/**/
	auto animation = ax::Animation::create();

	auto which = rand() % 3;
	for (int i = 0; i < 3; ++i)
	{
		auto image_name = ax::StringUtils::format(IMAGES_DIR"bird%d_%d.png", which, i);
		animation->addSpriteFrameWithFile(image_name);
	}

	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(false);
	animation->setLoops(-1);
	
	normalAnimation = ax::Animate::create(animation);
	runAction(normalAnimation);

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
	if (y > visibleSize.height) {
		y = visibleSize.height;
	}
	setPositionY(y);
	if (velocity < 0 && velocity + gravity >= 0) {
		fall();
	}
	velocity += gravity;
}

void Bird::flyUp() {
	velocity = -360.0f;
	if (state != State::FlyingUp) {
		if (state == State::Falling) {
			stopAction(fallAnimation);
		}
		runAction(flyAnimation);
		state = State::FlyingUp;
	}
}





void Bird::fall() {
	if (state == State::FlyingUp) {
		stopAction(flyAnimation);
		runAction(fallAnimation);
		state = State::Falling;
	}
}


void Bird::die() {
	stopAllActions();
}