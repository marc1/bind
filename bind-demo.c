#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>

static char* shell = NULL;

void init_shell(void) {
    if(!shell) {
        char* env_shell = getenv("SHELL");
        shell = env_shell ? env_shell : "/bin/bash";
    }
}

CGEventRef callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {
    if(type == kCGEventKeyDown) {
        CGKeyCode kc = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

        if(kc != kVK_ANSI_B)
            return event;

        int cpid = fork();
        if (cpid == 0) {
            setsid();
            char *exec[] = { shell, "-c", "BIND TEST", NULL};
            int status_code = execvp(exec[0], exec);
            exit(status_code);
        }
    }

    return event;
}

int main(void) {
    init_shell();
    CGEventMask mask = 1 << kCGEventKeyDown;
    CFMachPortRef tap = CGEventTapCreate(kCGSessionEventTap,
                                         kCGHeadInsertEventTap,
                                         kCGEventTapOptionDefault,
                                         mask,
                                         callback,
                                         NULL);

    if(!tap) {
        fprintf(stderr, "cannot create tap\n");
        exit(1);
    }
            
    printf("tap enabled: %s\n", (tap && CGEventTapIsEnabled(tap)) ? "true" : "false");


    CFRunLoopSourceRef runloop = CFMachPortCreateRunLoopSource(kCFAllocatorDefault,
                                                               tap,
                                                               0);


    CFRunLoopAddSource(CFRunLoopGetMain(), runloop, kCFRunLoopCommonModes);
    CFRunLoopRun();

    return 0;
}
