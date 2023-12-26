#include "undo.h"
#include <cassert>

using namespace std;

int main() {
    
    Stringlist list1;
    Stringlist list2;
    Stringlist list3;

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.undo();
    list3.undo();
    list2.undo();

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.insert_back("1;");
    list1.insert_before(0, "2;");
    list1.insert_front("3 ;");
    list1.insert_front("4;");
    list1.insert_before(1, "5;");
    list1.insert_before(1, " 6;");
    list1.insert_back("7;");

    cout<<list1.to_string()<<endl;
   
    list2.insert_front("Hello;");
    list2.insert_back("World;");
    list2.insert_before(1, "Py thon;");
    list2.insert_before(2, "Code;");
    list2.insert_front("Sample;");
    list2.insert_before(1, "Wow");
    list2.insert_back("Ran dom;");
    list2.insert_front("Joy;");
    list2.insert_before(0, "Ques tion;");

    cout<<list2.to_string()<<endl;

    list3.insert_back("86;");
    list3.insert_back("6;");
    list3.insert_back("Day;");
    list3.insert_before(1, "Command;");
    list3.insert_before(1, "Ano ther;");
    list3.insert_back("C at;");
    list3.insert_before(1, "More;");
    list3.insert_back("1;");
    list3.insert_before(1, "2;");
    list3.insert_front("3;");

    cout<<list3.to_string()<<endl;

    list1 = list2;
    list2 = list3;
    list3 = list3;
    list3 = list1;

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list1.undo());
    assert(list3.undo());
    assert(list2.undo());
    assert(list3.undo());
    list3.insert_front("3;");

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.set(2,"FILLER");
    list3.set(1,"FILLER");
    list1.set(4,"FILLER");
    list2.set(3,"FILLER");
    list1.set(1,"FILLER");
    list2.set(0,"FILLER");
    list3.set(1,"FILLER");
    list3.set(3,"FILLER");

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list1.undo());
    assert(list1.undo());
    assert(list1.undo());
    assert(list2.undo());
    assert(list2.undo());
    assert(list3.undo());
    assert(list3.undo());
    assert(list3.undo());

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list3.undo());
    assert(list2.undo());
    assert(list1.undo());

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.remove_at(0);
    list1.remove_at(0);
    list3.remove_at(1);
    list2.remove_at(4);
    assert(list2.undo());
    list1.remove_at(1);
    assert(list3.undo());
    list2.remove_at(2);
    assert(list1.undo());
    assert(list1.undo());
    list2.remove_at(0);
    list2.remove_at(1);
    list3.remove_at(2);
    assert(list1.undo());
    list3.remove_at(0);
    list3.remove_at(1);
    assert(list3.undo());
    assert(list3.undo());
    assert(list3.undo());
    assert(list2.undo());
    assert(list2.undo());
    assert(list2.undo());

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.remove_all();
    list3.remove_all();
    list2.remove_all();
    list1.remove_all();
    list2.remove_all();

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list1.undo());
    assert(list1.undo());
    assert(list2.undo());
    assert(list2.undo());
    assert(list3.undo());
    
    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.remove_first("5;");
    list1.remove_first("1;");
    list1.remove_first("5;");
    list3.remove_first("2;");
    list2.remove_first("Sample;");
    list2.remove_first("Sample;");
    list2.remove_first("World;");
    list3.remove_first("Day;");

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list2.undo());
    assert(list2.undo());
    assert(list1.undo());
    assert(list1.undo());
    assert(list3.undo());
    assert(list3.undo());

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    list1.remove_all();
    list2.remove_all();
    list3.remove_all();
    list1.remove_all();
    list2.remove_all();
    list3.remove_all();

    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

    assert(list2.undo());
    assert(list1.undo());
    assert(list3.undo());
   
    cout<<list1.to_string()<<endl;
    cout<<list2.to_string()<<endl;
    cout<<list3.to_string()<<endl;

}
