#include "LevelStartView.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "string"

Layer* LevelStartView::createStartLayer()
{	
	init();

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
	
	initPropList(pStart);	

	p_mlayer->addChild(rootNode);
	return p_mlayer;
}

bool LevelStartView::init()
{
	/*初始化道具选择列表*/	
	Sprite *pInitPropSelect = Sprite::create();
	for (int i = 1; i <= PROP_SELECT_NUM; i++)
	{	
		m_propSelect[i] = pInitPropSelect;
	}

	/*初始化道具列表*/
	getPropList();

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

bool LevelStartView::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
		// 获取事件所绑定的 target 
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		// 获取当前点击点所在相对按钮的位置坐标
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		// 点击范围判断检测
		if (rect.containsPoint(locationInNode))
		{
			log("onTouchBegan sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);			
			propListClick(target);
			return true;
		}
		return false;
}
void LevelStartView::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
	CCLOG("in onTouchMoved");
}
void LevelStartView::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	
	CCLOG("in onTouchEnded");
}

bool LevelStartView::onPropTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		propSelectClick(target);
		return true;
	}
	return false;
}

void LevelStartView::onPropTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
	CCLOG("in onPropTouchMoved");
}
void LevelStartView::onPropTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
	CCLOG("in onPropTouchEnded");
}

void LevelStartView::getPropListData(std::vector<std::string> &propList)
{	
	for (int i = 1; i <= 5; i++)
	{		
		std::string baseProp = "prop_list_";
		std::string propListName = baseProp + int2string(i);
		propList.push_back(propListName);
	}
}

void LevelStartView::getPropList()
{
	std::string prefix = "prop_";
	std::string suffix = ".png";
	
	for (int i = 1; i <= 5; i++)
	{
		std::string propImg = prefix + int2string(i) + suffix;
		m_propList.push_back(propImg);
	}
}

std::string LevelStartView::int2string(int index)
{
	char a[2];
	_itoa(index, a, 10);
	return std::string(a);
}

int LevelStartView::getFreePropSelectSpace()
{
	std::map<int, Sprite * >::iterator _it;
	int index = 0;

	/**/for (int i = 1; i < 4; i++)
	{
		Sprite * p = this->m_propSelect[i];
		int aa = p->getTag();
	}

	index = 2;
	/*for (_it = m_propSelect.begin(); _it != m_propSelect.end(); _it++){
		index ++;
		Sprite * p = _it->second;
		int aa = p->getTag();
		if (_it->second->getTag() == -1)
		{
			break;
		}
	}*/
	return index;
}

void LevelStartView::setFreePropSelectSpace(int index, Sprite * pItem)
{
	m_propSelect[index] = pItem;
}

void LevelStartView::resetFreePropSelectSpace(int index)
{
	m_propSelect[index] = Sprite::create();
}

void LevelStartView::initPropList(cocos2d::Layer * pStart)
{
	std::vector<std::string> propList;	

	getPropListData(propList);


	for (size_t i = 0; i < propList.size(); i++)
	{
		Sprite* pPropList = static_cast<Sprite *>(pStart->getChildByName(propList.at(i)));
		Size s = pPropList->getContentSize();

		Sprite* pProp = Sprite::create(m_propList.at(i));
		pProp->setScale(1.2f);
		pProp->setPosition(s.width / 2, s.height / 2);
		pProp->setTag(i + 1);
		pPropList->addChild(pProp);

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(LevelStartView::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(LevelStartView::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(LevelStartView::onTouchEnded, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pProp);
	}
}

void LevelStartView::propListClick(cocos2d::Sprite * pItem)
{
	Vector< Node * > pStartChildren = p_mlayer->getChildren();
	Node * aa = pStartChildren.at(0);
	Layer *pStart = static_cast<Layer *>(aa->getChildByName("StartPanel"));
	int clickIndex = pItem->getTag();

	int propSelectSpaceIndex = getFreePropSelectSpace();	
	Sprite* prop_select = static_cast<Sprite *>(pStart->getChildByName(std::string("Sprite_19_") + int2string(propSelectSpaceIndex)));
	Sprite* pProp = Sprite::create(std::string("prop_") + int2string(clickIndex) + std::string(".png"));

	setFreePropSelectSpace(propSelectSpaceIndex, pItem);

	pProp->setScale(0.8f);
	Size s = prop_select->getContentSize();
	pProp->setPosition(s.width / 2, s.height / 2);
	pProp->setTag(propSelectSpaceIndex);
	prop_select->addChild(pProp);

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(LevelStartView::onPropTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(LevelStartView::onPropTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(LevelStartView::onPropTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, pProp);

	pItem->setOpacity(180);
	this->getEventDispatcher()->pauseEventListenersForTarget(pItem);
}

void LevelStartView::propSelectClick(cocos2d::Sprite * pItem)
{
	int index = pItem->getTag();
	resetFreePropSelectSpace(index);
	Sprite *  propListIndex = m_propSelect.at(index);
	propListIndex->setOpacity(255);
	this->getEventDispatcher()->resumeEventListenersForTarget(propListIndex);
	pItem->removeFromParent();
}