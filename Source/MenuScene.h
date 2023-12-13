#pragma once

#include "axmol.h"


class MenuScene : public ax::Layer
{
public:
	static ax::Scene* createScene();
	bool init();

	static void startGame(ax::Ref* sender);
	static void endGame(ax::Ref* sender);
};