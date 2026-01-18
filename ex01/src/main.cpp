/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:29:14 by tsilveir          #+#    #+#             */
/*   Updated: 2026/01/18 20:20:59 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include "../includes/RPN.hpp"


int main(int argc, char* argv[])
{
	if (argc != 2 )
	{
		std::cout << "Error: expected './RPN \"<expression>\"'.\n";
		return (EXIT_SUCCESS);
	}

	RPN nums;

	try
	{
		std::cout << nums.process_expression(argv[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error" << '\n';
	}
	
}
