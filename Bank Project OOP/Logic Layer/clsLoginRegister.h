#pragma once
#include "clsBank User.h"

const string LoginRegisterPath = "Data File/Login Register.txt";

class clsLoginRegister
{
private:
    string _FullDate;
    string _Username;
    string _Password;
    short _Permission;
    inline static const short _EncryptKey = 7;

    static clsLoginRegister _ConvertLineToLoginRecord(string & Line, const string & Separator = "#//#")
    {
        vector<string> Vec = clsString::SplitString(Line, Separator);

        if (Vec.size() != 4)
            throw invalid_argument("Error, Convert Line Tp Record");

        return clsLoginRegister(Vec[0], Vec[1], clsUtil::DecryptText(Vec[2], _EncryptKey), stoi(Vec[3]));
    }

    string _ConvertLoginRecordToLine(const string & Separator = "#//#")
    {
        return (_FullDate + Separator + _Username + Separator + clsUtil::EncryptText(_Password, _EncryptKey) + Separator + to_string(_Permission));        
    }

    void _AppendToFile()
    {
        fstream MyFile;
        MyFile.open(LoginRegisterPath, ios::app);

        if(MyFile.is_open())
        {
            string Line = _ConvertLoginRecordToLine();
            MyFile << Line << endl;

            MyFile.close();
        }
    }

    static vector<clsLoginRegister> _LoadLoginRegisterData()
    {
        vector<clsLoginRegister> vRegisters;
        ifstream MyFile;
        MyFile.open(LoginRegisterPath);

        if (MyFile.is_open())
        {
            string Line = "";
            while(getline(MyFile, Line))
            {
                vRegisters.emplace_back(_ConvertLineToLoginRecord(Line));
            }

            MyFile.close();
        }

        return vRegisters;
    }


public:
    clsLoginRegister(const clsBankUser & User)
    {
        _FullDate = clsDate::GetSystemDateTimeString();

        _Username = User.Username();
        _Password = User.Password();
        _Permission = User.Permission();
    }

    clsLoginRegister(const string & DateTime, const string & Username, const string & Password, short Permission)
    {
        _FullDate = DateTime;
        _Username = Username;
        _Password = Password;
        _Permission = Permission;
    }


    string DateTime() const { return _FullDate; }
    string Username() const { return _Username; }
    string Password() const { return _Password; }
    short Permission() const { return _Permission; }


    void Save()
    {
        _AppendToFile();
    }

    static vector<clsLoginRegister> GetLoginRecords()
    {
        return _LoadLoginRegisterData();
    }

};