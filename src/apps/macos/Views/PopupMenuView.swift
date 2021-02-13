//
//  PopupMenuView.swift
//  PowerTip
//
//  Created by Ahmad Chatila on 6/17/20.
//  Copyright © 2020 Ahmad N. Chatila. All rights reserved.
//

import Foundation
import Cocoa

class PopupMenuView: NSView {
    
    //
    //
    // MARK: Properties
    //
    
    @IBOutlet var contentView: NSView!
    
    @IBOutlet weak var titleLabel: NSTextField!
    @IBOutlet weak var qrImageView: NSImageView!
    
    override init(frame: CGRect) { // for using CustomView in code
        super.init(frame: frame)
        commonInit()
    }
    
    required init?(coder: NSCoder) { // for using CustomView in IB
        super.init(coder: coder)
        commonInit()
    }
    
    private func commonInit() {
        Bundle.main.loadNibNamed("PopupMenuView", owner: self, topLevelObjects: nil)
        addSubview(contentView)
        contentView.frame = self.bounds
//         contentView.autoresizingMask = [.flexibleHeight, .flexibleWidth]
        contentView.layer?.borderWidth = 1
        // contentView.layer.borderColor = UIColor.black.cgColor
    }
    
    //
    //
    // MARK: Cocoa callbacks
    //
    override func viewWillDraw() {
        
    }
    
    override func updateLayer() {
        updateUI()
    }
    
    //
    //
    // MARK: Custom Functions
    //
    private func updateUI() {
        wantsLayer = true
        layer?.backgroundColor = NSColor(named: "PopupMenu_BackgroundColor")?.cgColor
    }
    
    func setIpAddress(ipString: String) {
        qrImageView.image = generateQRCode(from: ipString)
    }
}
