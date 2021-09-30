package edu.jhu.apl.patterns_class;

public class XMLValidator
{
	private java.util.Vector<ValidChildren>	schema	= new java.util.Vector<ValidChildren>();

	//
	// Supercedes any existing description for this element.
	//
	public ValidChildren addSchemaElement(String element)
	{
		ValidChildren	schemaElement	= findSchemaElement(element);

		if (schemaElement != null)
			schema.remove(schemaElement);

		schema.add(schemaElement = new ValidChildren(element));
		return schemaElement;
	}

	public ValidChildren findSchemaElement(String element)
	{
		for (int i = 0; i < schema.size(); i++)
			if ((schema.elementAt(i).getThisElement() == null && element == null) ||
			 (schema.elementAt(i).getThisElement()!=null && schema.elementAt(i).getThisElement().compareTo(element)==0))
				return schema.elementAt(i);

		return null;
	}

	public static void main(String args[])
	{
		if (args.length < 1)
		{
			System.out.println("No output filenames provided.");
			System.exit(0);
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
		// Schema for this document:
		// document contains:  element
		// element contains:  element
		// element contains attributes:  attribute, attribute2
		//
		XMLValidator	xmlValidator	= new XMLValidator();
		ValidChildren	schemaElement	= xmlValidator.addSchemaElement(null);
		schemaElement.addValidChild("document", false);
		schemaElement	= xmlValidator.addSchemaElement("document");
		schemaElement.addValidChild("element", false);
		schemaElement	= xmlValidator.addSchemaElement("element");
		schemaElement.addValidChild("element", false);
		schemaElement.addValidChild("attribute", true);
		schemaElement.addValidChild("attribute2", true);
		schemaElement.setCanHaveText(true);

		edu.jhu.apl.patterns_class.dom.replacement.Document	document	=
		  new edu.jhu.apl.patterns_class.dom.DocumentValidator(new edu.jhu.apl.patterns_class.dom.Document(), xmlValidator);
		edu.jhu.apl.patterns_class.dom.replacement.Element	root		= null;
		edu.jhu.apl.patterns_class.dom.replacement.Element	child		= null;
		edu.jhu.apl.patterns_class.dom.replacement.Attr		attr		= null;

		root	= new edu.jhu.apl.patterns_class.dom.ElementValidator(document.createElement("document"), xmlValidator);
		document.appendChild(root);
		child	= new edu.jhu.apl.patterns_class.dom.ElementValidator(document.createElement("element"), xmlValidator);
		attr	= document.createAttribute("attribute");
		attr.setValue("attribute value");
		child.setAttributeNode(attr);
		root.appendChild(child);
		child	= new edu.jhu.apl.patterns_class.dom.ElementValidator(document.createElement("element"), xmlValidator);
		root.appendChild(child);
		child	= new edu.jhu.apl.patterns_class.dom.ElementValidator(document.createElement("element"), xmlValidator);
		child.setAttribute("attribute", "attribute value");
		child.setAttribute("attribute2", "attribute2 value");
		edu.jhu.apl.patterns_class.dom.replacement.Text text = document.createTextNode("Element Value");
		child.appendChild(text);
		root.appendChild(child);
		child	= new edu.jhu.apl.patterns_class.dom.ElementValidator(document.createElement("element"), xmlValidator);
		root.appendChild(child);

		//
		// Serialize
		//
		try
		{
			XMLSerializer	xmlSerializer	=
			  new XMLSerializer(new java.io.BufferedWriter(new java.io.OutputStreamWriter(
			  new java.io.FileOutputStream(new java.io.File(args[0])))));
			xmlSerializer.serializePretty(document);
			xmlSerializer.close();
		}
		catch (java.io.IOException e)
		{
			System.out.println("Error writing file.");
			e.printStackTrace();
		}
	}
}
