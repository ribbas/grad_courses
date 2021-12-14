#include <string>
#include <fstream>
#include <ios>
#include <vector>

#include "Element.H"

class ValidChildren;

class Memento
{
protected:
	Memento() {}
	virtual ~Memento() {}
};

class XMLValidator
{
private:
	std::vector<ValidChildren *>	schema;
public:
	XMLValidator(void)	{}
	~XMLValidator() { for (int i = 0; i < schema.size(); i++) delete schema[i]; }

	virtual ValidChildren *				addSchemaElement(std::string element);
	virtual std::vector<ValidChildren *>::iterator	findSchemaElement(std::string element);

	Memento *	 				CreateMemento(void);
	bool						SetMemento(Memento * memento);
};

class Memento_Impl : public Memento
{
	friend class XMLValidator;
private:
	std::vector<ValidChildren *>	schema;

	Memento_Impl(std::vector<ValidChildren *> & _schema);
	void		GetSchema(std::vector<ValidChildren *> & s);
	void		duplicateSchema(std::vector<ValidChildren *> & ins, std::vector<ValidChildren *> & outs);
};
