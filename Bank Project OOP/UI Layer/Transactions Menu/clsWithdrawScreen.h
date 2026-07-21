#pragma once
#include "../../Logic Layer/clsBank Client.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../clsScreen.h"

class clsWithdrawScreen : protected clsScreen
{
private:
    static void _Withdraw()
    {
        string AccountNumber = clsInputValidate<string>::Read("\nEnter the account number : ");
        clsBankClient Client = clsGetObjectIfExists::GetClientIfExists(AccountNumber);
        Client.Print();
    
        float Amount = clsInputValidate<float>::Input("\n\nEnter the amount you want to withdraw : ");
        while (Amount <= 0 || Amount > Client.AccountBalance())
        {
            Amount = clsInputValidate<float>::Input("\nWithdrawal failed.\nPlease enter another amount: ");
        }

        char Choice;
        cout << "\n\nAre you sure you want to make a withdrawal from this account? [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\n\nWithdrawal completed successfully";
                cout << "\nAccount balance now is : " << Client.AccountBalance() << endl;
            }
            else
                cout << "\n\nWithdrawal failed.\n";
        }
    }

public:
    static void WithdrawScreen()
    {
        _DrawScreenHeader("WITHDRAW SCREEN");
        _Withdraw();
    }
};