#include "GameLayer.h"
#include "Paths.h"

GameLayer::GameLayer() 
    : speed(150)
    , pipe_distance(180)
    , pipe_width(52)
    , score(0)
    , visibleSize(ax::Director::getInstance()->getVisibleSize())
    , origin(ax::Director::getInstance()->getVisibleOrigin())
    , point_x(visibleSize.width * 0.36f - 26)

{
}

bool GameLayer::init() {
    if (!ax::Layer::init())
    {
        return false;
    }
    //Game 
    auto t = time(NULL);
    //get hour
    auto hour = localtime(&t)->tm_hour;
    bool is_night = hour <= 6 || hour >= 18;

    //Set background properties
    auto bg = ax::Sprite::create(is_night ? IMG_BG_NIGHT : IMG_BG_DAY);
    bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    addChild(bg, 0);

    //Set land properties
    auto land = ax::Sprite::create(IMG_LAND);
    /*auto draw_node = ax::DrawNode::create();
    draw_node->setPosition(land->getAnchorPoint());
    draw_node->drawRect(land->getAnchorPoint(), land->getContentSize(), ax::Color4F::RED);
    land->addChild(draw_node);*/
    land->setAnchorPoint(ax::Point(0, 0));
    land->setPosition(0, 0);
    //Land animation properties
    auto movement_distance = land->getContentSize().width - visibleSize.width;
    auto land_movement_duration = movement_distance / speed;
    AXLOG("visibleSize.width\t%f\nland_content_size\t%f\nmovement_distance\t%f\nland_movement_duration\t%f", visibleSize.width ,land->getContentSize().width,movement_distance, land_movement_duration);
    //Land animations
    auto land_animation_sequence = ax::Sequence::create(
        ax::MoveTo::create(land_movement_duration, ax::Point(-movement_distance, 0)),
        ax::MoveTo::create(0, ax::Point(0, 0)),
        nullptr
    );

    auto land_animation = ax::RepeatForever::create(land_animation_sequence);
    land->runAction(land_animation);

    addChild(land, 3);



    return true;
}

