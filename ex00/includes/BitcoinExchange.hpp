#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>

class Date
{
	private:
		int	year;
		int	month;
		int day;
	public:
	// Constructors
	Date(void);
	Date(const std::string &other);
	Date(const Date& other);

	// Destructor
	~Date(void);

	// Getter
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	// Methods
	
	
	// Overloaded Operator
	Date&		operator=(const Date& other);
	bool		operator==(const Date& other);
	bool		operator<(const Date& other) const;

	class InvalidDate: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

std::ostream&	operator<<(std::ostream& os, const Date& obj);

class BitcoinExchange
{
private:
	std::map<Date, float> database;
public:
	// Constructors
	BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange& other);

	// Destructor
	~BitcoinExchange(void);

	// Getter

	// Methods
	float	get_db_value(const Date& target);
	void	process_input_file(char *filename);
	void print_all() const;


	// Overloaded Operator
	BitcoinExchange&		operator=(const BitcoinExchange& other);

	class InvalidDataFile: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class DateBeforeBitcoinInception: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};

	class InvalidFloat: public std::exception
	{
	public:
		virtual const char *what() const throw();
	};
};

#endif