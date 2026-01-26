#include "../includes/BitcoinExchange.hpp"

// Utils
bool	is_valid_float(std::string str){
	if (str.empty())
		return false;

	if (str.find(' ') != std::string::npos)
		return false;
	
	char *endptr;
	std::strtof(str.c_str(),&endptr);

	if (*endptr != 0)
		return false;
	return true;
}


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
int Date::getYear() const
{
	return(this->year);
}

int Date::getMonth() const
{
	return(this->month);
}

int Date::getDay() const
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

std::ostream&	operator<<(std::ostream& os, const Date& obj)
{
	os << obj.getYear() << "-" <<
		std::setfill('0') << std::setw(2) << obj.getMonth() << "-" <<
		std::setfill('0') << std::setw(2) << obj.getDay();
	return(os);
}

const char *Date::InvalidDate::what() const throw()
{
	return ("Invalid Date");
}


// ======================================= BitcoinExchange =======================================

// Utils
struct ParseResult {
    bool valid;
    Date date;
    float quantity;
    std::string error_msg;
};

ParseResult parse_line(const std::string& line) {
	ParseResult result = {false, Date(), 0.0f, ""};
	
	if (line.size() < 14) {
		result.error_msg = "Line too short";
		return result;
	}
	
	if (line.find('|') == std::string::npos) {
		result.error_msg = "Line not formatted correctly";
		return result;
	}
	
	std::string date_str = line.substr(0, line.find('|') - 1);
	std::string float_str = line.substr(line.find('|') + 2);
	
	try {
		result.date = Date(date_str);
	} catch(const Date::InvalidDate&) {
		result.error_msg = "bad input => " + date_str;
		return result;
	}
	
	if (!is_valid_float(float_str)) {
		result.error_msg = "invalid float => " + line;
		return result;
	}
	
	result.quantity = atof(float_str.c_str());
	
	if (result.quantity < 0) {
		result.error_msg = "not a positive number.";
		return result;
	}
	
	if (result.quantity > 1000) {
		result.error_msg = "too large a number.";
		return result;
	}
	
	result.valid = true;
	return result;
}

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
	std::string float_str;
	float num;

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
			float_str = temp.substr(temp.find(',')+1, temp.size() - temp.find(',')-1);
		}
		if (is_valid_float(float_str) == false)
			throw BitcoinExchange::InvalidDataFile();
		
		num = static_cast<float>(atof(float_str.c_str()));
		this->database.insert(std::make_pair(Date(date), num));
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
	std::map<Date, float>::iterator it = this->database.upper_bound(target);
	if (it == this->database.begin())
		throw BitcoinExchange::DateBeforeBitcoinInception();
	
	--it;
	return (it->second);
}

void	BitcoinExchange::process_input_file(char *filename)
{
	std::ifstream	in_file;

	in_file.open(filename, std::ios::in | std::ios::binary);
	if (in_file.fail())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string header;

	std::getline(in_file, header);
	if(header.compare("date | value") != 0)
	{
		std::cerr << "Error: No header in file" << std::endl;
		return;
	}

	std::string line;
	std::string date;
	std::string float_str;

	while (std::getline(in_file, line))
	{
		ParseResult parsed = parse_line(line);

		if (!parsed.valid)
		{
			std::cerr << "Error: " << parsed.error_msg <<'\n';
			continue;
		}

		try
		{
			float bitcoin_value = this->get_db_value(parsed.date);
			std::cout << parsed.date << " | " <<  
					parsed.quantity << " = " << parsed.quantity * bitcoin_value<< std::endl;

		}
		catch(const BitcoinExchange::DateBeforeBitcoinInception& e)
		{
			std::cerr << "Error: Bitcoin did not exist yet.\n";
			continue;
		}
	}
	return;
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

void BitcoinExchange::print_all() const {
    std::map<Date, float>::const_iterator it;
    for (it = this->database.begin(); it != this->database.end(); ++it) {
        Date d = it->first;
        std::cout << d.getYear() << "-" 
                  << std::setw(2) << std::setfill('0') << d.getMonth() << "-" 
                  << std::setw(2) << std::setfill('0') << d.getDay() 
                  << " => " << it->second << std::endl;
    }
}

const char *BitcoinExchange::InvalidDataFile::what() const throw()
{
	return ("Invalid Data File");
}

const char *BitcoinExchange::DateBeforeBitcoinInception::what() const throw()
{
	return ("Date before Bitcoin inception");
}
