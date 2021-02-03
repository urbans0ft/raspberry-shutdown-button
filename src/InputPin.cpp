#include "InputPin.h"
#include "APin.h"
#include "debug.h"

#include <bcm2835.h>

#include <utility>

using namespace bcm;

InputPin::InputPin(PinNumber pinNo) : APin(pinNo), _currentPinDetect{PinDetect::None}
{
	DBGPRINT("PinNumber = %d", _pinNo);
	bcm2835_gpio_fsel(_pinNo, BCM2835_GPIO_FSEL_INPT);
}

InputPin::InputPin(InputPin&& other) : APin(std::move(other))
{
}

InputPin::~InputPin()
{
	DBGPRINT("Tidy up!");
	clearDetect(); // remove detection
}

void InputPin::setDetect(PinDetect pinDetect)
{
	// clear the old value first
	if (_currentPinDetect != PinDetect::None)
		clearDetect(); // sets _currentPinDetect to None

	if (_currentPinDetect == pinDetect)
		return;

	switch(pinDetect)
	{
		case PinDetect::RisingEdge:
			DBGPRINT("Setting rising edge detection.");
			bcm2835_gpio_ren(_pinNo);
			break;
		case PinDetect::FallingEdge:
			DBGPRINT("Setting falling edge detection.");
			bcm2835_gpio_fen(_pinNo);
			break;
		case PinDetect::Low:
			DBGPRINT("Setting low detection.");
			bcm2835_gpio_len(_pinNo);
			break;
		case PinDetect::High:
			DBGPRINT("Setting high detectino.");
			bcm2835_gpio_hen(_pinNo);
			break;
		case PinDetect::None: //! \todo is this ever called?
			DBGPRINT("Setting none detectino.");
			clearDetect(); // sets _currentPinDetect
			return;
	}
	_currentPinDetect = pinDetect;
}

void InputPin::clearDetect()
{
	if (_currentPinDetect == PinDetect::None)
		return;

	switch (_currentPinDetect)
	{
	case PinDetect::RisingEdge:
		DBGPRINT("Clearing rising edge detection.");
		bcm2835_gpio_clr_ren(_pinNo);
		break;
	case PinDetect::FallingEdge:
		DBGPRINT("Clearing falling edge detection.");
		bcm2835_gpio_clr_fen(_pinNo);
		break;
	case PinDetect::Low:
		DBGPRINT("Clearing low detection.");
		bcm2835_gpio_clr_len(_pinNo);
		break;
	case PinDetect::High:
		DBGPRINT("Clearing high detection.");
		bcm2835_gpio_clr_hen(_pinNo);
		break;
	}
	// after clearing set (possible) event status back
	bcm2835_gpio_set_eds(_pinNo);
	_currentPinDetect = PinDetect::None;
}

PinDetect InputPin::getDetect()
{
	return _currentPinDetect;
}

bool InputPin::hasDetected(bool clear)
{
	if (_currentPinDetect == PinDetect::None)
		return false;
	bool detectStatus = bcm2835_gpio_eds(_pinNo) == HIGH;
	DBGPRINT("hasDetected => %s", (detectStatus) ? "true" : "false");
	if (clear)
		bcm2835_gpio_set_eds(_pinNo);
	return detectStatus;
}
