#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <string>

namespace dom
{
	class Node;
};

class Observer;

class Subject
{
public:
	void	attach(Observer * observer);
	void	detach(Observer * observer);
protected:
	void notify(dom::Node * container, short targetType, const std::string & target);
};

#endif // SUBJECT_H
