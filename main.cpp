/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/07/11 19:36:31 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
// #include "map.hpp"
#include <map>

int main(void)
{
	// std::cout << "\e[7m=============EMPTY MAP============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::map<int> test;
	// 		std::cout << test.size() << std::endl;
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	std::cout << "\e[7m============UPPER BOUND MAP==========\e[0m" << std::endl;
	{
		try
		{
			std::map<char, int> mymap;
			std::map<char, int>::iterator itlow, itup;

			mymap['a'] = 20;
			mymap['c'] = 40;
			mymap['e'] = 60;
			mymap['g'] = 80;
			mymap['i'] = 100;

			itlow = mymap.lower_bound('b'); // itlow points to b
			itup = mymap.upper_bound('d');	// itup points to e (not d!)

			itlow--;
			
			std::cout << itlow->first << std::endl;
			std::cout << itup->first << std::endl;

		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	// std::cout << "\e[7m=============SIZED MAP============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> test;
	// 		std::cout << test.size() << std::endl;
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	return (0);
}