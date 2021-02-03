#ifndef _PULLUPPIN_H_
#define _PULLUPPIN_H_

#include "InputPin.h"

namespace bcm {

class PullUpPin : public InputPin
{
	public:
		PullUpPin(PinNumber pinNo);
		PullUpPin(PullUpPin&& other);
};

} // namespace bcm

#endif // _PULLUPPIN_H_
