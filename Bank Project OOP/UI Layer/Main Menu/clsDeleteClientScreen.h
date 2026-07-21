#pragma once
#include "../clsScreen.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../../Logic Layer/clsBank Client.h"

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _DeleteClient()
    {
        string AccountNumber = clsInputValidate<string>::Read("\nEnter the account number : ");
        clsBankClient Client = clsGetObjectIfExists::GetClientIfExists(AccountNumber);
        Client.Print();
    
        char Choice;
        cout << "\n\nAre you sure you want to delete this account?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            if (Client.Delete())
                cout << "\n\nClient deleted successfully.\n";
            else
                cout << "\n\nError: Cannot delete this account.\n";
        }
    }

public:
    static void DeleteClientScreen()
    {
        _DrawScreenHeader("DELETE CLIENT SCREEN");
        _DeleteClient();
    }
};