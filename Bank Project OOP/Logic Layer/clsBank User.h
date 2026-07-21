#pragma once
#include "clsBank Client.h"
#include "../Library/clsUtil.h"
#include "clsCurrencyExchange.h"

class clsBankUser 
{
private:
    string _Username, _Password;
    short _Permission;
    enum enMode { EmptyMode, UpdateMode, AddMode };
    enMode _Mode;

    inline static const string UserFilePath = "Data File/Users List.txt";
    inline static const short _EncryptKey = 7;


    static clsBankUser _ConvertLineToUserObject(string & Line, const string & Separator = "#//#")
    {
        vector<string> Vec = clsString::SplitString(Line, Separator);

        if (Vec.size() != 3)
            throw invalid_argument("Error In Convert Line To User Object.");

        return clsBankUser(UpdateMode, Vec[0], clsUtil::DecryptText(Vec[1], _EncryptKey), stoi(Vec[2]));
    }

    string _ConvertUserObjectToLine(const clsBankUser & User, const string & Separator = "#//#") const
    {
        return (User._Username + Separator + clsUtil::EncryptText(User._Password, _EncryptKey) + Separator + to_string(User._Permission));
    }

    static vector<clsBankUser> _LoadUsersDataFromFile()
    {
        vector<clsBankUser> vUsers;
        ifstream Myfile;
        Myfile.open(UserFilePath);

        if (Myfile.is_open())
        {
            string Line = "";
            while(getline(Myfile, Line))
            {
                vUsers.emplace_back(_ConvertLineToUserObject(Line));
            }

            Myfile.close();
        }
        return vUsers;
    }

    void _SaveUsersDataToFile(const vector<clsBankUser> & vUsers)
    {
        ofstream MyFile;
        MyFile.open(UserFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            for (const clsBankUser & U : vUsers)
            {
                Line = _ConvertUserObjectToLine(U);
                MyFile << Line << endl;
            }

            MyFile.close();
        }
    }

    static clsBankUser _GetEmptyObject()
    {
        return (clsBankUser(EmptyMode, "", "", Nothing));
    }

    void _Update()
    {
        vector<clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (clsBankUser & U : vUsers)
        {
            if (U._Username == this->_Username)
            {
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);
    }

    void _AddNew()
    {
        vector<clsBankUser> vUsers = _LoadUsersDataFromFile();
        vUsers.emplace_back(*this);
        _SaveUsersDataToFile(vUsers);
    }


public:
    clsBankUser(enMode Mode, const string & Username, const string & Password, short Permission)
    {
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permission = Permission;
    }


    string Username() const { return _Username; }

    void Password(const string & Password) { _Password = Password; }
    string Password() const { return _Password; }

    void Permission(short Permission) { _Permission = Permission; }
    short Permission() const { return _Permission; }


    enum enPermission { All = -1, Nothing = 0, ShowClients = 1, FindClient = 2, AddClient = 4, UpdateClient = 8, DeleteClient = 16, Transactions = 32, ManageUser = 64, LoginRegister = 128, CurrencyExchange = 256 };
    
    void Print() const
    {
        cout << "\n========================================";
        cout << "\n   Username   : " << _Username;
        cout << "\n   Password   : " << _Password;
        cout << "\n   Permission : " << _Permission;
        cout << "\n========================================";
    }

    bool IsEmpty() const
    {
        return (this->_Mode == EmptyMode);
    }

    static clsBankUser Find(const string & Username)
    {
        ifstream MyFile;
        MyFile.open(UserFilePath);

        if (MyFile.is_open())
        {
            string Line = "";
            while(getline(MyFile, Line))
            {
                clsBankUser User = _ConvertLineToUserObject(Line);
                if (User._Username == Username)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyObject();
    }

    static clsBankUser Find(const string & Username, const string & Password)
    {
        clsBankUser User = Find(Username);

        if (!User.IsEmpty() && User._Password == Password)
            return User;

        return _GetEmptyObject();
    }

    static bool IsUserExists(const string & Username)
    {
        clsBankUser User = Find(Username);
        return !(User.IsEmpty());
    }

    static bool IsUserExists(const string & Username, const string & Password)
    {
        clsBankUser User = Find(Username, Password);
        return !(User.IsEmpty());
    }

    static clsBankUser GetAddNewUserObject(const string & Username)
    {
        return clsBankUser(AddMode, Username, "", Nothing);
    }

    static vector<clsBankUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool IsHasPermission(enPermission Option) const
    {
        if (this->_Permission == All)
            return true;

        if ((this->_Permission & Option) == Option)
            return true;

        return false;
    }

    enum enSaveResult { svFailedEmptyUser, svSucceeded, svFailedUsernameExists };

    enSaveResult Save()
    {
        switch(this->_Mode)
        {
            case UpdateMode:
            {
                _Update();
                return svSucceeded;
            }

            case AddMode:
            {
                if (IsUserExists(this->_Username))
                    return svFailedUsernameExists;

                if (this->_Password == "")
                    return svFailedEmptyUser;

                _AddNew();
                this->_Mode = UpdateMode;
                return svSucceeded;
            }

            default:
                return svFailedEmptyUser;
        }
    }

    bool Delete()
    {
        if (this->_Username == "Admin")
            return false;

        vector<clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (auto iter = vUsers.begin(); iter != vUsers.end(); ++iter)
        {
            
            if (iter->_Username == this->_Username)
            {
                vUsers.erase(iter);
                _SaveUsersDataToFile(vUsers);
                *this = _GetEmptyObject();
                return true;
            }
        }

        return false;
    }

    bool ChangePassword(const string & OldPassword, const string & NewPassword)
    {
        if (this->_Password != OldPassword || NewPassword == "")
            return false;

        this->_Password = NewPassword;
        _Update();
        return true;
    }

};