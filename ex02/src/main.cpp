/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:29:14 by tsilveir          #+#    #+#             */
/*   Updated: 2026/01/21 16:45:51 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "../includes/PmergeMe.hpp"


int main(int argc, char* argv[])
{
		// input validation
	if (argc == 1)
	{
		std::cerr << "Error\n";
		return 0;
	}
	
	try
	{
		PmergeMe a(argc, argv);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error\n";
	}
	
}
