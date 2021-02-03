#ifndef _APIN_H_
#define _APIN_H_

#include "IPin.h"

#include <bcm2835.h>

namespace bcm {

/*!
 * Abstract Pin which acts as an abstract class.
 */
class APin : public IPin
{
	public:
    	APin(PinNumber pinNo);
		APin(APin&& other);
		virtual ~APin() override {}
		/*!
		 * \brief  Reads the current level on the specified pin
		 *         and returns either HIGH or LOW. Works whether
		 *         or not the pin is an input or an output.
		 * \return the current PinLevel.
		 */
        PinLevel read() const final;
};

} // namespace bcm

#endif // _APIN_H_

