#include "UI Layer/clsLoginScreen.h"

int main()
{
    char Choice;
    do
    {
        if (!clsLoginScreen::LoginScreen())
            break;
            
        system("clear");
        cout << "\nDo you want to login again?  [y/n] : ";
    
    } while(cin >> Choice && (Choice == 'y' || Choice == 'Y'));
    
    return 0;
}