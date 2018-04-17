#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;
void New_account(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 5);
cout<<"please enter your username: "<<endl;
cout<<"please enter your password: "<<endl;
cout<<"please enter your gender: "<<endl;
cout<<"please enter your age: "<<endl;
char dummy;
dummy=getch();
system("CLS");

}
void Welcome(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
cout<<"Welcome, (username)!"<<endl;
cout<<"What do you want to do today (please type a number corresponding to one of the following options:)?"<<endl;
SetConsoleTextAttribute(hConsole, 5);
cout <<"1) Add a new friend." << endl;
cout <<"2) Write a new post." << endl;
cout <<"3) View your friends." << endl;
cout <<"4) View someone's posts." << endl;
char dummy;
dummy=getch();
system("CLS");


}
void startpage(){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 2);
cout << "Hello! (please type a number corresponding to one of the following options:)" << endl;
SetConsoleTextAttribute(hConsole, 5);
    cout <<"1) Create a new account." << endl;
     cout <<"2) Login to an existing account." << endl;
     char choice;
     choice=getch();
     system("CLS");
     if(choice=='1')
        New_account();
     else if(choice=='2')
        Welcome();
     }
int main()
{
    while(1)
    startpage();

    return 0;
}
