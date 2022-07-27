/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:58:57 by mababou           #+#    #+#             */
/*   Updated: 2022/07/27 17:49:50 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <list>

#ifdef FT

# include "map.hpp"
# include "vector.hpp"
# include "stack.hpp"
# include "set.hpp"
namespace TEST = ft;

#else

# include <map>
# include <vector>
# include <stack>
# include <set>
namespace TEST = std;

#endif


#define T1 int
#define T2 std::string
typedef TEST::map<T1, T2>::value_type T3;
typedef TEST::map<int, const char*>::value_type T4;


void console(std::string msg)
{
	std::cout << msg << std::endl;
}


template <typename T>
void	print_vec(TEST::vector<T> const &vct, bool print_content = true)
{
	const std::size_t size = vct.size();
	const std::size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "empty? " << vct.empty() << std::endl;
	if (print_content)
	{
		typename TEST::vector<T>::const_iterator it = vct.begin();
		typename TEST::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T_STACK>
void	print_stack(T_STACK &stck, bool print_content = 1)
{
	std::cout << "size: " << stck.size() << std::endl;
	std::cout << "empty? " << stck.empty() << std::endl;
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
void	print_map(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	// std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T>
std::string	printPair_set(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "value: " << *iterator;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_SET>
void	print_set(T_SET const &st, bool print_content = 1)
{
	std::cout << "size: " << st.size() << std::endl;
	// std::cout << "max_size: " << st.max_size() << std::endl;
	if (print_content)
	{
		typename T_SET::const_iterator it = st.begin(), ite = st.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair_set(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename I>
void print_equal_range(I first, I lb, I ub, I last) {
    for (I i = first; i != lb; ++i)
        std::cout << *i << " ";
    std::cout << "[ ";
    for (I i = lb; i != ub; ++i)
        std::cout << *i << " ";
    std::cout << ") ";
    for (I i = ub; i != last; ++i)
        std::cout << *i << " ";
    std::cout << '\n';
}

int main(void)
{
	std::cout << "\e[7m=============EMPTY/SIZED VECTOR============\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test;
			TEST::vector<int> test2(10);
			
			print_vec(test);
			print_vec(test2);

		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=========VECTOR ASSIGN / IT CONSTR.=========\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test_v(10, 10);	
			TEST::vector<int> test;
			
			test.assign(test_v.begin(), test_v.end());
			print_vec(test);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m===========ITERATOR VECTOR==================\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test(10);
			print_vec(test);
			
			int i = 0;
			for (TEST::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
				*it = i++;
			}
			console("after changes:");
			print_vec(test);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=========REVERSE ITERATOR VECTOR============\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test(10);
			print_vec(test);
			
			int i = 0;
			for (TEST::vector<int>::iterator it = test.begin(); it != test.end(); ++it) {
				*it = i++;
			}
			console("after changes:");
			print_vec(test);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m===========VECTOR PUSH_BACK==========\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test;

			for (int i = 0; i < 50; ++i)
				test.push_back(i);
			
			print_vec(test);
			
			std::cout << "front: " << test.front() << std::endl;
			std::cout << "back: " << test.back() << std::endl;
			
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m============VECTOR INSERT============\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> test(3, 100);
			print_vec(test);
			test.insert(test.begin(), 200);
			console("after insert (begin):");
			print_vec(test);	
			test.insert(test.begin() + 2, 2, 300);
			console("after insert (middle):");
			print_vec(test);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m===========VECTOR ERASE==============\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> c;
			for (int i = 0; i < 10; ++i)
				c.push_back(i);
			print_vec(c);

			c.erase(c.begin());
			console("after erase (begin):");
			print_vec(c);
			
			c.erase(c.begin() + 2, c.begin() + 4);
			console("after erase (middle):");
			print_vec(c);
			
			// Erase all even numbers
			for (TEST::vector<int>::iterator it = c.begin(); it != c.end(); ) {
				if (*it % 2 == 0)
					it = c.erase(it);
				else
					++it;
				}
			console("after erasing even numbers");
			print_vec(c);
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=====SWAP VECTOR / COMPARISONS=======\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> a1, a2;
			a1.push_back(1);a1.push_back(2);a1.push_back(3);
			a2.push_back(4);a2.push_back(5);
			console("1.");
			print_vec(a1);
			console("2.");
			print_vec(a2);
						
			std::cout << "After swap:" << std::endl;
			TEST::swap(a1, a2);
			console("1.");
			print_vec(a1);
			console("2.");
			print_vec(a2);		


			console("==");
			std::cout << (a1 == a2) << std::endl;
			console("<");
			std::cout << (a1 < a2) << std::endl;
			console(">");
			std::cout << (a1 > a2) << std::endl;
			console("<=");
			std::cout << (a1 <= a2) << std::endl;
			console(">=");
			std::cout << (a1 >= a2) << std::endl;
			console("!=");
			std::cout << (a1 != a2) << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============EMPTY STACK============\e[0m" << std::endl;
	{
		try
		{
			TEST::stack<std::string> test;
			print_stack(test);
			
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============COPY STACK============\e[0m" << std::endl;
	{
		try
		{
			TEST::stack<std::string> test;
			
			test.push("lala");
			test.push("lolo");
			test.push("lili");
			console("test stack:");
			print_stack(test);

			TEST::stack<std::string> test2(test);
			console("copied stack:");
			print_stack(test2);
			
			TEST::stack<std::string> test3;

			test3 = test;
			console("copied with = stack:");
			print_stack(test3);			
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=====STACK COMPARISONS=======\e[0m" << std::endl;
	{
		try
		{
			TEST::stack<int> a1, a2;

			a1.push(1);a1.push(2);a1.push(3);
			a2.push(4);a2.push(5);

			console("==");
			std::cout << (a1 == a2) << std::endl;
			console("<");
			std::cout << (a1 < a2) << std::endl;
			console(">");
			std::cout << (a1 > a2) << std::endl;
			console("<=");
			std::cout << (a1 <= a2) << std::endl;
			console(">=");
			std::cout << (a1 >= a2) << std::endl;
			console("!=");
			std::cout << (a1 != a2) << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	
	std::cout << "\e[7m=============EMPTY MAP============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<char, int> test;
			
			print_map(test);
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
			TEST::vector<TEST::pair<const char, int> > vec;
			
			vec.push_back(TEST::pair<const char, int>('a', 100));
			vec.push_back(TEST::pair<const char, int>('e', 150));
			vec.push_back(TEST::pair<const char, int>('f', 175));
			vec.push_back(TEST::pair<const char, int>('z', 200));

			
			TEST::map<char, int> test(vec.begin(), vec.end());
			print_map(test);		
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m=============COPIED MAP============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<char, int> mymap;
			
			mymap.insert(TEST::pair<const char, int>('a', 100));
			mymap.insert(TEST::pair<const char, int>('e', 150));
			mymap.insert(TEST::pair<const char, int>('f', 175));
			mymap.insert(TEST::pair<const char, int>('z', 200));
			
			TEST::map<char, int> test(mymap);
			print_map(test);			
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============MAP: BOUNDS============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<char, int> mymap;
			
			mymap.insert(TEST::pair<const char, int>('a', 100));
			mymap.insert(TEST::pair<const char, int>('e', 150));
			mymap.insert(TEST::pair<const char, int>('f', 175));
			mymap.insert(TEST::pair<const char, int>('z', 200));

			print_map(mymap);

			console("key: a");
			console("lower_bound: ");
			std::cout << (mymap.lower_bound('a'))->first << std::endl;
			console("upper_bound: ");
			std::cout << (mymap.upper_bound('a'))->first << std::endl;

			console("key: Z");
			console("lower_bound: ");
			std::cout << (mymap.lower_bound('Z'))->first << std::endl;
			console("upper_bound: ");
			std::cout << (mymap.upper_bound('Z'))->first << std::endl;

			console("key: c");
			console("lower_bound: ");
			std::cout << (mymap.lower_bound('c'))->first << std::endl;
			console("upper_bound: ");
			std::cout << (mymap.upper_bound('c'))->first << std::endl;

		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============MAP: []============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<char, std::string> mp;

			mp['a'] = "an element";
			mp['b'] = "another element";
			mp['c'] = mp['b'];
			mp['b'] = "old element";

			print_map(mp);

			console("insert a new element via operator[]: ");
			std::cout << mp['d'] << std::endl;

			print_map(mp);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=======MAP: INSERT / COMPARISONS=====\e[0m" << std::endl;
	{
		try
		{
			TEST::map<T1, T2> mp, mp2;

			mp.insert(T3(42, "lol"));
			mp.insert(T3(42, "mdr"));
			mp.insert(T3(50, "mdr"));
			mp.insert(T3(35, "funny"));
			mp.insert(T3(45, "bunny"));
			mp.insert(T3(21, "fizz"));
			mp.insert(T3(38, "buzz"));
			mp.insert(T3(55, "fuzzy"));
			mp2.insert(T3(1337, "beauty"));
			mp2.insert(mp2.end(), T3(1000, "Hello"));
			mp2.insert(mp2.end(), T3(1500, "World"));

			console("mp");
			print_map(mp);
			console("mp2");
			print_map(mp2);


			console("==");
			std::cout << (mp == mp2) << std::endl;
			console("<");
			std::cout << (mp < mp2) << std::endl;
			console(">");
			std::cout << (mp > mp2) << std::endl;
			console("<=");
			std::cout << (mp <= mp2) << std::endl;
			console(">=");
			std::cout << (mp >= mp2) << std::endl;
			console("!=");
			std::cout << (mp != mp2) << std::endl;
					
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============MAP: ERASE/CLEAR============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<T1, T2> mp;

			mp.insert(T3(42, "lol"));
			mp.insert(T3(42, "mdr"));
			mp.insert(T3(50, "mdr"));
			mp.insert(T3(35, "funny"));
			mp.insert(T3(45, "bunny"));
			mp.insert(T3(21, "fizz"));
			mp.insert(T3(38, "buzz"));
			mp.insert(T3(55, "fuzzy"));

			console("before erase");
			print_map(mp);


			mp.erase(42);
			console("after erasing 42");
			print_map(mp);
			
			
			mp.clear();
			console("after clear");
			print_map(mp);
					
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============MAP: EQUAL RANGE============\e[0m" << std::endl;
	{
		try
		{
			TEST::map<int, const char*> m;
			
			m.insert(T4(0, "zero"));
			m.insert(T4(1, "one"));
			m.insert(T4(2, "two"));

			{
				TEST::pair<TEST::map<int, const char*>::iterator, TEST::map<int, const char*>::iterator> p = m.equal_range(1);
				for (TEST::map<int, const char*>::iterator & q = p.first; q != p.second; ++q) {
					std::cout << "m[" << q->first << "] = " << q->second << '\n';
				}

				if (p.second == m.find(2)) {
					std::cout << "end of equal_range (p.second) is one-past p.first\n";
				} else {
					std::cout << "unexpected; p.second expected to be one-past p.first\n";
				}
			}

			{
				TEST::pair<TEST::map<int, const char*>::iterator, TEST::map<int, const char*>::iterator> pp = m.equal_range(-1);
				if (pp.first == m.begin()) {
					std::cout << "pp.first is iterator to first not-less than -1\n";
				} else {
					std::cout << "unexpected pp.first\n";
				}

				if (pp.second == m.begin()) {
					std::cout << "pp.second is iterator to first element greater-than -1\n";
				} else {
					std::cout << "unexpected pp.second\n";
				}
			}

			{
				TEST::pair<TEST::map<int, const char*>::iterator, TEST::map<int, const char*>::iterator> ppp = m.equal_range(3);
				if (ppp.first == m.end()) {
					std::cout << "ppp.first is iterator to first not-less than 3\n";
				} else {
					std::cout << "unexpected ppp.first\n";
				}

				if (ppp.second == m.end()) {
					std::cout << "ppp.second is iterator to first element greater-than 3\n";
				} else {
					std::cout << "unexpected ppp.second\n";
				}
			}
							
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}


	std::cout << "\e[7m=============EMPTY SET============\e[0m" << std::endl;
	{
		try
		{
			TEST::set<char> test;
			
			print_set(test);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m=============SIZED SET============\e[0m" << std::endl;
	{
		try
		{
			TEST::vector<int> vec;
			
			vec.push_back(100);
			vec.push_back(150);
			vec.push_back(175);
			vec.push_back(200);
			
			TEST::set<int> test(vec.begin(), vec.end());
			print_set(test);	
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	
	std::cout << "\e[7m=============COPIED SET============\e[0m" << std::endl;
	{
		try
		{
			TEST::set<int> myset;
			
			myset.insert(100);
			myset.insert(150);
			myset.insert(175);
			myset.insert(200);
			
			TEST::set<int> test(myset);
			print_set(test);			
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============SET: BOUNDS============\e[0m" << std::endl;
	{
		try
		{
			TEST::set<int> myset;
			
			myset.insert(100);
			myset.insert(150);
			myset.insert(175);
			myset.insert(200);

			print_set(myset);

			console("key: 50");
			console("lower_bound: ");
			std::cout << *(myset.lower_bound(50)) << std::endl;
			console("upper_bound: ");
			std::cout << *(myset.upper_bound(50)) << std::endl;

			console("key: 300");
			console("lower_bound: ");
			std::cout << (myset.lower_bound(300) == myset.end()) << std::endl;
			console("upper_bound: ");
			std::cout << (myset.upper_bound(300)== myset.end()) << std::endl;

			console("key: 120");
			console("lower_bound: ");
			std::cout << *(myset.lower_bound(120)) << std::endl;
			console("upper_bound: ");
			std::cout << *(myset.upper_bound(120)) << std::endl;

		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=======SET: INSERT / COMPARISONS=====\e[0m" << std::endl;
	{
		try
		{
			TEST::set<std::string> mp, mp2;

			mp.insert("lol");
			mp.insert("mdr");
			mp.insert("mdr");
			mp.insert("funny");
			mp.insert("bunny");
			mp.insert("fizz");
			mp.insert("buzz");
			mp.insert("fuzzy");
			mp2.insert("beauty");
			mp2.insert(mp2.end(), "Hello");
			mp2.insert(mp2.end(), "World");

			console("mp");
			print_set(mp);
			console("mp2");
			print_set(mp2);


			console("==");
			std::cout << (mp == mp2) << std::endl;
			console("<");
			std::cout << (mp < mp2) << std::endl;
			console(">");
			std::cout << (mp > mp2) << std::endl;
			console("<=");
			std::cout << (mp <= mp2) << std::endl;
			console(">=");
			std::cout << (mp >= mp2) << std::endl;
			console("!=");
			std::cout << (mp != mp2) << std::endl;
					
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "\e[7m=============SET: ERASE/CLEAR============\e[0m" << std::endl;
	{
		try
		{
			TEST::set<std::string> mp, mp2;

			mp.insert("lol");
			mp.insert("mdr");
			mp.insert("mdr");
			mp.insert("funny");
			mp.insert("bunny");
			mp.insert("fizz");
			mp.insert("buzz");
			mp.insert("fuzzy");
			mp2.insert("beauty");
			mp2.insert(mp2.end(), "Hello");
			mp2.insert(mp2.end(), "World");

			console("before erase");
			print_set(mp);

			mp.erase("bunny");
			console("after erasing bunny");
			print_set(mp);
			
			
			mp.clear();
			console("after clear");
			print_set(mp);
					
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return (0);
}