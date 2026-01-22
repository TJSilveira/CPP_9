#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <deque>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstddef>

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

	void merge_insertion_sort_vec();
	int	sort_pairs_vec(int rec_depth);
	void initialize_main_pend_vec(int rec_depth, std::vector<int> &main, std::vector<int> &pend, std::vector<int> &non_pend);
	void binary_sort_vec(int rec_depth, std::vector<int> pend_seq);

	void merge_insertion_sort_deque();
	int sort_pairs_deque(int rec_depth);
	void initialize_main_pend_deque(int rec_depth, std::deque<int> &main, std::deque<int> &pend, std::deque<int> &non_pend);
	void binary_sort_deque(int rec_depth, std::deque<int> pend_seq);

	void is_sorted_vec();
	void is_sorted_deque();

	// Overloaded Operator
	PmergeMe&		operator=(const PmergeMe& other);

			
	// Exceptions
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

	class NotSorted: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif