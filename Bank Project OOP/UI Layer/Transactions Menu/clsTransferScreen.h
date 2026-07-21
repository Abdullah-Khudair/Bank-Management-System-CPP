#pragma once
#include "../clsScreen.h"
#include "../../Library/clsGetObjectIfExists.h"
#include "../../Logic Layer/clsTransferLog.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _Transfer()
    {
        string AccountNumber1 = clsInputValidate<string>::Read("\nEnter the account number to transfer from : ");
        clsBankClient FromClient = clsGetObjectIfExists::GetClientIfExists(AccountNumber1);
        FromClient.Print();

        string AccountNumber2 = clsInputValidate<string>::Read("\n\nEnter the account number to transfer to : ");
        clsBankClient ToClient = clsGetObjectIfExists::GetClientIfExists(AccountNumber2);
            
        while(FromClient.AccountNumber() == ToClient.AccountNumber())
        {
            cout << "\n\nYou cannot transfer to the same account; please try again.\n\n";

            AccountNumber2 = clsInputValidate<string>::Read("\nEnter the account number to transfer to : ");
            ToClient = clsGetObjectIfExists::GetClientIfExists(AccountNumber2);
        }
        ToClient.Print();

        float Amount = clsInputValidate<float>::Input("\n\nEnter the transfer amount : ");
        while (Amount <= 0 || Amount > FromClient.AccountBalance())
        {
            Amount = clsInputValidate<float>::Input("\nTransfer failed.\nPlease enter another amount: ");
        }
        
        char Answer;
        cout << "\n\nAre you sure you want to transfer this amount?  [y/n] : ";
        if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
        {
            if (FromClient.Transfer(Amount, ToClient))
            {
                cout << "\n\nTransfer completed successfully.";
                cout << "\nAccount [" << FromClient.AccountNumber() << "] balance is now : " << FromClient.AccountBalance();
                cout << "\nAccount [" << ToClient.AccountNumber() << "] balance is now: " << ToClient.AccountBalance() << endl;

                clsTransferLog Log(Amount, FromClient, ToClient);
                Log.Save();
            }
            else
                cout << "\n\nTransfer failed.\n"; 
        }   
} 

public:
    static void TransferScreen()
    {
        _DrawScreenHeader("TRANSFER SCREEN");
        _Transfer();
    }
};