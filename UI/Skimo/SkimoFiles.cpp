#include "SkimoFiles.hpp"

SkimoFiles::SkimoFiles(){}

SkimoFiles::~SkimoFiles(){
}
	
void SkimoFiles::openDoc(std::string dir)
{
	directory = dir;
	std::string data = "{\"annotations\":[\n";

	notes.open(directory + "/annotations.json", std::ios::app);
	notes.write(data.c_str(), data.length());
	notes.close();
}
	
	
void SkimoFiles::closeDoc()
{
	notes.open(directory + "/annotations.json", std::ios::app);
	std::string data = "]}";
	notes.write(data.c_str(), data.length());
	notes.close();

	directory = "";
}

void SkimoFiles::addBookmark(std::string timestamp)
{
	//Open and close each time so that if recording is interupted the data will not be lost
	notes.open(directory + "/annotations.json", std::ios::app);
	std::string data = "{ \"type\":\"bookmark\",\"timecode\":" +
			   timestamp + " },\n";
	notes.write(data.c_str(), data.length());
	notes.close();
}

void SkimoFiles::addNote(std::string timestamp, std::string note)
{
	//Open and close each time so that if recording is interupted the data will not be lost
	notes.open(directory + "/annotations.json", std::ios::app);

	//{ "type":"bookmark", "timecode":210 },
	std::string data = "{ \"type\":\"annotation\",\"timecode\":"+ timestamp + ",\"note\":\"" + note +"\"},\n";
	notes.write(data.c_str(), data.length());
	notes.close();
}
