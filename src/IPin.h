#ifndef _IPIN_H_
#define _IPIN_H_

#include <bcm2835.h>

namespace bcm {

using Byte = uint8_t;

enum class PinNumber : Byte
{
	Pin03 = RPI_BPLUS_GPIO_J8_03,
	Pin05 = RPI_BPLUS_GPIO_J8_05,
	Pin07 = RPI_BPLUS_GPIO_J8_07,
	Pin08 = RPI_BPLUS_GPIO_J8_08,
	Pin10 = RPI_BPLUS_GPIO_J8_10,
	Pin11 = RPI_BPLUS_GPIO_J8_11,
	Pin12 = RPI_BPLUS_GPIO_J8_12,
	Pin13 = RPI_BPLUS_GPIO_J8_13,
	Pin15 = RPI_BPLUS_GPIO_J8_15,
	Pin16 = RPI_BPLUS_GPIO_J8_16,
	Pin18 = RPI_BPLUS_GPIO_J8_18,
	Pin19 = RPI_BPLUS_GPIO_J8_19,
	Pin21 = RPI_BPLUS_GPIO_J8_21,
	Pin22 = RPI_BPLUS_GPIO_J8_22,
	Pin23 = RPI_BPLUS_GPIO_J8_23,
	Pin24 = RPI_BPLUS_GPIO_J8_24,
	Pin26 = RPI_BPLUS_GPIO_J8_26,
	Pin29 = RPI_BPLUS_GPIO_J8_29,
	Pin31 = RPI_BPLUS_GPIO_J8_31,
	Pin32 = RPI_BPLUS_GPIO_J8_32,
	Pin33 = RPI_BPLUS_GPIO_J8_33,
	Pin35 = RPI_BPLUS_GPIO_J8_35,
	Pin36 = RPI_BPLUS_GPIO_J8_36,
	Pin37 = RPI_BPLUS_GPIO_J8_37,
	Pin38 = RPI_BPLUS_GPIO_J8_38,
	Pin40 = RPI_BPLUS_GPIO_J8_40,
};

enum class PinLevel : Byte
{
	Low  = LOW,  // from bcm2835 lib
	High = HIGH, // from bcm2835 lib
};

/*!
 * Pure virtual Pin which acts as an interface.
 */
class IPin
{
	protected:
		const Byte _pinNo;
	public:
		IPin(PinNumber pinNo);
		//! Delete Copy C'tor 
		IPin(const IPin&) = delete;
		//! Delete Copy Assignment operator
		IPin& operator=(const IPin&) = delete;
		//! Move C'tor
		IPin(IPin&& other);
		virtual ~IPin() = 0;
		/*!
		 * \brief  Reads the current level of the pin.
		 * \return the PinLevel
		 */
		virtual PinLevel read() const = 0;
};

} // namespace bcm

#endif // _IPIN_H_
