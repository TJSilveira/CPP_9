#include "../includes/RPN.hpp"

	// Constructors
RPN::RPN(void): nums()
{
	return;
}

RPN::RPN(const RPN& other)
{
	// std::cout << "[RPN] Copy constructor called. " <<
	// 			std::endl;
	*this = other;
	return;
}

	// Destructor
RPN::~RPN(void)
{
	return;
}

void RPN::operation(char c)
{
	if (this->nums.size() < 2)
		throw RPN::InvalidExpression();
	else if (!(c == '+' ||
					 c == '-' ||
					 c == '/' ||
					 c == '*'))
	{
		throw RPN::InvalidCharacter();
	}
	
	int num2 = this->nums.top();
	this->nums.pop();
	int num1 = this->nums.top();
	this->nums.pop();
	long int res;

	if (c == '+')
		res = static_cast<long int>(num1) + num2;
	else if (c == '-')
		res = static_cast<long int>(num1) - num2;
	else if (c == '/')
		res = static_cast<long int>(num1) / num2;
	else
		res = static_cast<long int>(num1) * num2;

	if (res > static_cast<long int>(std::numeric_limits<int>::max()) ||
			res < static_cast<long int>(std::numeric_limits<int>::min()))
	{
		throw RPN::IntegerOverflow();
	}
	this->nums.push(res);
}

int	RPN::process_expression(char *expression)
{
	int i = -1;

	while (expression[++i])
	{
		if (expression[i] == ' ')
			continue;
		
		if (isdigit(expression[i]))
			this->nums.push(expression[i] - '0');
		else
			this->operation(expression[i]);
	}
	if (this->nums.size() != 1)
		throw RPN::InvalidExpression();
	return(this->nums.top());
}

	// Overloaded Operator
RPN&		RPN::operator=(const RPN& other)
{
	if(this != &other)
		this->nums = other.nums;
	// std::cout << "[RPN] Copy assignment operator called. " <<
	// 		std::endl;
	return *this;
}

const char *RPN::InvalidCharacter::what() const throw()
{
	return ("Invalid Character");
}

const char *RPN::InvalidExpression::what() const throw()
{
	return ("Invalid Expression");
}

const char *RPN::IntegerOverflow::what() const throw()
{
	return ("Integer Overflow");
}
