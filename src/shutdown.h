#ifndef _SHUTDOWN_H_
#define _SHUTDOWN_H_
// #############################################################################
#ifndef PIN_NO
#define PIN_NO Pin05        // default shutdown pin
#endif

#ifndef SAFETY_DELAY
#define SAFETY_DELAY 3000ms // default button down time before shutdown
#endif

#ifndef POLL_DELAY
#define POLL_DELAY 500ms    // default pin polling interval
#endif
// #############################################################################
#endif // _SHUTDOWN_H_
