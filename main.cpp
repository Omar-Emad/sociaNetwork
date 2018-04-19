#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
using namespace std;

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
char dummy;
dummy=getch();
system("CLS");

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
cout<<"Please enter your password: " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>password;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
cout<<"Please enter your gender: " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>gender;
cout<<endl<<endl ;
SetConsoleTextAttribute(hConsole, 5);
cout<<"Please enter your age: " ;
SetConsoleTextAttribute(hConsole, 12);
cin>>age;
cout<<endl<<endl ;
system("CLS");
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
   clock_t begin_time = clock();
   while(((clock()-begin_time)/CLOCKS_PER_SEC)< 3);
   system("CLS");
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
int main()
{
    while(1)
    startpage();

    return 0;
}
