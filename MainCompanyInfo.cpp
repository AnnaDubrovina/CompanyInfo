//
//  MainCompanyInfo.cpp
//  InfoCompany
//
//  Created by Аня Дубровина on 16.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#include "./MainCompanyInfo.h"
#include "./common.h"

#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>


MainCompanyInfo::MainCompanyInfo()
{
    
}
/*MainCompanyInfo::~MainCompanyInfo()
{
}*/
void MainCompanyInfo::parseCommand(const char command)
{
    if(command == 'l')
        loadCompanyStructure();
    else if(command == 't')
    {
        if(m_companyStructure.size() == 0)
        {
            cout<<"Сначала необходимо загрузить данные о сотрудниках!"<<endl;
            return;
        }
        
        setTask();
    }
    else if(command == 'r')
    {
        if(m_companyStructure.size() == 0)
        {
            cout<<"Сначала необходимо загрузить данные о сотрудниках!"<<endl;
            return;
        }
        
        getDoneTasksInfo();
    }
    else if(command == 'h')
        printMainCommands();
    else
        cout<<"Введена несуществующая команда!"<<endl;
    
}
void MainCompanyInfo::loadCompanyStructure()
{
    if(m_companyStructure.size() > 0)
        m_companyStructure.clear();
    
    /*string filePaths;//char expStr[1024];
  
    char expStr[2048];
    cout<<"Введите файлы со штатной структурой через пробел:"<<endl;
    cin.getline(expStr,sizeof(expStr));
    
    std::stringstream ss(expStr);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, ' '))
        elems.push_back(item);
    
    for(string fileName: elems)
        parseDepartmentFile(fileName);*/
        
    //getline( cin, dir );
    string dir;
    cout<<"введите путь до каталога с файлами со штатной структурой:";
    cin>>dir;
    DIR *dp = opendir(dir.c_str());
    if (dp == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return ;
    }
    
    string filepath;
    struct dirent *dirp;
    struct stat filestat;
    
    while ((dirp = readdir( dp )))
    {
        filepath = dir + "/" + dirp->d_name;
        
        if (stat( filepath.c_str(), &filestat ))
            continue;
        
        if (S_ISDIR( filestat.st_mode ))
            continue;
        
        cout << filepath << endl;
        parseDepartmentFile(filepath);

    }
    
    //closedir( dp );
}


void MainCompanyInfo::parseDepartmentFile(const string fileName)
{
    if(fileName.find(".csv") == string::npos)
        return;
    
    string buf = fileName.substr(fileName.find_last_of("/") + 1);
    buf.resize (buf.size () - 4);
    std::shared_ptr<Emploee> ptr_department= shared_ptr<Department>(new Department(Dep,buf));
    if(!ptr_department)
        return;
    
    ifstream fin;
    fin.open( fileName.c_str() );
    string line;
    while (std::getline(fin, line))
    {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(ss, item, ';'))
            elems.push_back(item);
      
        if(elems.size() == 2)
        {
            auto worker =createEmploee(elems);
            if(worker)
            {
                if(ptr_department->add(worker))
                    cout<<"сотрудник добавлен:"<<elems.at(0)<<" " <<elems.at(1)<<endl;
                else
                    cout<<"ошибка добавления :"<<elems.at(0)<<" " <<elems.at(1)<<endl;
            }
            else
                cout<<"неизвестнная квалификация :"<<elems.at(1);
        }
        else
            cout<<"Неполная информация о сотруднике:"<<line;
    }
    
    m_companyStructure.push_back(ptr_department);
}


shared_ptr<Emploee> MainCompanyInfo::createEmploee(const vector<string> &emploeeInfo)
{
    string surname = emploeeInfo.at(0);
    string profesion = emploeeInfo.at(1);
    
    auto iter = qualification.cbegin();
    auto iter_end = qualification.cend();
    while(iter!=iter_end)
    {
        if(iter->second.compare(profesion) ==0)
            return std::shared_ptr<PersonEmploee>(new PersonEmploee(iter->first,surname));
        
        
        ++iter;
    }
    
    return nullptr;
}

void MainCompanyInfo::setTask()
{
    string command_str;
    cout<<"a - для всего предприятия\nd - для отдела\np - для сотрудника"<<endl;
    cin >> command_str;
    if(command_str.size() > 1)
    {
        cout<<"Введена ошибочная команда"<<endl;
        return;
    }
    char command = command_str[0];
    if(command =='a')
    {
        int num;
        printTasks(Dep);
        cin >> num;
        for(auto d : m_companyStructure)
            d->setTask(num);
    }
    else if(command == 'd')
    {
        string department;
        cout<<"Название отдела:";
        cin>>department;
        
        std::shared_ptr<Emploee> depart = nullptr;
        for(auto d : m_companyStructure)
        {
            if(d->getName() == department)
            {
                depart = d;
                break;
            }
        }
        
        if(!depart)
        {
            cout<<"Отдел не найден!"<<endl;
            return;
        }
        
        int num;
        printTasks(depart->getQualifiaction());
        cin >> num;
        
        depart->setTask(num);
    }
    else if(command == 'p')
    {
        string department,surname;
        cout<<"Название отдела:"<<endl;//в разных отделах могут работать однофамильцы.
        cin>>department;
        cout<<"Фамилия сотрудника:"<<endl;
        cin>>surname;
        
        shared_ptr<Emploee> emploee = nullptr;
        for(auto d : m_companyStructure)
        {
            if(d->getName() == department)
            {
                emploee = d->findEmploee(surname);
                break;
            }
        }
        if(!emploee)
        {
            cout<<"Сотрудник не найден!";
            return;
        }
        
        int num;
        printTasks(emploee->getQualifiaction());
        cin >> num;

        if(!emploee->setTask(num))
            cout<<"Задача не выполнена!";
    }
}

void MainCompanyInfo::getDoneTasksInfo()
{
    for(auto emp:m_companyStructure)
        emp->getDoneTasks();
}
