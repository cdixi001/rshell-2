#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <algorithm>
#include <pwd.h>
#include <grp.h>
#include <time.h>
using namespace std;


void organize(deque <string> &files)
{
	sort(files.begin(), files.end(), locale("en_US.UTF-8"));
}

void printlFlag(struct stat name)
{
	if(name.st_mode & S_IFDIR)
		cout << 'd';
	else if(!(name.st_mode & S_IFLNK)) //! because prints otherwise 
		cout << 'l';
	else
		cout << '-';
	

	cout << ((name.st_mode & S_IRUSR)? "r" : "-" );
	cout << ((name.st_mode & S_IWUSR)? "w" : "-" );
	cout << ((name.st_mode & S_IXUSR)? "x" : "-" );
	cout << ((name.st_mode & S_IRGRP)? "r" : "-" );
	cout << ((name.st_mode & S_IWGRP)? "w" : "-" );
	cout << ((name.st_mode & S_IXGRP)? "x" : "-" );
	cout << ((name.st_mode & S_IROTH)? "r" : "-" );
	cout << ((name.st_mode & S_IWOTH)? "w" : "-" );
	cout << ((name.st_mode & S_IXOTH)? "x" : "-" );
	cout << " " << name.st_nlink << " ";

	struct passwd* p;
	if((p = getpwuid(name.st_uid)) == NULL)
	{
		perror("getpwuid error");
		exit(1);
	}
	else
		cout << p->pw_name << " ";
	

	struct group* g;
	if((g = getgrgid(name.st_gid)) == NULL)
	{
		perror("getgrgid error");
		exit(1);
	}
	else
		cout << g->gr_name << " ";

	
	cout << name.st_size << " ";

	string time = ctime(&name.st_mtime);
	if(time.at(time.size() - 1) == '\n')
		time.at(time.size() - 1) = '\0';
	cout << time << " ";
}


void printme(string argument, struct stat name)
{
	if(argument.at(0) == '.') //argument is a hidden file
	{
		if(name.st_mode & S_IFDIR) //argument is a directory
		{
		}
		else if(name.st_mode & S_IXUSR) //argument is a usr file
		{
		}
		else //argument is a regular file
		{
		}
	}
	else if(name.st_mode & S_IFDIR) //argument is a directory
	{
	}
	else if(name.st_mode & S_IXUSR) //argument is a usr file
	{
	}
	else //argument is a regular file
		cout << argument; 
}


int main(int argc, char* argv[])
{

	//cout << "argc = " << argc << endl;	
	
	bool aFlag = false;
	bool lFlag = false;
	bool RFlag = false;
	bool filesonly = false;

	deque <string> arguments;
	//put all passed in arguments into a vector
	for(int i = 0; i < (argc - 1); i++)
	{
		arguments.push_back(argv[i + 1]);
	}
	//for(unsigned int i = 0; i < arguments.size(); i++)
	//{
	//	cout << arguments.at(i) << endl;
	//}


	//check for directory argument
	deque <string> directories;
	deque <string> flags;
	for(unsigned int i = 0; i < arguments.size(); i++)
	{
		if(arguments.at(i).at(0) == '-') //if argument starts with a -, then it is a flag
			flags.push_back(arguments.at(i));
		else
			directories.push_back(arguments.at(i));
	}
	//cout << "flags: " << endl;
	//for(unsigned int i = 0; i < flags.size(); i++)
	//{
	//	cout << flags.at(i) << endl;
	//}
	//cout << " directories: "<< endl;
	//for(unsigned int i = 0; i < directories.size(); i++)
	//{
	//	cout << directories.at(i);
	//}

	
	//flag checking
	for(unsigned int i = 0; i < flags.size(); i++)
	{
		for(unsigned int j = 0; j < flags.at(i).size(); j++) //loop through each letter of the flag
		{
			//cout << i << " " << j << " ";
			//cout << flags.at(i).at(j) << endl;
			if(flags.at(i).at(j) == '-') //do nothing
				{}	
			else if(flags.at(i).at(j) == 'a')
				aFlag = true;
			else if(flags.at(i).at(j) == 'l')
				lFlag = true;
			else if(flags.at(i).at(j) == 'R')
				RFlag = true;
			else
			{
				perror("invalid flag");
				exit(1);
			}
		}
	}
	
	if(aFlag || lFlag || RFlag)
		cout << "yay" << endl;

	
	struct stat name;
	
	if(directories.size() == 0) //case where no arguments are passed in
		directories.push_back("."); //add current directory as default


	//handle case if file names are passed in
	deque <string> files;
	if(directories.size() > 0)
	{
		for(unsigned int i = 0; i < directories.size(); i++)
		{
			//DIR *directory;
			
			//Check if argument is a file
			if(stat(directories.at(i).c_str(), &name) == -1)
			{
				perror("stat error");
				directories.erase(directories.begin() + i);
				i--;
			}
			else
			{
				if(!(name.st_mode & S_IFDIR))
				{
					files.push_back(directories.at(i));
					directories.erase(directories.begin() + i);
					i--;
				}
			}
		}
	}
	if(directories.size() == 0)
	{
		filesonly = true;
	}

	//for(unsigned int i = 0; i < directories.size(); i++)
	//	cout << "Listed as dir: " << directories.at(i) << endl;


	//cout << filesonly << endl;
	//for(unsigned int i = 0; i < files.size(); i++)
	//{
	//	cout << "Tracked files: " << files.at(i) << endl;
	//}

	organize(files); //sort files alphabetically

	//for(unsigned int i = 0; i < files.size(); i++)
	//{
	//	cout << "Sorted files: " << files.at(i) << endl;
	//}


	if(filesonly)
	{
		if(!lFlag) //print without -l descriptors
		{
			for(unsigned int i = 0; i < files.size(); i++)
				cout << files.at(i) << "  ";
			cout << endl;
			return 0; //end program
		}
		else //only l flag has effect when only file names a inputted
		{
			for(unsigned int i = 0; i < files.size(); i++)
			{
				if(stat(files.at(i).c_str(), &name) == -1)
					perror("stat error");
				
				printlFlag(name);
				cout << files.at(i) << endl;
			}
			return 0; //end program
		}
	}



	else //case with directories as args
	{
		for(unsigned int i = 0; i < files.size(); i++)
			cout << files.at(i) << "  "; //print out file arguments first

		if(files.size() > 0)
			cout << endl;
		files.clear();

		organize(directories);
		for(unsigned int i = 0; i < directories.size(); i++)
		{
		
			DIR* dp;
			if((dp = opendir(directories.at(i).c_str()))==0)
			{
				perror("cannot open dir");
				exit(1);
			}
			dirent* direntp;
			while((direntp = readdir(dp)) != 0) //extract files from directory
			{
				files.push_back(direntp->d_name);
			}
			organize(files); //sort extracted files
			
			
			if(lFlag)
			{
				int total = 0;
				for(unsigned int h = 0; h < files.size(); h++) //get total block size
				{
					string path = directories.at(i);
					path += "/";
					path += files.at(h);
					if(-1 == (stat(path.c_str(), &name)))
					{
						perror("stat error 1");
						exit(1);
					}
					else
						total += name.st_blocks;
				}
				cout << "total " << total/3 << endl; //output total block size
			}

			if(directories.size() > 1) //output directory currently working on
				cout << directories.at(i) << ":" << endl;
			
			
			if(!aFlag) //remove hidden files
			{
				for(unsigned int k = 0; k < files.size(); k++)
				{
					if(files.at(k).at(0) == '.')
					{
						files.erase(files.begin() + k); //erase hidden files
						k--;
					}
				}
			}


			for(unsigned int j = 0; j < files.size(); j++)
			{
				if(lFlag)
				{
					string path = directories.at(i) + "/" + files.at(j);
					if(stat(path.c_str(), &name) == -1)
						perror("stat error 2");
					
					printlFlag(name);
				}
				cout << files.at(j) << "  ";
				if(lFlag) 
					cout << endl;
			}
			cout << endl << endl;
			files.clear();
		}
	}
	return 0;
}
