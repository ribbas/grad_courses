package edu.jhu.apl.patterns_class.dom.replacement;

public interface Attr extends Node
{
	//
	// Serialization Data Extraction Strategy
	//
	public void serialize(java.io.Writer writer, edu.jhu.apl.patterns_class.XMLSerializer.WhitespaceStrategy whitespace)
	  throws java.io.IOException;

	//
	// Implemented Attr members.
	//
	public String getName();
	public String getValue();
	public void setValue(String value);
	public Element getOwnerElement();

	//
	// Unimplemented Attr members.
	//
	public boolean getSpecified();
	public boolean isId();
	public org.w3c.dom.TypeInfo getSchemaTypeInfo();
}
