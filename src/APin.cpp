#include "APin.h"
#include "debug.h"

#include <utility>

using namespace bcm;

APin::APin(PinNumber pinNo) : IPin(pinNo)
{
	DBGPRINT("PinNumber = %d", _pinNo);
}

APin::APin(APin&& other) : IPin(std::move(other))
{
}

PinLevel APin::read() const
{
	return static_cast<PinLevel>(bcm2835_gpio_lev(_pinNo));
}
