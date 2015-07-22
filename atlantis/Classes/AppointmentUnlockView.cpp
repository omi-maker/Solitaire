#include "AppointmentUnlockView.h"
#include "KFDataManager.h"

AppointmentUnlockView::AppointmentUnlockView()
{

}

AppointmentUnlockView::~AppointmentUnlockView()
{

}

bool AppointmentUnlockView::init()
{
	if (!KButtonLayer::init())
	{
		return false;
	}

	/*KFDataManager::addWithFile("beginPanel.kflx");	
	KSharedPointer<KFSprite> sp = KFSprite::createWithLinkName("beginPanel").dynamicCast<KFSprite>();	
	_mainView = sp->getChildByName("beginPanel").dynamicCast<KFSprite>();

	_nameTxt = _mainView->getChildByName("levelTxt").dynamicCast<KTextBase>();	
	_nameTxt->setText("Level 30");
	this->addChild(sp->getDisplayNode());*/

	return true;
}
