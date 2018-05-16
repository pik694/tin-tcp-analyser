//
// Created by Piotr Żelazko on 16.05.2018.
// Copyright (c) 2018 Piotr Żelazko. All rights reserved.
//

import UIKit

extension UITextView {

    func scrollToBottom() {
        let range = NSMakeRange(text.characters.count - 1, 1);
        scrollRangeToVisible(range);
    }

}
