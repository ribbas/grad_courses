//
//  AttrImpl.swift
//  Patterns
//
//  Created by Jon Lindberg on 12/30/18.
//  Copyright © 2018 Jon Lindberg. All rights reserved.
//

import Foundation

class AttrImpl : NodeImpl, Attr
{
	init(document : Document, tagName : String)
	{
		super.init(document: document, name: tagName, type: NodeType.ATTRIBUTE_NODE)
	}
	
	public var name	: String		{ get { return nodeName } }
	public var value	: String	{ get { return nodeValue } set { nodeValue = newValue } }
	public var ownerElement : Element?	{ get { return parentNode as? Element } }

	//
	// Serialization Data Extraction Strategy
	//
	public override func serialize(writer : FileHandle, whitespace : WhitespaceStrategy)
	{
		if let attrValue = (" " + name + "=\"" + value + "\"").data(using: String.Encoding.utf8)
		{
			writer.write(attrValue)
		}
	}
	
	public override func insertBefore(newChild : Node, refChild : Node?) throws	-> Node?	{ return nil }
	public override func replaceChild(newChild : Node, oldChild : Node) throws	-> Node?	{ return nil }
	public override func removeChild(oldChild : Node) throws			-> Node?	{ return nil }
	public override func appendChild(newChild : Node) throws			-> Node?	{ return nil }
}
