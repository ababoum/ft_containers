/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/07/18 20:06:10 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include "map.hpp"
#include <map>
#include <vector>

int main(void)
{
	std::cout << "\e[7m=============EMPTY MAP============\e[0m" << std::endl;
	{
		try
		{
			ft::map<char, int> test;
			std::cout << test.size() << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m=============SIZED MAP============\e[0m" << std::endl;
	{
		try
		{
			std::vector<std::pair<char, int> > mymap;
			mymap.push_back(std::pair<char, int>('a', 100));
			mymap.push_back(std::pair<char, int>('e', 150));
			mymap.push_back(std::pair<char, int>('f', 175));
			mymap.push_back(std::pair<char, int>('z', 200));

			ft::map<char, int> test(mymap.begin(), mymap.end());
			std::cout << test.size() << std::endl;			
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}