#include "../includes/PmergeMe.hpp"

// Static functions

template <typename T> static std::string to_string(const T &value)
{
	std::stringstream ss;
	ss << value;
	return (ss.str());
}

// void print_vec(std::vector<int> &vec, std::string str)
// {
// 	printf("[%s]\n", str.c_str());
// 	for (size_t i = 0; i < vec.size(); i++)
// 	{
// 		printf("[%li] This is %s: %i\n", i, str.c_str(), vec.at(i));
// 	}
// 	fflush(stdout);
// }

static std::string argv_to_str(int argc, char *argv[])
{
	int	i;

	i = 0;
	std::string str;
	while (argv[++i])
	{
		if (i == 5 && argc > 6)
		{
			str.append("[...]");
			break ;
		}
		str.append(argv[i]);
		str.append(" ");
	}
	return (str);
}

static std::string vec_to_str(std::vector<int> &vec)
{
	int	i;
	int	size;

	i = -1;
	size = vec.size();
	std::string str;
	while (++i < size)
	{
		if (i == 4 && size > 5)
		{
			str.append("[...]");
			break ;
		}
		str.append(to_string(vec.at(i)));
		str.append(" ");
	}
	return (str);
}

static void	input_validator(char *argv)
{
	long int	num;

	if (argv[0] == '-')
	{
		throw PmergeMe::InvalidNumber();
	}
	num = strtol(argv, NULL, 10);
	if (num == 0 && argv[0] != '0')
	{
		throw PmergeMe::InvalidNumber();
	}
	else if (num > static_cast<long int>(std::numeric_limits<int>::max())
		|| errno == ERANGE)
	{
		throw PmergeMe::InvalidNumber();
	}
}

// Constructors
PmergeMe::PmergeMe(void)
{
}
PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe::PmergeMe(int &argc, char *argv[])
{
	clock_t	start_vec;
	clock_t	end_vec;
	double	time_elapsed_vec;
	clock_t	start_deque;
	clock_t	end_deque;
	double	time_elapsed_deque;

	start_vec = clock();
	this->intialize_vector(argc, argv);
	this->merge_insertion_sort_vec();
	end_vec = clock();
	time_elapsed_vec = static_cast<double>(end_vec - start_vec)
		/ CLOCKS_PER_SEC;
	start_deque = clock();
	this->intialize_deque(argc, argv);
	this->merge_insertion_sort_deque();
	end_deque = clock();
	time_elapsed_deque = static_cast<double>(end_deque - start_deque) / CLOCKS_PER_SEC;
	std::cout << "\033[31mBefore\033[00m: " << argv_to_str(argc, argv) << "\n";
	std::cout << "\033[32mAfter\033[00m:  " << vec_to_str(this->_vec) << "\n";
	std::cout << "Time to process a range of " << this->_vec.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << time_elapsed_vec << "s\n";
	std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque:  " << std::fixed << std::setprecision(6) << time_elapsed_deque << "s\n";
}

// Destructor
PmergeMe::~PmergeMe(void)
{
}

// Overloaded Operator
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_deque = other._deque;
		this->_vec = other._vec;
	}
	return (*this);
}

// Function templates
template <typename T> T &next(T it, int distance)
{
	std::advance(it, distance);
	return (it);
}

// Methods

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



// [VECTOR IMPLEMENTATION]
int PmergeMe::sort_pairs_vec(int rec_depth)
{
	int	elems_per_group;
	int	num_groups;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_vec.size() / elems_per_group;
	if (num_groups < 2)
		return (rec_depth - 1);
	for (size_t i = 0; i + 2 * elems_per_group - 1 < this->_vec.size(); i += 2
		* elems_per_group)
	{
		if (this->_vec[i + elems_per_group - 1] > this->_vec[i + 2 * elems_per_group - 1])
		{
			std::swap_ranges(this->_vec.begin() + i,
				this->_vec.begin() + i + elems_per_group,
				this->_vec.begin() + i + elems_per_group);
		}
	}
	return (this->sort_pairs_vec(rec_depth + 1));
}

std::vector<int> initialize_jac_sequence_vec(int max_pending)
{
	int	next;

	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	while (vec.back() < max_pending)
	{
		next = vec[vec.size() - 1] + 2 * vec[vec.size() - 2];
		vec.push_back(next);
	}
	return (vec);
}

std::vector<int> initialize_pend_sequence_vec(std::vector<int> &jac_seq)
{
	std::vector<int> vec;
	if (jac_seq.size() < 4)
	{
		vec.push_back(3);
		vec.push_back(2);
		return (vec);
	}
	for (size_t i = 3; i < jac_seq.size(); i++)
	{
		for (int j = 0; j < jac_seq[i] - jac_seq[i - 1]; j++)
		{
			vec.push_back(jac_seq[i] - j);
		}
	}
	return (vec);
}

void	insert_group_vec(std::vector<int> &vec,
		std::vector<int>::iterator begin, int i, int elems_per_group)
{
	vec.insert(vec.end(), begin + i * elems_per_group, begin + (i + 1)
		* elems_per_group);
}

void PmergeMe::initialize_main_pend_vec(int rec_depth, std::vector<int> &main,
	std::vector<int> &pend, std::vector<int> &non_pend)
{
	int	elems_per_group;
	int	num_groups;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_vec.size() / elems_per_group;
	std::vector<int>::iterator begin = this->_vec.begin();
	for (int i = 0; i < num_groups; i++)
	{
		if (i == 0)
		{
			insert_group_vec(main, begin, i, elems_per_group);
		}
		else if (i == 1 || (i % 2 == 1 && i + 1 <= num_groups) || (i % 2 == 1 && rec_depth == 1))
		{
			insert_group_vec(main, begin, i, elems_per_group);
		}
		else
		{
			insert_group_vec(pend, begin, i, elems_per_group);
		}
	}
	non_pend.insert(non_pend.end(), begin + (num_groups)*elems_per_group, begin
		+ this->_vec.size());
}

std::vector<int> initialize_loc_as_vec(int num_groups)
{
	int	i;

	std::vector<int> res;
	i = -1;
	while (++i < num_groups)
		res.push_back(i + 1);
	return (res);
}

int	get_last_member_of_group_vec(std::vector<int> &vec, int elems_per_group,
		int i)
{
	return (vec[((i)*elems_per_group) + elems_per_group - 1]);
}

int	get_index_binary_search_vec(std::vector<int> &main, std::vector<int> &pend,
		std::vector<int> &loc_as, int elems_per_group, int k_to_sort)
{
	int	high;
	int	current_n;
	int	low;
	int	mid;
	int	item;

	high = loc_as[k_to_sort - 1];
	current_n = main.size() / elems_per_group;
	if (high >= current_n)
		high = current_n - 1;
	low = 0;
	mid = low + (high - low) / 2;
	item = get_last_member_of_group_vec(pend, elems_per_group, k_to_sort - 2);
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (item == get_last_member_of_group_vec(main, elems_per_group, mid))
		{
			return (mid + 1);
		}
		else if (item > get_last_member_of_group_vec(main, elems_per_group,
				mid))
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

void	update_location_as_vec(std::vector<int> &loc_as, int index_to_insert)
{
	for (size_t i = 0; i < loc_as.size(); i++)
	{
		if (loc_as.at(i) >= index_to_insert)
		{
			loc_as.at(i)++;
		}
	}
}

void	binary_search_insertion_vec(std::vector<int> &main, std::vector<int> &pend,
						std::vector<int> &loc_as, int elems_per_group, int k_to_sort)
{
	int	index_to_insert;

	index_to_insert = get_index_binary_search_vec(main, pend, loc_as, elems_per_group, k_to_sort);
	main.insert(main.begin() + index_to_insert * elems_per_group,
				pend.begin() + (k_to_sort - 2) * elems_per_group,
				pend.begin() + (k_to_sort - 1) * elems_per_group);
	update_location_as_vec(loc_as, index_to_insert);
}

void PmergeMe::binary_sort_vec(int rec_depth, std::vector<int> pend_seq)
{
	int	elems_per_group;
	int	num_groups;
	int	total_num_pend;
	int	remaining_num_pend;
	int	i;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_vec.size() / elems_per_group;
	total_num_pend = num_groups / 2 + (num_groups % 2 == 1);
	remaining_num_pend = total_num_pend;
	std::vector<int> loc_as = initialize_loc_as_vec(num_groups);
	std::vector<int> main;
	std::vector<int> pend;
	std::vector<int> non_pend;
	this->initialize_main_pend_vec(rec_depth, main, pend, non_pend);
	i = 0;
	while (remaining_num_pend > 1)
	{
		if (total_num_pend < pend_seq[i])
		{
			i++;
			continue ;
		}
		binary_search_insertion_vec(main, pend, loc_as, elems_per_group,
			pend_seq[i]);
		remaining_num_pend--;
		i++;
	}
	main.insert(main.end(), non_pend.begin(), non_pend.end());
	this->_vec = main;
	main.size();
}

void PmergeMe::merge_insertion_sort_vec()
{
	int	rec_depth;
	int	max_pending;
	
	// Ascending part of the recursion. 
	rec_depth = this->sort_pairs_vec(1);
	max_pending = this->_vec.size() / 2 + 1;
	std::vector<int> jac_seq = initialize_jac_sequence_vec(max_pending);
	std::vector<int> pend_seq = initialize_pend_sequence_vec(jac_seq);

	// Descending part of the recursion. Now that the elements were swaped
	// according to their groups, we need to insertion sort them for each
	// rec_depth
	while (rec_depth > 0)
	{
		this->binary_sort_vec(rec_depth, pend_seq);
		rec_depth--;
	}
	this->is_sorted_vec();
}

// [DEQUE IMPLEMENTATION]

int PmergeMe::sort_pairs_deque(int rec_depth)
{
	int	elems_per_group;
	int	num_groups;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_deque.size() / elems_per_group;
	if (num_groups < 2)
		return (rec_depth - 1);
	for (size_t i = 0; i + 2 * elems_per_group - 1 < this->_deque.size(); i += 2
		* elems_per_group)
	{
		if (this->_deque[i + elems_per_group - 1] > this->_deque[i + 2 * elems_per_group - 1])
		{
			std::swap_ranges(this->_deque.begin() + i,
				this->_deque.begin() + i + elems_per_group,
				this->_deque.begin() + i + elems_per_group);
		}
	}
	return (this->sort_pairs_deque(rec_depth + 1));
}

std::deque<int> initialize_jac_sequence_deque(int max_pending)
{
	int	next;

	std::deque<int> deque;
	deque.push_back(0);
	deque.push_back(1);
	while (deque.back() < max_pending)
	{
		next = deque[deque.size() - 1] + 2 * deque[deque.size() - 2];
		deque.push_back(next);
	}
	return (deque);
}

std::deque<int> initialize_pend_sequence_deque(std::deque<int> &jac_seq)
{
	std::deque<int> deque;
	if (jac_seq.size() < 4)
	{
		deque.push_back(3);
		deque.push_back(2);
		return (deque);
	}
	for (size_t i = 3; i < jac_seq.size(); i++)
	{
		for (int j = 0; j < jac_seq[i] - jac_seq[i - 1]; j++)
		{
			deque.push_back(jac_seq[i] - j);
		}
	}
	return (deque);
}

void	insert_group_deque(std::deque<int> &deque,
		std::deque<int>::iterator begin, int i, int elems_per_group)
{
	deque.insert(deque.end(),
		begin + i * elems_per_group,
		begin + (i + 1) * elems_per_group);
}

void PmergeMe::initialize_main_pend_deque(int rec_depth, std::deque<int> &main,
	std::deque<int> &pend, std::deque<int> &non_pend)
{
	int	elems_per_group;
	int	num_groups;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_deque.size() / elems_per_group;
	std::deque<int>::iterator begin = this->_deque.begin();
	for (int i = 0; i < num_groups; i++)
	{
		if (i == 0)
		{
			insert_group_deque(main, begin, i, elems_per_group);
		}
		else if (i == 1 || (i % 2 == 1 && i + 1 <= num_groups) || (i % 2 == 1 && rec_depth == 1))
		{
			insert_group_deque(main, begin, i, elems_per_group);
		}
		else
		{
			insert_group_deque(pend, begin, i, elems_per_group);
		}
	}
	non_pend.insert(non_pend.end(), begin + (num_groups)*elems_per_group, begin
		+ this->_deque.size());
}

std::deque<int> initialize_loc_as_deque(int num_groups)
{
	int	i;

	std::deque<int> res;
	i = -1;
	while (++i < num_groups)
		res.push_back(i + 1);
	return (res);
}

int	get_last_member_of_group_deque(std::deque<int> &deque, int elems_per_group,
		int i)
{
	return (deque[((i)*elems_per_group) + elems_per_group - 1]);
}

int	get_index_binary_search_deque(std::deque<int> &main, std::deque<int> &pend,
		std::deque<int> &loc_as, int elems_per_group, int k_to_sort)
{
	int	high;
	int	current_n;
	int	low;
	int	mid;
	int	item;

	high = loc_as[k_to_sort - 1];
	current_n = main.size() / elems_per_group;
	if (high >= current_n)
		high = current_n - 1;
	low = 0;
	mid = low + (high - low) / 2;
	item = get_last_member_of_group_deque(pend, elems_per_group, k_to_sort - 2);
	while (low <= high)
	{
		mid = low + (high - low) / 2;
		if (item == get_last_member_of_group_deque(main, elems_per_group, mid))
		{
			return (mid + 1);
		}
		else if (item > get_last_member_of_group_deque(main, elems_per_group,
				mid))
			low = mid + 1;
		else
			high = mid - 1;
	}
	return (low);
}

void	update_location_as_deque(std::deque<int> &loc_as, int index_to_insert)
{
	for (size_t i = 0; i < loc_as.size(); i++)
	{
		if (loc_as.at(i) >= index_to_insert)
		{
			loc_as.at(i)++;
		}
	}
}

void	binary_search_insertion_deque(std::deque<int> &main,
		std::deque<int> &pend, std::deque<int> &loc_as, int elems_per_group,
		int k_to_sort)
{
	int	index_to_insert;

	index_to_insert = get_index_binary_search_deque(main, pend, loc_as,
			elems_per_group, k_to_sort);
	// std::deque<int>::iterator begin = main.begin();
	main.insert(main.begin() + index_to_insert * elems_per_group, pend.begin()
		+ (k_to_sort - 2) * elems_per_group, pend.begin() + (k_to_sort - 1)
		* elems_per_group);
	update_location_as_deque(loc_as, index_to_insert);
}

void PmergeMe::binary_sort_deque(int rec_depth, std::deque<int> pend_seq)
{
	int	elems_per_group;
	int	num_groups;
	int	total_num_pend;
	int	remaining_num_pend;
	int	i;

	elems_per_group = 1u << (rec_depth - 1);
	num_groups = this->_deque.size() / elems_per_group;
	total_num_pend = num_groups / 2 + (num_groups % 2 == 1);
	remaining_num_pend = total_num_pend;
	std::deque<int> loc_as = initialize_loc_as_deque(num_groups);
	std::deque<int> main;
	std::deque<int> pend;
	std::deque<int> non_pend;
	this->initialize_main_pend_deque(rec_depth, main, pend, non_pend);
	i = 0;
	while (remaining_num_pend > 1)
	{
		if (total_num_pend < pend_seq[i])
		{
			i++;
			continue ;
		}
		binary_search_insertion_deque(main, pend, loc_as, elems_per_group,
			pend_seq[i]);
		remaining_num_pend--;
		i++;
	}
	main.insert(main.end(), non_pend.begin(), non_pend.end());
	this->_deque = main;
}

void PmergeMe::merge_insertion_sort_deque()
{
	int	rec_depth;
	int	max_pending;

	rec_depth = this->sort_pairs_deque(1);
	max_pending = this->_deque.size() / 2 + 1;
	std::deque<int> jac_seq = initialize_jac_sequence_deque(max_pending);
	std::deque<int> pend_seq = initialize_pend_sequence_deque(jac_seq);
	while (rec_depth > 0)
	{
		this->binary_sort_deque(rec_depth, pend_seq);		
		rec_depth--;
	}
	this->is_sorted_deque();
}

void PmergeMe::is_sorted_vec()
{
	for (size_t i = 1; i < this->_vec.size(); i++)
	{
		if (this->_vec.at(i) < this->_vec.at(i - 1))
		{
			throw NotSorted();
		}
	}
}

void PmergeMe::is_sorted_deque()
{
	for (size_t i = 1; i < this->_deque.size(); i++)
	{
		if (this->_deque.at(i) < this->_deque.at(i - 1))
		{
			throw NotSorted();
		}
	}
}

const char *PmergeMe::MissingInput::what() const throw()
{
	return ("Missing Input");
}

const char *PmergeMe::InvalidNumber::what() const throw()
{
	return ("Invalid Expression");
}

const char *PmergeMe::NotSorted::what() const throw()
{
	return ("Not Sorted");
}
