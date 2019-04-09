#include <windows.h>
#include <tlhelp32.h>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "proc.h"

#include <SFML/Graphics.hpp>

#include "LCD_Solid.c"

#define FIRST_BASE 0x0240E850
#define SECOND_BASE 0x02070758

class ProgramGui
{
private:
   
    DWORD m_procId = 0;
    
    std::string m_exeName = "";
    
    HANDLE hProcess = 0;
    
    //bool running = true;
    
    float lastTimeValue = 0;
    float stageTimeValue = 0;
    float sumTime = 0;
    
    double delta = 0;
    
    uintptr_t moduleBase;
    uintptr_t dynamicPtrBaseAddress;
    uintptr_t stageTimeAddress;
    
    //std::vector<unsigned int> stageTimeOffsets = {0x18, 0x3E0, 0x2AC}; First try
    std::vector<unsigned int> stageTimeOffsets = {0x148, 0x188, 0x2C4};
    
    void mainLoop();
    void update();
    void handleInput();
    void pointerSetup();
    
    //Window Stuff
    
    sf::RenderWindow window;
    sf::Event event;
    
    sf::Font font_LCDSolid;
    sf::Text text_Time_Overall;
    sf::Text text_Time_Stage;
    
    char time_Overall[14] = "";
    char time_Stage[14] = "";
    
    void windowSetup();
    void poolEvents();
    void draw();
    
public:

    ProgramGui(DWORD procId, std::string exeName);
    
    void run();
    
};