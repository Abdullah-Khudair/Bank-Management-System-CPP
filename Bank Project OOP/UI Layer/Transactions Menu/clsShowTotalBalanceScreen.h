#pragma once
#include "../../Logic Layer/clsBank Client.h"
#include "../../Library/clsUtil.h"
#include "../clsScreen.h"

class clsShowTotalBalanceScreen : protected clsScreen
{
private:
    static void _ShowOneClient(const clsBankClient & Client)
    {
        cout << "| " << left << setw(22) << Client.AccountNumber();
        cout << "| " << left << setw(22) << Client.FullName();
        cout << "| " << left << setw(16) << Client.AccountBalance() << "|";
    }

    static void _ShowTotalBalance(const vector<clsBankClient> & vClients)
    {
        cout << "\n"; SetWidth(67, '=');
        cout << "\n| " << left << setw(22) << "Account Number";
        cout << "| " << left << setw(22) << "Full Name";
        cout << "| " << left << setw(16) << "Account Balance" << "|\n";
        SetWidth(67, '=');
        cout << endl;
    
        if (vClients.size() == 0)
            cout << "\n\t\t\t\t\t  No Clients Available In The System!\n\n";
        
        else
        {
            for (const clsBankClient & C : vClients)
            {
                _ShowOneClient(C);
                cout << endl;
            }
        }
    
        SetWidth(67, '=');
    
        float Total = clsBankClient::GetTotalBalance();
        cout << "\n\n\t\t\t   Total Balance : " << Total;
        cout << "\n\t\t(" << clsUtil::ConvertNumberToText(Total) << ").\n";
    }

public:
    static void ShowTotalBalanceScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        _DrawScreenHeader("TOTAL BALANCE SCREEN", "\tShow Clients List (" + to_string(vClients.size()) + ") Clients");
        _ShowTotalBalance(vClients);
    }
};