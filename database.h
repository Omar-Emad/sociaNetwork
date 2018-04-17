#include <iostream>
#include<string>
#include<fstream>
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
    string readLine(int col , string attribute)
    {

    }
	void replaceLine(int id, string newLine)
	{

	}
};

class dataBase{   // medium level
                  // here we will choose which file to write or read

file usersFile;
file postsFile;
file frindsFile;
int NoPosts;
public:
  dataBase()
  {
      usersFile.setFileName("data/users.txt");
      postsFile.setFileName("data/posts.txt");
      frindsFile.setFileName("data/friends.txt");
	  NoPosts=0;
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
  void savePost( string text, int postID=0 )  //postID = 0 means a new post
  {                                           // postID = number means edit this post   
	  if(postID==0)  
	  {
		  postsFile.writeLine(to_string(++NoPosts)+','+text);
	  }
	  else
	  {
		  postsFile.replaceLine(postID,to_string(postID)+','+text;
	  }
  }
  void editPost()
  {
  }
  string loadPost(int postID)
  {
	  return postsFile.readLine(1,to_string(postID));
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
	void creatPost (string text)
	{
		SNDB.savePost(to_string(id)+','+'0'+','+text);
	}

};


class post{
int id;
int userID;
string postText;
int noLikes;
public:
	 post(string text)     //text =   5,10,2,good morning         postID,OwnerID,NO.Likes,postText 
	 {
		 stringstream ss(text);
		 string x;
		 getline(ss,x,',');
		 id=stoi(x);
		 getline(ss,x,',');
		 userID=stoi(x);
		 getline(ss,x,',');
		 noLikes=stoi(x);
		 getline(ss,x,',');
		 postText=x;
	 }

	 void operator ++()  //increase likes
	 {
		 noLikes++;
		 SNDB.savePost(to_string(userID)+','+to_string(noLikes)+','+postText,id);
	 }

};
