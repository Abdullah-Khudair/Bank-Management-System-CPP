#pragma once
#include "clsShowClientsScreen.h"
#include "clsFindClientScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsLoginRegisterScreen.h"
#include "../Transactions Menu/clsTransactionsMenuList.h"
#include "../Manage Users Menu/clsManageUsersMenuList.h"
#include "../Currency Exchange Menu/clsCurrencyExchangeMenuList.h"
#include "../Global.h"
#include "../clsScreen.h"
#include "../../Library/clsInputValidate.h"


class clsMainScreen : protected clsScreen
{
private:
    enum enOptions { Show = 1, Find, AddNew, Update, Delete, Transactions, ManageUser, LoginRegister, CurrencyExchange, Logout };

    static void _PrintMainMenuList()
    {
        cout << "\n\n==================================================";
        cout << "\n\t\t  Main Menu List";
        cout << "\n==================================================";
        cout << "\n   [1] Show Clients List";
        cout << "\n   [2] Find Client";
        cout << "\n   [3] Add New Client";
        cout << "\n   [4] Update Client Info";
        cout << "\n   [5] Delete Client";
        cout << "\n   [6] Transactions";
        cout << "\n   [7] Manage Users";
        cout << "\n   [8] Login Register";
        cout << "\n   [9] Currency Exchange";
        cout << "\n  [10] Logout";
        cout << "\n==================================================";
    }

    static enOptions _ReadNumberFromList()
    {
        short Num = clsInputValidate<short>::InputBetween(Show, Logout, "\nChoose what you want to do? [1 to 10] : ");

        return static_cast<enOptions> (Num);
    }

    static void _GoToMainMenu()
    {
        cout << "\n\nPress Enter to return to the Main Menu...";
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.get();
    }

    static void _AccessDenied()
    {
        SetWidth(50, '=');
        cout << "\n  Access Denied, \n  You don't have permission to do this, \n  Please contact your admin." << endl;
        SetWidth(50, '=');
        cout << endl;
    }

    static void _ShowClientsListScreen()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::ShowClients))
        {
            clsShowClientsScreen::ShowClientsScreen();
        }
        
        else
            _AccessDenied();
    }

    static void _FindClientScreen()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::FindClient))
        {
            clsFindClientScreen::FindClientScreen();
        }
        
        else
            _AccessDenied();
    }

    static void _AddNewClientScreen()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::AddClient))
        {
            clsAddNewClientScreen::AddNewClientScreen();
        }

        else
            _AccessDenied();
    }

    static void _UpdateClientInfoScreen()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::UpdateClient))
        {
            clsUpdateClientScreen::UpdateClientScreen();
        }

        else
            _AccessDenied();    
}

    static void _DeleteClientScreen()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::DeleteClient))
        {
            clsDeleteClientScreen::DeleteClientScreen();
        }

        else
            _AccessDenied();
    }

    static void _TransactionsMenuList()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::Transactions))
        {
            clsTransactionsMenuList::TransactionsScreen();
        }

        else
        {
            system("clear");
            _AccessDenied();
            _GoToMainMenu();
        }
    }

    static void _ManageUsersMenuList()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::ManageUser))
            clsManageUsersMenuList::ManageUsersScreen();

        else
        {
            system("clear");
            _AccessDenied();
            _GoToMainMenu();
        }
    }

    static void _ShowLoginRegister()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::LoginRegister))
        {
            clsLoginRegisterScreen::ShowLoginRegisterScreen();
        }

        else
            _AccessDenied();
    }

    static void _CurrencyExchangeMenuList()
    {
        if (CurrentUser.IsHasPermission(clsBankUser::CurrencyExchange))
            clsCurrencyExchangeMenuList::CurrencyExchangeMenuList();

        else
        {
            system("clear");
            _AccessDenied();
            _GoToMainMenu();
        }
    }

    static void _Logout()
    {
        CurrentUser = clsBankUser::Find("", "");
    }

    static void _PerformMainMenuOption(enOptions OP)
    {
        switch(OP)
        {
            case Show:
            {
                system("clear");
                _ShowClientsListScreen();
                _GoToMainMenu();
                break;
            }

            case Find:
            {
                system("clear");
                _FindClientScreen();
                _GoToMainMenu();
                break;
            }

            case AddNew:
            {
                system("clear");
                _AddNewClientScreen();
                _GoToMainMenu();
                break;
            }

            case Update:
            {
                system("clear");
                _UpdateClientInfoScreen();
                _GoToMainMenu();
                break;
            }

            case Delete:
            {
                system("clear");
                _DeleteClientScreen();
                _GoToMainMenu();
                break;
            }

            case Transactions:
            {
                _TransactionsMenuList();
                break;
            }

            case ManageUser:
            {
                _ManageUsersMenuList();
                break;
            }

            case LoginRegister:
            {
                system("clear");
                _ShowLoginRegister();
                _GoToMainMenu();
                break;
            }

            case CurrencyExchange:
            {
                _CurrencyExchangeMenuList();
                break;
            }

            case Logout:
                _Logout();
        }
    }

public:
    static void MainScreen()
    {
        enOptions OP;
        do
        {
            system("clear");
            _DrawScreenHeader("MAIN SCREEN", "Welcome to the Bank Management System");

            _PrintMainMenuList();
            OP = _ReadNumberFromList();

            _PerformMainMenuOption(OP);
        } while(OP != Logout);
    }

};