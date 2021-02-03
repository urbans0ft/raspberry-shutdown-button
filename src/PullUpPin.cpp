#include "PullUpPin.h"
#include "debug.h"

#include <utility>

using namespace bcm;

PullUpPin::PullUpPin(PinNumber pinNo) : InputPin(pinNo)
{
	DBGPRINT("PinNumber = %d", _pinNo);
	bcm2835_gpio_set_pud(_pinNo, BCM2835_GPIO_PUD_UP);
}

PullUpPin::PullUpPin(PullUpPin&& other) : InputPin(std::move(other))
{
}

