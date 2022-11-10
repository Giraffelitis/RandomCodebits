#pragma once

#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>

class Utility
{
public:
	static std::set<int> WrtieHighScore(int score)
	{
		// Check if files exists
		std::string fileName = "highscores.txt";
		std::ifstream highscoreFile(fileName);
		std::istream_iterator<int> start(highscoreFile), end;
		std::set<int> highscores(start, end);
		highscoreFile.close();

		// If it doesnt exist populate and save
		if (highscores.size() == 0)
		{
			highscores.insert(100);
			highscores.insert(75);
			highscores.insert(50);
			highscores.insert(25);
			highscores.insert(10);

			std::ofstream outfile(fileName);
			std::ostream_iterator<int> output_iterator(outfile, "\n");
			std::copy(highscores.begin(), highscores.end(), output_iterator);
			outfile.close();
		}

		//write the score
		highscores.insert(score);

		//remove lowest
		highscores.erase(highscores.begin());

		// write the highscores
		std::ofstream outfile(fileName);
		std::ostream_iterator<int> output_iterator(outfile, "\n");
		std::copy(highscores.begin(), highscores.end(), output_iterator);
		outfile.close();

		return highscores;
	}

};