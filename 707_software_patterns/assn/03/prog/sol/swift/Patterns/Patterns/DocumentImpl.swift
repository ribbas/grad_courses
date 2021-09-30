//
//  DocumentImpl.swift
//  Patterns
//
//  Created by Jon Lindberg on 12/30/18.
//  Copyright © 2018 Jon Lindberg. All rights reserved.
//

import Foundation

class DocumentImpl : NodeImpl, Document
{
	class DOMIterator : Iterator
	{
		init(startWithNode : Node?, document : DocumentImpl)
		{
			firstNode	= startWithNode === nil ? document.documentElement : startWithNode!
			
			if var node = firstNode
			{
				while node.childNodes.count > 0
				{
					listStack.append(node.childNodes)
					indexStack.append(0)
					node	= node.childNodes[0]
				}
			}
		}
		
		internal var firstNode	: Node?
		internal var listStack	= [ [ Node ] ]()
		internal var indexStack	= [ Int ]()
		
		var hasNext: Bool
		{
			get
			{
				return firstNode !== nil
			}
		}
		
		var next: Node
		{
			get
			{
				if let currentList = listStack.last
				{
					var currentIndex	= indexStack.last!
					indexStack.remove(at: indexStack.count - 1)
					let temp		= elementAt(currentList: currentList, currentIndex: currentIndex)
					currentIndex		+= 1
					
					if (currentIndex >= currentList.count)
					{
						listStack.remove(at: listStack.count - 1)
					}
					else
					{
						indexStack.append(currentIndex)
						
						var node	= elementAt(currentList: currentList, currentIndex: currentIndex)
						while node.childNodes.count > 0
						{
							listStack.append(node.childNodes)
							indexStack.append(0)
							node	= node.childNodes[0]
						}
					}
					
					return temp
				}
				else
				{
					let temp	= firstNode!
					firstNode	= nil
					return temp
				}
			}
		}
		
		internal func elementAt(currentList : [Node], currentIndex : Int)	-> Node
		{
			return currentList[currentIndex]
		}
	}
	
	public init()
	{
		super.init(document: nil, name: "", type: NodeType.DOCUMENT_NODE)
		resetDocument(document: self)
	}

	public var documentElement	: Element?
	{
		get
		{
			for n in nodes
			{
				if let element = (n as? Element)
				{
					return element
				}
			}
			
			return nil
		}
	}
	
	public func createElement(tagName : String)	-> Element
	{
		return ElementImpl(document : self, tagName : tagName)
	}
	
	public func createTextNode(data : String)	-> Text
	{
		return TextImpl(document: self, value: data)
	}
	
	public func createAttribute(name : String)	-> Attr
	{
		return AttrImpl(document: self, tagName: name)
	}
	//
	// Iterator factory
	//
	func createIterator(node : Node?)	-> Iterator
	{
		return DOMIterator(startWithNode: node, document: self)
	}

	//
	// Serialization Data Extraction Strategy
	//
	public override func serialize(writer : FileHandle, whitespace : WhitespaceStrategy)
	{
		if let header = """
			  <? xml version="1.0" encoding="UTF-8"?>
			  """.data(using: String.Encoding.utf8)
		{
			writer.write(header)
			whitespace.newLine(writer: writer)
			
			if let documentElement = documentElement
			{
				documentElement.serialize(writer: writer, whitespace: whitespace)
			}
		}
	}
}
