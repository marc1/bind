#include "shell.h"
#include "event_tap.h"

#include "shell.c"
#include "event_tap.c"

EVENT_TAP_CALLBACK(test) {
    if(type == kCGEventKeyDown || type == kCGEventFlagsChanged) {
        CGEventFlags flags = CGEventGetFlags(event);
        CGKeyCode kc = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        bool repeat = CGEventGetIntegerValueField(event, kCGKeyboardEventAutorepeat);

        if(kc == kVK_ANSI_A) {
            shell_exec_cmd("echo Hello world");
        }
    }

    return event;
}

int main(int argc, char* argv[]) {
    event_tap tap;
    tap.mask = (1 << kCGEventKeyDown) | (1 << kCGEventFlagsChanged);

    shell_init();
    event_tap_init(&tap, test);

    CFRunLoopRun();

    return 0;
}
