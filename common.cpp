//
//  common.cpp
//  InfoCompany
//
//  Created by Аня Дубровина on 16.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#include <stdio.h>
#include "common.h"
#include <iostream>

//добавить задачи, специфичные для квалификации
unordered_map<int, string> addSpecialTasks(Qualification qualificationType)
{
    unordered_map<int, string> taskMap;
    taskMap.insert({1, "уйти в отпуск"});//общие для всех сотрудников задачи
    taskMap.insert({0, "убрать рабочее место"});
    
    switch(qualificationType)
    {
        case Dep:
        case DepHead: return taskMap;
        case Programmer:
        {
            taskMap.insert({2,"программировать"});
            taskMap.insert({3,"проектировать"});
            
        }break;
        case Tester:
        {
            taskMap.insert({5,"тестировать"});
            taskMap.insert({6,"составлять тестовые планы"});
            
        }break;
        case Writer:
        {
            taskMap.insert({4,"переводить тексты"});
            
        }break;
        case Accounter:
        {
            taskMap.insert({7,"начислить зарплату"});
            taskMap.insert({8,"составить квартальный отчет"});
            
        }break;
        default:return taskMap;
    }
    
    return taskMap;
}

void printTasks()
{
 
}

void printMainCommands()
{
    std::cout << "Список команд:\nl - загрузить данные о сотрудниках и отделах\nt - поставить задачу\nr - получить отчеты\ne - завершение работы\nh - список команд"<<endl;
}
void printTasks(Qualification qualif)
{
    auto tasks = addSpecialTasks(qualif);
    if(tasks.size() == 0)
    {
        std::cout<<"Нет доступных задач!";
        return;
    }
    for(auto task :tasks)
        std::cout<<task.first<<" - "<<task.second<<endl;
    
}
