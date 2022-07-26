/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/07/25 16:57:23 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <list>
#include "map.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "set.hpp"

#define SHOW(...) std::cout << std::setw(35) << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl;

#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

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

template <typename T_STACK>
void	printSize_stk(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	if (print_content)
	{
		std::cout << std::endl << "Content was:" << std::endl;
		while (stck.size() != 0) {
			std::cout << "- " << stck.top() << std::endl;
			stck.pop();
		}
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize_map(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
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

template <class T>
void	is_empty(T const &mp)
{
	std::cout << "is_empty: " << mp.empty() << std::endl;
}

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	printSize_map(mp);
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
		ft::set<int> s;

		return 0;
	}
}