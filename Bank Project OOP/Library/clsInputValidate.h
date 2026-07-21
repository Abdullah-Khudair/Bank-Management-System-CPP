#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;


template <typename Type>

class clsInputValidate
{
public:
    static bool IsNumberBetween(Type Num, Type From, Type To)
    {
        return (Num >= From && Num <= To);
    }

    static Type Input(const string & Message = "Enter a Number : ", const string & ErrorMessage = "Invalid Number, please enter a valid one : ")
    {
        Type Num = 0;
        cout << Message;
        while(true)
        {
            if (cin >> Num)
                return Num;

            cin.clear();
            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
            cout << ErrorMessage;
        }
        
        return Num;
    }

    static string Read(const string & Message = "Enter a String : ")
    {
        string Text;
        cout << Message;
        getline(cin >> ws, Text);
        return Text;
    }

    static Type InputBetween(Type From, Type To, const string & Message = "Enter a Number : ", const string & ErrorMessage = "Invalid Number, please enter a valid one between ")
    {
        Type Num = Input(Message);
        while (!IsNumberBetween(Num, From, To))
        {
            cout << ErrorMessage << From << " to " << To << endl;
            Num = Input(Message);
        }
        return Num;
    }

    static bool IsDateBetween(const clsDate & Date, const clsDate & From, const clsDate & To)
    {
        if (clsDate::IsDate1AfterDate2(From, To))
            return IsDateBetween(Date, To, From);

        return clsDate::IsDateWithinPeriod(Date, From, To);
    }
};