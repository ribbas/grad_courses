package edu.jhu.apl.patterns_class.dom;

public class DocumentValidator extends Node implements edu.jhu.apl.patterns_class.dom.DocumentDecorator
{
	private edu.jhu.apl.patterns_class.dom.replacement.Document	parent		= null;
	private edu.jhu.apl.patterns_class.ValidChildren		schemaElement	= null;

	public DocumentValidator(edu.jhu.apl.patterns_class.dom.replacement.Document parent,
	  edu.jhu.apl.patterns_class.XMLValidator xmlValidator)
	{
		super(null, org.w3c.dom.Node.DOCUMENT_NODE);
		this.parent	= parent;
		schemaElement	= xmlValidator.findSchemaElement(null);
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
	// Undecorated pass-through methods.
	//
	public edu.jhu.apl.patterns_class.dom.replacement.Element createElement(String tagName) throws org.w3c.dom.DOMException
	  {return parent.createElement(tagName);}
	public edu.jhu.apl.patterns_class.dom.replacement.Text createTextNode(String data) { return parent.createTextNode(data); }
	public edu.jhu.apl.patterns_class.dom.replacement.Attr createAttribute(String name) throws org.w3c.dom.DOMException
	  { return parent.createAttribute(name); }
	public edu.jhu.apl.patterns_class.dom.replacement.Element getDocumentElement()
	{
		return parent.getDocumentElement();
	}
	public java.util.Iterator<edu.jhu.apl.patterns_class.dom.replacement.Node>
	  createIterator(edu.jhu.apl.patterns_class.dom.replacement.Node node)
	{
		return parent.createIterator(node);
	}

	//
	// Decorated Methods
	//
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  insertBefore(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node refChild) throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.insertBefore(newChild, refChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid root node " + newChild.getNodeName() + ".");
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  replaceChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild,
	  edu.jhu.apl.patterns_class.dom.replacement.Node oldChild) throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.replaceChild(newChild, oldChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid root node " + newChild.getNodeName() + ".");
	}
	public edu.jhu.apl.patterns_class.dom.replacement.Node appendChild(edu.jhu.apl.patterns_class.dom.replacement.Node newChild)
	  throws org.w3c.dom.DOMException
	{
		if (schemaElement == null || schemaElement.childIsValid(newChild.getNodeName(), false))
			return parent.appendChild(newChild);
		else
			throw new org.w3c.dom.DOMException(org.w3c.dom.DOMException.VALIDATION_ERR,
			  "Invalid root node " + newChild.getNodeName() + ".");
	}

	//
	// Unimplemented Document members.
	//
	public org.w3c.dom.DOMImplementation getImplementation() { return null; }
	public org.w3c.dom.DocumentType getDoctype() { return null; }
	public org.w3c.dom.DocumentFragment createDocumentFragment() { return null; }
	public org.w3c.dom.Comment createComment(String data) { return null; }
	public org.w3c.dom.CDATASection createCDATASection(String data) throws org.w3c.dom.DOMException { return null; }
	public org.w3c.dom.ProcessingInstruction createProcessingInstruction(String target, String data)
	  throws org.w3c.dom.DOMException
	  { return null; }
	public org.w3c.dom.EntityReference createEntityReference(String name) throws org.w3c.dom.DOMException { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  importNode(edu.jhu.apl.patterns_class.dom.replacement.Node importedNode, boolean deep) throws org.w3c.dom.DOMException
	  { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Element createElementNS(String namespaceURI, String qualifiedName)
	  throws org.w3c.dom.DOMException
	  { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Attr createAttributeNS(String namespaceURI, String qualifiedName)
	  throws org.w3c.dom.DOMException
	  { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.NodeList getElementsByTagNameNS(String namespaceURI, String localName)
	  { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Element getElementById(String elementId) { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Node cloneNode(boolean deep) { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  renameNode(edu.jhu.apl.patterns_class.dom.replacement.Node n, String namespaceURI, String qualifiedName) { return null; }
	public void normalizeDocument() {}
	public org.w3c.dom.DOMConfiguration getDomConfig() { return null; }
	public edu.jhu.apl.patterns_class.dom.replacement.Node
	  adoptNode(edu.jhu.apl.patterns_class.dom.replacement.Node source) { return null; }
	public void setDocumentURI(String documentURI) {}
	public String getDocumentURI() { return null; }
	public void setStrictErrorChecking(boolean strictErrorChecking) {}
	public boolean getStrictErrorChecking() { return false; }
	public void setXmlVersion(String xmlVersion) {}
	public String getXmlVersion() { return null; }
	public void setXmlStandalone(boolean xmlStandalone) {}
	public boolean getXmlStandalone() { return false; }
	public String getXmlEncoding() { return null; }
	public String getInputEncoding() { return null; }
}
