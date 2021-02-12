#ifndef _SHUTDOWN_H_
#define _SHUTDOWN_H_
// #############################################################################
#define MAJOR 0
#define MINOR 1
#define PATCH 0

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define VERSION STR(MAJOR) "." STR(MINOR) "." STR(PATCH)

#ifndef PIN_NO
#define PIN_NO Pin05        // default shutdown pin
#endif

#ifndef SAFETY_DELAY
#define SAFETY_DELAY 3000ms // default button down time before shutdown
#endif

#ifndef POLL_DELAY
#define POLL_DELAY 500ms    // default pin polling interval
#endif

void ctrl_c(int signo);
void parseCmdArgs(int argc, char* argv[]);
void usage();
void install();
// #############################################################################
#endif // _SHUTDOWN_H_
