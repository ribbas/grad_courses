//
//  ElementValidator.swift
//  Patterns
//
//  Created by Jon Lindberg on 1/2/19.
//  Copyright © 2019 Jon Lindberg. All rights reserved.
//

import Foundation

protocol ElementDecorator : Element
{
}

class ElementValidator : Node, ElementDecorator
{
	public init(parent : Element, xmlValidator : XMLValidator)
	{
		parentImpl	= parent
		schemaElement	= xmlValidator.findSchemaElement(element: parent.tagName)
	}
	
	internal var parentImpl		: Element
	internal var schemaElement	: ValidChildren?

	//
	// Members from Node
	//
	public var nodeName: String		{ get { return parentImpl.nodeName } }
	public var nodeValue: String		{ get { return parentImpl.nodeValue } set { parentImpl.nodeValue = newValue } }
	public var nodeType: NodeType		{ get { return parentImpl.nodeType } }
	public var parentNode: Node?		{ get { return parentImpl.parentNode } set { parentImpl.parentNode = newValue } }
	public var childNodes: [Node]		{ get { return parentImpl.childNodes } }
	public var firstChild: Node?		{ get { return parentImpl.firstChild } }
	public var lastChild: Node?		{ get { return parentImpl.lastChild } }
	public var previousSibling: Node?	{ get { return parentImpl.previousSibling } }
	public var nextSibling: Node?		{ get { return parentImpl.nextSibling } }
	public var ownerDocument: Document	{ get { return parentImpl.ownerDocument } }
	public var hasChildNodes: Bool		{ get { return parentImpl.hasChildNodes } }
	public var localName: String		{ get { return parentImpl.localName } }
	public func removeChild(oldChild: Node) throws -> Node?	{ return try! parentImpl.removeChild(oldChild: oldChild) }

	//
	// Members from Element
	//
	public var tagName		: String	{ get { return parentImpl.tagName } }
	public var attributes		: [Attr]	{ get { return parentImpl.attributes } }
	public var hasAttributes	: Bool		{ get { return parentImpl.hasAttributes } }
	
	public func getAttribute(name : String)		-> String	{ return parentImpl.getAttribute(name: name) }
	public func getAttributeNode(name : String)	-> Attr?	{ return parentImpl.getAttributeNode(name: name) }
	public func elementsByTagName(tagName : String)	-> [Node]	{ return parentImpl.elementsByTagName(tagName: tagName) }
	public func hasAttribute(name : String)		-> Bool		{ return parentImpl.hasAttribute(name: name) }
	public func removeAttribute(name : String)			{ parentImpl.removeAttribute(name: name) }
	public func removeAttributeNode(oldAttr : Attr)	throws -> Attr	{ return try! parentImpl.removeAttributeNode(oldAttr: oldAttr)}
	public func setAttribute(name : String, value : String) throws
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: name, isAttribute: true)
		{
			try! parentImpl.setAttribute(name: name, value: value)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid attribute \(name).")
		}
	}
	
	public func setAttributeNode(newAttr : Attr) throws	-> Attr?
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: newAttr.name, isAttribute: true)
		{
			return try parentImpl.setAttributeNode(newAttr: newAttr)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid attribute \(newAttr.name).")
		}
	}
	
	public func insertBefore(newChild: Node, refChild: Node?) throws -> Node?
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: newChild.nodeName, isAttribute: false)
		{
			return try parentImpl.insertBefore(newChild: newChild, refChild: refChild)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid child element \(newChild.nodeName).")
		}
	}
	
	public func replaceChild(newChild: Node, oldChild: Node) throws -> Node?
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: newChild.nodeName, isAttribute: false)
		{
			return try parentImpl.replaceChild(newChild: newChild, oldChild: oldChild)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid child element \(newChild.nodeName).")
		}
	}
	
	public func appendChild(newChild: Node) throws -> Node?
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: newChild.nodeName, isAttribute: false)
		{
			return try parentImpl.appendChild(newChild: newChild)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid child element \(newChild.nodeName).")
		}
	}

	//
	// Serialization Data Extraction Strategy
	//
	public func serialize(writer : FileHandle, whitespace : WhitespaceStrategy)
	  { parentImpl.serialize(writer: writer, whitespace: whitespace) }

}
