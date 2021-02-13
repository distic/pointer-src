//
//  AppDelegate.h
//  PowerTip
//
//  Created by Ahmad Chatila on 8/4/20.
//  Copyright © 2020 Ahmad N. Chatila. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Pointer-Swift.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSUserNotificationCenterDelegate>

@property NSPopover* popover;
@property NSStatusItem* statusItem;

#
# pragma mark: Popupover Selectors
#
- (void) togglePopover;
- (void) showPopover:(id)sender;
- (void) closePopover:(id)sender;

@end

