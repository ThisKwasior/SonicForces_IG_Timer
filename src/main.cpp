#include <cstdio>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>

#include "proc.h"
#include "programCli.hpp"
#include "programGui.hpp"

#include <SFML/Graphics.hpp>

void printInfo();

int main(int argc, char** argv)
{
    if(argc > 1 && !strcmp(argv[1], "--help"))
    {
        printInfo();        
        getchar();
        return 0;
    }
    else
    {      
        bool GameFound = false;

        DWORD procId = 0;
        std::string exeName = "Sonic Forces.exe";
        procId = GetProcId(&exeName);
       
        printf("Exename: %s\n", exeName.c_str());
        printf("PID: %d\n", procId);
        printf("Last error: %d\n", GetLastError());

        if(procId != 0) GameFound = true;
        
        if(GameFound == false)
        {        
            MessageBox(NULL, "Sonic Forces you to launch the game.", "SONIC FORCES is not working.", MB_OK + MB_ICONINFORMATION);
        }
        else
        {
            MessageBox(NULL, "SONIC FORCES found!", "Success!", MB_OK + MB_ICONINFORMATION);
            
            /*if(argc > 1 && !strcmp(argv[1], "--gui"))
            {*/
                printf("Launching GUI\n");
                ProgramGui pgui(procId, exeName);
                pgui.run();
            /*}
            else
            {
                ProgramCli pcli(procId, exeName);
                pcli.run();
            }*/ 
        }
    }

    return 0;
}

void printInfo()
{
    printf("========================\n");
    printf("===USAGE:\n");
    printf("R - resets timer\n");
    printf("\n===INFO:\n");
    printf("Sonic Forces NG/NG+/Episode Shadow IGT counter\n");
    printf("By Kwasior/@ThisKwasior\n");
    printf("Version: 0.3v\n");
    printf("Keep in mind time in current state can be inaccurate in some cases.\n\n");
    printf("Special thanks: Sayuri; muraadmug; pshq\n");
}