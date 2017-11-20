//
//  List.hpp
//  Lab1_1
//
//  Created by Сергей on 15.03.16.
//  Copyright © 2016 Сергей. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include "Func.hpp"
#define NAME_MAX_LENGTH 64

struct Record
{
    int age;
    char name[NAME_MAX_LENGTH];
    char gender[NAME_MAX_LENGTH];
    char location[NAME_MAX_LENGTH];
    char diagnos[NAME_MAX_LENGTH];
    void print();
};

struct ListNode // дескриптор списка
{
    Record data;
    ListNode* next;
    ListNode* prev;
    ListNode(const Record& data, ListNode* next, ListNode* prev);
};

class List
{
public:
    List();
    Record getCurrent() const;
    bool next();
    bool previous();
    void goToFirst();
    void goToLast();
    bool isEmpty() const;
    bool add(Record& r);
    bool remove(char* name);
    bool edit(char* name, Record& r);
    int  getCount() const;
    void readFromFile(FILE* file);
    void writeToFile(FILE* file);
    void clear();
    bool isEnd() const;
    bool isStart() const;
        ~List();
private:
    ListNode* head;
    ListNode* tail;
    ListNode* current;
    ListNode* findNodeToInsertAfter(char*);
};

#endif
