#pragma once
#include "../../Logic Layer/clsTransferLog.h"
#include "../clsScreen.h"

class clsTransferLogsScreen : protected clsScreen
{
private:
    static void _PrintOneLog(const clsTransferLog & Log)
    {
        cout << "| " << left << setw(30) << Log.GetDateTime();
        cout << "| " << left << setw(15) << Log.GetFromAccount();
        cout << "| " << left << setw(15) << Log.GetToAccount();
        cout << "| " << left << setw(12) << Log.GetAmount();
        cout << "| " << left << setw(15) << Log.GetFromBalance();
        cout << "| " << left << setw(15) << Log.GetToBalance();
        cout << "| " << left << setw(13) << Log.GetUsername() << "|";
    }

    static void _PrintTransferLogs(const vector<clsTransferLog> & vLogs)
    {
        cout << "\n"; SetWidth(130, '=');
        cout << "\n| " << left << setw(30) << "Date / Time";
        cout << "| " << left << setw(15) << "From Account";
        cout << "| " << left << setw(15) << "To Account";
        cout << "| " << left << setw(12) << "Amount";
        cout << "| " << left << setw(15) << "From Balance";
        cout << "| " << left << setw(15) << "To Balance";
        cout << "| " << left << setw(13) << "Username" << "|\n";
        SetWidth(130, '=');
        cout << endl;
    
        if (vLogs.empty())
        {
            cout << "\n\t\t\tNo Transfer Logs Available In the System!\n\n";
        }

        else
        {
            for (const clsTransferLog& Log : vLogs)
            {
                _PrintOneLog(Log);
                cout << endl;
            }
        }
    
        SetWidth(130, '=');
        cout << endl;
    }

public:
    static void TransferLogsScreen()
    {
        vector<clsTransferLog> vLogs = clsTransferLog::GetLogs();

        _DrawScreenHeader("TRANSFER LOG SCREEN", "\tShow Transfer Logs (" + to_string(vLogs.size()) + " Logs)");
        _PrintTransferLogs(vLogs);
    }
};