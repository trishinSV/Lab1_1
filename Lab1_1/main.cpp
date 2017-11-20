//
//  main.cpp
//  Lab1_1
//
//  Created by Сергей on 15.03.16.
//  Copyright © 2016 Сергей. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Func.hpp"
#include "List.hpp"

#define FILE_NAME_MAX_SIZE 64
#define MAX_COMMAND_LENGTH  32

int main(int argc, char * argv[])
{
    system("clear");
    char fileName[FILE_NAME_MAX_SIZE];
    char command[MAX_COMMAND_LENGTH];
    char menu[] = "1. Сохранить в файл;\n2. Просмотр файла;\n3. Добавить запись;\n4. Редактирвоать запись;\n5. Удалить запись;\n6. Иногородние пациенты;\n7. Пациенты пенсионного возраста \n8. Выход;\n> ";
    if (argc == 1)
    {
        printf("Введите имя файла:\n> ");
        gets(fileName);
    }
    else
        strcpy(fileName, argv[1]);
    
    FILE* file = fopen(fileName, "rb");
    if (!file)
    {
        printf("Файл не существует. Создать? Y/N\n> ");
        gets(command);
        if (command[0] == 'y' || command[0] == 'Y')
        {
            file = fopen(fileName, "wb+");
            if (!file)
            {
                printf("Не удалось создать файл!\n");
                return 1;
            }
            else
            {
                printf("Файл создан.\n");
            }
        }
        else
        {
            return 0;
        }
    }
    
    List list; // список пациентов
    list.readFromFile(file); // читаем его из файла
    
    command[0] = 0;
    while (command[0] != '8')
    {
        
        system("clear");
        puts(menu);
        gets(command);
        switch (command[0])
        {
            case '1':
                fclose(file);
                file = fopen(fileName, "wb+"); // Очищаем файл и пишем в него пациентов из списка
                list.writeToFile(file);
                    puts("Файл сохранен");
                break;
            case '2':
                command[0] = 0;
                viewPages(&list,list.getCount());
                break;
            case '3':
                addRecord(&list);
                break;
            case '4':
                editRecord(&list);
                break;
            case '5':
                deleteRecord(&list);
                break;
            case '6':
                requestLocation(&list);
                break;
            case '7':
                requestAge(&list);
                break;
            case '8':
                break;
        }
    }
    fclose(file);

    return 0;
}
