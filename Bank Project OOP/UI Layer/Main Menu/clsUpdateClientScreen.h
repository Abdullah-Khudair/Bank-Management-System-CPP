#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank Client.h"
#include "../../Library/clsGetObjectIfExists.h"

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadNewInfoForClient(clsBankClient & Client)
    {
        char Choice;
    
        cout << "\nDo you want to change the name? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string FullName = clsInputValidate<string>::Read("Enter a full name : ");
            Client.FullName(FullName);
        }
    
        cout << "\nDo you want to change the PIN code? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string PIN = clsInputValidate<string>::Read("Enter a PIN code : ");
            Client.PIN(PIN);
        }
    
        cout << "\nDo you want to change the email? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string Email = clsInputValidate<string>::Read("Enter an email : ");
            Client.Email(Email);
        }
    
        cout << "\nDo you want to change the phone? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string Phone = clsInputValidate<string>::Read("Enter a Phone : ");
            Client.Phone(Phone);
        }
        
        cout << "\nDo you want to change the account balance? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            float Balance = clsInputValidate<float>::Input("Enter an account balance : ");
            Client.AccountBalance(Balance);
        }
    }
    
    static void _UpdateClient()
    {
        string AccountNumber = clsInputValidate<string>::Read("\nEnter the account number : ");
        clsBankClient Client = clsGetObjectIfExists::GetClientIfExists(AccountNumber);
        Client.Print();
    
        char Choice;
        cout << "\n\nAre you sure you want to update the information for this client?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            _ReadNewInfoForClient(Client);
    
            if (Client.Save() == clsBankClient::svSucceeded)
                cout << "\n\nClient updated successfully.\n";
            else
                cout << "\n\nFailed to save the account because the required information is missing.\n";
        }
    }
   
public:
    static void UpdateClientScreen()
    {
        _DrawScreenHeader("UPDATE CLIENT INFO SCREEN");
        _UpdateClient();
    }
};