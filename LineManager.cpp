//Emilia Segura, 40138440

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


#include "MiniDB.h"
#include "Menu.h"
#include "LineManager.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::size_t;

LineManager::LineManager() //constructor creates LineManager with both menus
{ 
    create_fullmenu();
    create_partialmenu();
}

void LineManager::create_partialmenu() //sets up the partial menu
{
    partial_menu.set_top_message("Choose one of the following options");
    partial_menu.set_bottom_message("Enter an option number");
    partial_menu.push_back("Append input from the keyboard");
    partial_menu.push_back("Insert input from the keyboard");
    partial_menu.push_back("Append input from text file");
    partial_menu.push_back("Insert input from text file");
    partial_menu.push_back("Quit");
}
void LineManager::create_fullmenu() //sets up the full menu
{
    full_menu.set_top_message("Choose one of the following options");
    full_menu.set_bottom_message("Enter an option number");
    full_menu.push_back("Append input from the keyboard");
    full_menu.push_back("Insert input from the keyboard");
    full_menu.push_back("Append input from text file");
    full_menu.push_back("Insert input from text file");
    full_menu.push_back("Print the current line");
    full_menu.push_back("Print a span of lines around the current position");
    full_menu.push_back("Set the length of upper or lower line spans");
    full_menu.push_back("Print all");
    full_menu.push_back("Move the current line");
    full_menu.push_back("Delete the current line");
    full_menu.push_back("Write mini-database to file");
    full_menu.push_back("Quit");
}

void LineManager::run()
{
    bool co{true};
    int i;
    bool change{false}; //boolean to keep track of changes to DB (see if there have been modifications since the last write to file)
    while (co) //infinite loop is broken when user chooses to quit
    {
        if (line_db.size() == 0) //switch case for empty DB (partial menu)
        { //partial menu!
            i = partial_menu.read_option_number(); //delegate choosing options to menu class Checks that input is a valid int within range

            switch (i) 
            {

            case 1:
                append_key();
                change =true;
                break;

            case 2:
                insert_key();
                change =true;
                break;

            case 3:
                append_file();
                change =true;
                break;

            case 4:
                insert_file();
                change =true;
                break;

            case 5: //quit nothing to save to file when DB is empty
                co = false; //breaks while loop
                cout << "goodbye" << endl;
                break;
            }
        }
        else
        { //full menu!
            i = full_menu.read_option_number();

            switch (i)  //switch case for full menu 
            {

            case 1:
                append_key();
                change =true;
                break;

            case 2:
                insert_key();
                change =true;
                break;

            case 3:
                append_file();
                change =true;
                break;

            case 4:
                insert_file();
                change =true;
                break;

            case 5:
                print_current();
                break;

            case 6:
                print_span();
                break;

            case 7:
                set_span();
                break;

            case 8:
                print_all();
                break;

            case 9:
                move_current();
                break;

            case 10:
                delete_current();
                change =true;
                break;

            case 11:
                write_to_file();
                change =false;
                break;

            case 12: 
                co = quit(change); //status of change determines wether user is prompted to save to file (when DB has been modified since last save)
                break;
            }
        }
    }
}



void LineManager::append_key(){ //option 1
    cout << "To end input, enter a single dot and press enter" << endl;
    string text;
    while (text != "."){ //stop when single . is entered
        getline(cin, text);
        if (text != "."){ //do not append . 
            line_db.append(text);
        }
    }
}
void LineManager::insert_key(){ //option 2
    if (line_db.size() == 0){ //when DB empty, insert is the same as append. Append is less complex, so prefer it
        append_key();
    }
    else{
        cout << "To end input, enter a single dot and press enter" << endl;
        string text;
        while (text != "."){ //same as append
            getline(cin, text);
            if (text != "."){ 
                line_db.insert(text);
                line_db.next(); //move pointer forward as insert inserts at position of pointer. Otherwise when inserting many lines, they are added backwards
            }  
        }
        line_db.prev(); //make pointer point to last line entered
    }
}

void LineManager::append_file(){ //option 3
    ifstream fin;
    openFile(fin); //openfile( )prompts user for file name and checks that is is open
    string line;
    while (getline(fin, line)){ //read until no lines left
        line_db.append(line); //append each line
    }
    fin.close();
}
void LineManager::insert_file(){ //option 4
    if (line_db.size() == 0){ //if db is empty, insert same as appending
        append_file();
    }
    else{
        ifstream fin;
        openFile(fin);
        string line;
        while (getline(fin, line)){
            line_db.insert(line);
            line_db.next(); //so the lines gets input in proper order
        }
        fin.close();
        line_db.prev();
    }
}

void LineManager::print_current(){ //option 5
    cout << line_db.getCurrentIndex()+1 << ":  " << line_db.getValue() << endl; //makes index 1 based
}

void LineManager::print_span(){ //option 6
    size_t start;
    size_t stop;
    if (upper_span <= line_db.getCurrentIndex()) { //check wether the span will go out of range. Not using try/catch because the substraction with size_t just wraps around to the largest positive value it can hold
        start =line_db.getCurrentIndex()-upper_span; //get starting index for printing (0-based as line_db is implemented)
    } else { //out of range set start to index 0 and print beginning of file message
        start = 0;
        cout << "**: BOF" << endl;
        }
    try {
    stop = line_db.getCurrentIndex()+lower_span; //ending index this could cause exception if out of bounds
    line_db.moveToIndex(start); //move pointer to start
    for (size_t i{start}; i < stop; i++){ //loop does not go to the last element otherwise next() goes out of bounds
            cout << i+1 << ":  " << line_db.getValue() << '\n';
            line_db.next();
        }
        cout << stop+1 << ":  " << line_db.getValue() << endl; //get last value
    }
    catch (const std::logic_error& e){
    cout << "**: EOF"<< endl;
    }
} 

void LineManager::set_span(){ //option 7 
cout<< "Enter length of the span" <<endl;
    int choice{readInt()}; //read int performs error checking makes sure input is an integer
    if (choice == 0){ //case n=0
        upper_span = 0;
        lower_span = 0;
    }
    else if (choice >0){ //case n > 0
        if (line_db.getCurrentIndex()+choice < line_db.size()){ //check valid range
            lower_span = choice; //set lower span
        }
        else { 
            cout << choice <<" out of range. Maximum span is " << line_db.size() -line_db.getCurrentIndex() -1   << endl; //print message with max span possible without going out of bounds
        }
    }
    else { //case n < 0
        if (-choice <= line_db.getCurrentIndex()){ //check valid range
            upper_span = -choice; //set upper_span
        }
        else{
            cout << choice <<" out of range. Maximum span is -" << line_db.getCurrentIndex()  << endl; //print message with max span possible without going out of bounds
        }
    }
} 

void LineManager::print_all(){  //option 8
    line_db.moveToFirst(); //move iterator to point to 1st element
    for (size_t i{1}; i < line_db.size(); i++){ //loop does not go to the last element otherwise next() goes out of bounds
        cout << i << ":  " << line_db.getValue() << endl; //as loop starts at 1, works out for printing line number
        line_db.next();
    }
    cout << line_db.size() << ":  " << line_db.getValue() << endl; //get last value
}

//testing a new version
void LineManager::move_current(){ //option 9
    cout << "Which line do you want to move to?" << endl;
    try{
    int choice{readInt()}; //check valid int
    line_db.moveToIndex(choice-1);  // -1 because line_db is 0-based indexing
    }
    catch (const std::logic_error& e){ //catch out of range logic error thrown by line_db
        cout << e.what() << ", Valid range is [1-" << line_db.size()<<"]"<<endl;
    }
}

void LineManager::delete_current(){ //option 10
    line_db.remove(); 
    cout << "current line deleted" <<endl;
} 

//maybe adjust as this will create a file to write to if it doesn't exist
void LineManager::write_to_file(){ //option 11
    ofstream fout;
    openFile(fout);
    line_db.moveToFirst();
    for (size_t i{1}; i <line_db.size(); i++){ //wirtes to file line by line
        fout << line_db.getValue() << '\n';
        line_db.next();
    }
    fout << line_db.getValue() << '\n'; //last value outside of loop so line_db.next() does not go out of bounds
    fout.close();
} 

bool LineManager::quit(bool& change) { //option 12
    if (change){ //only asks to save if there has been a change since last save
    cout << "Do you want to save changes to a file? ";
    string answer;
    getline(cin, answer);
    if (answer[0]=='y' || answer[0]=='Y'){ //only saves to file if user input starts with y or Y
        write_to_file();
    }
    }
    cout << "goodbye!" << endl;
    return false; //returns false to break infinite loop in run() an exit program
} 

void LineManager::openFile(ifstream &fin, const string &prompt){ //from posted lecture notes
    while (true){
        cout << prompt;
        string filename{};
        getline(cin, filename);     
        fin.open(filename); 
        if (fin){                    
            break;
        }
        cout << filename << " could not be opened, please try again " << endl;
        fin.clear(); // clear to good state and try again
    }
}

//will this be needed in this form as a file is created if does not exist?
void LineManager::openFile(ofstream &fout, const string &prompt){
    while (true){
        cout << prompt;
        string filename{};
        getline(cin, filename);     
        fout.open(filename); // try to open the file removed .c_str()
        if (fout){                    
            break;
        }
        cout << filename << " could not be opened, please try again " << endl;
        fout.clear(); // clear to good state and try again
    }
}