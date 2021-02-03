#include "debug.h"
#include "Bcm2835.h"
#include "IPin.h"
#include "PullUpPin.h"

#include <bcm2835.h>

#include <signal.h>
#include <iostream>
#include <chrono>

using bcm::Bcm2835;
using bcm::PinDetect;
using bcm::PinLevel;
using bcm::PinNumber;
using bcm::PullUpPin;

using std::cout;
using std::endl;

// ctrl + c handler
void ctrl_c(int signo)
{
    DBGPRINT("Ctrl + C Received.");
    exit(0);
}

auto pin05 = Bcm2835::Instance().create<PullUpPin, PinNumber::Pin05>();

int main (int argc, char* argv[])
{
	using namespace std::chrono_literals;

	signal(SIGINT, ctrl_c);
	DBGPRINT("Ctrl + C Handler created.");

	const auto& bcm = Bcm2835::Instance();
	pin05.setDetect(PinDetect::Low); // detect pin low => button press

	// enter reading loop
	do {
		DBGPRINT("Pin is %s", (pin05.read() == PinLevel::High ? "HIGH" : "LOW"));
		// check if a LOW-event occured and pin is still low
		if (pin05.hasDetected() && pin05.read() == PinLevel::Low)
		{
			pin05.setDetect(PinDetect::RisingEdge); // there mustn't be a rising edge
			bcm.delay(5000ms);                      // within 5sec
			if (!pin05.hasDetected())
			{
				cout << "Button down for 5 seconds." << endl;
				break;
			}
			// start again
			pin05.setDetect(PinDetect::Low);
		}
		bcm.delay(500ms);
	} while (true);

	return 0;
}
