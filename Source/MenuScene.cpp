#include "AudioEngine.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "Bird.h"
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
	auto bird = ax::utils::makeInstance<Bird>();
	bird->setPosition(mid_width, visibleSize.height * 0.6);
	addChild(bird, 1);

	AXLOG("Bird position x:%f\nposition y:%f", bird->getPositionX(), bird->getPositionY());
	//Logo setup
	auto logo = ax::Sprite::create(IMG_LOGO);
	logo->setPosition(mid_width, visibleSize.height * 0.8);
	addChild(logo, 2);

	
	//MainMenu options setup
	//menu option start
	auto menu_option_start = ax::MenuItemSprite::create(ax::Sprite::create(IMG_START_BTN), ax::Sprite::create(IMG_START_BTN_PRESSED), nullptr, MenuScene::startGame);
	//menu option close
	auto menu_option_close = ax::MenuItemSprite::create(ax::Sprite::create(IMG_CLOSE_BTN), ax::Sprite::create(IMG_CLOSE_BTN_PRESSED), nullptr, MenuScene::endGame);
	//menu container
	auto menu_container = ax::Menu::create(menu_option_start,menu_option_close,nullptr);
	menu_container->alignItemsHorizontally();
	menu_container->setPosition(mid_width, visibleSize.height * 0.4);

	addChild(menu_container, 3);

	return true;
}

 void MenuScene::startGame(ax::Ref* sender)
{
	 auto gameScene = GameScene::createScene();
	 auto transition = ax::TransitionFade::create(1.0f, gameScene, ax::Color3B(0, 0, 0));
	 ax::Director::getInstance()->replaceScene(transition);

	 ax::AudioEngine::play2d(SFX_SWOOSHING);
}


void MenuScene::endGame(ax::Ref* sender)
{
	ax::AudioEngine::end();
	ax::Director::getInstance()->end();

}

