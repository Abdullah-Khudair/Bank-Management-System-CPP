#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank Client.h"

class clsShowClientsScreen : protected clsScreen
{
private:
    static void ShowOneClient(const clsBankClient & Client)
    {
        cout << "| " << left << setw(16) << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(15) << Client.PIN();
        cout << "| " << left << setw(30)  << Client.Email();
        cout << "| " << left << setw(20) << Client.Phone();
        cout << "| " << left << setw(16) << to_string(Client.AccountBalance() + '$') << "|";
    }

    static void _ShowAllClients(const vector<clsBankClient> & vClients)
    {   
        cout << "\n"; SetWidth(130, '=');
        cout << "\n| " << left << setw(16) << "Account Number";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(15) << "PIN Code";
        cout << "| " << left << setw(30) << "Email";
        cout << "| " << left << setw(20) << "Phone Number";
        cout << "| " << left << setw(16) << "Account Balance" << "|\n";
        SetWidth(130, '=');
        cout << endl;
    
        if (vClients.size() == 0)
            cout << "\n\t\t\t\t\t  No Clients Available In The System!\n\n";
    
        else
        {
            for (const clsBankClient & C : vClients)
            {
                ShowOneClient(C);
                cout << endl;
            }
        }
        
        SetWidth(130, '=');
        cout << endl;
    }

public:
    static void ShowClientsScreen()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        _DrawScreenHeader("SHOW CLIENTS SCREEN", "\tShow Clients List (" + to_string(vClients.size()) + ") Clients");
        _ShowAllClients(vClients);
    }
};