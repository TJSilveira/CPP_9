#include "../includes/BitcoinExchange.hpp"

static bool is_leap_year(int &year);
static bool is_valid_date(const std::string &date_str);
static bool is_valid_day(int &year, int &month, int &day);

	// Constructors
Date::Date(void): year(1900), month(1), day(1)
{
	// std::cout << "[Date] Default constructor called. " << std::endl;
	return;
}

Date::Date(const Date& other)
{
	// std::cout << "[Date] Copy constructor called. " << std::endl;
	*this = other;
	return;
}

Date::Date(const std::string &other)
{
	// std::cout << "[Date] String constructor called. " << std::endl;

	if (is_valid_date(other) == false)
		throw Date::InvalidDate();

	int year = atoi(other.substr(0,4).c_str());
	int month = atoi(other.substr(5,2).c_str());
	int day = atoi(other.substr(8,2).c_str());

	if (!(month >= 1 && month <= 12) || 
			is_valid_day(year, month, day) == false)
		throw Date::InvalidDate();

	this->year = year;
	this->month = month;
	this->day = day;
	return;
}

	// Destructor
Date::~Date(void)
{
	return;
}

	// Overloaded Operator
Date&		Date::operator=(const Date& other)
{
	if(this != &other)
	{
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}
	// std::cout << "[Date] Copy assignment operator called. " << std::endl;
	return *this;
}

// Getters
int Date::getYear()
{
	return(this->year);
}

int Date::getMonth()
{
	return(this->month);
}

int Date::getDay()
{
	return(this->day);
}

// helper functions

static bool is_leap_year(int &year)
{
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
			return true;
		return false;
	}
	else if ( year % 4 == 0)
		return true;
	else
		return false;
}

static bool is_valid_date(const std::string &date_str)
{
	if (date_str.size()!=10)
		return (false);

	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
		{
			if (date_str.at(i) != '-')
				return (false);
		}
		else
		{
			if (!(::isdigit(date_str.at(i))))
				return (false);
		}
	}
	return (true);
}

static bool is_valid_day(int &year, int &month, int &day)
{
	int days_year[2][12] = {{31,28,31,30,31,30,31,31,30,31,30,31},
													{31,29,31,30,31,30,31,31,30,31,30,31}};

	if (day >= 1 &&
			day <= days_year[is_leap_year(year) * 1][month - 1])
	{
		return (true);
	}
	return (false);
}

// Operator Overload

bool		Date::operator==(const Date& other)
{
	if (this->day == other.day &&
			this->month == other.month &&
			this->year == other.year)
	{
		return true;
	}
	return false;
}

bool		Date::operator<(const Date& other) const
{
	if (this->year != other.year)
		return (this->year < other.year);
	else if (this->month != other.month)
		return (this->month < other.month);
	else
		return (this->day < other.day);
}


const char *Date::InvalidDate::what() const throw()
{
	return ("Invalid Date");
}


// ======================================= BitcoinExchange =======================================

	// Constructors
BitcoinExchange::BitcoinExchange(void)
{
	std::ifstream	in_file;

	in_file.open("data.csv", std::ios::in | std::ios::binary);
	if (in_file.fail())
	{
		std::cerr << "Error: data.csv: No file or directory" << std::endl;
		throw BitcoinExchange::InvalidDataFile();
	}

	std::string temp;
	std::string date;
	std::string float_num;

	std::getline(in_file, temp);
	if(temp.compare("date,exchange_rate") != 0)
		throw BitcoinExchange::InvalidDataFile();

	while (std::getline(in_file, temp))
	{					
		if (temp.find(',') == std::string::npos)
			throw BitcoinExchange::InvalidDataFile();
		else
		{
			date = temp.substr(0, temp.find(','));
			float_num = temp.substr(temp.find(','), temp.size() - temp.find(','));
		}
		this->database.insert(std::make_pair(Date(date), static_cast<float>(atof(float_num.c_str()))));
	}
	return;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	std::cout << "[BitcoinExchange] Copy constructor called. " <<
				std::endl;
	*this = other;
	return;
}

	// Destructor
BitcoinExchange::~BitcoinExchange(void)
{
	return;
}

float	BitcoinExchange::get_db_value(const Date& target)
{
	if (this->database.upper_bound(target) == this->database.begin())
		throw BitcoinExchange::DateBeforeBitcoinInception();
	
	return (this->database.upper_bound(target)->second);
}

float	BitcoinExchange::print_final_value(const std::string line)
{

	try
	{
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

std::ifstream	BitcoinExchange::process_input_file(char *filename)
{
	
}




	// Overloaded Operator
BitcoinExchange&		BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if(this != &other)
		this->database = other.database;
	std::cout << "[BitcoinExchange] Copy assignment operator called. " <<
	 			this <<
			std::endl;
	return *this;
}

const char *BitcoinExchange::InvalidDataFile::what() const throw()
{
	return ("Invalid Data File");
}

const char *BitcoinExchange::DateBeforeBitcoinInception::what() const throw()
{
	return ("Date before Bitcoin inception");
}
