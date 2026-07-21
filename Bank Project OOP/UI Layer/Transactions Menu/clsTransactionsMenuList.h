#pragma once
#include "../clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsShowTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogsScreen.h"

class clsTransactionsMenuList : protected clsScreen
{
private:
    enum enTransaction { Deposit = 1, Withdraw, TotalBalance, Transfer, TransferLogs, ReturnToMainMenu };

    static void _PrintMenuList()
    {
        cout << "\n\n==================================================";
        cout << "\n\t      Transactions Menu List";
        cout << "\n==================================================";
        cout << "\n   [1] Deposit";
        cout << "\n   [2] Withdraw";
        cout << "\n   [3] Show Total Balance";
        cout << "\n   [4] Transfer";
        cout << "\n   [5] Transfer Logs";
        cout << "\n   [6] Return To Main Menu";
        cout << "\n==================================================";
    }

    static enTransaction _ReadNumberFromList()
    {
        short Num = clsInputValidate<short>::InputBetween(Deposit, ReturnToMainMenu, "\nChoose what you want to do? [1 to 6] : ");
        return static_cast<enTransaction> (Num);
    }

    static void _GoToTransactionsMenu()
    {
        cout << "\n\nPress Enter to return to the Transactions Menu...";
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.get();
    }

    static void _Deposit()
    {
        clsDepositScreen::DepositScreen();
    }

    static void _Withdraw()
    {
        clsWithdrawScreen::WithdrawScreen();
    }

    static void _ShowTotalBalance()
    {
        clsShowTotalBalanceScreen::ShowTotalBalanceScreen();
    }

    static void _Transfer()
    {
        clsTransferScreen::TransferScreen();
    }

    static void _TransferLogs()
    {
        clsTransferLogsScreen::TransferLogsScreen();
    }

    static void _PerformTransactionsMenuOption(enTransaction OP)
    {
        switch(OP)
        {
            case Deposit:
            {
                system("clear");
                _Deposit();
                _GoToTransactionsMenu();
                break;
            }

            case Withdraw:
            {
                system("clear");
                _Withdraw();
                _GoToTransactionsMenu();
                break;
            }

            case TotalBalance:
            {
                system("clear");
                _ShowTotalBalance();
                _GoToTransactionsMenu();
                break;
            }

            case Transfer:
            {
                system("clear");
                _Transfer();
                _GoToTransactionsMenu();
                break;
            }

            case TransferLogs:
            {
                system("clear");
                _TransferLogs();
                _GoToTransactionsMenu();
                break;
            }

            default:
                return;
        }
    }


public:
    static void TransactionsScreen()
    {
        while(true)
        {
            system("clear");
            _DrawScreenHeader("TRANSACTIONS SCREEN");

            _PrintMenuList();
            enTransaction OP = _ReadNumberFromList();

            if (OP == ReturnToMainMenu)
                break;

            _PerformTransactionsMenuOption(OP);
        }
    }
};