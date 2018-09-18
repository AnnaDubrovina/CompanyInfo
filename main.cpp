//
//  main.cpp
//  InfoCompany
//
//  Created by Аня Дубровина on 16.09.2018.
//  Copyright © 2018 Анна Дубровина. All rights reserved.
//

#include <iostream>
#include "./MainCompanyInfo.h"
#include "./common.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    printMainCommands();
    string command;
    MainCompanyInfo mainInfo;
    while(true)
    {
        cout << "Введите команду:";
        cin >>command;
        
        if(command.size() > 1)
        {
            cout<<"Введена ошибочная команда!";
            continue;
        }
        if(command[0] == 'e')
        {
            cout<<"Завершение работы...";
            return 0;
        }
    
        mainInfo.parseCommand(command[0]);
    }
    
    return 0;
}


