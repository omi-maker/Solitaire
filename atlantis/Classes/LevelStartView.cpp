#include "LevelStartView.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"
#include "string"

Layer* LevelStartView::createLayer()
{	
	auto layer = LevelStartView::create();	
	return layer;
}

bool LevelStartView::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/*初始化道具选择列表*/	
	for (int i = 1; i <= PROP_SELECT_NUM; i++)
	{
		Sprite *pInitPropSelect = Sprite::create();	
		pInitPropSelect->retain();		
		m_propSelect.insert(std::pair<int, Sprite*>(i,pInitPropSelect));
	}

	/*初始化道具列表*/
	getPropList();
	
	auto *rootNode = CSLoader::createNode("StartScene.csb");
	Layer *pLeaderboard = static_cast<Layer *>(rootNode->getChildByName("LeaderboardPanel"));
	pLeaderboard->setPosition(500, 210);
	auto moveTo = MoveTo::create(0.7f, Point(220, 210));
	pLeaderboard->runAction(moveTo);

	Layer *pStart = static_cast<Layer *>(rootNode->getChildByName("StartPanel"));
	ui::Button *pnextBtn = static_cast<ui::Button *>(pStart->getChildByName("nextBtn"));
	pnextBtn->addClickEventListener(CC_CALLBACK_1(LevelStartView::nextLevelCallback, this));

	ui::Button *pcloseBtn = static_cast<ui::Button *>(pStart->getChildByName("closeBtn"));
	pcloseBtn->addClickEventListener(CC_CALLBACK_1(LevelStartView::layerCloseCallback, this));

	initPropList(pStart);

	this->addChild(rootNode);
	return true;
}

void LevelStartView::nextLevelCallback(cocos2d::Ref* pSender)
{
	CCLOG("in nextLevelCallback");
}

void LevelStartView::layerCloseCallback(cocos2d::Ref* pSender)
{
	releasePropSelect();
	removeFromParent();
}

void LevelStartView::initPropList(cocos2d::Layer * pStart)
{
	std::vector<std::string> propList;

	getPropListData(propList);
	
	size_t i = 0;
	for (std::map<std::string, std::string>::iterator it = m_propList.begin(); it != m_propList.end(); ++it)
	{
		Sprite* pPropList = static_cast<Sprite *>(pStart->getChildByName(propList.at(i++)));
		Size s = pPropList->getContentSize();

		Sprite* pProp = Sprite::create(it->first);
		pProp->setScale(1.2f);
		pProp->setPosition(s.width / 2, s.height / 2);
		pProp->setTag(i + 1);
		pPropList->addChild(pProp);

		LabelTTF* propFee = LabelTTF::create(it->second, "fonts/Marker Felt.ttf",36);
		propFee->setFontFillColor(ccc3(126, 126, 126));
		propFee->setPosition(s.width-20, -s.height/2+20);
		pPropList->addChild(propFee);

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
	Vector< Node * > pStartChildren = getChildren();
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
		//log("onTouchBegan sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);			
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
	CCLOG("in onTouchEnded");
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	propListClick(target);
}

bool LevelStartView::onPropTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))
	{
		selectedPropClick(target);
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
		m_propList[propImg] = "1000";
	}
}

std::string LevelStartView::int2string(int index)
{
	char a[5];
	_itoa(index, a, 10);
	return std::string(a);
}

int LevelStartView::getFreePropSelectSpace()
{
	std::map<int, Sprite * >::iterator _it;
	int index = 0;	
	for (_it = m_propSelect.begin(); _it != m_propSelect.end(); _it++){
		index ++;			
		if (_it->second->getTag() == -1)
		{
			_it->second->release();
			break;
		}
	}	
	return index;
}

void LevelStartView::setFreePropSelectSpace(int index, Sprite * pItem)
{
	m_propSelect[index] = pItem;
}

void LevelStartView::resetFreePropSelectSpace(int index)
{
	Sprite *pInitPropSelect = Sprite::create();
	pInitPropSelect->retain();
	m_propSelect[index] = pInitPropSelect;
}


void LevelStartView::selectedPropClick(cocos2d::Sprite * pItem)
{
	int index = pItem->getTag();	
	Sprite *  propListIndex = m_propSelect.at(index);
	propListIndex->setOpacity(255);
	this->getEventDispatcher()->resumeEventListenersForTarget(propListIndex);
	resetFreePropSelectSpace(index);
	pItem->removeFromParent();
}

void LevelStartView::releasePropSelect()
{
	std::map<int, Sprite * >::iterator _it;
	for (_it = m_propSelect.begin(); _it != m_propSelect.end(); _it++){	
		if (_it->second->getTag() == -1)
		{
			_it->second->release();
		}
	}
}