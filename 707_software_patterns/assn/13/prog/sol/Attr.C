#include "Attr.H"
#include "Visitor.H"

Attr_Impl::Attr_Impl(const std::string & tagName, dom::Document * document) : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
}

Attr_Impl::Attr_Impl(const std::string & tagName, const std::string & value, dom::Document * document) :
  Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE)
{
	Node_Impl::document	= document;
	setNodeValue(value);
}

Attr_Impl::~Attr_Impl() {}

void Attr_Impl::Accept(Visitor * visitor)
{
	visitor->VisitAttribute(this);
}

const std::string &	Attr_Impl::getName(void)
{
	return Node_Impl::getNodeName();
}

const std::string &	Attr_Impl::getValue(void)
{
	return Node_Impl::getNodeValue();
}

void Attr_Impl::setValue(const std::string & value)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

dom::Element *		Attr_Impl::getOwnerElement(void)
{
	throw dom::DOMException(dom::DOMException::NOT_SUPPORTED_ERR, "Not permitted to query parent of flyweight objects.");
}

dom::Node * Attr_Impl::cloneNode(bool deep)
{
	return this;
}
