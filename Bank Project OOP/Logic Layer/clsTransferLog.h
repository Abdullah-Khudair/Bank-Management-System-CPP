#pragma once
#include "clsBank Client.h"
#include "../UI Layer/Global.h"

const string TransferFilePath = "Data File/Transfer Log.txt";

class clsTransferLog
{
private:
    string _DateTime, _FromAccount, _ToAccount, _Username;
    float _Amount, _FromBalance, _ToBalance;
    

    string _ConvertObjectToLine(const string & Separator = "#//#")
    {
        return (_DateTime + Separator + _FromAccount + Separator + _ToAccount + Separator + to_string(_Amount) + Separator + to_string(_FromBalance) + Separator + to_string(_ToBalance) + Separator + _Username);
    }

    void _AppendToFile()
    {
        fstream MyFile;
        MyFile.open(TransferFilePath, ios::app);

        if (MyFile.is_open())
        {
            MyFile << _ConvertObjectToLine() << endl;
            MyFile.close();
        }
    }

    static clsTransferLog _ConvertLineToObject(string & Line, const string & Separator = "#//#")
    {
        vector<string> Vec = clsString::SplitString(Line, Separator);

        if (Vec.size() != 7)
            throw invalid_argument("Error Convert Line To Transfer Log.");

        return clsTransferLog(Vec[0], Vec[1], Vec[2], stof(Vec[3]), stof(Vec[4]), stof(Vec[5]), Vec[6]);
    }

    static vector<clsTransferLog> _LoadDataFromFile()
    {
        vector<clsTransferLog> vLogs;
        ifstream MyFile;
        MyFile.open(TransferFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while(getline(MyFile, Line))
            {
                vLogs.emplace_back(_ConvertLineToObject(Line));
            }

            MyFile.close();
        }

        return vLogs;
    }


public:
    clsTransferLog(float Amount, const clsBankClient & FromClient, const clsBankClient & ToClient)
    {
        _DateTime = clsDate::GetSystemDateTimeString();
        
        _FromAccount = FromClient.AccountNumber();
        _ToAccount = ToClient.AccountNumber();
        
        _Amount = Amount;
        _FromBalance = FromClient.AccountBalance() - Amount;
        _ToBalance = ToClient.AccountBalance() + Amount;
        
        _Username = CurrentUser.Username();
    }

    clsTransferLog(const string & DateTime, const string & FromAccount, const string & ToAccount, float Amount, float FromBalance, float ToBalance, const string & Username)
    {
        _DateTime = DateTime;
        _FromAccount = FromAccount;
        _ToAccount = ToAccount;
        _Amount = Amount;
        _FromBalance = FromBalance;
        _ToBalance = ToBalance;
        _Username = Username;
    }


    string GetDateTime() const { return _DateTime; }
    string GetFromAccount() const { return _FromAccount; }
    string GetToAccount() const { return _ToAccount; }
    float GetAmount() const { return _Amount; }
    float GetFromBalance() const { return _FromBalance; }
    float GetToBalance() const { return _ToBalance; }
    string GetUsername() const { return _Username; }

    
    void Save()
    {
        _AppendToFile();
    }

    static vector<clsTransferLog> GetLogs()
    {
        return _LoadDataFromFile();
    }
};