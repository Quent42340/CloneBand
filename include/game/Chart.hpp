/*
 * =====================================================================================
 *
 *       Filename:  Chart.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:25:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CHART_HPP_
#define CHART_HPP_

#include <string>
#include <vector>

#include "IntTypes.hpp"

struct ChartNote {
	ChartNote(u64 _id, u64 _position, u64 _time, u16 _type, u16 _length)
		: id(_id), position(_position), time(_time), type(_type), length(_length) {}

	u64 id = 0;
	u64 position = 0;
	u64 time = 0;
	u16 type = 0;
	u16 length = 0;
};

class Chart {
	public:
		Chart(const std::string &path);

		const ChartNote *getNextNote(u64 time);

	private:
		void parse(const std::string &path);
		bool parseSection(std::ifstream &chart);
		bool parseNotes(std::ifstream &chart);

		void skipWhitespaces(std::ifstream &chart);

		std::vector<ChartNote> m_notes;

		u64 m_time = 0;
};

#endif // CHART_HPP_