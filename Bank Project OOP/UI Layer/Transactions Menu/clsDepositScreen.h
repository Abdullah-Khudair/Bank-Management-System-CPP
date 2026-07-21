#pragma once
#include "../../Logic Layer/clsBank Client.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../clsScreen.h"

class clsDepositScreen : protected clsScreen
{
private:
    static void _Deposit()
    {
        string AccountNumber = clsInputValidate<string>::Read("\nEnter the account number : ");
        clsBankClient Client = clsGetObjectIfExists::GetClientIfExists(AccountNumber);
        Client.Print();
    
        float Amount = clsInputValidate<float>::Input("\n\nEnter the amount you want to deposit : ");
        while (Amount <= 0)
        {
            Amount = clsInputValidate<float>::Input("\nDeposit failed.\nPlease enter another amount: ");
        }
        
        char Choice;
        cout << "\n\nAre you sure you want to make a deposit to this account? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            if (Client.Deposit(Amount))
            {
                cout << "\n\nDeposit completed successfully";
                cout << "\nAccount balance now is : " << Client.AccountBalance() << endl;
            }
            else
                cout << "\n\nDeposit failed.\n";
        }
    }

public:
    static void DepositScreen()
    {
        _DrawScreenHeader("DEPOSIT SCREEN");
        _Deposit();
    }
};