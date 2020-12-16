#include "event_tap.h"

static bool event_tap_enabled(event_tap* tap) {
    return tap->handle && CGEventTapIsEnabled(tap->handle);
}

static bool event_tap_init(event_tap* tap, event_tap_callback* callback) {
    tap->handle = 
        CGEventTapCreate(kCGSessionEventTap,
                         kCGHeadInsertEventTap,
                         kCGEventTapOptionDefault,
                         tap->mask,
                         callback,
                         NULL);

    bool enabled = event_tap_enabled(tap);
    if(enabled) {
        tap->runloop_source =
            CFMachPortCreateRunLoopSource(kCFAllocatorDefault,
                                          tap->handle,
                                          0);

        CFRunLoopAddSource(CFRunLoopGetMain(), 
                           tap->runloop_source,
                           kCFRunLoopCommonModes);
    }

    return enabled;
}

static void event_tap_release(event_tap* tap) {
    if (event_tap_enabled(tap)) {
        CGEventTapEnable(tap->handle, false);
        CFMachPortInvalidate(tap->handle);
        CFRunLoopRemoveSource(CFRunLoopGetMain(), tap->runloop_source, kCFRunLoopCommonModes);
        CFRelease(tap->runloop_source);
        CFRelease(tap->handle);
        tap->handle = NULL;
    }
}
