/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 19:42:56 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <vector>
#include "vector.hpp"
#include "pairs/pair.hpp"
#include "utils/is_integral.hpp"

#define SHOW(...) std::cout << std::setw(35) << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl;

int	main(void)
{
	std::cout << "\e[7m=============EMPTY VECTOR============\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> test;
			std::cout << test.size() << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m=============SIZED VECTOR============\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> test(10);
			std::cout << test.size() << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m===========ASSIGN====================\e[0m" << std::endl;
	{
		try
		{
			std::vector<int> test_v(10, 10);
			
			ft::vector<int> test;

			test.assign(test_v.begin(), test_v.end());
			std::cout << test.size() << std::endl;
			for (int i = 0; i < 10; i++) {
				std::cout << i << ": " << test.at(i) << std::endl;
			}
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m===========ITERATOR==================\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> test(10);

			int i = 0;
			for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
				*it = i++;
			}
			i = 0;
			for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
				std::cout << i << ": " << test[i] << std::endl;
				i++;
			}
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m===========PAIRS==================\e[0m" << std::endl;
	{
		try
		{
			std::cout << std::boolalpha;
			
			ft::pair<int, int>	pair_test;
			ft::pair<int, int>	pair_test2(-10, 20);

			pair_test = pair_test2;
			std::cout << "test is equal to test2? " << (pair_test == pair_test2) <<std::endl;
			pair_test2 = ft::make_pair<int, int>(-50, 100);
			std::cout << "test is equal to test2? " << (pair_test == pair_test2) <<std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m===========IS_INTEGRAL==============\e[0m" << std::endl;
	{
		try
		{
			std::cout << std::boolalpha;
 
			SHOW( ft::is_integral<float>::value );
			SHOW( ft::is_integral<int>::value );
			SHOW( ft::is_integral<const int>::value );
			SHOW( ft::is_integral<bool>::value );
			SHOW( ft::is_integral<char>::value );
			SHOW( ft::is_integral<long long>::value );
			SHOW( ft::is_integral<std::string>::value );
			
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}