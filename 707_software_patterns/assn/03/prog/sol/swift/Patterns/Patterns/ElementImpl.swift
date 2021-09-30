//
//  ElementImpl.swift
//  Patterns
//
//  Created by Jon Lindberg on 12/30/18.
//  Copyright © 2018 Jon Lindberg. All rights reserved.
//

import Foundation

class ElementImpl : NodeImpl, Element
{
	public init(document : Document, tagName : String)
	{
		attributesImpl	= [String : Attr]()
		super.init(document: document, name: tagName, type: NodeType.ELEMENT_NODE)
	}
	
	internal var attributesImpl	: [String : Attr]
	
	public var tagName		: String	{ get { return nodeName } }
	public var attributes		: [Attr]	{ get { return [Attr](attributesImpl.values) } }
	public var hasAttributes	: Bool		{ get { return attributes.count > 0 } }

	public func getAttribute(name : String)		-> String
	{
		for (key, attr) in attributesImpl
		{
			if key == name
			{
				return attr.value
			}
		}
		
		return ""
	}
	public func getAttributeNode(name : String)	-> Attr?
	{
		for (key, attr) in attributesImpl
		{
			if key == name
			{
				return attr
			}
		}
		
		return nil
	}
	public 	func elementsByTagName(tagName : String)	-> [Node]
	{
		var nodeList	= [Node]()
				
		for node in childNodes
		{
			if node.nodeName == tagName
			{
				nodeList.append(node)
			}
		}
		
		return nodeList
	}
	public func hasAttribute(name : String)		-> Bool
	{
		return attributesImpl.index(forKey: name) != nil
	}
	public func removeAttribute(name : String)
	{
		for (key, _) in attributesImpl
		{
			if key == name
			{
				attributesImpl.removeValue(forKey: key)
				return
			}
		}
	}
	public func removeAttributeNode(oldAttr : Attr)	throws -> Attr
	{
		for (key, attr) in attributesImpl
		{
			if attr === oldAttr
			{
				attributesImpl.removeValue(forKey: key)
				return attr
			}
		}
		
		throw DOMException.NOT_FOUND_ERR(reason: "Attribute not found.")
	}
	public func setAttribute(name : String, value : String) throws
	{
		if let index = attributesImpl.index(forKey: name)
		{
			attributesImpl[index].value.value	= value
			return
		}
		
		attributesImpl[name]	= ownerDocument.createAttribute(name : name)
		attributesImpl[name]?.value	= value
	}
	public func setAttributeNode(newAttr : Attr) throws	-> Attr?
	{
		if newAttr.ownerDocument !== ownerDocument
		{
			throw DOMException.WRONG_DOCUMENT_ERR(reason: "Attribute not created by this document.")
		}
		
		if newAttr.parentNode !== nil
		{
			throw DOMException.INUSE_ATTRIBUTE_ERR(reason: "Attribute in use by other element.")
		}

		let oldAttribute = attributesImpl.removeValue(forKey: newAttr.name)
		attributesImpl[newAttr.name]	= newAttr
		(newAttr as! NodeImpl).parent	= self
		
		return oldAttribute
	}

	//
	// Serialization Data Extraction Strategy
	//
	public override func serialize(writer : FileHandle, whitespace : WhitespaceStrategy)
	{
		whitespace.prettyIndentation(writer: writer)
		if let openTag = ("<" + tagName).data(using: String.Encoding.utf8)
		{
			writer.write(openTag)
		}
		
		var attrCount	= 0
		
		for attr in attributes
		{
			attr.serialize(writer: writer, whitespace: whitespace)
			attrCount += 1
		}
		
		if attrCount > 0
		{
			if let space = " ".data(using: String.Encoding.utf8)
			{
				writer.write(space)
			}
		}
		
		if childNodes.count == 0
		{
			if let closer = "/>".data(using: String.Encoding.utf8)
			{
				writer.write(closer)
				whitespace.newLine(writer: writer)
			}
		}
		else
		{
			if let closer = ">".data(using: String.Encoding.utf8)
			{
				writer.write(closer)
			}
			
			whitespace.newLine(writer: writer)
			whitespace.incrementIndentation()
			
			for child in childNodes
			{
				if (child as? Element) != nil || (child as? Text) != nil
				{
					child.serialize(writer: writer, whitespace: whitespace)
				}
			}
			
			whitespace.decrementIndentation()
			whitespace.prettyIndentation(writer: writer)
			
			if let endTag = ("</" + tagName + ">").data(using: String.Encoding.utf8)
			{
				writer.write(endTag)
			}
			whitespace.newLine(writer: writer)
		}
	}
}
