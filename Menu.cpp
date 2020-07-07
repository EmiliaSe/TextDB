
#include <iostream>
#include <string>
#include <stdexcept>
#include "Menu.h"

using std::cout;
using std::endl;
using std::cin;
using std::ostream;
using std::string;

//default constructor
Menu::Menu(){
top_message ="";
bottom_message = "";
}

void Menu::set_top_message(const string& t){
    top_message = t;
} 
void Menu::set_bottom_message(const string& b){
    bottom_message = b;
} 

void Menu::clear_top_message(){
    top_message ="";
} 
void Menu::clear_bottom_message(){
    bottom_message = "";
} 

bool Menu::isEmpty() const{
    return option_list.empty();
}
int Menu::size() const{
    return option_list.size();
}

void Menu::push_back(const string& pOption){ //inserts at end of vector
    option_list.push_back(pOption);
}

void Menu::pop_back(){ 
if (!isEmpty()){ //checks that the is an item to remove
option_list.pop_back(); //remove from end
}
else{
    cout<< "Nothing to remove, list empty" << endl;
}
} 

string Menu::getOptionNumber(int k){ //1 based indexing!
if (k >size() || k<1){
        throw std::out_of_range( "No such option" );
    }
    return this->option_list[k-1];

} //return option at the kth array index

string Menu::toString() const{
    if (isEmpty() && top_message.empty() && bottom_message.empty()){ //case completely empty menu
        return "\n??";
    }
    else { //appends line by line to a single string that represents the whole menu
        string m{"\n"};
        m+=top_message;
        m+="\n";
        for (std::size_t i = 0; i < size(); ++i) { //all the menu options
            string num = std::to_string(i+1);
            m = m +"  "+ num +": "+ option_list[i]+ "\n"; //1 based -index precedes content
        }
        m+=bottom_message;
        m+="\n??";
        return m;
    }
} 

void Menu::insert(int index, const std::string& option){
    if (index > (size()+2) || index<=0){ //checks that index is within correct range (1 based indexing)
        std::cout << "ERROR, "<< index <<" out of range cannot insert" << std::endl;
    }
    else{

    option_list.insert(option_list.begin()+index-1, option);
    }
} //insert option into menu   


void Menu::remove(int index){ //1 based-index
    if (isEmpty()){
        std::cout << "ERROR no options to remove" << std::endl; //case empty list
    }
    else if (index> size()  || index < 1){
       std::cout << "ERROR, "<< index <<" out of range of menu options" << std::endl; //case out of range
    }
    else{
        option_list.erase(option_list.begin()+index-1);
    }

} //remove option at any index

int Menu::read_option_number(){
    std::cout << toString() <<" "; //print out whole menu 
    int choice = readInt(); //delegate error checking to readInt
    if (isEmpty()){   //if option list is empty, accepts any int
        return choice;
    }
    else{ 
    while (choice >size() || choice < 1) { //if not empty, only accepts in correct range
        std::cout <<"Invalid choice " << choice << ". It must be in the range [1, " << size()<<"]"<<std::endl;
        std::cout << toString()<< " "; //prints whole menu until input is valid  //removed endl
        std::cin >> choice;
    }
    return choice; //returns an int in valid range of menu options
    }
}

ostream& operator<<(ostream & sout, const Menu& me) //overloading operation to print Menu object
{
sout << me.toString();
   return sout;
}


//error checking for user input. only accepts int. very close to what was presented in a lecture. Is used in Menu and LineManager, choice to implement as free function so can be easily reused
int readInt(){
    std::string bad_data;
    int number;
    cin >> number;
    while(! cin){
        cin.clear(); //reset cin 
        std::getline(cin, bad_data);
        cout << "please enter an integer" <<endl;
        cin >> number;
    }
    std::getline(cin, bad_data);
    return number;
}