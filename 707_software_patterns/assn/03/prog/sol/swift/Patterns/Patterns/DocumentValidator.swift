//
//  DocumentValidator.swift
//  Patterns
//
//  Created by Jon Lindberg on 1/2/19.
//  Copyright © 2019 Jon Lindberg. All rights reserved.
//

import Foundation

protocol DocumentDecorator : Document
{
}

class DocumentValidator : Node, DocumentDecorator
{
	public init(parent : Document, xmlValidator : XMLValidator)
	{
		parentImpl	= parent
		schemaElement	= xmlValidator.findSchemaElement(element: "")
	}
	
	internal var parentImpl		: Document
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
	// Members from Document
	//
	public var documentElement	: Element?	{ get { return parentImpl.documentElement } }
	
	public func createElement(tagName : String)	-> Element	{ return parentImpl.createElement(tagName : tagName) }
	public func createTextNode(data : String)	-> Text		{ return parentImpl.createTextNode(data: data) }
	public func createAttribute(name : String)	-> Attr		{ return parentImpl.createAttribute(name: name) }
	//
	// Iterator factory
	//
	func createIterator(node : Node?)	-> Iterator		{ return parentImpl.createIterator(node: node) }

	//
	// Serialization Data Extraction Strategy
	//
	public func serialize(writer : FileHandle, whitespace : WhitespaceStrategy)
	{
		parentImpl.serialize(writer: writer, whitespace: whitespace)
	}
	
	public func insertBefore(newChild: Node, refChild: Node?) throws -> Node?
	{
		if let schemaElement = schemaElement, schemaElement.childIsValid(child: newChild.nodeName, isAttribute: false)
		{
			return try parentImpl.insertBefore(newChild: newChild, refChild: refChild)
		}
		else
		{
			throw DOMException.VALIDATION_ERR(reason: "Invalid root node \(newChild.nodeName).")
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
			throw DOMException.VALIDATION_ERR(reason: "Invalid root node \(newChild.nodeName).")
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
			throw DOMException.VALIDATION_ERR(reason: "Invalid root node \(newChild.nodeName).")
		}
	}
}
