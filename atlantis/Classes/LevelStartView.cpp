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


	auto *propNode = CSLoader::createNode("PropScene.csb");
	//Sprite *pProp = static_cast<Sprite *>(propNode->getChildByName("prop_1"));
	Sprite* pPropList = static_cast<Sprite *>(pStart->getChildByName("prop_list_1"));
	
	Sprite* pProp = Sprite::create("prop 1.png");
	pProp->setPosition(0, 0);
	pPropList->addChild(pProp);	
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