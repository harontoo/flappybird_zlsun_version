#include "MenuScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "Paths.h"

ax::Scene* MenuScene::createScene()
{
	auto scene = ax::Scene::create();
	//game layer
	auto bg =ax::utils::createInstance<GameLayer>();
	//menu scene
	//auto game_menu = MenuScene::create();
	scene->addChild(bg, 1);
	
	return scene;
}

bool MenuScene::init()
{
	return true;
}

 void MenuScene::startGame(ax::Ref* sender)
{

}


void MenuScene::endGame(ax::Ref* sender)
{

}

