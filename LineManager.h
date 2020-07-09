//Emilia Segura, 40138440

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <fstream>
#include <string>
#include "MiniDB.h"
#include "Menu.h"

class LineManager{

private:
    MiniDB<std::string> line_db; 
    Menu partial_menu; 
    Menu  full_menu;  

    size_t upper_span{2};
    size_t lower_span{2};
    //private functions to simplify run();
    void create_partialmenu();
    void create_fullmenu();

    void append_key();  //option 1
    void insert_key(); //option 2
    void append_file(); //option 3
    void insert_file(); //option 4
    void print_current(); //option 5
    void print_span(); //option 6
    void set_span(); //option 7
    void print_all(); //option 8
    void move_current(); //option 9
    void delete_current(); //option 10
    void write_to_file(); //option 11
    bool quit(bool& change); //option 12

    int readInt_in_range();
    void openFile(std::ifstream & fin, const std::string & prompt = "Enter input file name: ");
    void openFile(std::ofstream & fout, const std::string & prompt = "Enter ouput file name: ");

public:
    LineManager(); //default constructor (creates the menus)
    LineManager(const LineManager& lm) = delete; //there should only be one instance of LineManager delete copy constructor
    LineManager& operator=(const LineManager& lm) = delete; //same no use for copy assignment
    virtual ~LineManager() = default; //default destructor
    void run();
};

#endif