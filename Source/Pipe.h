#pragma once
#include "axmol.h"
#include "Bird.h"



class Pipe : public ax::Node
{
public:

    bool init();


    void setRandomPositionY();
    float getPositionX();
    void setPositionX(float x);
    bool checkCollision(Bird* bird);

private:
    ax::Sprite* upPipe;
    ax::Sprite* downPipe;

};
