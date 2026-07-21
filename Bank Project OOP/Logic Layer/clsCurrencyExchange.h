#pragma once
#include "../Library/clsString.h"
#include <fstream>

class clsCurrencyExchange
{
private:
    string _CountryName, _CurrencyCode, _CurrencyName;
    double _Rate;
    enum enMode { EmptyMode, UpdateMode };
    enMode _Mode;

    inline static const string FilePath = "Data File/Currencies.txt";


    static clsCurrencyExchange _ConvertLineToCurrencyObject(const string & Line, const string & Separator = "#//#")
    {
        vector<string> Parts = clsString::SplitString(Line, Separator);

        if (Parts.size() != 4)
            throw invalid_argument("Error in Convert Line To Object");

        return clsCurrencyExchange(UpdateMode, Parts[0], Parts[1], Parts[2], stod(Parts[3]));
    }

    static vector<clsCurrencyExchange> _LoadDataFromFile()
    {
        vector<clsCurrencyExchange> vCurrencies;
        ifstream MyFile;
        MyFile.open(FilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while(getline(MyFile, Line))
            {
                vCurrencies.emplace_back(_ConvertLineToCurrencyObject(Line));
            }

            MyFile.close();
        }

        return vCurrencies;
    }

    string _ConvertCurrencyObjectToLine(const clsCurrencyExchange & C, const string & Separator = "#//#")
    {
        return (C._CountryName + Separator + C._CurrencyCode + Separator + C._CurrencyName + Separator + to_string(C._Rate));
    }

    bool _SaveDataToFile(const vector<clsCurrencyExchange> & vCurrencies)
    {
        ofstream MyFile;
        MyFile.open(FilePath);

        if (MyFile.is_open())
        {
            for (const clsCurrencyExchange & C : vCurrencies)
            {
                MyFile << _ConvertCurrencyObjectToLine(C) << endl;
            }

            MyFile.close();
            return true;
        }
        return false;
    }

    static clsCurrencyExchange _GetEmptyObject()
    {
        return clsCurrencyExchange(EmptyMode, "", "", "", 0);
    }

    bool _UpdateRate()
    {
        vector<clsCurrencyExchange> vCurrencies = _LoadDataFromFile();
        _CurrencyCode = clsString::UpperAllString(_CurrencyCode);

        bool Found = false;

        for (clsCurrencyExchange & C : vCurrencies)
        {
            if (C._CurrencyCode == _CurrencyCode)
            {
                C._Rate = _Rate;
                Found = true;
                break;
            }
        }

        if (!Found)
            return false;

        return _SaveDataToFile(vCurrencies);
    }

public:
    clsCurrencyExchange(enMode Mode, const string & Country, const string & Code, const string & Name, double Rate)
    {
        _Mode = Mode;
        _CountryName = Country;
        _CurrencyCode = Code;
        _CurrencyName = Name;
        _Rate = Rate;
    }


    string GetCountryName() const { return _CountryName; }
    string GetCurrencyCode() const { return _CurrencyCode; }
    string GetCurrencyName()const { return _CurrencyName; }
    double GetRate () const { return _Rate; }

    bool UpdateRate(double Rate)
    {
        if (this->IsEmpty() || Rate <= 0)
            return false;
        
        _Rate = Rate;
        return _UpdateRate();
    }


    void Print() const
    {
        cout << "\n========================================";
        cout << "\n   Country Name   : " << _CountryName;
        cout << "\n   Currency Code  : " << _CurrencyCode;
        cout << "\n   Currency Name  : " << _CurrencyName;
        cout << "\n   Rate (1$)      : " << _Rate;
        cout << "\n========================================";
    }

    bool IsEmpty() const
    {
        return (this->_Mode == EmptyMode);
    }

    static vector<clsCurrencyExchange> GetDataCurrencies()
    {
        return _LoadDataFromFile();
    }

    static clsCurrencyExchange FindByCode(const string & Code)
    {
        ifstream MyFile;
        MyFile.open(FilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            string UpperCode = clsString::UpperAllString(Code);

            while(getline(MyFile, Line))
            {
                clsCurrencyExchange Temp = _ConvertLineToCurrencyObject(Line);

                if (Temp._CurrencyCode == UpperCode)
                {
                    MyFile.close();
                    return Temp;
                }
            }

            MyFile.close();
        }

        return _GetEmptyObject();
    }

    static clsCurrencyExchange FindByCountry(const string & Country)
    {
        ifstream MyFile;
        MyFile.open(FilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            string UpperCountry = clsString::UpperFirstLetterOfEachWord(Country);

            while(getline(MyFile, Line))
            {
                clsCurrencyExchange Temp = _ConvertLineToCurrencyObject(Line);

                if (Temp._CountryName == UpperCountry)
                {
                    MyFile.close();
                    return Temp;
                }
            }

            MyFile.close();
        }

        return _GetEmptyObject();
    }

    static bool IsCurrencyExistsByCode(const string & Code)
    {
        return !(FindByCode(Code).IsEmpty());
    }
    
    static bool IsCurrencyExistsByCountry(const string & Country)
    {
        return !(FindByCountry(Country).IsEmpty());
    }

    static double CurrencyCalculator(double Amount, const clsCurrencyExchange & FromCurrency, const clsCurrencyExchange& ToCurrency)
    {
        if (FromCurrency.IsEmpty() || ToCurrency.IsEmpty() || Amount < 0)
            return -1;

        if (FromCurrency._Rate <= 0 || ToCurrency._Rate <= 0)
            return -1;

        double CurrencyInDollars = Amount / FromCurrency._Rate;
        return CurrencyInDollars * ToCurrency._Rate;
    }

};