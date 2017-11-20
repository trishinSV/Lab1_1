//
//  List.cpp
//  Lab1_1
//
//  Created by Сергей on 15.03.16.
//  Copyright © 2016 Сергей. All rights reserved.
//

#include "List.hpp"
#define MAX_COMMAND_LENGTH 32

ListNode::ListNode(const Record& data, ListNode* next, ListNode* prev)
{
    this->data = data;
    this->next = next;
    this->prev = prev;
}

List::List()
{
    head = tail = current = 0; // список пуст, текущий - никакой
}

Record List::getCurrent() const
{
    Record fake;
    if (current == 0) // если текущий установлен неверно - исключение
        return fake;
    
    return current->data;       // иначе - возвращам его информационное поле
}


bool List::next()
{
    if (current != 0)
    {
        current = current->next; // переходим к следующему
        return true;
    }
    return false;
}

bool List::previous()
{
    if (current != 0)
    {
        current = current->prev; // предыдущему
        return true;
    }
    return false;
}


bool List::add(Record& r)
{
    ListNode* tmp = new ListNode(r, 0, 0);
    
    if (isEmpty())
        head = tail = tmp;
    
    else
    {
        ListNode* pos = findNodeToInsertAfter(r.name); // имем, после какого элемента вставить новый
        if (pos == 0) // если в начало
        {
            tmp->next = head; // за новым следует старая голова
            head->prev = tmp; // перед старой головой новый элемент
            head = tmp; // новый элемент - текущаяя голова
            return true; // добавлен
        }
        tmp->next = pos->next; // тогда не в начало
        if (pos->next != 0) // если нужно вставить в середину (за тем, после которго вставляем, есть другой элемент
            pos->next->prev = tmp; // этот другой указывает на новый (новый будет перед ним)
        else
            tail = tmp; // иначе - вставляет в конец, у нас новый хвост
        tmp->prev = pos; // перед новым элементом тот, за который мы его помещаем
        pos->next = tmp; // тот, за которым помещаем, указывает на новый (новый после него)
    }
    
    return true;
}

bool List::edit(char* name, Record& r)
{
        char command[MAX_COMMAND_LENGTH];
    char menu3[] = "\nB - назад\n";
    
    if (isEmpty())
        return false;
    ListNode* p = head;
    while (p != 0) // идём по списку
    {
        
          do  {
              
                int result = strcmp(p->data.name, name);
                if ( result == 0) // если совпадают (нашли её)
                {
                system("clear");
                printf("Тот? Y/N\n> ");
                p->data.print();
                puts(menu3);
                gets(command);
                }
              p = p->next;
              if(p==0)
                  command[0]='b';
            }
        
        while (command[0] != 'Y' and command[0] != 'y' and command[0] != 'B' and command[0] != 'b');
        
        if (command[0] == 'Y' or command[0] == 'y'){
            p = p->prev;
            ListNode* tmp = p;
            if (p == head) // если она первая
            {
                if (p->next != 0) // если после неё есть ещё пациент
                    p->next->prev = 0; // то пациент после не имеет перед собой людей
                head = p->next; // у нас новая голова - человек, стоящий после удаляемого
                delete tmp; // очищаем память
            }
            
            else if (p == tail) // Если удаляем с конца
            {
                tail->prev->next = 0; // он не единственный, перед ним кто-то есть, теперь этот кто-то не имеет людей после себя
                delete tmp;
                
            }
            else// Иначе удаляем из середины
            {
                p->next->prev = p->prev; // человек после удаляемого будет перед собой иметь человека, стоящего перед удаляемым
                p->prev->next = p->next;  // человек перед удаляемым будет после себя иметь того, кто стоит после удаляемого
                delete p;
                
            }
            return true; // нашли и удалили
        }

            
        command[0]=0;
   //     if (command[0] != 'N' or command[0] != 'n'){
   //         return true;}
     //           else p = p->next;
            }

    return false;
}


ListNode* List::findNodeToInsertAfter(char* r)
{
    if (isEmpty()) // Если пуст - то вставляем в начало
        return 0;
    
    ListNode* p = head; // Начинаем идти от головы
    while (p != 0)
    {
        int result = strcmp((p->data).name, r);   // сравниваем имя текущего пациента  и добавляемого
         if (result > 0) // если текущее название "больше" названия добавляемой, то вставим её перед этой текущей
            return p->prev;
        else
            p = p->next; // иначе идём по списку дальше
    }
    // если прошли весь список, то добавляем после хвоста
    return tail;
}


void Record::print()
{
    printf("| %22s | %6s | %10d | %20s | %8s |\n",name,gender,age,location, diagnos);
}

bool List::isEnd() const
{
    if (current == 0)
        return true;
    
    return false;
}

bool List::isStart() const
{
    if (current == head)
        return true;
    
    return false;
}

bool List::remove(char* name)
{
    // если пуст, то удалять нечего
    if (isEmpty())
        return false;
    
    ListNode* p = head;
    while (p != 0) // идём по списку
    {
        int result = strcmp(p->data.name, name);  // сравниваем название текущей и той, что нужно удалить
        if ( result == 0) // если совпадают (нашли её)
        {
            ListNode* tmp = p;
            if (p == head) // если она первая
            {
                if (p->next != 0) // если после неё есть ещё пациент
                    p->next->prev = 0; // то пациент после не имеет перед собой людей
                head = p->next; // у нас новая голова - человек, стоящий после удаляемого
                delete tmp; // очищаем память
            }

            else if (p == tail) // Если удаляем с конца
            {
                tail->prev->next = 0; // он не единственный, перед ним кто-то есть, теперь этот кто-то не имеет людей после себя
                delete tmp;
            
            }
            else// Иначе удаляем из середины
            {
                p->next->prev = p->prev; // человек после удаляемого будет перед собой иметь человека, стоящего перед удаляемым
                p->prev->next = p->next;  // человек перед удаляемым будет после себя иметь того, кто стоит после удаляемого
                delete p;

            }
            return true; // нашли и удалили
        }
        else
            p = p->next; // иначе, пока не нашли, идём дальше
    }
    
    return false;
}


void List::goToFirst()
{
    current = head; // текущий - голова
}

void List::goToLast()
{
    current = tail; // текущий - хвост
}

bool List::isEmpty() const
{
    return head == 0;
}

int List::getCount() const
{
    int count = 0;
    
    for (ListNode* p = head; p != 0; p = p->next, count++);
    
    return count;
}

List::~List()
{
    clear(); // есть метод, который очищает список, его и  вызываем
}

void List::clear()
{
    ListNode* p = head;
    ListNode* q = head;
    
    while (p != 0) // Идём по всем элементам
    {
        q = p; // запомнили текущий
        p = p->next; // перешли к следующему
        delete q; // удалили текущий
    }
    head = tail = current = 0; // присвоили 0 всем указателям, т.к. список пуст
}

void List::readFromFile(FILE* file)
{
    clear(); // очищаем список
    Record currentRecord;
    fseek(file, sizeof(int), SEEK_SET);
    for (;;)
    {
        if (fread(&currentRecord, sizeof(Record), 1, file) == 0)
            break;
        else
            add(currentRecord); // если прочитался пациент из файла, добавим его
    }
}


void List::writeToFile(FILE* file)
{
    char menu3[] = "\nB - назад\n";
    char command[MAX_COMMAND_LENGTH];
while (command[0] != 'B' and command[0] != 'b')
    {
    int size = getCount();
    goToFirst();
    fseek(file, 0, SEEK_SET);
    fwrite(&size, sizeof(int), 1, file);
    for (ListNode* p = head; p != 0; p = p->next) // идём по всему списку и записываем пациентов в файл
        fwrite(&(p->data), sizeof(Record), 1, file);
        system("clear");
    puts("Файл сохранен");
    puts(menu3);
    gets(command);
        
    }

}


