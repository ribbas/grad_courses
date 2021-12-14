#include "XMLValidator.H"
#include "ValidChildren.H"

ValidChildren * XMLValidator::addSchemaElement(std::string element)
{
	std::vector<ValidChildren *>::iterator	schemaElementIterator	= findSchemaElement(element);

	if (schemaElementIterator != schema.end())
	{
		schema.erase(schemaElementIterator);
		delete *schemaElementIterator;
	}

	ValidChildren *	schemaElement	= 0;
	schema.push_back(schemaElement = new ValidChildren(element));
	return schemaElement;
}

std::vector<ValidChildren *>::iterator XMLValidator::findSchemaElement(std::string element)
{
	for (std::vector<ValidChildren *>::iterator i = schema.begin(); i != schema.end(); i++)
		if (((*i)->getThisElement().size() == 0 && element.size() == 0) ||
		  ((*i)->getThisElement().size() > 0 && (*i)->getThisElement().compare(element) == 0))
			return i;

	return schema.end();
}

Memento * XMLValidator::CreateMemento(void)
{
	return new Memento_Impl(schema);
}

bool XMLValidator::SetMemento(Memento * memento)
{
	if (dynamic_cast<Memento_Impl *>(memento) != 0)
	{
		Memento_Impl *	m	= (Memento_Impl *)memento;

		m->GetSchema(schema);

		return true;
	}
	else
		return false;
}

Memento_Impl::Memento_Impl(std::vector<ValidChildren *> & _schema)
{
	duplicateSchema(_schema, schema);
}

void Memento_Impl::GetSchema(std::vector<ValidChildren *> & s)
{
	duplicateSchema(schema, s);
}

void Memento_Impl::duplicateSchema(std::vector<ValidChildren *> & ins, std::vector<ValidChildren *> & outs)
{
	for (std::vector<ValidChildren *>::iterator iterator = outs.begin(); iterator != outs.end(); iterator++)
		delete *iterator;

	outs.clear();

	for (std::vector<ValidChildren *>::iterator iterator = ins.begin(); iterator != ins.end(); iterator++)
		outs.push_back(new ValidChildren(**iterator));
}
