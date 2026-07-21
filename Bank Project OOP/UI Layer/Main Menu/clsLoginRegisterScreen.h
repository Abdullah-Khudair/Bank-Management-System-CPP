#pragma once
#include "../../Logic Layer/clsLoginRegister.h"
#include "../clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _ShowOneLoginRegister(const clsLoginRegister & Log)
    {
        cout << "| " << left << setw(35) << Log.DateTime();
        cout << "| " << left << setw(20) << Log.Username();
        cout << "| " << left << setw(20) << Log.Password();
        cout << "| " << left << setw(12) << Log.Permission() << "|";
    }

    static void _PrintLoginRegisters(const vector<clsLoginRegister> & vLog)
    {
        SetWidth(96, '=');
        cout << "\n| " << left << setw(35) << "Date / Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(12) << "Permission" << "|\n";
        SetWidth(96, '=');
        cout << endl;
    
        if (vLog.size() == 0)
            cout << "\n\t\t\t\t\tNo Logins Available In The System!\n\n";
    
        for (const clsLoginRegister & L : vLog)
        {
            _ShowOneLoginRegister(L);
            cout << endl;
        }
    
        SetWidth(96, '=');
        cout << endl;
    }

public:
    static void ShowLoginRegisterScreen()
    {
        vector<clsLoginRegister> vRegister = clsLoginRegister::GetLoginRecords();

        _DrawScreenHeader("LOGIN REGISTER SCREEN", "\tLogin Register List (" + to_string(vRegister.size()) + ") Record(s)");
        _PrintLoginRegisters(vRegister);
    }
};