#pragma once
#include <iostream>
using namespace std;


class ContactService
{
public:
    virtual void sentEmail(const string & Subject, const string & Body) = 0;
    virtual void sentSMS(const string & Message) = 0;
};