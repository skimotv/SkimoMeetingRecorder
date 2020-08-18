#pragma once

#include <string>
#include <iostream>
#include <fstream>

class SkimoFiles {
	public:
		SkimoFiles();
		~SkimoFiles();

		void openDoc(std::string dir);
		void addBookmark(std::string timestamp);
		void addNote(std::string timestamp,std::string note);
		void closeDoc();
	private:
		//File output streams
		std::ofstream notes;

		//Information
		std::string directory;
		const int SEP_LENGTH = 1;
		const std::string  SEPERATOR = "\n";
		const std::string BOOKMARK = "Bookmark";
};
