#include "cocos2d.h"

class LevelStartView : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	cocos2d::Layer* createStartLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void nextLevelCallback(cocos2d::Ref* pSender);
	void layerCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	//CREATE_FUNC(LevelStartView);
private:
	 Layer *p_mlayer;
};
