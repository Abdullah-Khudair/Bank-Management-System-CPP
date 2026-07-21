#pragma once
#include "ContactService.h"


class clsPerson : public ContactService
{
private:
    string _FullName, _Email, _Phone;

public:
    clsPerson(const string & name, const string & email, const string & phone)
    {
        _FullName = name;
        _Email = email;
        _Phone = phone;
    }


    void FullName(const string & FullName) { _FullName = FullName; }
    string FullName() const { return _FullName; }

    void Email(const string & Email) { _Email = Email; }
    string Email() const { return _Email; }
    
    void Phone(const string & Phone) { _Phone = Phone; }
    string Phone() const { return _Phone; }


    void sentEmail(const string & Subject, const string & Body)
    {
        cout << "\n---------------------------------------------";
        cout << "\n[✔] Email Sent Successfully to: " << Email();
        cout << "\n---------------------------------------------";
        cout << "\n Subject : " << Subject;
        cout << "\n Body    : " << Body;
        cout << "\n---------------------------------------------\n\n";
    }

    void sentSMS(const string & Message)
    {
        cout << "\n---------------------------------------------";
        cout << "\n[✔] SMS Sent Successfully to: " << Phone();
        cout << "\n---------------------------------------------";
        cout << "\n " << Message;
        cout << "\n---------------------------------------------";
    }
};