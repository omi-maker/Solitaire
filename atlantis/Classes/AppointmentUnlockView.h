#ifndef _APPOINTMENT_UNLOCK_VIEW__
#define _APPOINTMENT_UNLOCK_VIEW__
#include "KButtonLayer.h"
#include "KObject.h"
#include "KButtonColor.h"
#include "KTextBase.h"

class AppointmentUnlockView : public KObject,public KButtonLayer
{
public:
	AppointmentUnlockView();
	~AppointmentUnlockView();

	static AppointmentUnlockView* create()
	{
		AppointmentUnlockView* view = new AppointmentUnlockView();
		view->init();
		view->autorelease();
		return view;
	}

	bool init();

	virtual void retain()override
	{
		KButtonLayer::retain();
	}
	virtual void release()override
	{
		KButtonLayer::release();
	}

	virtual int getReferenceCount()override
	{
		return KButtonLayer::getReferenceCount();
	}
	


private:
	/*KSharedPointer<KFSprite> _mainView;
	KSharedPointer<KTextBase> _nameTxt;	*/
};


#endif // !_APPOINTMENT_UNLOCK_VIEW__
