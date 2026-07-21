#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank User.h"

class clsFindUserScreen : protected clsScreen
{
private:
    static void _FindUser()
    {
        string username = clsInputValidate<string>::Read("\nEnter the username : ");
        clsBankUser User = clsBankUser::Find(username);
        User.Print();
    }
    
public:
    static void FindUserScreen()
    {
        _DrawScreenHeader("FIND USER SCREEN");
        _FindUser();
    }
};