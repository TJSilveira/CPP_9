#include "../includes/PmergeMe.hpp"

	// Constructors
PmergeMe::PmergeMe(void){}
PmergeMe::PmergeMe(const PmergeMe& other){*this = other;}

	// Destructor
PmergeMe::~PmergeMe(void){}

	// Overloaded Operator
PmergeMe&		PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		this->_deque = other._deque;
		this->_vec = other._vec;
	}	
	return *this;
}

static void input_validator(char *argv)
{
	if (argv[0] == '-')
	{
		throw PmergeMe::InvalidNumber();
	}
	long int num = strtol(argv, NULL, 10);
	if (num == 0 && argv[0] != '0')
	{
		throw PmergeMe::InvalidNumber();
	}
	else if (num > static_cast<long int>(std::numeric_limits<int>::max()) ||
			errno == ERANGE)
	{
		throw PmergeMe::InvalidNumber();
	}
}

void PmergeMe::intialize_vector(int &argc, char **argv)
{
	this->_vec.reserve(argc - 1);
	for (int i = 1; i < argc; i++)
	{
		input_validator(argv[i]);
		this->_vec.push_back(atoi(argv[i]));
	}
}

void PmergeMe::intialize_deque(int &argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		input_validator(argv[i]);
		this->_deque.push_back(atoi(argv[i]));
	}
}

PmergeMe::PmergeMe(int &argc, char *argv[])
{
	this->intialize_vector(argc, argv);
	this->intialize_deque(argc, argv);	
}

const char *PmergeMe::MissingInput::what() const throw()
{
	return ("Missing Input");
}

const char *PmergeMe::InvalidNumber::what() const throw()
{
	return ("Invalid Expression");
}

const char *PmergeMe::IntegerOverflow::what() const throw()
{
	return ("Integer Overflow");
}
