#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <ctype.h>
#include "database.h"
using namespace std;

user Current_user;

void delay(int seconds){
clock_t begin_time = clock();
   while(((clock()-begin_time)/CLOCKS_PER_SEC)< seconds);
}

bool is_number(int number)
{
    stringstream ss;
    ss<<number ;
    string s;
    ss>>s ;
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void Welcome(string name){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 10);
cout<<"Welcome, "<<name<<'!'<<endl<<endl;
cout<<"What do you want to do today? (please type a number corresponding to one of the following options:)"<<endl;
cout<<endl;
SetConsoleTextAttribute(hConsole, 5);
cout<<endl<<endl;
cout <<"1) Add a new friend." << endl << endl;
cout <<"2) Write a new post." << endl << endl;
cout <<"3) View your friends." << endl << endl;
cout <<"4) View someone's posts." << endl << endl;
cout <<"5) View someone's friends." << endl << endl;
cout <<"6) Logout of your account." << endl << endl;
char dummy;
dummy=getch();
system("CLS");
SetConsoleTextAttribute(hConsole, 10);
if(dummy=='1'){
        string friendy;
    cout<<"Enter the name you want to add as a friend"<<endl<<endl ;
    SetConsoleTextAttribute(hConsole, 5);
    cout<<"Name: ";
    SetConsoleTextAttribute(hConsole, 12);
    cin>>friendy ;
    SetConsoleTextAttribute(hConsole, 10);
    Current_user.addFriend(friendy);
    system("CLS");
    cout<<" Friend added!";
    delay(3);
    system("CLS");
    Welcome(name);

}
if(dummy=='2'){
        string post ;
    cout<<"What do you want to write about?"<<endl<<endl ;
    cout<<": " ;
    cin.ignore();
    SetConsoleTextAttribute(hConsole, 12);
    getline(cin,post);
    SetConsoleTextAttribute(hConsole, 10);
    system("CLS");
    Current_user.createPost(post);
    cout<<" You have just made a new post!" ;
    delay(3);
    system("CLS");
    Welcome(name);



}
if(dummy=='3'){
    cout<<endl<<" Your Friends List"<<endl ;
    cout<<Current_user.viewMyFriends();
    cout<<endl<<endl<<"Press Any Key to Back"<<endl;
    getch();
    system("CLS");
    Welcome(name);

}
if(dummy=='4'){
    cout<<endl<<" User Name :" ;
    string Uname;
    cin>>Uname;
    system("cls");
    cout<<Uname<<" Posts"<<endl<<endl;
    cout<<SNDB.getPosts(Uname);
    cout<<endl<<endl<<"Press Any Key to Back"<<endl;
    getch();
    system("CLS");
    Welcome(name);

}
if(dummy=='5'){
    cout<<endl<<" User Name :" ;
    string Uname;
    cin>>Uname;
    system("cls");
    cout<<Uname<<" friendss :"<<endl<<endl;
    cout<<SNDB.loadFriendships(Uname);
    cout<<endl<<endl<<"Press Any Key to Back"<<endl;
    getch();
    system("CLS");
    Welcome(name);
}
if(dummy=='6'){

}
else{Welcome(name);}
}



void New_account(){
    string username;
    string password;
    string gender;
    int age;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 5);
cout<<endl;
cout<<"Please enter your username: ";
SetConsoleTextAttribute(hConsole, 12);
cin>>username;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
if(SNDB.userIsExisted(username)){
    cout<<"This username is already in use!"<<endl<<endl ;
    New_account();
}
cout<<"Please enter your password: " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>password;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
GENDER:cout<<"Please enter your gender (m or f): " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>gender;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
if(gender != "m" && gender != "f"){
    cout<<"Please select a valid gender! "<<endl<<endl ;
    goto GENDER;
}
AGE:cout<<"Please enter your age: " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>age;
cout<<endl<<endl ;
if((!is_number(age)) || age <=3 || age>100){
    cout<<"Please enter a valid age!"<<endl<<endl ;
    cin.ignore();
    goto AGE;
}
system("CLS");
Current_user.createUser(username, gender[0], age);
Current_user.login(username);
Welcome(username) ;

}
void Login(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 10);
string username;
string password;
cout<<"Please enter your username and password:"<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
cout<<"Username: ";
SetConsoleTextAttribute(hConsole, 12);
cin>>username ;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
if(!SNDB.userIsExisted(username)){
    cout<<"Username does not exist!"<<endl<<endl ;
    Login();

}
cout<<"Password: ";
SetConsoleTextAttribute(hConsole, 12);
password="" ;
char ch;
ch=getch() ;
while(ch != 13){
      password.push_back(ch);
      cout << '*';
      ch = getch();
   }
   system("CLS");
   SetConsoleTextAttribute(hConsole, 10);
   cout<<endl<<"  Access Granted !!!" ;
   delay(3);
   system("CLS");
   Current_user.login(username);
   Welcome(username);




}

void startpage(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 10);
cout << "Hello! (please type a number corresponding to one of the following options:)" << endl;
SetConsoleTextAttribute(hConsole, 5);
cout<<endl<<endl;
    cout <<"1) Create a new account." << endl<<endl ;
     cout <<"2) Login to an existing account." << endl << endl;
     char choice;
     choice=getch();
     system("CLS");
     if(choice=='1')
        New_account();
     else if(choice=='2')
        Login();
     }
     void dataBaseInit()
     {


         ofstream f("data/counts.txt");
         if(!f.good())
         {
             system("mkdir \"data\"");
             f.open("data/counts.txt");
             f<<1 <<endl <<1;
             f.close();
         }
     }
int main()
{
   // dataBaseInit();
    while(1)
     startpage();

    return 0;
}
