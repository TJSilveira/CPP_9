/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:29:14 by tsilveir          #+#    #+#             */
/*   Updated: 2026/01/18 00:40:03 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "../includes/BitcoinExchange.hpp"


int main(int argc, char* argv[])
{
	if (argc != 2 )
	{
		std::cout << "Error: could not open file.\n";
		return (EXIT_SUCCESS);
	}

	BitcoinExchange exchange;

	exchange.print_all();

	exchange.process_input_file(argv[1]);
}
