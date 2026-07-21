#pragma once
#include "Main Menu/clsMainScreen.h"
#include "../Logic Layer/clsLoginRegister.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
    static void _SystemLocked()
    {
        system("clear");
        SetWidth(50, '=');
        cout << "\n   System locked after 3 failed tries.";
        cout << "\n   Please contact the admin for help." << endl;
        SetWidth(50, '=');
    }

    static bool _Login()
    {
        bool LoginFailed = false;
        short Count = 3;
        do
        {
            if (LoginFailed)
            {
                if (--Count == 0)
                {
                    _SystemLocked();
                    return false;
                }
                
                else
                {
                    cout << "\n\nLogin failed!\nInvalid username or password.";
                    cout << "\nYou have " << Count << " trial(s) left." << endl;
                }
            }
            
            string Username = clsInputValidate<string>::Read("\n\nEnter the username : ");
            string Password = clsInputValidate<string>::Read("Enter the password : ");

            CurrentUser = clsBankUser::Find(Username, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while(LoginFailed);

        clsLoginRegister Log(CurrentUser);
        Log.Save();
        
        clsMainScreen::MainScreen();
        return true;
    }

public:
    static bool LoginScreen()
    {
        system("clear");
        _DrawScreenHeader("LOGIN SCREEN");
        return _Login();
    }
};