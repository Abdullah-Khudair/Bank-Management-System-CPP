#pragma once
#include "../clsScreen.h"
#include "../../Logic Layer/clsCurrencyExchange.h"

class clsShowCurrenciesScreen : protected clsScreen
{
private:
    static void ShowOneCurrency(const clsCurrencyExchange & Currency)
    {
        cout << "| " << left << setw(40) << Currency.GetCountryName();
        cout << "| " << left << setw(15) << Currency.GetCurrencyCode();
        cout << "| " << left << setw(40) << Currency.GetCurrencyName();
        cout << "| " << left << setw(12) << Currency.GetRate() << "|";
    }

    static void _PrintAllCurrencies(const vector<clsCurrencyExchange> & vCurrencies)
    {
        cout << "\n"; SetWidth(120, '=');
        cout << "\n| " << left << setw(40) << "Country Name";
        cout << "| " << left << setw(15) << "Currency Code";
        cout << "| " << left << setw(40) << "Currency Name";
        cout << "| " << left << setw(12) << "Rate" << "|\n";
        SetWidth(120, '=');
        cout << endl;
    
        if (vCurrencies.size() == 0)
            cout << "\n\t\t\t\t\tNo Currencies Available In The System!\n\n";
    
        else
        {
            for (const clsCurrencyExchange & C : vCurrencies)
            {
                ShowOneCurrency(C);
                cout << endl;
            }
        }
        
        SetWidth(120, '=');
        cout << endl;
    }

public:
    static void ShowCurrenciesScreen()
    {
        vector<clsCurrencyExchange> vCurrencies = clsCurrencyExchange::GetDataCurrencies();

        _DrawScreenHeader("SHOW CURRENCIES SCREEN", "\tTotal Available Currencies (" + to_string(vCurrencies.size()) + ")");
        _PrintAllCurrencies(vCurrencies);
    }
};