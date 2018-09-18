//
//  emploee.hpp
//  CompanyInfo
//
//  Created by Аня Дубровина on 14.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#ifndef emploee_h
#define emploee_h

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "./common.h"

using namespace std;

//паттерн Composite

/////////////////////////////////////////////////////
class Emploee
{
public:
    
    virtual ~Emploee();
    virtual string getName() const;//получить наименование
    virtual bool setTask(int taskNum,const string &name = string());//поставить задачу (для составного объекта - если name не задано, то для всех частей)
    virtual void getDoneTasks() const;//получить список сделанных задач
    virtual Qualification getQualifiaction() const;//получить квалификацию
    
    virtual bool add(std::shared_ptr<Emploee> emploee);
    virtual shared_ptr<Emploee> findEmploee(const string &name) const;//найти сотрудника
    
protected:
    Emploee(Qualification qualificationType,const string &name);
    
    Qualification m_qualificationType;//квалификация
    string m_name;//имя или название
   
};

class PersonEmploee: public Emploee
{
public:
     PersonEmploee(Qualification qualificationType,const string &name);
     virtual bool setTask(int taskNum,const string &name = string()) override;
     virtual void getDoneTasks() const override;
    
private:
     vector<int> m_tasksDone;//список сделанных задач
};

/////////////////////////////////
class Department : public Emploee
{
public:
    Department(Qualification qualificationType,const string &name);
    //virtual ~Department();
    
    virtual bool add(std::shared_ptr<Emploee> emploee) override;
    virtual shared_ptr<Emploee> findEmploee(const string &name) const override;

    virtual bool setTask(int taskNum,const string &name = string()) override;
    virtual void getDoneTasks() const override;
    
private:
    vector<std::shared_ptr<Emploee>> m_subords;//список подчиненных
};

#endif /* emploee_h */
