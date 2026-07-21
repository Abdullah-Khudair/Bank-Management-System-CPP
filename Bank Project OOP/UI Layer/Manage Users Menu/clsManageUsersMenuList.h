#pragma once
#include "../clsScreen.h"
#include "clsShowUsersScreen.h"
#include "clsFindUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsUpdateUserInfoScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsChangePasswordScreen.h"
#include "../../Library/clsInputValidate.h"

class clsManageUsersMenuList : protected clsScreen
{
private:
    enum enManageUsers { Show = 1, Find, AddNew, Update, Delete, ChangePassword, ReturnToMainMenu };

    static void _PrintMenuList()
    {
        cout << "\n\n==================================================";
        cout << "\n\t\tManage Users List";
        cout << "\n==================================================";
        cout << "\n   [1] Show Users List";
        cout << "\n   [2] Find User";
        cout << "\n   [3] Add New User";
        cout << "\n   [4] Update User Info";
        cout << "\n   [5] Delete User";
        cout << "\n   [6] Change Password for User";
        cout << "\n   [7] Return To Main Menu";
        cout << "\n==================================================";
    }

    static enManageUsers _ReadNumberFromList()
    {
        short Num = clsInputValidate<short>::InputBetween(Show, ReturnToMainMenu, "\nChoose what you want to do? [1 to 7] : ");
        return static_cast<enManageUsers> (Num);
    }

    static void _GoToManageUsersMenu()
    {
        cout << "\n\nPress Enter to return to the Manage Users Menu...";
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.get();
    }

    static void _ShowUsersListScreen()
    {
        clsShowUsersScreen::ShowUsersScreen();
    }

    static void _FindUserScreen()
    {
        clsFindUserScreen::FindUserScreen();
    }

    static void _AddNewUserScreen()
    {
        clsAddNewUserScreen::AddNewUserScreen();
    }

    static void _UpdateUserInfoScreen()
    {
        clsUpdateUserInfoScreen::UpdateUserInfoScreen();
    }

    static void _DeleteUserScreen()
    {
        clsDeleteUserScreen::DeleteUserScreen();
    }

    static void _ChangePasswordUser()
    {
        clsChangePasswordUserScreen::ChangePasswordUser();
    }

    static void _PerformManageUsersMenuOption(enManageUsers OP)
    {
        switch(OP)
        {
            case Show:
            {
                system("clear");
                _ShowUsersListScreen();
                _GoToManageUsersMenu();
                break;
            }

            case Find:
            {
                system("clear");
                _FindUserScreen();
                _GoToManageUsersMenu();
                break;
            }

            case AddNew:
            {
                system("clear");
                _AddNewUserScreen();
                _GoToManageUsersMenu();
                break;
            }

            case Update:
            {
                system("clear");
                _UpdateUserInfoScreen();
                _GoToManageUsersMenu();
                break;
            }

            case Delete:
            {
                system("clear");
                _DeleteUserScreen();
                _GoToManageUsersMenu();
                break;
            }

            case ChangePassword:
            {
                system("clear");
                _ChangePasswordUser();
                _GoToManageUsersMenu();
                break;
            }

            default:
                return;
        }
    }

public:
    static void ManageUsersScreen()
    {
        while(true)
        {
            system("clear");
            _DrawScreenHeader("MANAGE USERS SCREEN");
            
            _PrintMenuList();
            enManageUsers OP = _ReadNumberFromList();

            if (OP == ReturnToMainMenu)
                break;

            _PerformManageUsersMenuOption(OP);
        }
    }
};