#include "Bcm2835.h"
#include "debug.h"

#include <bcm2835.h>

#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace bcm;

using std::cout;
using std::endl;
using std::chrono::milliseconds;
using std::chrono::microseconds;

Bcm2835::Bcm2835()
{
	DBGPRINT("Initializing bcm2835 library.");
	if (!bcm2835_init())
    {
        throw std::runtime_error("bcm2835_init() failed!");
	}
}

Bcm2835::~Bcm2835() noexcept(false)
{
	DBGPRINT("Closing bcm2835 library.");
	if (!bcm2835_close())
	{
		throw std::runtime_error("bcm2835_close() failed!");
	}
}

#ifdef delay // defined in the bcm2835 library
#undef delay
#endif

void Bcm2835::delay(const milliseconds& ms) const noexcept
{
	DBGPRINT("delay for %lld ms.", ms.count());
	bcm2835_delay(ms.count());
}

void Bcm2835::delay(const microseconds& us) const noexcept
{
	DBGPRINT("delay for %lld us.", us.count());;
	bcm2835_delayMicroseconds(static_cast<uint64_t>(us.count()));
}
