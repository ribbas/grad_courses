//
//  XMLSerializer.swift
//  Patterns
//
//  Created by Jon Lindberg on 12/31/18.
//  Copyright © 2018 Jon Lindberg. All rights reserved.
//

import Foundation

public class XMLSerializer
{
	init(file : FileHandle)
	{
		self.file	= file
	}
	
	internal var file		: FileHandle
	
	class PrettyWhitespaceStrategy : WhitespaceStrategy
	{
		init() {}
		
		internal var indentationLevel	= 0
		
		public func prettyIndentation(writer: FileHandle)
		{
			if let data = "\t".data(using: String.Encoding.utf8)
			{
				for _ in 0..<indentationLevel
				{
					writer.write(data)
				}
			}
		}
		public func incrementIndentation()	{ indentationLevel += 1 }
		public func decrementIndentation()	{ indentationLevel -= 1 }
		public func newLine(writer: FileHandle)
		{
			if let data = "\n".data(using: String.Encoding.utf8)
			{
				writer.write(data)
			}
		}
	}
	
	class MinimalWhitespaceStrategy : WhitespaceStrategy
	{
		init() {}
		
		public func prettyIndentation(writer: FileHandle)	{}
		public func incrementIndentation()			{}
		public func decrementIndentation()			{}
		public func newLine(writer: FileHandle)			{}
	}
	
	//
	// Strategized Serialization
	//
	public func serializePretty(node : Node)
	{
		node.serialize(writer: file, whitespace: PrettyWhitespaceStrategy())
	}
	public func serializeMinimal(node : Node)
	{
		node.serialize(writer: file, whitespace: MinimalWhitespaceStrategy())
	}
}
