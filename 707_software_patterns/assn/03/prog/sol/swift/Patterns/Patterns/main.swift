//
//  main.swift
//  Patterns
//
//  Created by Jon Lindberg on 12/29/18.
//  Copyright © 2018 Jon Lindberg. All rights reserved.
//

import Foundation

func printUsage()
{
	print("Usage:")
	print("\tTest t [file] ...")
	print("\tTest s [file1] [file2]")
	print("\tTest v [file]")
	print("\tTest i")
}


func testTokenizer()
{
	let document	= DocumentImpl()
	
	let element	= document.createElement(tagName: "NewElement")
	let text	= document.createTextNode(data: "Text Data")
	let attr	= document.createAttribute(name: "NewAttribute")
	
	print("Element Tag = '\(element.tagName)'")
	print("Text Data = '\(text.value)'")
	print("Attr Name = '\(attr.name)'")
	
	_ = try! element.setAttributeNode(newAttr: attr)
	let attrValue = element.getAttribute(name: "NewAttribute")
	print("Element attribute '\(attr.name)'='\(attrValue)'")
	
	for i in 2..<CommandLine.argc
	{
		print("Tokenizing file '\(CommandLine.arguments[Int(i)])'")
		
		if let tokenizer = XMLTokenizer(filename: CommandLine.arguments[Int(i)])
		{
			var token = XMLTokenizer.XMLToken(type: XMLTokenizer.TokenTypes.NULL_TOKEN, token: "")
			
			repeat
			{
				token	= tokenizer.getNextToken()
			
				print("\tLine \(tokenizer.lineNumber):  \(token.type) = '\(token.token)'")
			} while token.type != XMLTokenizer.TokenTypes.NULL_TOKEN
		}
		else
		{
			print("Unable to open file.")
		}
	}
}

func testSerializer()
{
	if CommandLine.argc < 4
	{
		printUsage()
		exit(0)
	}
	
	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	let document	= DocumentImpl()
	let root	= document.createElement(tagName: "document")
	_ = try! document.appendChild(newChild: root)
	
	var child	= document.createElement(tagName: "element")
	let attr	= document.createAttribute(name: "attribute")
	attr.value	= "attribute value"
	_ = try! child.setAttributeNode(newAttr: attr)
	_ = try! root.appendChild(newChild: child)
	
	child		= document.createElement(tagName: "element")
	_ = try! root.appendChild(newChild: child)
	
	child		= document.createElement(tagName: "element")
	_ = try! child.setAttribute(name: "attribute", value: "attribute value")
	_ = try! child.setAttribute(name: "attribute2", value: "attribute2 value")
	let text	= document.createTextNode(data: "Element Value")
	_ = try! child.appendChild(newChild: text)
	_ = try! root.appendChild(newChild: child)
	
	//
	// Serialize
	//

	//
	// There must be a way to create the file and get a handle to writing to it in one call without
	// jumping down to direct 'C' Posix calls, but I haven't found it yet.
	//
	var file	: FileHandle
	
	if !FileManager.default.createFile(atPath: CommandLine.arguments[2], contents: nil, attributes: nil)
	{
		print("Unable to create file '\(CommandLine.arguments[2])'.")
		exit(0)
	}
	
	do
	{
		let tempFile = try FileHandle(forWritingTo: URL(fileURLWithPath: CommandLine.arguments[2]))
		file	= tempFile
	}
	catch
	{
		print(error)
		exit(0)
	}

	var xmlSerializer = XMLSerializer(file: file)
	xmlSerializer.serializePretty(node: document)
	
	if !FileManager.default.createFile(atPath: CommandLine.arguments[3], contents: nil, attributes: nil)
	{
		print("Unable to create file '\(CommandLine.arguments[3])'.")
		exit(0)
	}
	
	do
	{
		let tempFile = try FileHandle(forWritingTo: URL(fileURLWithPath: CommandLine.arguments[3]))
		file	= tempFile
	}
	catch
	{
		print(error)
		exit(0)
	}
	
	xmlSerializer = XMLSerializer(file: file)
	xmlSerializer.serializeMinimal(node: document)
}

func testValidator()
{
	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	// Schema for this document:
	// document contains:  element
	// element contains:  element
	// element contains attributes:  attribute, attribute2
	//
	let xmlValidator		= XMLValidator()
	var schemaElement		= xmlValidator.addSchemaElement(element: "")
	schemaElement.addValidChild(child: "document", isAttribute: false)
	schemaElement			= xmlValidator.addSchemaElement(element: "document")
	schemaElement.addValidChild(child: "element", isAttribute: false)
	schemaElement			= xmlValidator.addSchemaElement(element: "element")
	schemaElement.addValidChild(child: "element", isAttribute: false)
	schemaElement.addValidChild(child: "attribute", isAttribute: true)
	schemaElement.addValidChild(child: "attribute2", isAttribute: true)
	schemaElement.canHaveText	= true
	
	let document	= DocumentValidator(parent: DocumentImpl(), xmlValidator: xmlValidator)
	let root : Element = ElementValidator(parent: document.createElement(tagName: "document"), xmlValidator: xmlValidator)
	_ = try! document.appendChild(newChild: root)
	var child : Element = ElementValidator(parent: document.createElement(tagName: "element"), xmlValidator: xmlValidator)
	let attr	: Attr	= document.createAttribute(name: "attribute")
	attr.value	= "attribute value"
	_ = try! child.setAttributeNode(newAttr: attr)
	_ = try! root.appendChild(newChild: child)
	child	= ElementValidator(parent: document.createElement(tagName: "element"), xmlValidator: xmlValidator)
	_ = try! root.appendChild(newChild: child)
	child	= ElementValidator(parent: document.createElement(tagName: "element"), xmlValidator: xmlValidator)
	_ = try! child.setAttribute(name: "attribute", value: "attribute value")
	_ = try! child.setAttribute(name: "attribute2", value: "attribute2 value")
	_ = try! root.appendChild(newChild: child)
	child	= ElementValidator(parent: document.createElement(tagName: "element"), xmlValidator: xmlValidator)
	_ = try! root.appendChild(newChild: child)

	//
	// Serialize
	//
	//
	// There must be a way to create the file and get a handle to writing to it in one call without
	// jumping down to direct 'C' Posix calls, but I haven't found it yet.
	//
	var file	: FileHandle
	
	if !FileManager.default.createFile(atPath: CommandLine.arguments[2], contents: nil, attributes: nil)
	{
		print("Unable to create file '\(CommandLine.arguments[2])'.")
		exit(0)
	}
	
	do
	{
		let tempFile = try FileHandle(forWritingTo: URL(fileURLWithPath: CommandLine.arguments[2]))
		file	= tempFile
	}
	catch
	{
		print(error)
		exit(0)
	}
	
	let xmlSerializer = XMLSerializer(file: file)
	xmlSerializer.serializePretty(node: document)
}

func testIterator()
{
	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	let document	= DocumentImpl()
	let root	= document.createElement(tagName: "document")
	_ = try! document.appendChild(newChild: root)
	
	var child	= document.createElement(tagName: "element1")
	let attr	= document.createAttribute(name: "attribute")
	attr.value	= "attribute value"
	_ = try! child.setAttributeNode(newAttr: attr)
	_ = try! root.appendChild(newChild: child)
	
	child		= document.createElement(tagName: "element2")
	_ = try! root.appendChild(newChild: child)
	
	child		= document.createElement(tagName: "element3")
	_ = try! child.setAttribute(name: "attribute2", value: "attribute2 value")
	_ = try! child.setAttribute(name: "attribute3", value: "attribute3 value")
	let text	= document.createTextNode(data: "Element Value")
	_ = try! child.appendChild(newChild: text)
	_ = try! root.appendChild(newChild: child)
	
	child		= document.createElement(tagName: "element4")
	_ = try! root.appendChild(newChild: child)
	
	print("Depth first iteration:")
	let domIterator	= document.createIterator(node: nil)
	while domIterator.hasNext
	{
		let node	= domIterator.next
		print("\(node.nodeType) = " + node.nodeName + " : " + node.nodeValue)
	}
}

if CommandLine.argc < 2
{
	printUsage()
	exit(0)
}
	
switch CommandLine.arguments[1].prefix(1)
{
case "T", "t":
	testTokenizer()
case "S", "s":
	testSerializer()
case "V", "v":
	testValidator()
case "I", "i":
	testIterator()
default:
	printUsage()
}
