#pragma once
#include "../Logic Layer/clsBank User.h"
#include "../Logic Layer/clsCurrencyExchange.h"

class clsGetObjectIfExists
{
public:

    static clsBankClient GetClientIfExists(string & AccountNumber)
    {
        while(!clsBankClient::IsClientExists(AccountNumber))
        {
            cout << "\nThis account does not exist. Please try again.";
            AccountNumber = clsInputValidate<string>::Read("\nEnter the account number : ");
        }
    
        return clsBankClient::Find(AccountNumber);
    }

    static clsBankClient GetClientIfExists(string & FullName, string & PIN)
    {
        while(!clsBankClient::IsClientExists(FullName, PIN))
        {
            cout << "\nThis account does not exist. Please try again.";
            FullName = clsInputValidate<string>::Read("\nEnter the full name : ");
            PIN = clsInputValidate<string>::Read("Enter the PIN code : ");
        }
    
        return clsBankClient::Find(FullName, PIN);
    }

    static clsBankUser GetUserIfExists(string & Username)
    {
        while(!clsBankUser::IsUserExists(Username))
        {
            cout << "\nThis user does not exist; please try again.";
            Username = clsInputValidate<string>::Read("\nEnter the username : ");
        }

        return clsBankUser::Find(Username);
    }

    static clsBankUser GetUserIfExists(string & Username, string & Password)
    {
        while(!clsBankUser::IsUserExists(Username, Password))
        {
            cout << "\nThis user does not exist; please try again.";
            Username = clsInputValidate<string>::Read("\nEnter the username : ");
            Password = clsInputValidate<string>::Read("Enter the password : ");
        }

        return clsBankUser::Find(Username, Password);
    }

    static clsCurrencyExchange GetCurrencyIfExistsByCode(string & CurrencyCode)
    {
        while(!clsCurrencyExchange::IsCurrencyExistsByCode(CurrencyCode))
        {
            cout << "\nThis currency does not exist; please try again.";
            CurrencyCode = clsInputValidate<string>::Read("\nEnter the currency code : ");
        }

        return clsCurrencyExchange::FindByCode(CurrencyCode);
    }

    static clsCurrencyExchange GetCurrencyIfExistsByCountry(string & CountryName)
    {
        while(!clsCurrencyExchange::IsCurrencyExistsByCountry(CountryName))
        {
            cout << "\nThis currency does not exist; please try again.";
            CountryName = clsInputValidate<string>::Read("\nEnter the country name : ");
        }

        return clsCurrencyExchange::FindByCountry(CountryName);
    }
};