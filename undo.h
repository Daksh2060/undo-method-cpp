#pragma once

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class Stringlist{

    class LL_Stack{

        struct LL_Node{

            string data;
            LL_Node* next;
        };
        
        LL_Node* top = nullptr;

        public:

            //Constructor for the stack
            LL_Stack(){
                top = nullptr;
            }

            string pop(){
                string word = top->data;
                LL_Node* temp = top;
                top = top->next;
                delete temp;
                return word;
            }

            void push(string word){
                LL_Node* new_node = new LL_Node;
                new_node->data = word;
                new_node->next = top;
                top = new_node;
            }

            bool is_empty() {
                return top == nullptr;
            }

            //Default stack destructor
            ~LL_Stack(){ 
                while (top){
                    LL_Node* current = top;
                    top = top->next;
                    delete current;
                }
                top = nullptr;
            }  
    };

    LL_Stack command_stack;

    void push_on(string word) {
        command_stack.push(word);
    }

    string pop_off() {
        return command_stack.pop();
    }

    bool empty_check(){
        return command_stack.is_empty();
    }
    
    int cap;     
    string *arr; 
    int sz;      

    
    int backup_sz;
    int reapply;

    // Helper function for throwing out_of_range exceptions.
    void bounds_error(const string &s) const
    {
        throw out_of_range("Stringlist::" + s + " index out of bounds");
    }

    // Helper function for checking index bounds.
    void check_bounds(const string &s, int i) const
    {
        if (i < 0 || i >= sz)
            bounds_error(s);
    }

    // Helper function for copying array of strings.
    void copy(const string *other)
    {
        for (int i = 0; i < sz; i++)
        {
            arr[i] = other[i];
        }
    }

    // Helper function for checking capacity; doubles size of array if necessary.
    void check_capacity()
    {
        if (sz == cap)
        {
            cap *= 2;
            string *temp = new string[cap];

            for (int i = 0; i < sz; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
    }

public:

    // Default constructor: makes an empty StringList.
    Stringlist()
        : cap(10), arr(new string[cap]), sz(0) {}


    // Copy constructor: makes a copy of the given StringList.
    Stringlist(const Stringlist &other)
        : cap(other.cap), arr(new string[cap]), sz(other.sz)
    {
        copy(other.arr);
    }

    ~Stringlist()
    {
        delete[] arr;
    }

    /*
     Assignment operator: makes a copy of the given StringList.
    
     For undoing, when assignment different lists, the undo stack is not
     copied:
    
       lst1 = lst2; lst1 undo stack is updated to be able to undo the
       assignment; lst1 does not copy lst2's stack
       
       lst2 is not changed in any way
    
     Self-assignment is when you assign a list to itself:
    
       lst1 = lst1;
    
     In this case, nothing happens to lst1. Nothing is changed. Both its
     string data and undo stack are left as-is. 
    */
    Stringlist &operator=(const Stringlist &other)
    { 
        if (this != &other)
        {
            //Makes a backup copy of the current list size before it's destroyed
            backup_sz = sz;

            for(int i = 0; i < sz; i ++){
                std::string temp = arr[i];
                push_on(temp);
            }

            delete[] arr;
            cap = other.capacity();
            arr = new string[cap];
            sz = other.size();
            copy(other.arr);

            //Pushes the size and command of the undo list onto stack
            push_on(std::to_string(backup_sz));
            push_on("UNDO_OPERATOR");
        }

        return *this;
    }

    // Returns the number of strings in the list.
    int size() const { return sz; }
    
    // Returns true if the list is empty, false otherwise.
    bool empty() const { return size() == 0; }

    // Returns the capacity of the list, i.e. the size of the underlying array.
    int capacity() const { return cap; }

    // Returns the string at the given index.
    string get(int index) const
    {
        check_bounds("get", index);
        return arr[index];
    }


    // Returns the index of the first occurrence of s in the list, or -1 if s is not in the lst.
    int index_of(const string &s) const
    {
        for (int i = 0; i < sz; i++)
        {
            if (arr[i] == s)
            {
                return i;
            }
        }
        return -1;
    }


    // Returns true if s is in the list, false otherwise.
    bool contains(const string &s) const
    {
        return index_of(s) != -1;
    }

    // Returns a string representation of the list.
    string to_string() const
    {
        string result = "{";
        for (int i = 0; i < size(); i++)
        {
            if (i > 0)
                result += ", ";
            result += "\"" + get(i) + "\"";
        }
        return result + "}";
    }

    // Sets the string at the given index.
    void set(int index, string value)
    {
        //Pushes 3 string commands to the stack, all remaining methods use this system
        std::string temp = arr[index];
        push_on(temp);
        push_on(std::to_string(index));
        push_on("UNDO_SET");

        check_bounds("set", index);
        arr[index] = value;
    }

    // Insert s before index; if necessary, the capacity of the underlying array is doubled.
    void insert_before(int index, const string &s)
    {
        if (index < 0 || index > sz) // allows insert at end, i == sz
            bounds_error("insert_before");
        check_capacity();

        push_on(std::to_string(index));
        push_on("UNDO_INSERT_BEFORE");

        for (int i = sz; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = s;
        sz++;
    }

    // Appends s to the end of the list; if necessary, doubles capacity
    void insert_back(const string &s)
    {
        insert_before(size(), s);
        //Pops off extra commands from the helper function in undo
        pop_off();
        pop_off();
        push_on("UNDO_INSERT_BACK");
    }

    // Inserts s at the front of the list; if necessary, doubles capacity
    void insert_front(const string &s)
    {
        insert_before(0, s);
        pop_off();
        pop_off();
        push_on("UNDO_INSERT_FRONT");
    }

    // Removes the string at the given index; doesn't change the capacity.
    void remove_at(int index)
    {
        std::string temp = arr[index];
        push_on(temp);
        push_on(std::to_string(index));
        push_on("UNDO_REMOVE_AT");

        check_bounds("remove_at", index);
        for (int i = index; i < sz - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        sz--;
    }

    // Removes all strings from the list; doesn't change the capacity.
    void remove_all()
    {
        int copy_size = sz;
        reapply = sz;

        while (sz > 0)
        {
            std::string temp = arr[sz-1];
            push_on(temp);

            remove_at(sz - 1);

            pop_off();
            pop_off();
            pop_off();
        }
        push_on(std::to_string(copy_size));
        push_on("UNDO_REMOVE_ALL");
    }

    /*
     Removes the first occurrence of s in the list, and returns true. If s is
     nowhere in the list, nothing is removed and false is returned.
     Is undoable Assuming is item is not in list, undo stack is unchanged
    */
    bool remove_first(const string &s)
    {
        int index = index_of(s);
        if (index == -1)
            return false;

        std::string temp = s;
        push_on(temp);
        push_on(std::to_string(index));
        push_on("UNDO_REMOVE_FIRST");

        remove_at(index);

        pop_off();
        pop_off();
        pop_off();
        return true;
    }


    // Undoes the last operation that modified the list. Return true if change was undone
    bool undo(){

        //When called, first checks if the stack is empty
        if(empty_check()){
            return false;
        }

        //execute stores the string command from the methods
        string execute = pop_off();
        //Index and size pop and convert the index value back to int using std::stoi
        int index, size;
        string word;
        cout<<execute<<endl;

        if(execute == "UNDO_INSERT_BACK"){
            undo_insert_back();
            return true;
        }

        else if(execute == "UNDO_INSERT_FRONT"){
            undo_insert_front();
            return true;
        }

        else if(execute == "UNDO_REMOVE_ALL"){
            size = std::stoi(pop_off());
            undo_remove_all(size);
            return true;
        }

        else if(execute == "UNDO_SET"){
            index = stoi(pop_off());
            word = pop_off();
            undo_set(index,word);
            return true;
        }

        else if(execute == "UNDO_INSERT_BEFORE"){
            index = stoi(pop_off());
            undo_insert_before(index);
            return true;
        }

        else if(execute == "UNDO_OPERATOR"){
            size = stoi(pop_off());
            undo_operator(size);
            return true;
        }

        else if(execute == "UNDO_REMOVE_AT" || execute == "UNDO_REMOVE_FIRST"){
            index = stoi(pop_off());
            word = pop_off();
            undo_remove_at(index,word);
            return true;
        }

        //Also returns false if the command on the stack does not match
        return false;
    }

////HELPER FUNCTIONS for undo which also maintain the stack

    void undo_insert_back(){

        remove_at(sz-1);
        pop_off();
        pop_off();
        pop_off();
    }

    void undo_insert_front(){

        remove_at(0);
        pop_off();
        pop_off();
        pop_off();
    }

    void undo_set(int index, string word){

        set(index, word);
        pop_off();
        pop_off();
        pop_off();
    }

    void undo_insert_before(int index){

        remove_at(index);
        pop_off();
        pop_off();
        pop_off();
    }

    void undo_remove_at(int index, string word){

        insert_before(index, word);
        pop_off();
        pop_off();
    }

    void undo_remove_all(int size){

        for(int i = 0; i < size; i++){
            insert_back(pop_off());
            pop_off();
        }
    }

    void undo_operator(int size){
        //Empties current list
        remove_all();
        pop_off();
        pop_off();

        for(int j = 0 ; j < reapply; j++){
            pop_off();
        } 

        //Refills list with previous state
        for(int i = 0; i < size; i++){
            insert_front(pop_off());
            pop_off();
        }
    }
}; // class Stringlist

// Prints list to in the format {"a", "b", "c"}.
ostream &operator<<(ostream &os, const Stringlist &lst)
{
    return os << lst.to_string();
}

/*
 Returns true if the two lists are equal, false otherwise.
 Does *not* consider any undo information when comparing two Stringlists. All
 that matters is that they have the same strings in the same order.
*/
bool operator==(const Stringlist &a, const Stringlist &b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (a.get(i) != b.get(i))
        {
            return false;
        }
    }
    return true;
}

/*
 Returns true if the two lists are not equal, false otherwise.
 Does *not* consider any undo information when comparing two Stringlists.
*/
bool operator!=(const Stringlist &a, const Stringlist &b)
{
    return !(a == b);
}
