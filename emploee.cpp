//
//  emploee.cpp
//  CompanyInfo
//
//  Created by Аня Дубровина on 14.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#include "emploee.h"


#include <iostream>

Emploee::Emploee(Qualification qualificationType,const string &name):m_qualificationType(qualificationType),m_name(name)
{
}

Emploee::~Emploee()
{
}

string Emploee::getName() const
{
    return m_name;
}
bool Emploee::setTask(int taskNum,const string &/*name*/)
{
    return false;
}

void Emploee::getDoneTasks() const
{
    return;
}
bool Emploee::add(std::shared_ptr<Emploee> emploee)
{
    return false;
}
shared_ptr<Emploee> Emploee::findEmploee(const string &name) const
{
    return nullptr;
}
Qualification Emploee::getQualifiaction() const
{
    return m_qualificationType;
}

/////////////////////////////////
PersonEmploee::PersonEmploee(Qualification qualificationType,const string &name):Emploee(qualificationType,name)
{
}

bool PersonEmploee::setTask(int taskNum,const string &/*name*/)
{
    unordered_map<int, string> possibleTasks = addSpecialTasks(m_qualificationType);
    if(possibleTasks.find(taskNum) != possibleTasks.end())
    {
        std::cout<<m_name<<": готово!\n";//т.к. задачи выполняются мгновенно
        m_tasksDone.push_back(taskNum);
        return true;
    }
    else
    {
        std::cout<<"Сотрудник с данной квалификацией не может выполнить поставленную задачу!"<<endl;
        return false;
    }
}

void PersonEmploee::getDoneTasks() const
{
    cout<<getName()<<":"<<endl;
    if(m_tasksDone.size() == 0)
    {
        cout<<"нет задач"<<endl;
        return;
    }
    
    unordered_map<int, string> possibleTasks = addSpecialTasks(m_qualificationType);
    for(int task: m_tasksDone)
        cout<<possibleTasks[task]<<" - сделано"<<endl;
}

/////////////////////////////////
Department::Department(Qualification qualificationType,const string &name):Emploee(qualificationType,name)
{
}
/*Department::~Department()
{
}*/

bool Department::add(std::shared_ptr<Emploee> emploee)
{
    //добавляем подчиненного
    if(emploee)
    {
        m_subords.push_back(emploee);
        return true;
    }
    else
        return false;
    
    
}
bool Department::setTask(int taskNum,const string &name)
{
    cout<<m_name<<endl;
    //для отдела - по всем сотрудникам проходимся
    bool somebodyFound = false;
    
    int failedTasks = 0;
    for(auto emp : m_subords)
    {
        if(!emp)
            continue;
        if(emp->getName() == name || name.size() == 0)
        {
            if(!emp->setTask(taskNum))
                failedTasks++;
            
            somebodyFound = true;
        }
    }
    
    if(failedTasks > 0)
        cout<<"failed tasks:"<<failedTasks;
    
    if(name.size() == 0)
        return failedTasks == 0;
    else
    {
        if(!somebodyFound)
            cout<<"Сотрудник не найден!";
        
        return (somebodyFound && failedTasks == 0);
    }
}

void Department::getDoneTasks() const
{
    for(auto emp : m_subords)
    {
        if(emp)
            emp->getDoneTasks();
    }
}

shared_ptr<Emploee> Department::findEmploee(const string &name) const
{
    for(auto emp : m_subords)
    {
        if(emp && emp->getName() == name)
            return emp;
    }
    
    return nullptr;
}
