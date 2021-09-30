//
//  Iterator.swift
//  Patterns
//
//  Created by Jon Lindberg on 1/2/19.
//  Copyright © 2019 Jon Lindberg. All rights reserved.
//

import Foundation

public protocol Iterator : class
{
	var hasNext	: Bool	{ get }
	var next	: Node	{ get }
}
