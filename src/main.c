#include "shell.h"
#include "event_tap.h"

#include "shell.c"
#include "event_tap.c"

typedef const char* mod;

typedef struct bind {
    CGEventFlags flags;
    CGKeyCode key;
    char* cmd;
} bind;

static size_t len = 0;
static bind binds[5];

EVENT_TAP_CALLBACK(test) {
    if(type == kCGEventKeyDown || type == kCGEventFlagsChanged) {
        CGEventFlags flags = CGEventGetFlags(event);
        CGKeyCode kc = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
        bool repeat = CGEventGetIntegerValueField(event, kCGKeyboardEventAutorepeat);

        for(int i = 0; i < len; ++i) {
            bind* b = &binds[i];
            if(b->key == kc && flags & b->flags) {
                shell_exec_cmd(b->cmd); 
            }
        }
    }

    return event;
}

int main(int argc, char* argv[]) {
    bind b0 = { kCGEventFlagMaskControl, kVK_F12, "echo HELLO WORLD" };
    binds[0] = b0;
    len++;

    shell_init();

    event_tap tap;
    tap.mask = (1 << kCGEventKeyDown) | (1 << kCGEventFlagsChanged);
    event_tap_init(&tap, test);

    CFRunLoopRun();

    return 0;
}
