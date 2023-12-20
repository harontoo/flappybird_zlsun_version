#include "GameScene.h"
#include "MenuScene.h"
#include "Bird.h"
#include "Paths.h"
#include "AudioEngine.h"

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

	bird = ax::utils::createInstance<Bird>();
	bird->setPosition(ax::Point(visibleSize.width * 0.36f, visibleSize.height * 0.6f));
	addChild(bird, 1);

	tutorialNode = ax::Node::create();

	auto tutorial = ax::Sprite::create(IMG_TUTORIAL);
	tutorial->setPosition(mid_width, visibleSize.height / 2);
	tutorialNode->addChild(tutorial);

	auto text_ready = ax::Sprite::create(IMG_TEXT_READY);
	text_ready->setPosition(mid_width, visibleSize.height * 0.7);
	tutorialNode->addChild(text_ready);

	addChild(tutorialNode, 2);

	scoreLabel = ax::Label::createWithBMFont(FNT_FONT, "0", ax::TextHAlignment::CENTER);
	scoreLabel->setAnchorPoint(ax::Point(0.5f, 0.5f));
	scoreLabel->setPosition(mid_width, visibleSize.height * 0.9);
	addChild(scoreLabel, 3);


	auto listener = ax::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = AX_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	schedule(AX_SCHEDULE_SELECTOR(GameScene::update));

	return true;
}



bool GameScene::onTouchBegan(ax::Touch* touch, ax::Event* event)
{
	auto pos = touch->getLocationInView();
	if (pos.x < 20 && pos.y < 20) {
		cheating = !cheating;
		return true;
	}
	if (state == State::Tutorial) {
		startPlaying();
		ax::AudioEngine::play2d(SFX_WING);

		bird->flyUp();
		return true;
	}
	else if (state == State::Playing) {
		ax::AudioEngine::play2d(SFX_WING);
		bird->flyUp();
		return true;
	}
	return false;

}

void GameScene::startPlaying()
{
	//hides the tutorial node
	tutorialNode->setVisible(false);
	//start adding pipes to the game
	gameLayer->addPipes();
	//run bird's fallAnimation
	bird->fall();
	//switch GameScene's state to State::Playing
	state = State::Playing;
}

void GameScene::gameOver()
{
	state = State::GameOver;

	scoreLabel->setVisible(false);

	ax::Size visibleSize = ax::Director::getInstance()->getVisibleSize();
	ax::Point origin = ax::Director::getInstance()->getVisibleOrigin();
	float scrWidth = visibleSize.width;
	float scrHeight = visibleSize.height;
	float midWidth = scrWidth / 2;
	float midHeight = scrHeight / 2;

	auto gameover = ax::Sprite::create(IMG_TEXT_GAME_OVER);
	gameover->setPosition(midWidth, scrHeight * 0.7);
	addChild(gameover, 4);

	auto panel = ax::Sprite::create(IMG_SCORE_PANEL);
	panel->setPosition(midWidth, midHeight);
	addChild(panel, 4);

	int score = gameLayer->getScore();
	auto finalScoreLabel = ax::Label::createWithBMFont(FNT_SCORE, ax::Value(score).asString());
	finalScoreLabel->setAnchorPoint(ax::Point(1.0f, 1.0f));
	finalScoreLabel->setPosition(midWidth + 100, midHeight + 30);
	addChild(finalScoreLabel, 5);

	int record = readRecord();
	if (score > record) {
		record = score;
		writeRecord(record);
		auto newRecord = ax::Sprite::create(IMG_NEW);
		newRecord->setPosition(midWidth + 34, midHeight - 4);
		addChild(newRecord, 5);
	}
	auto recordLabel = ax::Label::createWithBMFont(FNT_SCORE, ax::Value(record).asString());
	recordLabel->setAnchorPoint(ax::Point(1.0f, 1.0f));
	recordLabel->setPosition(midWidth + 100, midHeight - 10);
	addChild(recordLabel, 5);

	if (score >= 10) {
		int idx = 0;
		static int scoreLevel[] = { 20, 30, 40 };
		while (idx < 3 && score >= scoreLevel[idx]) {
			++idx;
		}
		//auto medal = Sprite::create(String::createWithFormat(IMAGES_DIR"medals_%d.png", idx)->getCString());
		auto medal = ax::Sprite::create(ax::StringUtils::format(IMAGES_DIR"medals_%d.png", idx));

		medal->setPosition(scrWidth * 0.27f, scrHeight * 0.49f);
		addChild(medal, 5);
	}

	auto menu = ax::Menu::create(
		ax::MenuItemSprite::create(
			ax::Sprite::create(IMG_START_BTN),
			ax::Sprite::create(IMG_START_BTN_PRESSED),
			nullptr,
			MenuScene::startGame
		),
		ax::MenuItemSprite::create(
			ax::Sprite::create(IMG_CLOSE_BTN),
			ax::Sprite::create(IMG_CLOSE_BTN_PRESSED),
			nullptr,
			MenuScene::endGame
		),
		nullptr
	);
	menu->alignItemsHorizontally();
	menu->setPosition(midWidth, scrHeight * 0.3);
	addChild(menu, 4);

}

void GameScene::update(float dt)
{
	if (state == State::Playing) {
		bird->update(dt);
		gameLayer->update(dt);
		if (!cheating && gameLayer->checkCollision(bird)) {
			ax::AudioEngine::play2d(SFX_HIT);
			gameLayer->stop();
			bird->fall();
			state = State::Falling;
		}
		else if (gameLayer->hitGround(bird)) {
	

			ax::AudioEngine::play2d(SFX_DIE);
			gameLayer->stop();
			bird->die();
			gameOver();
		}
		updateScore();
	}
	else if (state == State::Falling) {
		bird->update(dt);
		if (gameLayer->hitGround(bird)) {
			ax::AudioEngine::play2d(SFX_DIE);
			bird->die();
			gameOver();
		}
	}
}

void GameScene::updateScore()
{
	int score = gameLayer->getScore();
	scoreLabel->setString(ax::Value(score).asString());
}


int GameScene::readRecord()
{
	return ax::UserDefault::getInstance()->getIntegerForKey("score", 0);
}

void GameScene::writeRecord(int record)
{
	ax::UserDefault::getInstance()->setIntegerForKey("score", record);
}

