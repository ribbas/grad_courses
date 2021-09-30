package edu.jhu.apl.patterns_class.dom;

public class Attr extends Node implements edu.jhu.apl.patterns_class.dom.replacement.Attr
{
	Attr(String tagName, Document document)
	{
		super(tagName, org.w3c.dom.Node.ATTRIBUTE_NODE);
		this.document	= document;
	}

	Attr(String tagName, String value, Document document)
	{
		super(tagName, org.w3c.dom.Node.ATTRIBUTE_NODE);
		this.document	= document;
		setValue(value);
	}

	//
	// Serialization Data Extraction Strategy
	//
	public void serialize(java.io.Writer writer, edu.jhu.apl.patterns_class.XMLSerializer.WhitespaceStrategy whitespace)
	  throws java.io.IOException
	{
		writer.write(" " + getName() + "=\"" + getValue() + "\"");
	}

	//
	// Implemented Attr members.
	//
	public String getName()
	{
		return getNodeName();
	}
	public String getValue()
	{
		return getNodeValue();
	}
	public void setValue(String value)
	{
		// TODO:  Check for readonly status.  NO_MODIFICATION_ALLOWED_ERR

		setNodeValue(value);
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Element getOwnerElement()
	{
		return (Element )getParentNode();
	}

	//
	// Overridden functions for conforming to Composite Leaf node behavior.
	//
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  insertBefore(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node refChild) throws org.w3c.dom.DOMException
	{
		return null;
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  replaceChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node oldChild) throws org.w3c.dom.DOMException
	{
		return null;
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node removeChild(edu.jhu.apl.patterns_class.dom.replacement.Node oldChild)
	  throws org.w3c.dom.DOMException
	{
		return null;
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node appendChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild)
	  throws org.w3c.dom.DOMException
	{
		return null;
	}

	//
	// Unimplemented Attr members.
	//
	public boolean getSpecified()	{ return true; }
	public boolean isId()		{ return false; }
	public org.w3c.dom.TypeInfo getSchemaTypeInfo() { return null; }
}
