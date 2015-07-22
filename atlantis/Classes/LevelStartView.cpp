#include "LevelStartView.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"

Layer* LevelStartView::createStartLayer()
{
	p_mlayer = Layer::create();
	auto *rootNode = CSLoader::createNode("StartScene.csb"); 
	
	Layer *pLeaderboard = static_cast<Layer *>(rootNode->getChildByName("LeaderboardPanel"));
	pLeaderboard->setPosition(500,210);
	auto moveTo = MoveTo::create(0.5f, Point(220, 210));	
	pLeaderboard->runAction(moveTo);
	
	Layer *pStart = static_cast<Layer *>(rootNode->getChildByName("StartPanel"));	
	ui::Button *pnextBtn = static_cast<ui::Button *>(pStart->getChildByName("nextBtn"));
	pnextBtn->addClickEventListener(CC_CALLBACK_1(LevelStartView::nextLevelCallback,this));

	ui::Button *pcloseBtn = static_cast<ui::Button *>(pStart->getChildByName("closeBtn"));
	pcloseBtn->addClickEventListener(CC_CALLBACK_1(LevelStartView::layerCloseCallback,this));

	p_mlayer->addChild(rootNode);
	return p_mlayer;
}

bool LevelStartView::init()
{
	return true;
}

void LevelStartView::nextLevelCallback(cocos2d::Ref* pSender)
{
	CCLOG("in nextLevelCallback");
}

void LevelStartView::layerCloseCallback(cocos2d::Ref* pSender)
{
	p_mlayer->removeFromParent();
}