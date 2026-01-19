/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:29:14 by tsilveir          #+#    #+#             */
/*   Updated: 2026/01/19 22:53:36 by tsilveir         ###   ########.fr       */
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
	
	PmergeMe a(argc, argv);

	std::cout << "[Vector section]\n";
	for (int i = 0; i < static_cast<int>(a._vec.size()); i++)
	{
		std::cout << a._vec[i] <<"\n";
	}
	std::cout << "[deque section]\n";
	for (int i = 0; i < static_cast<int>(a._deque.size()); i++)
	{
		std::cout << a._deque[i] <<"\n";
	}
}
