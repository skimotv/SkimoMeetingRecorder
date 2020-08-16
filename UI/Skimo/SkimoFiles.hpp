#pragma once

#include <string>
#include <iostream>
#include <fstream>

//Whole thing is set up weirdly, definitly should be improved later
class SkimoFiles {
	public:
		SkimoFiles();
		~SkimoFiles();

		void openDoc(std::string dir);
		void addBookmark(std::string timestamp);
		void addNote(std::string note);
		void closeDoc();
	private:
		//File output streams
		std::ofstream bookmarks;
		std::ofstream notes;

		//Information
		std::string directory;
		const int SEP_LENGTH = 1;
		const std::string  SEPERATOR = "\n";
};
