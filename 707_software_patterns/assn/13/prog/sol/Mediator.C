#include "Mediator.H"
#include "Observer.H"
#include <stdio.h>

std::multimap<Subject *, Observer *>	Mediator::observers;

void Mediator::_register(Subject * subject, Observer * observer)
{
	auto	range	= observers.equal_range(subject);

	for (std::multimap<Subject *, Observer *>::iterator i = range.first; i != range.second; i++)
		if (i->second == observer)
			return;

	observers.emplace(subject, observer);
}

void Mediator::unregister(Subject * subject, Observer * observer)
{
	auto	range	= observers.equal_range(subject);

	for (std::multimap<Subject *, Observer *>::iterator i = range.first; i != range.second; i++)
		if (i->second == observer)
			observers.erase(i);
}

void Mediator::notify(Subject * subject, dom::Node * container, short targetType, const std::string & target)
{
	auto	range	= observers.equal_range(subject);

	for (std::multimap<Subject *, Observer *>::iterator i = range.first; i != range.second; i++)
		i->second->update(container, targetType, target);
}
