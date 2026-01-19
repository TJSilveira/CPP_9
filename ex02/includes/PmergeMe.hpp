#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <limits>
#include <cstdlib>


class PmergeMe
{
private:
public:
	std::vector<int> _vec;
	std::deque<int> _deque;

	static int number_of_operations;
// Constructors
	PmergeMe(void);
	PmergeMe(const PmergeMe& other);
	PmergeMe(int &argc, char *argv[]);

	// Destructor
	~PmergeMe(void);

	// Getter

	// Methods
	void intialize_vector(int &argc, char **argv);
	void intialize_deque(int &argc, char **argv);


	// Overloaded Operator
	PmergeMe&		operator=(const PmergeMe& other);

	class MissingInput: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidNumber: public std::exception
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