
#include "DAutoEvent.h"

CDAutoEvent::CDAutoEvent( 
	INT nInitialState /*= 0*/,
	LPCSTR pszName /*= 0*/,
	LPVOID pArg /*= 0 */ )
	: CDEvent( 0, nInitialState, pszName, pArg )
{
}

CDAutoEvent::~CDAutoEvent()
{
}
