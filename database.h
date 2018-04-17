#include <iostream>
#include<string>
#include<fstream>
#include <vector>
#include <sstream>

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
    string readLine(int col , string attribute) //0 for ID ... 1 for userName
    {
        ifile.open (fileName,std::ofstream::out | std::ofstream::app);
        string line;
        while(ifile >> line)
        {
            vector <string> fields_line;
            stringstream ss(line);
            string temp;
            while(getline(ss, temp, ','))
            {
                fields_line.push_back(temp);
            }   // this vector have every data in every column in the line
            if(attribute == fields_line[col])
            {
                ifile.close();
                return line;
            }
        }
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
