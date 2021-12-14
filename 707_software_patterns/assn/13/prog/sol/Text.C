#include "Text.H"
#include <stdexcept>
#include "Visitor.H"

Text_Impl::Text_Impl(const std::string value, dom::Document * document) : Node_Impl("", dom::Node::TEXT_NODE)
{
	setNodeValue(value);
	Node_Impl::document	= document;
}

Text_Impl::~Text_Impl()
{
}

void Text_Impl::Accept(Visitor * visitor)
{
	visitor->VisitText(this);
}

const std::string &	Text_Impl::getName(void)
{
	return getNodeName();
}

const std::string &	Text_Impl::getData(void)
{
	return getNodeValue();
}

const std::string &	Text_Impl::getValue(void)
{
	return getData();
}

void			Text_Impl::setData(const std::string & value)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

void			Text_Impl::setValue(const std::string & value)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

int			Text_Impl::getLength(void)
{
	return getValue().size();
}

const std::string &	Text_Impl::substringData(int offset, int count)
{
	try
	{
		//
		// This is not thread-safe, of course.
		//
		static std::string	value;
		value	= getValue().substr(offset, count);

		return value;
	}
	catch (std::out_of_range &)
	{
		throw dom::DOMException(dom::DOMException::INDEX_SIZE_ERR, "Index larger than Text node's value.");
	}
}

void			Text_Impl::appendData(const std::string & arg)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

void			Text_Impl::insertData(int offset, const std::string & arg)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

void			Text_Impl::deleteData(int offset, int count)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

void			Text_Impl::replaceData(int offset, int count, const std::string & arg)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

dom::Text *		Text_Impl::splitText(int offset)
{
	throw dom::DOMException(dom::DOMException::NO_MODIFICATION_ALLOWED_ERR, "Not permitted to modify flyweight objects.");
}

dom::Node * Text_Impl::cloneNode(bool deep)
{
	return new Text_Impl(getValue(), getOwnerDocument());
}
