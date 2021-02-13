//
//  AppDelegate.m
//  PowerTip
//
//  Created by Ahmad Chatila on 8/4/20.
//  Copyright © 2020 Ahmad N. Chatila. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)togglePopover {
    if (_popover.isShown) {
        [self closePopover:nil];
    } else {
        [self showPopover:nil];
    }
}

- (void) showPopover:(id)sender {
    NSStatusBarButton* button = _statusItem.button;
    [_popover showRelativeToRect:button.bounds ofView:button preferredEdge: NSRectEdgeMinY];
}

- (void) closePopover:(id)sender {
    [_popover performClose:sender];
}

- (BOOL)userNotificationCenter:(NSUserNotificationCenter *)center shouldPresentNotification:(NSUserNotification *)notification{
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    [[NSUserNotificationCenter defaultUserNotificationCenter] setDelegate:self];
    
    _popover = [[NSPopover alloc] init];

    _statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSSquareStatusItemLength];
    _statusItem.button.image = [NSImage imageNamed: @"StatusBarButtonImage"];
    _statusItem.button.action = @selector(togglePopover);
    
    _popover.contentViewController = [PopupMenuViewController freshController];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
