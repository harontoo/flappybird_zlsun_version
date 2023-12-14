#include "Pipe.h"
#include "Paths.h"

bool Pipe::init()
{
    if (!Node::init()) {
        return false;
    }

    downPipe = ax::Sprite::create(IMG_PIPE_DOWN);
    downPipe->setAnchorPoint(ax::Point(0, 0));
    addChild(downPipe);

    upPipe = ax::Sprite::create(IMG_PIPE_UP);
    upPipe->setAnchorPoint(ax::Point(0, 1));
    addChild(upPipe);

    return true;
}

void Pipe::setRandomPositionY()
{
    float gap = 100;
    float mid = 112 + 200 + AXRANDOM_MINUS1_1() * gap;
    downPipe->setPositionY(mid + gap / 2);
    upPipe->setPositionY(mid - gap / 2);
}

float Pipe::getPositionX()
{
    return upPipe->getPositionX();
}

void Pipe::setPositionX(float x)
{
    downPipe->setPositionX(x);
    upPipe->setPositionX(x);
}

bool Pipe::checkCollision(Bird* bird)
{
    auto birdPos = bird->getPosition();
    if (upPipe->getPositionX() < birdPos.x
        && birdPos.x < upPipe->getPositionX() + upPipe->getContentSize().width) {
        if (birdPos.y > downPipe->getPositionY() || birdPos.y < upPipe->getPositionY()) {
            return true;
        }
    }
    return false;
}
