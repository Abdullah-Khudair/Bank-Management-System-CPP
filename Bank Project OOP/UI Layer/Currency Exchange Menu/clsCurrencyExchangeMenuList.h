#pragma once
#include "../clsScreen.h"
#include "clsShowCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "../../Library/clsInputValidate.h"


class clsCurrencyExchangeMenuList : protected clsScreen
{
private:
    enum enOption { ShowCurrencies = 1, FindCurrency, UpdateRate, CurrencyCalculator, ReturnToMainMenu };

    static void _PrintMenuList()
    {
        cout << "\n\n==================================================";
        cout << "\n\t      Currency Exchange Menu";
        cout << "\n==================================================";
        cout << "\n   [1] Show List Currencies";
        cout << "\n   [2] Find Currency";
        cout << "\n   [3] Update Rate";
        cout << "\n   [4] Currency Calculator";
        cout << "\n   [5] Return To Main Menu";
        cout << "\n==================================================";
    }

    static enOption _ReadNumberFromList()
    {
        short Num = clsInputValidate<short>::InputBetween(ShowCurrencies, ReturnToMainMenu, "\nChoose what you want to do? [1 to 5] : ");
        return static_cast<enOption> (Num);
    }

    static void _GoToCurrencyExchangeMenu()
    {
        cout << "\n\nPress Enter to return to the Currency Exchange Menu...";
        cin.ignore(numeric_limits <streamsize> ::max(), '\n');
        cin.get();
    }

    static void _ShowCurrencies()
    {
        clsShowCurrenciesScreen::ShowCurrenciesScreen();
    }

    static void _FindCurrency()
    {
        clsFindCurrencyScreen::FindCurrencyScreen();
    }

    static void _UpdateRate()
    {
        clsUpdateRateScreen::UpdateRateScreen();
    }

    static void _CurrencyCalculator()
    {
        clsCurrencyCalculatorScreen::CurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenuOption(enOption OP)
    {
        switch(OP)
        {
            case ShowCurrencies:
            {
                system("clear");
                _ShowCurrencies();
                _GoToCurrencyExchangeMenu();
                break;
            }

            case FindCurrency:
            {
                system("clear");
                _FindCurrency();
                _GoToCurrencyExchangeMenu();
                break;
            }

            case UpdateRate:
            {
                system("clear");
                _UpdateRate();
                _GoToCurrencyExchangeMenu();
                break;
            }

            case CurrencyCalculator:
            {
                _CurrencyCalculator();
                _GoToCurrencyExchangeMenu();
                break;
            }

            default:
                return;
        }
    }

public:
    static void CurrencyExchangeMenuList()
    {
        enOption OP;
        do
        {
            system("clear");
            _DrawScreenHeader("CURRENCY EXCHANGE SCREEN");

            _PrintMenuList();
            OP = _ReadNumberFromList();

            if (OP == ReturnToMainMenu)
                break;

            _PerformCurrencyExchangeMenuOption(OP);
        } while(OP != ReturnToMainMenu);
    }
};