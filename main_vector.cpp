/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/06/14 10:19:12 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <vector>
#include "vector.hpp"
#include "pairs/pair.hpp"

#define SHOW(...) std::cout << std::setw(35) << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl;

static void print_vector(int id, const ft::vector<int>& container)
{
    std::cout << id << ". ";
    for (size_t x = 0; x < container.size(); x++) {
         std::cout << container[x] << ' ';
    }
    std::cout << std::endl;
}

template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
    os << "{";
    for (std::size_t i = 0; i < co.size(); ++i) { os << ' ' << i; }
    return os << " } ";
}

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
			ft::vector<int> test_v(10, 10);
			
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
	// std::cout << "\e[7m=========REVERSE ITERATOR============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> test(10);

	// 		int i = 0;
	// 		for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
	// 			*it = i++;
	// 		}
	// 		i = 0;
	// 		for (ft::vector<int>::reverse_iterator it = test.rbegin(); it != test.rend(); ++it) {
	// 			std::cout << i << ": " << test[i] << std::endl;
	// 			i++;
	// 		}
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	std::cout << "\e[7m============VECTOR INSERT============\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> c1(3, 100);
			print_vector(1, c1);
		
			// ft::vector<int>::iterator it = c1.begin();
			// it = c1.insert(it, 200);
			// print_vector(2, c1);
		
			// c1.insert(it, 2, 300);
			// print_vector(3, c1);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m==============ERASE==================\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> c;
			for (int i = 0; i < 10; ++i)
				c.push_back(i);
			print_vector(0, c);

			c.erase(c.begin());
			print_vector(1, c);

			c.erase(c.begin()+2, c.begin()+5);
			print_vector(2, c);

			// Erase all even numbers
			for (ft::vector<int>::iterator it = c.begin(); it != c.end(); ) {
				if (*it % 2 == 0) {
				it = c.erase(it);
				} else {
				++it;
				}
			}
			print_vector(3, c);
			
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
	std::cout << "\e[7m==============EQUAL==================\e[0m" << std::endl;
	{
		try
		{
			std::string s = "radar";
			std::cout << "\"" << s << "\" "
				<< (ft::equal(s.begin(), s.begin() + s.size()/2, s.rbegin()) ? "is" : "is not")
				<< " a palindrome\n";

			s = "prout";
			std::cout << "\"" << s << "\" "
				<< (ft::equal(s.begin(), s.begin() + s.size()/2, s.rbegin()) ? "is" : "is not")
				<< " a palindrome\n";
			
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\e[7m==============SWAP VECTOR==================\e[0m" << std::endl;
	{
		try
		{
			ft::vector<int> a1, a2;
		
			a1.push_back(1);a1.push_back(2);a1.push_back(3);
			a2.push_back(4);a2.push_back(5);
			
			ft::vector<int>::iterator it1 = 1 + a1.begin();
			ft::vector<int>::iterator it2 = 1 + a2.begin();
		
			int& ref1 = a1.front();
			int& ref2 = a2.front();
		
			std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
			a1.swap(a2);
			std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';						
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}