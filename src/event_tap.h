#pragma once

#include <stdbool.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>

typedef struct event_tap {
    CFMachPortRef handle;
    CGEventMask mask;
    CFRunLoopSourceRef runloop_source;
} event_tap;

#define EVENT_TAP_CALLBACK(name) \
    CGEventRef name(CGEventTapProxy proxy, \
                    CGEventType type, \
                    CGEventRef event, \
                    void* ref) \

typedef EVENT_TAP_CALLBACK(event_tap_callback);

static bool event_tap_enabled(event_tap* tap);
static bool event_tap_init(event_tap* tap, event_tap_callback* callback); 
static void event_tap_release(event_tap* tap);

