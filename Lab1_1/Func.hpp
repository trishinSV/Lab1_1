//
//  Func.hpp
//  Lab1_1
//
//  Created by Сергей on 15.03.16.
//  Copyright © 2016 Сергей. All rights reserved.
//

#ifndef Func_hpp
#define Func_hpp

#include "List.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>


class List;

FILE* createFile();

void printPage(List* l, int, int numRecords);

void printReversedPage(List* l, int pageNumber, int numRecords);

void requestAge(List* l);

void viewPages(List* l,int num);

int addRecord(List* l);

void deleteRecord(List* l);

void requestLocation(List* l);

void editRecord(List* l);

#endif
