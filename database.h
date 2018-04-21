#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>


using namespace std;
vector  <string> strPars(string str)
{
    vector<string> fields_line;
    string temp;
    stringstream ss(str);
    while(getline(ss, temp, ','))
    {
        fields_line.push_back(temp);
    }   // this vector have every data in every column in the line
    return fields_line;
}
void replaceSpaces(string & str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]==' ')
            str[i]='~';
    }
}
void returnSpaces(string & str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]=='~')
            str[i]=' ';
    }
}
string toString(int num)
{
    stringstream buffer;
    buffer<<num;
    string chStr;
    buffer >> chStr;
    return chStr;
}

int toInt(string s)
{
    int x;
    stringstream ss(s);
    ss >> x;
    return x;
}
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
    void writeLine(string line, int del=0)
    {
        if(del==1)
            remove(fileName);
        ofile.open (fileName, std::ofstream::out | std::ofstream::app);
        ofile << line <<"\n";
        ofile.close();
    }
    string readLine(int col , string attribute) //0 for ID ... 1 for userName
    {
        ifile.open (fileName);
        string line;
        while(ifile >> line)
        {
            if(col== -1 && line==attribute)
                {
                    ifile.close();
                    return line;
                }
            if(col == -1)
                continue;
            vector <string> line_Vstr;
            stringstream ss(line);
            line_Vstr=strPars(line);
            if(attribute == line_Vstr[col])
            {
                ifile.close();
                return line;
            }
        }
        ifile.close();
        return "-1";
    }

    string readLine(int lineNumbre )
    {
        ifile.open (fileName,std::ofstream::out | std::ofstream::app);
        string line;
        int i=0;
        while((ifile >> line))
        {
            if(i++ != lineNumbre) continue;
            ifile.close();
            return line;
        }
        ifile.close();
        return "-1";
    }
    bool lineISExist(string line)
    {
        if(readLine(-1,line) =="-1")
            return false;
        else
            return true;
    }

    string readAttribute(string attribute, int rcol , int col)
    {  //This FN to load an attribute like ID or Name
        string line= readLine(col , attribute);
        vector<string> line_Vstr=strPars(line);
        return line_Vstr[rcol];

    }
    vector <string> readMultipleLines(int col, string attribute)
    {
        vector <string> ans;
        ifile.open (fileName);
        string line;
        while(ifile >> line)
        {
            if(col== -1 && line==attribute)
                {
                    ans.push_back(line);
                }
            if(col == -1)
                continue;
            vector <string> line_Vstr;
            stringstream ss(line);
            line_Vstr=strPars(line);
            if(attribute == line_Vstr[col])
            {
                ans.push_back(line);
            }
        }
        ifile.close();
        return ans;
    }

    void replaceLine(string oldLine, string newLine)
{
     ifile.open(fileName); //File to read from
    ofstream temp("temp.txt"); //Temporary file

    string strTemp;
    while(ifile >> strTemp)
    {
        if(strTemp == oldLine)
            strTemp = newLine;
        temp << strTemp<<"\n";
    }
	temp.close();
	ifile.close();
	remove(fileName);
	rename("temp.txt",fileName);
}

void replaceLine(int col,string attribute, string newLine)
{
    ifile.open(fileName); //File to read from
    ofstream temp("temp.txt"); //Temporary file

    string strTemp;

    while(ifile >> strTemp)
    {
		stringstream ss(strTemp);
		string paramter;
		int i=0;
		while(getline(ss,paramter,','))
		{
			if(paramter == attribute && col==i)
			{
				strTemp = newLine;
				break;
			}
			else i++;
		}

        temp << strTemp<<"\n";
    }
	temp.close();
	ifile.close();
	remove(fileName);
	rename("temp.txt",fileName);

}


};

class dataBase{   // medium level
                  // here we will choose which file to write or read

file usersFile;
file postsFile;
file frindsFile;
file countFile;
public:
  dataBase()
  {
      usersFile.setFileName("data/users.txt");
      postsFile.setFileName("data/posts.txt");
      frindsFile.setFileName("data/friends.txt");
      countFile.setFileName("data/counts.txt");
  }
  bool userIsExisted(int col,string attribute)
  {
      if(usersFile.readLine(col,attribute) == "-1")
        return false;
      else
        return true;
  }
  bool userIsExisted(string name)
  {
      if(usersFile.readLine(1,name) == "-1")
        return false;
      else
        return true;
  }
  void saveCount(string userID, string postID)
  {
      countFile.writeLine(userID,1);
      countFile.writeLine(postID);
  }

   string loadCount(int request)// "user" for userID .. "post" for postID
  {

      return countFile.readLine(request);

  }

  void saveUser(string userText) //return ID
  {
        string line =loadCount(0)+','+userText;
        usersFile.writeLine(line);
        saveCount(toString(toInt(loadCount(0))+1)  , loadCount(1) );
  }
  string loadUser(string user_name)
  {
        return usersFile.readLine(1,user_name);
  }
  string loadUser(int col)  //overloaded
  {

  }
  void savePost(string text)
  {
      text =loadCount(1)+','+text;
      postsFile.writeLine(text);
      saveCount(loadCount(0), toString(toInt(loadCount(1))+1) );
  }
  string loadPost(string postID)
  {
     return postsFile.readLine(1,postID);
  }
    void like(string postId)
  {
	  string oldPost = postsFile.readLine(1,postId);
	  stringstream ss(oldPost) ;   string newPost;     string s;
	  getline(ss,s,',');
	  newPost=s+",";
	  getline(ss,s,',');
	  newPost+=s+",";
	  getline(ss,s,',');
	  newPost+=toString(toInt(s)+1);
	  getline(ss,s,',');
	  newPost+=","+s;
	  postsFile.replaceLine(0,postId,newPost);
  }
  string getPosts(string Mname)
  {
      string id=usersFile.readAttribute(Mname,0,1);
      vector<string> AllPosts =postsFile.readMultipleLines(1,id);
      string strPosts="";
      for(int i=0;i<AllPosts.size();i++)
      {
          vector<string> temp=strPars(AllPosts[i]);
          returnSpaces(temp[3]);
          strPosts+=temp[3]+"\n\n";
      }
      return strPosts;
  }
  string loadFriendships(string Mname)
  {
      string id=usersFile.readAttribute(Mname,0,1);
      vector<string> AllFriends =frindsFile.readMultipleLines(0,id);
      string strfriends="";
      for(int i=0;i<AllFriends.size();i++)
      {
          vector<string> temp=strPars(AllFriends[i]);
          strfriends+=usersFile.readAttribute(temp[1],1,0)+"\n";
      }
      return strfriends;
  }
  void saveFriendship(string id,string fname)
  {
         string friendID=usersFile.readAttribute(fname,0,1);
         frindsFile.writeLine(id+','+friendID);
         frindsFile.writeLine(friendID+','+id);
  }
  bool friendIsExist(string id, string fname)
  {
        string friendID=usersFile.readAttribute(fname,0,1);
        if(frindsFile.lineISExist(id+','+friendID))
            return true;
        else
            return false;

  }
};
dataBase SNDB;

class user{
int id;
string name;
char gender;
int age;
public:
    int ID()
    {
        return id;
    }
    string NAME()
    {
        return name;
    }
    user createUser(string name,char gender,int age)
    {
        this->name=name;
        this->gender=gender;
        this->age=age;
        string userStr = name+','+gender+','+toString(age);
        SNDB.saveUser(userStr);
        return *this;
    }
    void login(string name)
    {
       string logedUser= SNDB.loadUser(name);
       vector<string> user_Vstr=strPars(logedUser);
       this->id=toInt(user_Vstr[0]);
       this->name=user_Vstr[1];
       this->gender=user_Vstr[2][0];
       this->age=toInt(user_Vstr[3]);
    }
    bool addFriend(string fname)
    {
        if(SNDB.userIsExisted(fname)&&
           !SNDB.friendIsExist(toString(this->id) , fname) &&
           this->name!=fname)
        {
                SNDB.saveFriendship(toString(this->id),fname);
                return true;
        }
        else
            return false;
    }

    void createPost(string text)
    {
        replaceSpaces(text);
        string line= toString(this->id)+','+"0,"+text;
        SNDB.savePost(line);
    }
    void likePost(string postID)
    {
        SNDB.like(postID);
    }

    string getPosts(string Mname)
    {

    }
    string viewMyFriends()
    {
       return SNDB.loadFriendships(this->name);
    }
};

class post{
int id;
int userID;
string postTest;
int noLikes;
public:
};
