#ifndef _BCM2835_H_
#define _BCM2835_H_

#include "IPin.h"
#include "PullUpPin.h"

#include <type_traits>
#include <chrono>

namespace bcm
{

class Bcm2835
{
	public:
		static Bcm2835& Instance()
		{
			static Bcm2835 _instance;
			return _instance;
		}
		~Bcm2835() noexcept(false);
		Bcm2835(const Bcm2835&) = delete;
		Bcm2835& operator=(const Bcm2835&) = delete;

		// template create only valid for derived classes of IPin
		template<class T, PinNumber pinNo,
		typename = std::enable_if_t<std::is_base_of<IPin, T>::value> >
		inline T create()
		{
			return T{pinNo};
		}

		void delay(const std::chrono::milliseconds& ms);
		void delay(const std::chrono::microseconds& us);

	private:
		Bcm2835();
};

} // namespace bcm

#endif // _BCM2835_H_
