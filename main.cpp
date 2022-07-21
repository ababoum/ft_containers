/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/07/21 16:02:22 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include "map.hpp"
#include "vector.hpp"
#include <map>
#include <vector>


#define SHOW(...) std::cout << std::setw(35) << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl;

void print_vector(int id, const ft::vector<int>& container)
{
    std::cout << id << ". ";
    for (size_t x = 0; x < container.size(); x++) {
         std::cout << container[x] << ' ';
    }
    std::cout << std::endl;
}

// template<class Os, class Co> Os& operator<<(Os& os, const Co& co) {
//     os << "{";
//     for (std::size_t i = 0; i < co.size(); ++i) { os << ' ' << i; }
//     return os << " } ";
// }

template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const std::size_t size = vct.size();
	const std::size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <class T>
void	checkErase(ft::vector<T> const &vct,
					typename ft::vector<T>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int main(void)
{
	// std::cout << "\e[7m=============EMPTY MAP============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::map<char, int> test;
	// 		std::cout << test.size() << std::endl;
	// 	}
	// 	catch (std::exception &e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	
	// std::cout << "\e[7m=============SIZED MAP============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		std::vector<ft::pair<char, int> > mymap;
	// 		mymap.push_back(ft::pair<char, int>('a', 100));
	// 		mymap.push_back(ft::pair<char, int>('e', 150));
	// 		mymap.push_back(ft::pair<char, int>('f', 175));
	// 		mymap.push_back(ft::pair<char, int>('z', 200));
	// 		ft::map<char, int> test(mymap.begin(), mymap.end());
	// 		std::cout << test.size() << std::endl;			
	// 	}
	// 	catch (std::exception &e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	
	// std::cout << "\e[7m=============SIZED MAP 2============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::map<char, int> mymap;
	// 		mymap.insert(ft::pair<const char, int>('a', 100));
	// 		mymap.insert(ft::pair<const char, int>('e', 150));
	// 		mymap.insert(ft::pair<const char, int>('f', 175));
	// 		mymap.insert(ft::pair<const char, int>('z', 200));
	// 		ft::map<char, int> test(mymap);
	// 		std::cout << test.size() << std::endl;			
	// 	}
	// 	catch (std::exception &e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	// return (0);
	
	// std::cout << "\e[7m=============EMPTY VECTOR============\e[0m" << std::endl;
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
	
	// std::cout << "\e[7m=============SIZED VECTOR============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> test(10);
	// 		std::cout << test.size() << std::endl;
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

	// std::cout << "\e[7m===========ASSIGN====================\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> test_v(10, 10);	
	// 		ft::vector<int> test;
	// 		test.assign(test_v.begin(), test_v.end());
	// 		std::cout << test.size() << std::endl;
	// 		for (int i = 0; i < 10; i++) {
	// 			std::cout << i << ": " << test.at(i) << std::endl;
	// 		}
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	
	// std::cout << "\e[7m===========ITERATOR==================\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> test(10);
	// 		int i = 0;
	// 		for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
	// 			*it = i++;
	// 		}
	// 		i = 0;
	// 		for (ft::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
	// 			std::cout << i << ": " << *it << std::endl;
	// 			i++;
	// 		}
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

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
	// 			std::cout << i << ": " << *it << std::endl;
	// 			i++;
	// 		}
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	
	// std::cout << "\e[7m===========VECTOR PUSH_BACK==========\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> c1;
	// 		c1.push_back(1);
	// 		c1.push_back(2);
	// 		c1.push_back(3);
	// 		c1.push_back(4);
	// 		print_vector(1, c1);
	// 		std::cout << "front: " << c1.front() << std::endl;
	// 		std::cout << "back: " << c1.back() << std::endl;
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

	// std::cout << "\e[7m============VECTOR INSERT============\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> c1(3, 100);
	// 		print_vector(1, c1);
	// 		c1.insert(c1.begin(), 200);
	// 		print_vector(2, c1);	
	// 		c1.insert(c1.begin() + 2, 2, 300);
	// 		print_vector(3, c1);
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }
	
	// std::cout << "\e[7m==============ERASE==================\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> c;
	// 		for (int i = 0; i < 10; ++i)
	// 			c.push_back(i);
	// 		print_vector(0, c);
	// 		c.erase(c.begin());
	// 		print_vector(1, c);
	// 		c.erase(c.begin() + 2, c.begin() + 4);
	// 		print_vector(2, c);
	// 		// Erase all even numbers
	// 		for (ft::vector<int>::iterator it = c.begin(); it != c.end(); ) {
	// 			if (*it % 2 == 0) {
	// 			it = c.erase(it);
	// 			} else {
	// 			++it;
	// 			}
	// 		}
	// 		print_vector(3, c);	
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

	// std::cout << "\e[7m==============SWAP VECTOR==================\e[0m" << std::endl;
	// {
	// 	try
	// 	{
	// 		ft::vector<int> a1, a2;
	// 		a1.push_back(1);a1.push_back(2);a1.push_back(3);
	// 		a2.push_back(4);a2.push_back(5);
	// 		print_vector(1, a1);
	// 		print_vector(2, a2);					
	// 		std::cout << "After swap:" << std::endl;
	// 		ft::swap(a1, a2);
	// 		print_vector(1, a1);
	// 		print_vector(2, a2);			
	// 	}
	// 	catch (std::exception & e)
	// 	{
	// 		std::cout << e.what() << std::endl;
	// 	}
	// }

	std::cout << "\e[7m==============TESTER AREA==================\e[0m" << std::endl;
	{

		const int size = 5;
		ft::vector<int> vct(size);
		ft::vector<int>::reverse_iterator it = vct.rbegin();
		ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 1) << std::endl;

		*(it -= 2) = 42;
		*(it += 2) = 21;

		std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		std::cout << "(it == const_it): " << (ite == it) << std::endl;
		std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

		printSize(vct, true);
		return (0);
		
	}
}