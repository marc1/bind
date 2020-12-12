#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

CGEventRef callback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon) {

    if(type == kCGEventKeyDown) {
        CGKeyCode kc = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

        printf("\t%#X\n", kc);
    }

    return event;
}

int main(void) {
    CGEventMask mask = 1<<kCGEventKeyDown;
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
