#ifndef _INPUTPIN_H_
#define _INPUTPIN_H_
#include "IPin.h"
#include "APin.h"

namespace bcm {

enum class PinDetect
{
	RisingEdge,
	FallingEdge,
	Low,
	High,
	None,
};

class InputPin : public APin
{
	protected:
		PinDetect _currentPinDetect;
	public:
		InputPin(PinNumber pinNo);
		InputPin(InputPin&& other);
		virtual ~InputPin() override;
		void setDetect(PinDetect pinDetect);
		void clearDetect();
		/*!
		 * \brief Get the currently set pin detect status.
		 * \return the PinDetect status.
		 */
		PinDetect getDetect();
		/*!
		 * \brief  Check if the status set by setDetect() occured.
		 * \return `true` if the set PinDetect status occured; 
		 *         otherwise `false`. If no pin detect is set the method
		 *         returns `false`;
		 */
		bool      hasDetected(bool clear = true);
};

} // namespace bcm

#endif // _INPUTPIN_H_
