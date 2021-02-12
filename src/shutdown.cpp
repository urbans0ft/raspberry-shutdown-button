// - custom -------------------------------------------------------------------
#include "shutdown.h"
#include "debug.h"
#include "Bcm2835.h"
#include "IPin.h"
#include "PullUpPin.h"
// - 3rd party ----------------------------------------------------------------
#include <bcm2835.h>
// - std ----------------------------------------------------------------------
#include <signal.h> // signal - ctrl + c
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <unistd.h> // getopt
// - using --------------------------------------------------------------------
using bcm::Bcm2835;
using bcm::PinDetect;
using bcm::PinLevel;
using bcm::PinNumber;
using bcm::PullUpPin;

using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::filesystem::create_directories;
using std::filesystem::copy_file;
using std::filesystem::copy_options;
using std::ofstream;

using namespace std::chrono_literals;
// ----------------------------------------------------------------------------
// the shutdown pin (depends on conditional compilation)
auto pin = Bcm2835::Instance().create<PullUpPin, PinNumber::PIN_NO>();
// ============================================================================
int main (int argc, char* argv[])
{
	signal(SIGINT, ctrl_c);
	DBGPRINT("Ctrl + C Handler created.");

	DBGPRINT("Parsing cmd line arguments.");
	parseCmdArgs(argc, argv);
	if (argc > 1) // exit if not started as daemon
		return 0;

	const auto& bcm = Bcm2835::Instance();
	
	pin.setDetect(PinDetect::Low); // detect pin low => button press

	// enter reading loop
	do {
		DBGPRINT("Pin is %s", (pin.read() == PinLevel::High ? "HIGH" : "LOW"));
		// check if a LOW-event occured and pin is still low
		if (pin.hasDetected() && pin.read() == PinLevel::Low)
		{
			pin.setDetect(PinDetect::RisingEdge); // there mustn't be a rising edge
			bcm.delay(SAFETY_DELAY);              // within SAFETY_DELAY
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
// ============================================================================
void usage()
{
	cout << "shutdown " << VERSION <<  ", a non-interactive shutdown daemon." << endl;
	cout << "Usage: shutdown [OPTION]" << endl << endl;
	cout << "Build with: PIN_NO=" << STR(PIN_NO)
		 << " SAFETY_DELAY=" << STR(SAFETY_DELAY)
		 << " POLL_DELAY=" << STR(POLL_DELAY) << endl << endl;
	cout << "OPTIONS:" << endl;
	cout << "  -h Print this info." << endl;
	cout << "  -I Install the service to ~/shutdown.d/" << endl;
	cout << "  -V Print version info." << endl;
	cout << endl;

}
// ============================================================================
void install()
{
	// stop service just in case it's already running
	DBGPRINT("systemctl stop shutdown.service");
	system("systemctl stop shutdown.service");
	// write service file
	DBGPRINT("Write service file shutdown.service.");
	ofstream fout{"/etc/systemd/system/shutdown.service"};
	fout << "[Unit]" << endl;
	fout << "Description=Shutdown by pressing a Button" << endl;
	fout << "After=network.target" << endl;
	fout << endl;
	fout << "[Service]" << endl;
	fout << "User=pi" << endl;
	fout << "Type=simple" << endl;
	fout << "WorkingDirectory=/home/pi/shutdown.d" << endl;
	fout << "ExecStart=/usr/bin/sudo /home/pi/shutdown.d/shutdown" << endl;
	fout << endl;
	fout << "[Install]" << endl;
	fout << "WantedBy=multi-user.target" << endl;
	fout.close();
	// copy service executable
	DBGPRINT("Copy shutdown file to ~/shutdown.d/");
	create_directories("/home/pi/shutdown.d");
	copy_file("shutdown", "/home/pi/shutdown.d/shutdown", copy_options::update_existing);
	// enable service
	DBGPRINT("systemctl enable shutdown.service");
	system("systemctl enable shutdown.service");
	// start service
	DBGPRINT("systemctl start shutdown.service");
	system("systemctl start shutdown.service");
}
// ============================================================================
void parseCmdArgs(int argc, char* argv[])
{
	int c;
	while ((c = getopt(argc, argv, "hIV")) != -1) {
		switch (c) {
		case 'h':
			usage();
			break;
		case 'I':
			install();
			break;
		case 'V':
			cout << "shutdown " << VERSION << " " << __DATE__ << " " << __TIME__ << endl;
			break;
		case '?':
			usage();
			break;
		default:
			printf ("?? getopt returned character code 0%o ??\n", c);
		}
	}
	if (optind < argc) {
		printf ("non-option ARGV-elements: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		printf ("\n");
	}
}
// ============================================================================
// ctrl + c handler
void ctrl_c(int signo)
{
    DBGPRINT("Ctrl + C Received.");
    exit(0);
}
// ============================================================================
