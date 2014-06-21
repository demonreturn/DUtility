
#include "DBase.h"
class CDLogMessage;

class CDFormatter
{
public:
	virtual ~CDFormatter(){}

	virtual void Format( const CDFormatter& msg, CDString& str ) = 0;
};

typedef std::shared_ptr<CDFormatter>		TFormatterPtr;

