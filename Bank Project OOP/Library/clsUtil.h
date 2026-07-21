#pragma once
#include <iostream>
#include <cstdlib>
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:
    static void Srand()
    {
        srand((unsigned) time(NULL));
    }

    static short GetRandomNumber(short From, short To)
    {
        short Random = rand() % (To - From + 1) + From;
        return Random;
    }

    static short SumReversedOrder(int Num)
    {
        short Sum = 0, Remainder = 0;
        while (Num > 0)
        {
            Remainder = Num % 10;
            Num /= 10;
            Sum += Remainder;
        }
        return Sum;
    }

    static int ReversNumber(int Num)
    {
        int revers = 0;
        short Remainder = 0;
        while (Num > 0)
        {
            Remainder = Num % 10;
            Num /= 10;
            revers = revers * 10 + Remainder;
        }
        return revers;
    }

    static short Frequency (int Num, short Digit)
    {
        short Remainder = 0,  Counter = 0;
        while (Num > 0)
        {
            Remainder = Num % 10;
            Num /= 10;
            if (Digit == Remainder)
                Counter ++;
        }
        return Counter;
    }

    static string EncryptText (string text, short Encryption_Key)
    {
        for (size_t i=0; i < text.length(); i++)
        {
            text[i] = static_cast <char> ( (short) text[i] + Encryption_Key);
        }
        return text;
    }
    
    static string DecryptText (string text, short Encryption_Key)
    {
        for (size_t i=0; i < text.length(); i++)
        {
            text[i] = static_cast <char> ( (short) text[i] - Encryption_Key);
        }
        return text;
    }                                

    enum enCharType { Digit = 1, CapitalLetter, SmallLetter, SpecialCharacter, MixChars };
    
    static char GetRandomCharacter (enCharType CharType)
    {
        if (CharType == MixChars)
            CharType = (enCharType) GetRandomNumber(1,3);
        
        switch (CharType)
        {
            case Digit:
                return static_cast <char> (GetRandomNumber (48, 57));

            case CapitalLetter:
                return GetRandomNumber (65, 90);
    
            case SmallLetter:
                return GetRandomNumber (97, 122);

            case SpecialCharacter:
                return GetRandomNumber (33, 47);
        
        default: return '?';
    }
}

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Str = "";
        for (short i = 1; i <= Length; i++)
        {
            Str += GetRandomCharacter(CharType);
        }

        return Str;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Str = "";
        for (short i = 1; i <= 4; i++)
        {
            Str += GenerateWord(CharType, 4) + '-';
        }

        Str.pop_back();
        return Str;
    }

    static void Swap(short & a, short & b)
    {
        short c = a;
        a = b;
        b = c;
    }

    static void Swap(double & a, double & b)
    {
        double c = a;
        a = b;
        b = c;
    }

    static void Swap(string & a, string & b)
    {
        string c = a;
        a = b;
        b = c;
    }

    static void Swap(clsDate & a, clsDate & b)
    {
        clsDate c = a;
        a = b;
        b = c;
    }

    static short ReadNumber (const string & Message)
    {
        short Num;
        while (true)
        {
            cout << Message;
            if (cin >> Num && cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                cout << "\nError,\n";
            }

            else
                return Num;
        }
    }
    
    static void ReadArray (short Arr[], short size)
    {
        cout << "\nEnter Array Elements:\n";
        for (short i=0; i < size; i++)
            Arr[i] = ReadNumber ("Element [" + to_string(i+1) + "] : ");
    }
    
    static void ReadRandomArray (short Arr[], short arrLength, short From, short To)
    {
        for (short i=0; i < arrLength; i++)
            Arr[i] = GetRandomNumber(From,To);
    }

    static void PrintArray (short Arr[], short size)
    {
        cout << "\nOriginal Array : { ";
        for (short i=0; i < size; i++)
            cout << Arr[i] << "  ";
        cout << "}\n";
    }
    
    static short Times_Repeated (short Arr[], short size, short Number)
    {
        short count = 0;
        for (short i=0; i<size; i++)
        {
            if (Number == Arr[i])
                count++;
        }
        return count;
    }

    static short MaxNumberInArray (short Arr[], short arrLength)
    {
        short Max = Arr[0];
        for (short i=1; i < arrLength; i++)
            if (Arr[i] > Max)
                Max = Arr[i];
        
        return Max;
    }
    
    static short MinNumberInArray (short Arr[], short arrLength)
    {
        short Min = Arr[0];
        for (short i=1; i < arrLength; i++)
            if (Min > Arr[i])
                Min = Arr[i];
        
        return Min;
    }

    static void ShuffleArray (short Arr[], short arrSize)
    {
        for (short i=0; i < arrSize; i++)
        {
            Swap (Arr[GetRandomNumber(1, arrSize)-1], Arr[GetRandomNumber(1, arrSize)-1]);
        }
    }

    static short FindNumberPositionInArray (short Arr[], short arrSize, short Num)
    {
        for (short i=0; i < arrSize; i++)
        {
            if (Num == Arr[i])
                return i;
        }
        return -1;
    }

    static bool CheckNumberInArray (short Arr[], short arrSize, short Num)
    {
        return (FindNumberPositionInArray(Arr, arrSize, Num) != -1);
    }

    static string Tabs(short Length = 1)
    {
        string Tabs = "";
        for (short i = 1; i <= Length; i++)
        {
            Tabs += '\t';
        }

        return Tabs;
    }

    static string ConvertNumberToText (long long int Num)
    {
        if (Num == 0)
            return "";
    
        if (Num > 0 && Num < 20)
        {
            string Arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
            return Arr[Num];
        }
    
        if (Num > 19 && Num < 100)
        {
            string Arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return Arr[Num / 10] + ' ' + ConvertNumberToText(Num % 10);
        }
    
        if (Num > 99 && Num < 1000)
        {
            return ConvertNumberToText(Num / 100) + " Hundred " + ConvertNumberToText(Num % 100);
        }
    
        if (Num > 999 && Num < 10000)
        {
            return ConvertNumberToText(Num / 1000) + " Thousand " + ConvertNumberToText(Num % 1000);
        }
    
        if (Num > 9999 && Num < 1000000)
        {
            return ConvertNumberToText(Num / 1000) + " Thousands " + ConvertNumberToText(Num % 1000);
        }
    
        if (Num > 999999 && Num < 1000000000)
        {
            return ConvertNumberToText(Num / 1000000) + " Million " + ConvertNumberToText(Num % 1000000);
        }
    
        if (Num > 999999999 && Num < 1000000000000)
        {
            return ConvertNumberToText(Num / 1000000000) + " Billion " + ConvertNumberToText(Num % 1000000000);
        }
    
        return "Exceeded the allowed number";
    }

};