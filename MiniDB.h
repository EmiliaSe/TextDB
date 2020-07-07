//Emilia Segura, 40138440

#ifndef MINIDB_H
#define MINIDB_H

#include <list>
#include <iterator>
#include <stdexcept>
#include <iostream>

template <typename T>
class MiniDB{

private:
std::list<T> db_store;
typename std::list<T>::iterator current_position;

public:

//special member functions. see 4.2.1 do I have to do anything????

size_t size() const;
void insert(const T& item);
void append(const T& item);
void prev();
void next();
T remove();
void moveToFirst();
void moveToLast();
size_t getCurrentIndex() const; 
void moveToIndex(size_t index);
const T& getValue() const; // returns the value at the current position

};
//Implementation of all functions here

template<typename T>
size_t MiniDB<T>::size() const{ //returns size
    return db_store.size();
}

template<typename T>
void  MiniDB<T>::insert(const T& item){
    if (db_store.empty()){ //case if list is empty
        db_store.push_front(item); //add item at front of list 
        current_position = db_store.begin(); //point iterator to 1st item
    }
    else {
    db_store.insert(current_position, item);
    --current_position;  //adjust current_position to point to inserted item
}
}

template<typename T>
void MiniDB<T>:: append(const T& item){
    if (db_store.empty()){ //case if list is empty
        db_store.push_front(item); //add item
        current_position = db_store.begin(); //point iterator to 1st item
    }
    else {
    db_store.push_back(item);
    current_position = --db_store.end();  //point iterator to last item of list (newly appended)
    }
}

template<typename T>
void MiniDB<T>::prev(){
    if (db_store.empty()){ //case list empty
        throw std::logic_error("error, DB empty");
    }
    else if (current_position == db_store.begin()){ //case iterator already at start
        throw std::logic_error("out of range error");
    }
    else{ //normal case
        --current_position;
    }
}

template<typename T>
void MiniDB<T>::next(){
    if (db_store.empty()){ //case empty list
        throw std::logic_error("error, DB empty");
    }
    else if (current_position == --db_store.end()){ //case iterator already at last item
        throw std::logic_error("out of range error (next)");
    }
    else{ //normal case
        ++current_position;
    }
}

template<typename T> 
T MiniDB<T>::remove(){
    std::string temp;
    if (db_store.empty()){ //nothing to remove when empty
            throw std::logic_error("error, DB empty");
        }
        else if (current_position == --db_store.end()){ // for case last item removed  
            temp = *current_position;
            db_store.pop_back(); //remove item
            current_position = --db_store.end(); //move iterator to last item in list
            return temp;  
        }
        else if (size() == 1){ //case becomes empty
            temp = *current_position;
            db_store.pop_back();
            current_position = db_store.end(); 
            return temp;
        }
        else { // general case. current_pointer should point to item after the one removed
            temp = *current_position;
            current_position = db_store.erase(current_position); //erase item and returns iterator pointing to the element following the deleted element
            return temp; //returns the item removed
        }
}

template<typename T>
void MiniDB<T>::moveToFirst(){
    if (db_store.empty()){ //if empty nowhere to move to
        throw std::logic_error("error, DB empty");
    }
    else {
    current_position = db_store.begin(); //move to first
    }
}

template<typename T>
void MiniDB<T>::moveToLast(){
    if (db_store.empty()){ //if empty nowhere to move to
        throw std::logic_error("error, DB empty");
    }
    else {
    current_position = --db_store.end(); //points to last item
    }
}

template<typename T>
size_t MiniDB<T>::getCurrentIndex() const { //uses 0 based indexing
if (db_store.empty()){
        throw std::logic_error("error, DB empty");
    }
    else {
       typename std::list<T>::const_iterator start = db_store.cbegin(); //both iterators are const, so function can be const
       typename std::list<T>::const_iterator stop = current_position;
       return std::distance(start,stop);  //get index by looking at distance between the beginning of list and current position   
    }
}

template<typename T>   
void MiniDB<T>::moveToIndex(size_t index){ //uses 0 based indexing
    if (db_store.empty()){ //if empty nowhere to move to
    throw std::logic_error("error, DB empty");
    }
    else if (index < size()){
    current_position = db_store.begin(); //set iterator to point to start
    std::advance(current_position, index); //advance to correct index
    }
    else { //if move is beyond range
        throw std::logic_error("Index out of range");
    }
}

template<typename T>
const T& MiniDB<T>::getValue() const{ 
if (db_store.empty()){ //no value to get if empty
    throw std::logic_error("error, DB empty");
    }
    else{
return *current_position; //uses iterator to access value
    }
}

#endif