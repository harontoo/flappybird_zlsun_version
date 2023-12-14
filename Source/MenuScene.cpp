#include "MenuScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "Paths.h"

ax::Scene* MenuScene::createScene()
{
	auto scene = ax::Scene::create();
	//game layer
	auto bg =ax::utils::createInstance<GameLayer>();
	scene->addChild(bg, 1);

	//menu scene
	auto game_menu = ax::utils::createInstance<MenuScene>();
	scene->addChild(game_menu, 1);

	return scene;
}

bool MenuScene::init()
{
	if (!ax::Layer::init())
	{
		return false;
	}
	//Setup the menu scene
	ax::Size visibleSize = ax::Director::getInstance()->getVisibleSize();
	ax::Point origin = ax::Director::getInstance()->getVisibleOrigin();
	auto mid_width = visibleSize.width / 2;

	//Bird

	//Logo setup
	auto logo = ax::Sprite::create(IMG_LOGO);
	logo->setPosition(mid_width, visibleSize.height * 0.6);
	addChild(logo, 2);


	return true;
}

 void MenuScene::startGame(ax::Ref* sender)
{

}


void MenuScene::endGame(ax::Ref* sender)
{

}

