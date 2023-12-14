#pragma once
#include "axmol.h"
#include "GameLayer.h"
#include "Bird.h"

class GameScene : public ax::Layer
{
public:
	static ax::Scene* createScene();
	bool init();

	void startPlaying();
	void gameOver();

	void update(float dt);
	void updateScore();

	int readRecord();
	void writeRecord(int record);

	bool onTouchBegan(ax::Touch* touch, ax::Event* event);

private:
	enum class State{Tutorial,Playing,Falling,GameOver};

	bool cheating;
	State state;

	ax::Label* scoreLabel;
	ax::Node* tutorialNode;
	GameLayer* gameLayer;
	Bird* bird;


};