#pragma once
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>


using namespace std;
using ariel::Direction;



namespace ariel {
	class Notebook
	{
	private:
		// int _lineNumber;
		// int _pageNumber;
		vector <vector<string> > _nbooke;

	public:
		void write(unsigned int page, unsigned int row, unsigned int column, Direction d, const string & str);
		string read(unsigned int page, unsigned int row, unsigned int column, Direction d, unsigned int chars);
		void erase(unsigned int page, unsigned int row, unsigned int column, Direction d, unsigned int chars);
		string show(unsigned int page);

		// int getYear() { return m_year; }
		// int getMonth() { return m_month; }
		// int getDay()  { return m_day; }
	};
};
