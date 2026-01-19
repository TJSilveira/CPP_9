#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <limits>

class RPN
{
private:
	std::stack<int, std::list<int> > nums;
public:
	// Constructors
	RPN(void);
	RPN(const RPN& other);

	// Destructor
	~RPN(void);

	// Getter

	// Methods
	int process_expression(char *expression);
	void operation(char c);

	// Overloaded Operator
	RPN&		operator=(const RPN& other);

	class InvalidCharacter: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidExpression: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class IntegerOverflow: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif