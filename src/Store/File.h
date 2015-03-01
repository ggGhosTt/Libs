#ifndef FILE_H
#define FILE_H

#include <string>
#include <list>

namespace flame_ide
{

class File
{
	bool eof;

	std::string filename;
	
	std::string content_string;
//	std::list< std::string > content_list;
	
	void initialization();
	
	void load();
	void loadAll();
	void loadWorlds();
	
public:
	
	struct Settings
	{
		bool loadAll;
		bool loadWords;
		
		bool loadToList;
		bool LoadToString;
		
	} settings;

	File();
	File(std::string&, bool toLoad);
	
	~File();

	void setToLoad(Settings&);
	
	void setPartition(unsigned int partition_bytes);

	static unsigned int getSizeFile(std::string& file);
	static unsigned int getSizeFile(char* file);

	std::string getLoaded();
//	bool endOfFile();
};

}


#endif // FILE_H
