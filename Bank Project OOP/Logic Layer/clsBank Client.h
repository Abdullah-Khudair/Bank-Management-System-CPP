#pragma once
#include <fstream>
#include <iomanip>
#include "../Library/clsString.h"
#include "../Library/clsInputValidate.h"
#include "../Library/clsPerson.h"


const string ClientFilePath = "Data File/Clients List.txt";

class clsBankClient : public clsPerson
{
private:
    string _AccountNumber, _PinCode;
    float _AccountBalance;
    enum enMode { EmptyMode, UpdateMode, AddMode };
    enMode _Mode;


    static clsBankClient _ConvertLineToClientObject(const string & Line, const string & Separator = "#//#")
    {
        vector<string> Vec = clsString::SplitString(Line, Separator);

        if (Vec.size() != 6)
            throw invalid_argument("Error Convert Line To Client Object");

        return clsBankClient(UpdateMode, Vec[0], Vec[1], Vec[2], Vec[3], Vec[4], stof(Vec[5]));
    }

    string _ConvertClientObjectToLine(const clsBankClient & Client, const string & Separator = "#//#")
    {
        return Client._AccountNumber + Separator + Client.FullName() + Separator + Client._PinCode + Separator + Client.Email() + Separator + Client.Phone() + Separator + to_string(Client._AccountBalance);
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(EmptyMode, "", "", "", "", "", 0);
    }

    void _SaveClientsDataToFile(vector <clsBankClient> & vClients)
    {
        ofstream MyFile;
        MyFile.open(ClientFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            for(clsBankClient & i : vClients)
            {
                Line = _ConvertClientObjectToLine(i);
                MyFile << Line << endl;
            }

            MyFile.close();
        }
    }

    static vector<clsBankClient> _LoadClientsDataFromFile()
    {
        vector<clsBankClient> Vec;
        ifstream MyFile;
        MyFile.open(ClientFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                if (Line != "")
                    Vec.emplace_back(_ConvertLineToClientObject(Line));
            }

            MyFile.close();
        }

        return Vec;
    }

    void _Update()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (clsBankClient & i : vClients)
        {
            if (i._AccountNumber == this->_AccountNumber)
            {
                i = *this;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);
    }

    void _Add()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        vClients.emplace_back(*this);
        _SaveClientsDataToFile(vClients);
    }
    

public:
    clsBankClient(enMode Mode, const string & AccountNumber, const string & FullName, const string & PIN, const string & Email, const string & Phone, float AccountBalance)
        : clsPerson(FullName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PIN;
        _AccountBalance = AccountBalance;
    }


    string AccountNumber() const { return _AccountNumber; }

    void PIN(const string & PIN) { _PinCode = PIN; }
    string PIN() const { return _PinCode; }

    void AccountBalance(float AccBalance) { _AccountBalance = AccBalance; }
    float AccountBalance() const { return _AccountBalance; }


    bool IsEmpty() const
    {
        return (_Mode == EmptyMode);
    }

    void Print() const
    {
        cout << "\n========================================";
        cout << "\n   Account Number  : " << _AccountNumber;
        cout << "\n   Full Name       : " << FullName();
        cout << "\n   PIN Code        : " << _PinCode;
        cout << "\n   Email           : " << Email();
        cout << "\n   Phone           : " << Phone();
        cout << "\n   Account Balance : " << _AccountBalance;
        cout << "\n========================================";
    }

    static clsBankClient Find(const string & AccountNumber)
    {
        ifstream MyFile;
        MyFile.open(ClientFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client._AccountNumber == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(const string & FullName, const string & PIN)
    {
        ifstream MyFile;
        MyFile.open(ClientFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while(getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.FullName() == FullName && Client._PinCode == PIN)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static bool IsClientExists(const string & AccountNumber)
    {
        clsBankClient Client = Find(AccountNumber);
        return !(Client.IsEmpty());
    }

    static bool IsClientExists(const string & FullName, const string & PIN)
    {
        clsBankClient Client = Find(FullName, PIN);
        return !(Client.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(const string & AccNum)
    {
        return clsBankClient(AddMode, AccNum, "", "", "", "", 0);
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    enum enSaveResults { svFailedEmptyObject, svSucceeded, svFailedAccountNumberExists }; 

    enSaveResults Save()
    {
        switch (this->_Mode)
        {
            case UpdateMode:
                _Update();
                return svSucceeded;


            case AddMode:
                if (IsClientExists(this->_AccountNumber))
                    return svFailedAccountNumberExists;
                
                _Add();
                this->_Mode = UpdateMode;
                return svSucceeded;


            default:
                return svFailedEmptyObject;
        }
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();

        for (auto iter = vClients.begin(); iter != vClients.end(); ++iter)
        {
            if (iter->_AccountNumber == this->_AccountNumber)
            {
                vClients.erase(iter);
                _SaveClientsDataToFile(vClients);
                *this = _GetEmptyClientObject();
                return true;
            }
        }

        return false;
    }

    bool Deposit(float Amount)
    {
        if (Amount <= 0)
            return false;

        this->_AccountBalance += Amount;
        Save();
        return true;
    }

    bool Withdraw(float Amount)
    {
        if (Amount <= 0 || Amount > this->_AccountBalance)
            return false;

        this->_AccountBalance -= Amount;
        Save();
        return true;
    }

    bool Transfer(float Amount, clsBankClient & ToClient)
    {
        if (!Withdraw(Amount))
            return false;

        if (!ToClient.Deposit(Amount))
            return false;

        return true;
    }

    static float GetTotalBalance()
    {
        vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        float Sum = 0;

        for (clsBankClient & C : vClients)
        {
            Sum += C._AccountBalance;
        }

        return Sum;
    }
};