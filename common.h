//
//  common.cpp
//  CompanyInfo
//
//  Created by Аня Дубровина on 14.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//
#ifndef common_h
#define common_h

#include <unordered_map>
#include <string>

using namespace std;

//список квалификаций
enum Qualification{Dep,DepHead,Programmer,Tester,Writer,Accounter};

//квалификации с названиями
const unordered_map<Qualification, string> qualification = {{Dep,"Отдел"},{DepHead,"Начальник отдела"},{Programmer,"Разработчик"},{Tester,"Специалист тестирования"},{Writer,"Технический писатель"},{Accounter,"Бухгалтер"}};

//добавить задачи, специфичные для квалификации
unordered_map<int, string>  addSpecialTasks(Qualification qualificationType);

//вывести список задач для данной квалификации
void printTasks(Qualification qualif);
//вывести список основных команд
void printMainCommands();



#endif /* common_h */
