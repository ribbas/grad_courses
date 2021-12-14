#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <map>

namespace dom
{
	class Node;
}

class Subject;
class Observer;

class Mediator // and also Monostate
{
private:
	static std::multimap<Subject *, Observer *>	observers;
public:
	virtual ~Mediator() {}
	virtual void _register(Subject * subject, Observer * observer);
	virtual void unregister(Subject * subject, Observer * observer);
	virtual void notify(Subject * subject, dom::Node * container, short targetType, const std::string & target);
};

#endif // MEDIATOR_H
