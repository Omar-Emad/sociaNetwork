#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctype.h>
#include <vector>
#include<fstream>
#include<sstream>
#include "E:\projects_code_blocks\XML\tinyxml2.h"

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace std;
using namespace tinyxml2;

//=============================================================================================

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
      usersFile.setFileName("D:\\data_small\\users.txt");
      postsFile.setFileName("D:\\data_small\\posts.txt");
      frindsFile.setFileName("D:\\data_small\\friends.txt");
      countFile.setFileName("D:\\data_small\\counts.txt");
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
  //////////////////////////////////////////////////
  vector<string> loadallUsers()
  {
      vector <string> answer;
      for(int i=0 ; i<toInt(countFile.readLine(0)) ; i++)
      {
          string str = usersFile.readLine(i);
          stringstream ss(str);
          string temp;
          int j=0;
          while(getline(ss, temp, ','))
          {
              if(j==0) {j++; continue;}
              else
              {
                  answer.push_back(temp);
                  break;
              }
          }
      }
      return answer;
  }
  string loadAge(string currentUser)
  {
      return usersFile.readAttribute(currentUser, 3, 1);
  }
  string loadID(string currentUser)
  {
      return usersFile.readAttribute(currentUser, 0, 1);
  }
  string loadGendre(string currentUser)
  {
      return usersFile.readAttribute(currentUser, 2, 1);
  }
  string loadPostID(string currentPost)
  {
      return postsFile.readAttribute(currentPost, 0, 3);
  }
  string loadPostLikes(string currentPost)
  {
      return postsFile.readAttribute(currentPost, 2, 3);
  }
  ////////////////////////////////////////////////
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
  vector<string> getPostsVector(string Mname)
  {
      string id=usersFile.readAttribute(Mname,0,1);
      vector<string> AllPosts =postsFile.readMultipleLines(1,id);
      vector<string> answer;
      string strPosts="";
      for(int i=0;i<AllPosts.size();i++)
      {
          vector<string> temp=strPars(AllPosts[i]);
          returnSpaces(temp[3]);
          answer.push_back(temp[3]);
      }
      return answer;
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
  vector<string> loadFriendshipsVector(string Mname)
  {
      string id=usersFile.readAttribute(Mname,0,1);
      vector<string> AllFriends =frindsFile.readMultipleLines(0,id);
      vector<string> strfriends;
      for(int i=0;i<AllFriends.size();i++)
      {
          vector<string> temp=strPars(AllFriends[i]);
          strfriends.push_back(usersFile.readAttribute(temp[1],1,0));
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

XMLError generateXML()
{
    vector <string> theUsers;
    theUsers = SNDB.loadallUsers();

    //---------- Creating the Document --------------
    XMLDocument xmlDoc;
    XMLNode *pRoot = xmlDoc.NewElement("SocialNetwork");
    xmlDoc.InsertFirstChild(pRoot);
    //-----------------------------------------------

    //---------- Adding data to the Document --------
    for(int item=0 ; item<toInt(SNDB.loadCount(0)) ; item++)
    {
        XMLElement * pElement = xmlDoc.NewElement("user");
        //*************************************
        string currentUser = theUsers[item];
        //*************************************
        string ID = SNDB.loadID(currentUser);
        XMLElement * pListElement1 = xmlDoc.NewElement("ID");
        pListElement1->SetText(ID.c_str());
        pElement->InsertEndChild(pListElement1);
        //*************************************
        XMLElement * pListElement2 = xmlDoc.NewElement("Name");
        pListElement2->SetText(currentUser.c_str());
        pElement->InsertEndChild(pListElement2);
        //*************************************
        string gender = SNDB.loadGendre(currentUser);
        XMLElement * pListElement3 = xmlDoc.NewElement("Gender");
        pListElement3->SetText(gender.c_str());
        pElement->InsertEndChild(pListElement3);
        //*************************************
        string age = SNDB.loadAge(currentUser);
        XMLElement * pListElement4 = xmlDoc.NewElement("Age");
        pListElement4->SetText(age.c_str());
        pElement->InsertEndChild(pListElement4);
        //*************************************
        vector<string> posts = SNDB.getPostsVector(currentUser);
        XMLElement * pListElement5 = xmlDoc.NewElement("Posts");
        for(int k=0 ; k<posts.size() ; k++)
        {
            //******************************************************
            XMLElement * pListElement_ID = xmlDoc.NewElement("ID");
            string idPost = SNDB.loadPostID(posts[k]);
            pListElement_ID->SetText(idPost.c_str());
            pListElement5->InsertEndChild(pListElement_ID);
            //******************************************************
            XMLElement * pListElement_text = xmlDoc.NewElement("Text");
            //string idPost = SNDB.loadPostID(posts[k]);
            pListElement_text->SetText(posts[k].c_str());
            pListElement5->InsertEndChild(pListElement_text);
            //******************************************************
            XMLElement * pListElement_likes = xmlDoc.NewElement("Likes");
            string likesPost = SNDB.loadPostLikes(posts[k]);
            pListElement_likes->SetText(likesPost.c_str());
            pListElement5->InsertEndChild(pListElement_likes);
            //******************************************************
        }
        pElement->InsertEndChild(pListElement5);
        //*************************************
        vector<string> friends = SNDB.loadFriendshipsVector(currentUser);
        XMLElement * pListElement6 = xmlDoc.NewElement("Friends");
        for(int k=0 ; k<posts.size() ; k++)
        {
            //******************************************************
            //XMLElement * pListElement_ID = xmlDoc.NewElement("ID");
            //string idPost = SNDB.loadPostID(posts[k]);
            //pListElement_ID->SetText(idPost.c_str());
            //pListElement5->InsertEndChild(pListElement_ID);
            //******************************************************
            XMLElement * pListElement_friend = xmlDoc.NewElement("friend");
            pListElement_friend->SetText(friends[k].c_str());
            pListElement6->InsertEndChild(pListElement_friend);
            //******************************************************
            //XMLElement * pListElement_likes = xmlDoc.NewElement("Likes");
            //string likesPost = SNDB.loadPostLikes(posts[k]);
            //pListElement_likes->SetText(likesPost.c_str());
            //pListElement5->InsertEndChild(pListElement_likes);
            //******************************************************
        }
        pElement->InsertEndChild(pListElement6);
        //*************************************
        pRoot->InsertEndChild(pElement);
    }
    //-----------------------------------------------

    //---------- Saving the Document ----------------
    XMLError eResult = xmlDoc.SaveFile("SavedData.xml");
    XMLCheckResult(eResult);
    //-----------------------------------------------
}

//=============================================================================================
