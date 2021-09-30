//
//  WhitespaceStrategy.swift
//  Patterns
//
//  Created by Jon Lindberg on 1/2/19.
//  Copyright © 2019 Jon Lindberg. All rights reserved.
//

import Foundation

public protocol WhitespaceStrategy : class
{
	func prettyIndentation(writer : FileHandle)
	func incrementIndentation()
	func decrementIndentation()
	func newLine(writer : FileHandle)
}
