#include "GameScene.h"

ax::Scene* GameScene::createScene()
{
	auto scene = ax::Scene::create();
	auto game_scene = ax::utils::createInstance<GameScene>();

	scene->addChild(game_scene, 0);
	return scene;
}
bool GameScene::init()
{
	if (!ax::Layer::init())
	{
		return false;
	}
	
	cheating = false;
	state = State::Tutorial;

	ax::Size visibleSize = ax::Director::getInstance()->getVisibleSize();
	ax::Point origin = ax::Director::getInstance()->getVisibleOrigin();
	float mid_width = visibleSize.width / 2;


	gameLayer = ax::utils::createInstance<GameLayer>();
	addChild(gameLayer, 0);

	return true;
}

