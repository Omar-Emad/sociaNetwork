#include <iostream>
#include<string>
#include<fstream>

using namespace std;

class file{      //This is the low level of file
                 // just read or write a write a single line
ofstream ofile;
ifstream ifile;
char * fileName;

public:
    file( char* file_Name)
    {
        this->fileName=file_Name;
    }
    file(){}
    void setFileName(char * file_Name)
    {
        this->fileName=file_Name;
    }
    void writeLine(string line)
    {
        ofile.open (fileName,std::ofstream::out | std::ofstream::app);
        ofile << line <<"\n";
        ofile.close();
    }
    string readLine(int col , string attribute)
    {

    }
};

class dataBase{   // medium level
                  // here we will choose which file to write or read

file usersFile;
file postsFile;
file frindsFile;
public:
  dataBase()
  {
      usersFile.setFileName("data/users.txt");
      postsFile.setFileName("data/posts.txt");
      frindsFile.setFileName("data/friends.txt");
  }

  void saveUser()
  {

  }
  string loadUser(string user_name)
  {

  }
  string loadUser(int col)  //overloaded
  {

  }
  void savePost()
  {

  }
  string loadPost()
  {

  }

  void saveFrindship()
  {

  }



};
dataBase SNDB;

class user{
int id;
string name;
char gender;
int age;
public:
};


class post{
int id;
int userID;
string postTest;
int noLikes;
public:

};
