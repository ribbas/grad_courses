package edu.jhu.apl.patterns_class.dom;

public class ElementValidator extends Node implements edu.jhu.apl.patterns_class.dom.ElementDecorator
{
	private edu.jhu.apl.patterns_class.dom.replacement.Element	parent		= null;
	private edu.jhu.apl.patterns_class.ValidChildren		schemaElement	= null;

	public ElementValidator(edu.jhu.apl.patterns_class.dom.replacement.Element parent,
	  edu.jhu.apl.patterns_class.XMLValidator xmlValidator)
	{
		super(parent.getTagName(), org.w3c.dom.Node.ELEMENT_NODE);
		this.parent	= parent;
		schemaElement	= xmlValidator.findSchemaElement(parent.getTagName());
	}

	//
	// Serialization Data Extraction Strategy
	//
	public void serialize(java.io.Writer writer, edu.jhu.apl.patterns_class.XMLSerializer.WhitespaceStrategy whitespace)
	  throws java.io.IOException
	{
		parent.serialize(writer, whitespace);
	}

	//
	// Implemented Element members.
	//
	public String getAttribute(String name)
	{
		return parent.getAttribute(name);
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Attr getAttributeNode(String name)
	{
		return parent.getAttributeNode(name);
	}
	public edu.jhu.apl.patterns_class.dom.replacement.NodeList getElementsByTagName(String tagName)
	{
		return parent.getElementsByTagName(tagName);
	}
	public String getTagName()
	{
		return parent.getTagName();
	}
	public boolean hasAttribute(String name)
	{
		return parent.hasAttribute(name);
	}
	public void removeAttribute(String name)
	{
		parent.removeAttribute(name);
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Attr
	  removeAttributeNode(edu.jhu.apl.patterns_class.dom.replacement.Attr oldAttr)
	{
		return parent.removeAttributeNode(oldAttr);
	}

	//
	// Decorated Methods
	//
	public void setAttribute(String name, String value)
	{
		if (schemaElement == null || schemaElement.childIsValid(name, true))
			parent.setAttribute(name, value);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid attribute " + name + ".");
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Attr
	  setAttributeNode(edu.jhu.apl.patterns_class.dom.replacement.Attr newAttr)
	{
		if (schemaElement == null || schemaElement.childIsValid(newAttr.getName(), true))
			return parent.setAttributeNode(newAttr);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid attribute " + newAttr.getName() + ".");
	}

	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  insertBefore(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node refChild) throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || newChild instanceof edu.jhu.apl.patterns_class.dom.replacement.Text ||
		  schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.insertBefore(newChild, refChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid child node " + newChild.getNodeName() + ".");
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  replaceChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node oldChild) throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || newChild instanceof edu.jhu.apl.patterns_class.dom.replacement.Text ||
		  schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.replaceChild(newChild, oldChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid child node " + newChild.getNodeName() + ".");
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node appendChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild)
	  throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || newChild instanceof edu.jhu.apl.patterns_class.dom.replacement.Text ||
		  schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.appendChild(newChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid child node " + newChild.getNodeName() + ".");
	}

	//
	// Unimplemented Element members.
	//
	public edu.jhu.apl.patterns_class.dom.replacement.Attr getAttributeNodeNS(String namespaceURI, String localName)
	  { return null; }
	public String getAttributeNS(String namespaceURI, String localName) { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.NodeList getElementsByTagNameNS(String tagName) { return null; }
	public boolean hasAttributeNS(String namespaceURI, String localName) { return false; }
	public void removeAttributeNS(String namespaceURI, String localName) {}
	public edu.jhu.apl.patterns_class.dom.replacement.Attr
	  setAttributeNodeNS(edu.jhu.apl.patterns_class.dom.replacement.Attr newAttr) { return null; }
	public void setAttributeNS(String namespaceURI, String localName, String value) {}
	public edu.jhu.apl.patterns_class.dom.replacement.Attr
	  setAttributeNS(edu.jhu.apl.patterns_class.dom.replacement.Attr newAttr) { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.NodeList
	  getElementsByTagNameNS(String namespaceURI, String localName) { return null; }
	public void setIdAttributeNode(edu.jhu.apl.patterns_class.dom.replacement.Attr idAttr, boolean isId) {}
	public void setIdAttributeNS(String namespaceURI, String localName, boolean isId) {}
	public void setIdAttribute(String name, boolean isId) {}
	public org.w3c.dom.TypeInfo getSchemaTypeInfo() { return null; }



	//
	// Reimplemented Node members.
	//
	public String getNodeName()							{ return parent.getNodeName(); }
	public String getNodeValue() throws org.w3c.dom.DOMException			{ return parent.getNodeValue(); }
	public void setNodeValue(String nodeValue) throws org.w3c.dom.DOMException	{ parent.setNodeValue(nodeValue); }
	public short getNodeType()							{ return parent.getNodeType(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Node getParentNode()		{ return parent.getParentNode(); }
	public edu.jhu.apl.patterns_class.dom.replacement.NodeList getChildNodes()	{ return parent.getChildNodes(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Node getFirstChild()		{ return parent.getFirstChild(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Node getLastChild()		{ return parent.getLastChild(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Node getPreviousSibling()	{ return parent.getPreviousSibling(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Node getNextSibling()		{ return parent.getNextSibling(); }
	public edu.jhu.apl.patterns_class.dom.replacement.Document getOwnerDocument()	{ return parent.getOwnerDocument(); }
	public edu.jhu.apl.patterns_class.dom.replacement.NamedNodeMap getAttributes()	{ return parent.getAttributes(); }
	public boolean hasAttributes()							{ return parent.hasAttributes(); }
	public boolean hasChildNodes()							{ return parent.hasChildNodes(); }
	public String getLocalName()							{ return parent.getLocalName(); }
}
