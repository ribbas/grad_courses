//
//  XMLValidator.swift
//  Patterns
//
//  Created by Jon Lindberg on 1/1/19.
//  Copyright © 2019 Jon Lindberg. All rights reserved.
//

import Foundation

public class ValidChildren
{
	public init(thisElement : String)
	{
		thisElementImpl	= thisElement
	}
	
	internal let thisElementImpl	: String
	internal var validChildren	= [String]()
	internal var childIsAttribute	= [Bool]()
	internal var canHaveTextImpl	= false
	
	public var thisElement	: String	{ get { return thisElementImpl } }
	public var canHaveText : Bool		{ get { return canHaveTextImpl } set { canHaveTextImpl = newValue } }

	public func addValidChild(child : String, isAttribute : Bool)
	{
		if childIsValid(child: child, isAttribute: isAttribute)
		{
			return
		}
		
		validChildren.append(child)
		childIsAttribute.append(isAttribute)
	}
	public func childIsValid(child : String, isAttribute : Bool) -> Bool
	{
		for i in 0..<validChildren.count
		{
			if childIsAttribute[i] == isAttribute && validChildren[i] == child
			{
				return true
			}
		}
		
		return false
	}
}

public class XMLValidator
{
	init() {}
	
	internal var schema	= [ValidChildren]()
	
	public func addSchemaElement(element : String)				-> ValidChildren
	{
		let schemaElementIterator : Int	= findSchemaElement(element: element)
		
		if schemaElementIterator < schema.count
		{
			schema.remove(at: schemaElementIterator)
		}
		
		let schemaElement	= ValidChildren(thisElement: element)
		schema.append(schemaElement)
		return schemaElement
	}
	public func findSchemaElement(element : String)				-> Int
	{
		for i in 0..<schema.count
		{
			if (schema[i].thisElement.count == 0 && element.count == 0) ||
			  (schema[i].thisElement.count > 0 && schema[i].thisElement == element)
			{
				return i
			}
		}
		
		return schema.count
	}
	public func findSchemaElement(element : String)				-> ValidChildren?
	{
		let i : Int	= findSchemaElement(element: element)
		return i < schema.count ? schema[i] : nil
	}
}