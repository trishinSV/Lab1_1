//
//  Func.cpp
//  Lab1_1
//
//  Created by Сергей on 15.03.16.
//  Copyright © 2016 Сергей. All rights reserved.
//

#include "Func.hpp"
#include <stdio.h>
#define FILE_NAME_MAX_SIZE 64
#define MAX_COMMAND_LENGTH 32
#define NAME_MAX_LENGTH 64
#define RECORDS_PER_PAGE 3

using namespace std;

char menu2[] = "N - следующая страница, P - предыдущая, B - назад\n> ";
char menu3[] = "\nB - назад\n";

// используется указатель на список, данные хранятся в памяти компьютера

void viewPages(List* l, int num)
{
    int currentPage = 0;
    int cmd = 1;
    char command[MAX_COMMAND_LENGTH];
    printf("1 - в прямом\n2 - в обратном");
    scanf("%d",&cmd);
    while (command[0] != 'B' and command[0] != 'b')
    {
            system("clear");
        if (cmd==1)
            printPage(l, currentPage, RECORDS_PER_PAGE);
        else
            
            printReversedPage(l, currentPage, RECORDS_PER_PAGE);
            puts(menu2);
            gets(command);
            switch (command[0])
            {
                case 'n': case 'N':
                    if (currentPage<num/RECORDS_PER_PAGE)
                    currentPage++;
                    else currentPage=0;
                    break;
                case 'p': case 'P':
                    if (currentPage > 0)
                        currentPage--;
                    else currentPage =num/ RECORDS_PER_PAGE;
                    break;
            }
    }
    
}

void printPage(List* l, int pageNumber, int numRecords)
{
    puts("---------------------------------------------------------------------------------");
    puts("|      Имя пациента      |   Пол  |   Возраст  |   Город проживания   | Диагноз  |");
    puts("---------------------------------------------------------------------------------");
    l->goToFirst();
    int i = 0;
    while (!l->isEnd())
    {
        i++; // Если элмент на нужной странице - выводим
        if (i > (pageNumber * numRecords) and i <= ((pageNumber + 1) * numRecords))
            l->getCurrent().print();
        l->next();    }
}



void printReversedPage(List* l, int pageNumber, int numRecords)
{
    puts("---------------------------------------------------------------------------------");
    puts("|      Имя пациента      |   Пол  |   Возраст  |   Город проживания   | Диагноз  |");
    puts("---------------------------------------------------------------------------------");
    l->goToLast();
    int i = 0;
    while (!l->isStart())
    {
        i++; // Если элмент на нужной странице - выводим
        if (i > (pageNumber * numRecords) and i <= ((pageNumber + 1) * numRecords))
            l->getCurrent().print();
        l->next();    }
}

void requestAge(List* l)
{
    system("clear");
    int k = 0;
    char command[MAX_COMMAND_LENGTH];
    while (command[0] != 'B' and command[0] != 'b')
    {
        puts("---------------------------------------------------------------------------------");
        puts("|      Имя пациента      |   Пол  |   Возраст  |   Город проживания   | Диагноз  |");
        puts("---------------------------------------------------------------------------------");
    Record max;
    max.age = 65;
    l->goToFirst();
    while (!l->isEnd())
    {
        if (l->getCurrent().age > max.age){
             l->getCurrent().print();
            k++;
        }
        l->next();
    }
        if(k == 0)
            puts("Таких нет");
        puts(menu3);
        gets(command);
        
    }
    
}


void requestLocation(List* l)
{
    system("clear");
    int k = 0;
    char command[MAX_COMMAND_LENGTH];
    while (command[0] != 'B' and command[0] != 'b')
    {
        puts("---------------------------------------------------------------------------------");
        puts("|      Имя пациента      |   Пол  |   Возраст  |   Город проживания   | Диагноз  |");
        puts("---------------------------------------------------------------------------------");
    Record city;
      char ans[]="Saint-P";
    l->goToFirst();
    while (!l->isEnd())
    {
        if (strcmp(ans,l->getCurrent().location)!=0){
            city = l->getCurrent();
            city.print();
            k++;
        }
        if(k == 0)
            puts("Таких нет");
        
        
     l->next();

    }
        puts(menu3);
        gets(command);
        
    }

}

int addRecord(List* l)
{
    char command[MAX_COMMAND_LENGTH];
    while (command[0] != 'B' and command[0] != 'b')
    {
    
    Record currentRecord;
    puts("Введите имя пациента:\n> ");
    gets(currentRecord.name);
    puts("Введите возраст пациента:\n> ");
    scanf("%d", &currentRecord.age);
    puts("Введите пол пациента:\n> ");
    cin>>currentRecord.gender;
    puts("Введите город пациента:\n> ");
    cin>>currentRecord.location;
    puts("Введите диагноз пациента\n> ");
    cin>>currentRecord.diagnos;
    if (l->add(currentRecord))
        puts("Запись была добавлена\n");
    else
        puts("Запись не была добавлена\n");
        
        puts(menu3);
        gets(command);
        gets(command);
    }
    return true;
}

void editRecord(List* l)
{
    char command[MAX_COMMAND_LENGTH];

    Record currentRecord;
    char oldName[64];
    puts("Введите имя пациента:\n> ");
    gets(oldName);
    if (l->edit(oldName, currentRecord)){
               addRecord(l);
    }

    else
        while (command[0] != 'B' and command[0] != 'b')
        {
        puts("Запись не найдена\n");
    puts(menu3);
    gets(command);
}

}

void deleteRecord(List* l)
{
    char command[MAX_COMMAND_LENGTH];
    while (command[0] != 'B' and command[0] != 'b')
    {
        Record currentRecord;
    char buffer[64];
    puts("Введите имя пациента:\n> ");
    gets(buffer);
    if (l->edit(buffer, currentRecord))
        puts("Запись была удалена\n");
    else
        puts("Запись не была удалена\n");
        puts(menu3);
        gets(command);
    }
}


FILE* createFile()
{
    char fileName[FILE_NAME_MAX_SIZE];
    printf("Введите имя файла:\n> ");
    gets(fileName);
    FILE* file = fopen(fileName, "wb+");
    if (!file)
    {
        printf("Не удалось создать файл!\n");
        return 0;
    }
    return file;
}
