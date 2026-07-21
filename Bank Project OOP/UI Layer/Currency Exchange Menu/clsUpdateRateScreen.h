#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsCurrencyExchange.h"
#include "../../Library/clsGetObjectIfExists.h"

class clsUpdateRateScreen : protected clsScreen
{
private:
    static void _UpdateRate()
    {
        string Code = clsInputValidate<string>::Read("\nEnter the currency code : ");
        clsCurrencyExchange Currency = clsGetObjectIfExists::GetCurrencyIfExistsByCode(Code);
        Currency.Print();

        char Answer;
        cout << "\nAre you sure you want to update the rate for this currency?  [y/n] : ";
        if (cin >> Answer && (Answer == 'y' || Answer == 'Y'))
        {
            double NewRate = clsInputValidate<double>::Input("\nEnter the new rate : ");
            if (Currency.UpdateRate(NewRate))
                cout << "\n\nUpdated successfully.\n";
            else
                cout << "\n\nFailed to update the rate; please try again.\n";
        }
    }

public:
    static void UpdateRateScreen()
    {
        _DrawScreenHeader("UPDATE RATE SCREEN");
        _UpdateRate();
    }
};