//Emilia Segura, 40138440

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

class Menu{

private:

std::vector<std::string> option_list;
std::string top_message;
std::string bottom_message;


public: //all of these copied from assignemnt 1 with some slight modifications. 

Menu(); //default constructor
Menu(const Menu& mnu) = default; //default copy constructor
virtual ~Menu() = default; //destructor
Menu& operator=(const Menu& m) = default; //default assignment operator


void set_top_message(const std::string& t); //setter 
void set_bottom_message(const std::string& b); //setter
void clear_top_message(); // top message =""
void clear_bottom_message(); //bottom message =""
bool isEmpty() const; //check on content of option_list
int size() const; //return #of options
void push_back(const std::string& pOption); //add option at end  
void pop_back(); //remove last menu option
std::string getOptionNumber(int k); //return option at the kth array index
std::string toString() const; //returns menu object as string
void insert(int index, const std::string& option); //insert option into menu   
void remove(int index); //remove option at any index
int read_option_number(); //displays menu and reads number input by user

};

std::ostream& operator<<( std::ostream &, const Menu& ); //overloading to print menu

//error checking for int input
int readInt();

#endif 


