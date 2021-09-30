package edu.jhu.apl.patterns_class.dom;

public class Document extends Node implements edu.jhu.apl.patterns_class.dom.replacement.Document
{
	public Document()
	{
		super(null, org.w3c.dom.Node.DOCUMENT_NODE);
		document	= this;
	}

	//
	// Serialization Data Extraction Strategy
	//
	public void serialize(java.io.Writer writer, edu.jhu.apl.patterns_class.XMLSerializer.WhitespaceStrategy whitespace)
	  throws java.io.IOException
	{
		writer.write("<? xml version=\"1.0\" encoding=\"UTF-8\"?>");
		whitespace.newLine(writer);
		getDocumentElement().serialize(writer, whitespace);
	}

	//
	// Implemented Document members.
	//
	public edu.jhu.apl.patterns_class.dom.replacement.Element createElement(String tagName) throws org.w3c.dom.DOMException
	  {return new Element(tagName,this);}
	public edu.jhu.apl.patterns_class.dom.replacement.Text createTextNode(String data) { return new Text(data, this); }
	public edu.jhu.apl.patterns_class.dom.replacement.Attr createAttribute(String name) throws org.w3c.dom.DOMException
	  { return new Attr(name, this); }
	public edu.jhu.apl.patterns_class.dom.replacement.Element getDocumentElement()
	{
		for (java.util.ListIterator i = ((NodeList )getChildNodes()).listIterator(0); i.hasNext();)
		{
			edu.jhu.apl.patterns_class.dom.replacement.Node	element =
			  (edu.jhu.apl.patterns_class.dom.replacement.Node )i.next();

			if (element instanceof edu.jhu.apl.patterns_class.dom.replacement.Element)
				return (edu.jhu.apl.patterns_class.dom.replacement.Element )element;
		}

		return null;
	}

	//
	// Iterator Factory
	//
	public java.util.Iterator<edu.jhu.apl.patterns_class.dom.replacement.Node>
	  createIterator(edu.jhu.apl.patterns_class.dom.replacement.Node node)
	{
		return new DOMIterator(node);
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

	//
	// Concrete Iterator
	//
	class DOMIterator implements java.util.Iterator<edu.jhu.apl.patterns_class.dom.replacement.Node>
	{
		private edu.jhu.apl.patterns_class.dom.replacement.Node					firstNode	= null;
		private java.util.ArrayDeque<edu.jhu.apl.patterns_class.dom.replacement.NodeList>	listStack	=
		  new java.util.ArrayDeque<edu.jhu.apl.patterns_class.dom.replacement.NodeList>();
		private java.util.ArrayDeque<Integer>							indexStack	=
		  new java.util.ArrayDeque<Integer>();

		public DOMIterator(edu.jhu.apl.patterns_class.dom.replacement.Node startWithNode)
		{
			if (startWithNode == null)
				firstNode	= getDocumentElement();
			else
				firstNode	= startWithNode;

			if (firstNode != null)
				for (edu.jhu.apl.patterns_class.dom.replacement.Node node = firstNode;
				  node.getChildNodes().getLength() > 0;
				  node = node.getChildNodes().item(0))
				{
					listStack.push(node.getChildNodes());
					indexStack.push(0);
				}
		}

		public boolean hasNext()
		{
			return firstNode != null;
		}

		public edu.jhu.apl.patterns_class.dom.replacement.Node next()
		{
			edu.jhu.apl.patterns_class.dom.replacement.NodeList	currentList	= listStack.peek();

			if (currentList == null)
			{
				edu.jhu.apl.patterns_class.dom.replacement.Node	temp	= firstNode;
				firstNode						= null;
				return temp;
			}
			else
			{
				int						currentIndex	= indexStack.pop().intValue();
				edu.jhu.apl.patterns_class.dom.replacement.Node	temp		= currentList.item(currentIndex++);

				if (currentIndex >= currentList.getLength())
					listStack.pop();
				else
				{
					indexStack.push(currentIndex);

					for (edu.jhu.apl.patterns_class.dom.replacement.Node node = currentList.item(currentIndex);
					  node.getChildNodes().getLength() > 0;
					  node = node.getChildNodes().item(0))
					{
						listStack.push(node.getChildNodes());
						indexStack.push(0);
					}
				}

				return temp;
			}
		}

		public void remove()
		{
			throw new UnsupportedOperationException();
		}
	}

	//
	// Test of DOMIterator
	//
	public static void main(String args[])
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
		edu.jhu.apl.patterns_class.dom.replacement.Document	document	=
		  new edu.jhu.apl.patterns_class.dom.Document();
		edu.jhu.apl.patterns_class.dom.replacement.Element	root		= document.createElement("document");
		document.appendChild(root);
		System.out.println("<" + root + "> (Last and highest node out of iterator)");

		edu.jhu.apl.patterns_class.dom.replacement.Element	child		= document.createElement("element");
		edu.jhu.apl.patterns_class.dom.replacement.Attr		attr		= document.createAttribute("attribute");
		attr.setValue("attribute value");
		child.setAttributeNode(attr);
		root.appendChild(child);
		System.out.println("  <" + child + "> (First node out of iterator)");

		child	= document.createElement("element");
		root.appendChild(child);
		System.out.println("  <" + child + "> (Second node out of iterator)");

		child	= document.createElement("element");
		child.setAttribute("attribute", "attribute value");
		child.setAttribute("attribute2", "attribute2 value");
		edu.jhu.apl.patterns_class.dom.replacement.Text		text		= document.createTextNode("Element Value");
		child.appendChild(text);
		root.appendChild(child);
		System.out.println("  <" + child + "> (Fourth node out of iterator)");
		System.out.println("    <" + text + "> (Third and deepest node out of iterator)");

		child	= document.createElement("element");
		root.appendChild(child);
		System.out.println("  <" + child + "> (Fifth node out of iterator)");


		System.out.println("\nDepth first iteration:");
		for (java.util.Iterator domIterator = document.createIterator(null); domIterator.hasNext();)
			System.out.println("node:  " + domIterator.next());
	}
}
