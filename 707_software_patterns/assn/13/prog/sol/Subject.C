#include "Subject.H"
#include "Observer.H"
#include "Mediator.H"

void Subject::attach(Observer * observer)
{
	Mediator()._register(this, observer);
}

void Subject::detach(Observer * observer)
{
	Mediator().unregister(this, observer);
}

void Subject::notify(dom::Node * container, short targetType, const std::string & target)
{
	Mediator().notify(this, container, targetType, target);
}
