#include "SkimoFiles.hpp"

SkimoFiles::SkimoFiles(){}

SkimoFiles::~SkimoFiles(){
		bookmarks.close();
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
	//Open and close each time so that if recording is interupted the data will not be lost 
	bookmarks.open(directory + "/bookmarks.txt", std::ios::app);
	bookmarks.write((timestamp + SEPERATOR).c_str(),
			timestamp.length() + SEP_LENGTH);
	bookmarks.close();
}

void SkimoFiles::addNote(std::string note) {
	//Open and close each time so that if recording is interupted the data will not be lost
	notes.open(directory + "/annotate.txt", std::ios::app);
	notes.write((note + SEPERATOR).c_str(), note.length() + SEP_LENGTH);
	notes.close();
}
