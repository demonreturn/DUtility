
#ifndef _D_AUTO_EVENT_H_
#define _D_AUTO_EVENT_H_

#include "DEvent.h"

class CDAutoEvent : public CDEvent
{
public:
	CDAutoEvent(
		INT nInitialState = 0,
		LPCSTR pszName = 0,
		LPVOID pArg = 0 );

	
	~CDAutoEvent();
};

#endif	// _D_AUTO_EVENT_H_

