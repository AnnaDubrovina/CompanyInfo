//
//  MainCompanyInfo.hpp
//  InfoCompany
//
//  Created by Аня Дубровина on 16.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#ifndef MainCompanyInfo_hpp
#define MainCompanyInfo_hpp

#include <stdio.h>
#include "./emploee.h"

using namespace std;

class MainCompanyInfo
{
public:
    MainCompanyInfo();
    //~MainCompanyInfo();
    
    void parseCommand(const char command);
       
private:

    vector<shared_ptr<Emploee> > m_companyStructure;
    
    void loadCompanyStructure();
    void getDoneTasksInfo();
    void parseDepartmentFile(const string fileName);
    void setTask();
    shared_ptr<Emploee> createEmploee(const vector<string> &emploeeInfo);
    
};
#endif /* MainCompanyInfo_hpp */
