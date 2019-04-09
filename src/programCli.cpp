#include "programCli.hpp"

ProgramCli::ProgramCli(DWORD procId, std::string exeName)
{
    this->m_procId = procId;
    this->m_exeName = exeName;
}

void ProgramCli::run()
{
    pointerSetup();
    
    std::cout << "dynamicPtrBaseAddress = " << "0x" << std::hex << this->dynamicPtrBaseAddress << std::endl;
    std::cout << "stageTimeAddress = " << "0x" << std::hex << this->stageTimeAddress << std::endl;
    
    mainLoop();
}

void ProgramCli::mainLoop()
{
    while(true)
    {
        update();
        handleInput();
        
        if(!(this->stageTimeValue == this->lastTimeValue))
        {            
            printf("%f %f\n", this->stageTimeValue, this->sumTime);
        }
        
        sf::sleep(sf::seconds(0.0082645)); // 121FPS
    }
}

void ProgramCli::update()
{
    this->stageTimeAddress = FindDMAAddy(this->hProcess, this->dynamicPtrBaseAddress, this->stageTimeOffsets);
    
    this->lastTimeValue = this->stageTimeValue;
  
    ReadProcessMemory(this->hProcess, (BYTE*)this->stageTimeAddress, &this->stageTimeValue, sizeof(float), nullptr);

    this->delta = std::abs(this->lastTimeValue - this->stageTimeValue);
    
    if(this->stageTimeValue != 0 && this->delta < 1)
    {
        this->sumTime += this->delta;
    }
}

void ProgramCli::handleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        this->sumTime = 0;
        printf("%f %f\n", this->stageTimeValue, this->sumTime);
    }
}

void ProgramCli::pointerSetup()
{
    this->moduleBase = GetModuleBaseAddress(this->m_procId, &this->m_exeName);
    this->hProcess = OpenProcess(PROCESS_VM_READ, NULL, this->m_procId);
    this->dynamicPtrBaseAddress = this->moduleBase + SECOND_BASE;
    this->stageTimeAddress = FindDMAAddy(this->hProcess, this->dynamicPtrBaseAddress, this->stageTimeOffsets);
}
