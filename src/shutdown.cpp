#include "debug.h"
#include "Bcm2835.h"
#include "IPin.h"
#include "PullUpPin.h"

#include <bcm2835.h>

#include <signal.h>
#include <iostream>
#include <chrono>

#ifndef PIN_NO
#define PIN_NO Pin05 // default shutdown pin
#endif

#ifndef SAFETY_DELAY
#define SAFETY_DELAY 3000ms // default button down time before shutdown
#endif

#ifndef POLL_DELAY
#define POLL_DELAY 500ms // default pin polling interval
#endif

using bcm::Bcm2835;
using bcm::PinDetect;
using bcm::PinLevel;
using bcm::PinNumber;
using bcm::PullUpPin;

using std::chrono::milliseconds;
using std::cout;
using std::endl;

// ctrl + c handler
void ctrl_c(int signo)
{
    DBGPRINT("Ctrl + C Received.");
    exit(0);
}

auto pin = Bcm2835::Instance().create<PullUpPin, PinNumber::PIN_NO>();

int main (int argc, char* argv[])
{
	using namespace std::chrono_literals;

	signal(SIGINT, ctrl_c);
	DBGPRINT("Ctrl + C Handler created.");

	const auto& bcm = Bcm2835::Instance();
	
	pin.setDetect(PinDetect::Low); // detect pin low => button press

	// enter reading loop
	do {
		DBGPRINT("Pin is %s", (pin.read() == PinLevel::High ? "HIGH" : "LOW"));
		// check if a LOW-event occured and pin is still low
		if (pin.hasDetected() && pin.read() == PinLevel::Low)
		{
			pin.setDetect(PinDetect::RisingEdge); // there mustn't be a rising edge
			bcm.delay(SAFETY_DELAY);              // within 5sec
			if (!pin.hasDetected())
			{
				cout << "Button down for " << SAFETY_DELAY.count() << " ms." << endl;
				break;
			}
			// start again
			pin.setDetect(PinDetect::Low);
		}
		bcm.delay(POLL_DELAY);
	} while (true);

	system("shutdown -h now"); // shutdown system

	return 0;
}
