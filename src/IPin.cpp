#include "IPin.h"
#include "debug.h"

using namespace bcm;

IPin::IPin(PinNumber pinNo) : _pinNo{static_cast<Byte>(pinNo)}
{
	DBGPRINT("PinNumber = %d", _pinNo);
}

IPin::~IPin()
{
	DBGPRINT("PinNumber = %d", _pinNo);
}

IPin::IPin(IPin&& other) : _pinNo{other._pinNo}
{
	DBGPRINT("PinNumber = %d", _pinNo);
}

