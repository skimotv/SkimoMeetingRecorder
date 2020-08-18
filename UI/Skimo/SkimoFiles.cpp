#include "SkimoFiles.hpp"

SkimoFiles::SkimoFiles(){}

SkimoFiles::~SkimoFiles(){
}
	
void SkimoFiles::openDoc(std::string dir)
{
	directory = dir;
}
void SkimoFiles::closeDoc()
{
	directory = "";
}

void SkimoFiles::addBookmark(std::string timestamp)
{
	addNote(timestamp, BOOKMARK);
}

void SkimoFiles::addNote(std::string timestamp, std::string note)
{
	//Open and close each time so that if recording is interupted the data will not be lost
	notes.open(directory + "/Skimo.txt", std::ios::app);

	std::string data = "[" + timestamp + "] " + note + SEPERATOR;
	notes.write(data.c_str(), data.length());
	notes.close();
}
