/*
 * =====================================================================================
 *
 *       Filename:  ChartParser.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2018 15:56:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <fstream>

#include "Exception.hpp"
#include "Chart.hpp"

void ChartParser::parse(const std::string &path, std::vector<ChartNote> &notes) {
	std::ifstream chart(path);
	if (!chart.is_open())
		throw EXCEPTION("Error failed to open:", path);

	while (parseSection(chart, notes));

	chart.close();
}

bool ChartParser::parseSection(std::ifstream &chart, std::vector<ChartNote> &notes) {
	if (chart.get() != '[')
		return false;

	std::string sectionName;
	std::getline(chart, sectionName, ']');

	DEBUG("Section name:", sectionName);

	skipWhitespaces(chart);

	if (sectionName == "Song") {
		if (char c = chart.get() ; c != '{')
			throw EXCEPTION("Syntax error at char '", (int)c, "'", chart.tellg());

		skipWhitespaces(chart);

		try {
			while (parseSongInfo(chart))
				skipWhitespaces(chart);
		}
		catch(...) {
			throw EXCEPTION("Syntax error at char '", (int)chart.peek(), "'", chart.tellg());
		}
	}
	else if (sectionName == "SyncTrack") {
		if (char c = chart.get() ; c != '{')
			throw EXCEPTION("Syntax error at char '", (int)c, "'", chart.tellg());

		skipWhitespaces(chart);

		try {
			while (parseSyncTrack(chart))
				skipWhitespaces(chart);
		}
		catch(...) {
			throw EXCEPTION("Syntax error at char '", (int)chart.peek(), "'", chart.tellg());
		}
	}
	else if (sectionName == "MediumSingle") {
		if (char c = chart.get() ; c != '{')
			throw EXCEPTION("Syntax error at char '", (int)c, "'", chart.tellg());

		skipWhitespaces(chart);

		try {
			while (parseNotes(chart, notes))
				skipWhitespaces(chart);
		}
		catch(...) {
			throw EXCEPTION("Syntax error at char '", (int)chart.peek(), "'", chart.tellg());
		}
	}
	else {
		std::string sectionLine;
		while (std::getline(chart, sectionLine, '\n') && sectionLine[0] != '}')
			skipWhitespaces(chart);
	}

	skipWhitespaces(chart);

	return true;
}

bool ChartParser::parseSongInfo(std::ifstream &chart) {
	if (chart.peek() == '}') {
		chart.get();
		return false;
	}

	std::string key, value;
	std::getline(chart, key, '=');
	std::getline(chart, value, '\n');
	skipWhitespaces(chart);

	// DEBUG(key, value);

	if (key == "Offset ") {
		m_songOffset = std::stof(value) * 1000;
		DEBUG("Song offset:", m_songOffset);
	}
	else if (key == "Resolution ") {
		m_songResolution = std::stoi(value);
		DEBUG("Song resolution:", m_songResolution);
	}

	return true;
}

bool ChartParser::parseSyncTrack(std::ifstream &chart) {
	if (chart.peek() == '}') {
		chart.get();
		return false;
	}

	std::string key;
	std::getline(chart, key, '=');
	u64 position = std::stoull(key);

	skipWhitespaces(chart);
	char eventType = chart.get();
	if (eventType != 'B') {
		while (chart.get() != '\n');
		return true;
	}

	std::string value;
	std::getline(chart, value, '\n');
	m_songBpm.emplace(position, std::stoi(value));

	// DEBUG(position, std::stoi(value));

	return true;
}

bool ChartParser::parseNotes(std::ifstream &chart, std::vector<ChartNote> &notes) {
	if (chart.peek() == '}') {
		chart.get();
		return false;
	}

	std::string key;
	std::getline(chart, key, '=');
	u64 notePosition = std::stoull(key);

	skipWhitespaces(chart);
	char eventType = chart.get();
	if (eventType != 'N') {
		while (chart.get() != '\n');
		return true;
	}

	skipWhitespaces(chart);
	int noteType = chart.get() - '0';
	skipWhitespaces(chart);

	std::string length;
	std::getline(chart, length, '\n');
	int noteLength = std::stoi(length);

	// float currentBpm = 127500 / 1000.0f;
	float currentBpm = getCurrentBpm(notePosition);
	if (!notes.empty()) {
		m_time += 1000 * ((notePosition - notes.back().position) * 60 / (currentBpm * m_songResolution));
	}
	int noteTime = m_time + m_songOffset;

	if (notePosition < 1000)
		DEBUG("New note:", notePosition, noteTime, eventType, noteType, noteLength, currentBpm);

	notes.emplace_back(notes.size(), notePosition, noteTime, noteType, noteLength);

	return true;
}

float ChartParser::getCurrentBpm(u64 position) {
	u32 currentBpm = 0;
	for (auto &it : m_songBpm) {
		if (it.first > position)
			return currentBpm / 1000.0f;

		currentBpm = it.second;
	}

	return 0;
}

void ChartParser::skipWhitespaces(std::ifstream &chart) {
	while (chart.peek() == ' ' || chart.peek() == '\n' || chart.peek() == '\t' || chart.peek() == '\r')
		chart.get();
}
