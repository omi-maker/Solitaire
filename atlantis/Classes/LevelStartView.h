#include "cocos2d.h"
#include "stdlib.h"
#include "string"
#include "vector"
#include "map"

//NS_CC_BEGIN
const int PROP_LIST_NUM = 5;
const int PROP_SELECT_NUM = 4;

class LevelStartView : public cocos2d::Layer
{
public:	
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Layer* createLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(LevelStartView);

	// a selector callback
	void nextLevelCallback(cocos2d::Ref* pSender);
	void layerCloseCallback(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);

	virtual bool onPropTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onPropTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onPropTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);

	void getPropListData(std::vector<std::string> &propList);
	void getPropList();

	std::string int2string(int index);
	void initPropList(cocos2d::Layer * pStart);
	
	void propListClick(cocos2d::Sprite * pItem);
	void selectedPropClick(cocos2d::Sprite * pItem);

	/*release m_propSelect*/
	void releasePropSelect();

private:
	//����ѡ���б����
	int getFreePropSelectSpace();
	void setFreePropSelectSpace(int index, cocos2d::Sprite * pItem);
	void resetFreePropSelectSpace(int index);

private:	
	std::map<std::string, std::string> m_propList; /*�ؿ��ĵ����б�*/
	std::map<int, cocos2d::Sprite *> m_propSelect; /*�ؿ��ĵ���ѡ���б�*/	
};
