#include "Pipe.h"
#include "Paths.h"

bool Pipe::init()
{
    if (!Node::init()) {
        return false;
    }
    //Initialize pipes with their respective sprites
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
    //Get bird position
    auto birdPos = bird->getPosition();

    //Check for collision
    if (upPipe->getPositionX() < birdPos.x
        && birdPos.x < upPipe->getPositionX() + upPipe->getContentSize().width) {
        if (birdPos.y > downPipe->getPositionY() || birdPos.y < upPipe->getPositionY()) {

            /*
            AXLOG("\nCollision occured,\nupPipe\tx: %f y:%f\ndownPipe\tx: %f y:%f\nbird\tx: %f y:%f\nupPipe->getContentSize().width\t%f\n upPipe->getPositionX() + upPipe->getContentSize().width\t%f",
                upPipe->getPositionX(),
                upPipe->getPositionY(),
                downPipe->getPositionX(),
                downPipe->getPositionY(),
                bird->getPositionX(),
                bird->getPositionY(),
                upPipe->getContentSize().width,
                upPipe->getPositionX() + upPipe->getContentSize().width
                );
                */

            return true;
        }
    }
    return false;
}
