#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsCurrencyExchange.h"
#include "../../Library/clsGetObjectIfExists.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static void _CurrencyCalculator()
    {
        string FromCode = clsInputValidate<string>::Read("\nEnter the first currency code : ");
        clsCurrencyExchange Currency1 = clsGetObjectIfExists::GetCurrencyIfExistsByCode(FromCode);

        string ToCode = clsInputValidate<string>::Read("\nEnter the second currency code : ");
        clsCurrencyExchange Currency2 = clsGetObjectIfExists::GetCurrencyIfExistsByCode(ToCode);
    
        double Amount = clsInputValidate<double>::Input("\nEnter the amount to exchange : ");
        
        double Exchange = clsCurrencyExchange::CurrencyCalculator(Amount, Currency1, Currency2);
        if (Exchange == -1)
            cout << "\nFailed to calculate exchange rate.\n";
        else
            cout << "\n" << Amount << " " << Currency1.GetCurrencyCode() << " = " << Exchange << " " << Currency2.GetCurrencyCode() << endl;
    }

public:
    static void CurrencyCalculatorScreen()
    {
        char Answer;
        do
        {
            system("clear");
            _DrawScreenHeader("CURRENCY CALCULATOR SCREEN");
            _CurrencyCalculator();

            cout << "\n\nDo you want perform another calculation?  [y/n] : ";
        } while(cin >> Answer && (Answer == 'y' || Answer == 'Y'));
    }
};