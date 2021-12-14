#ifndef STDOUTOBSERVER_H
#define STDOUTOBSERVER_H

#include "Observer.H"

namespace dom
{
	class Node;
};

class StdOutObserver : public Observer
{
public:
	virtual void	update(dom::Node * container, short targetType, const std::string & target);
};

#endif // STDOUTOBSERVER_H
