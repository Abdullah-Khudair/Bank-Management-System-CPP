#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsBank Client.h"

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient & Client)
    {
        string name = clsInputValidate<string>::Read("\nEnter a Full Name : ");
        Client.FullName(name);
    
        string pin = clsInputValidate<string>::Read("Enter a PIN Code : ");
        Client.PIN(pin);
    
        string email = clsInputValidate<string>::Read("Enter an Email : ");
        Client.Email(email);
        
        string phone = clsInputValidate<string>::Read("Enter a Phone Number : ");
        Client.Phone(phone);
        
        float Balance = clsInputValidate<float>::Input("Enter an Account Balance : ");
        Client.AccountBalance(Balance);
    }
    
    static void _AddNewClient()
    {    
        string AccountNumber = clsInputValidate<string>::Read("\nEnter the account number you want to add : ");
        while(clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nThis account already exists.\n";
            AccountNumber = clsInputValidate<string>::Read("Please enter a different account : ");
        }
    
        clsBankClient Client = clsBankClient::GetAddNewClientObject(AccountNumber);
    
        _ReadClientInfo(Client);
    
        char Choice;
        cout << "\nAre you sure you want to add this client?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            clsBankClient::enSaveResults Result = Client.Save();
    
            if (Result == clsBankClient::svSucceeded)
                cout << "\n\nClient added successfully.\n";
    
            else if (Result == clsBankClient::svFailedAccountNumberExists)
                cout << "\n\nFailed to add the client because it already exists.\n";
            
            else
                cout << "\n\nUnable to save the client. Please fill in all required fields.\n";
        }
    }

public:
    static void AddNewClientScreen()
    {
        _DrawScreenHeader("ADD NEW CLIENT SCREEN");
        _AddNewClient();
    }
};