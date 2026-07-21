#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsCurrencyExchange.h"
#include "../../Library/clsGetObjectIfExists.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _FindCurrency()
    {
        char Choice;
        cout << "\nDo you want to search using the currency code?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string Code = clsInputValidate<string>::Read("\nEnter the currency code : ");
            clsCurrencyExchange Currency = clsGetObjectIfExists::GetCurrencyIfExistsByCode(Code);
            Currency.Print();
            return;
        }
    
        cout << "\nDo you want to search using the country name?  [y/n] : ";
        if (cin >> Choice && (Choice == 'y' || Choice == 'Y'))
        {
            string Country = clsInputValidate<string>::Read("\nEnter a country name : ");
            clsCurrencyExchange Currency = clsGetObjectIfExists::GetCurrencyIfExistsByCountry(Country);
            Currency.Print();
            return;
        }
    
        cout << "\nNo other options are available. Please try again later.n";
    }

public:
    static void FindCurrencyScreen()
    {
        _DrawScreenHeader("FIND CURRENCY SCREEN");
        _FindCurrency();
    }
};