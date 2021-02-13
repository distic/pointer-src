//
//  PopupMenuViewController.swift
//  PowerTip
//
//  Created by Ahmad Chatila on 6/17/20.
//  Copyright © 2020 Ahmad N. Chatila. All rights reserved.
//

import Cocoa

class PopupMenuViewController: NSViewController {
    
    @IBOutlet var popupMenuView: PopupMenuView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        popupMenuView.setIpAddress(ipString: getWiFiAddress()!)
    }
    
    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
}



// ===========================================================
//
// MARK: Required for Popover Menu Implementation
//

@objc extension PopupMenuViewController {
  // MARK: Storyboard instantiation
  static func freshController() -> PopupMenuViewController {
    //1.
    let storyboard = NSStoryboard(name: "Main", bundle: nil)
    //2.
    let identifier = "PopupMenuViewController"
    //3.
    guard let PopupMenuViewController = storyboard.instantiateController(withIdentifier: identifier) as? PopupMenuViewController else {
      fatalError("Why cant i find PopupMenuViewController? - Check Main.storyboard")
    }
    return PopupMenuViewController
  }
}
