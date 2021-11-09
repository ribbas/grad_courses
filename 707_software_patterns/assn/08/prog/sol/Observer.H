#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

namespace dom
{
	class Node;
};

class Observer
{
public:
	virtual void	update(dom::Node * container, short targetType, const std::string & target) = 0;
};

#endif // OBSERVER_H
