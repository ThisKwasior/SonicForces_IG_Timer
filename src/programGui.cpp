#include "programGui.hpp"

ProgramGui::ProgramGui(DWORD procId, std::string exeName)
{
    this->m_procId = procId;
    this->m_exeName = exeName;
}

void ProgramGui::run()
{
    pointerSetup();
    windowSetup();
    
    std::cout << "dynamicPtrBaseAddress = " << "0x" << std::hex << this->dynamicPtrBaseAddress << std::endl;
    std::cout << "stageTimeAddress = " << "0x" << std::hex << this->stageTimeAddress << std::endl;
    
    mainLoop();
}

void ProgramGui::mainLoop()
{
    while(this->window.isOpen())
    {
        poolEvents();
        update();
        handleInput();
        
        if(!(this->stageTimeValue == this->lastTimeValue))
        {            
            //printf("%f %f\n", this->stageTimeValue, this->sumTime);
        }
        
        draw();
        
        sf::sleep(sf::seconds(0.0082645)); // 121FPS
    }
}

void ProgramGui::update()
{
    this->stageTimeAddress = FindDMAAddy(this->hProcess, this->dynamicPtrBaseAddress, this->stageTimeOffsets);
    
    this->lastTimeValue = this->stageTimeValue;
  
    ReadProcessMemory(this->hProcess, (BYTE*)this->stageTimeAddress, &this->stageTimeValue, sizeof(float), nullptr);

    this->delta = std::abs(this->lastTimeValue - this->stageTimeValue);
    
    if(this->stageTimeValue != 0 && this->delta < 1)
    {
        this->sumTime += this->delta;
    }
    
    int sumTimeInt = this->sumTime;
    int stageInt = this->stageTimeValue;
    
    uint8_t minutes_o = sumTimeInt/60;
    uint8_t seconds_o = sumTimeInt%60;
    uint8_t mseconds_o = (this->sumTime*100) - sumTimeInt*100;
    sprintf(this->time_Overall, "%d:%d.%d", minutes_o, seconds_o, mseconds_o);
    
    uint8_t minutes_s = stageInt/60;
    uint8_t seconds_s = stageInt%60;
    uint8_t mseconds_s = (this->stageTimeValue*100) - stageInt*100;
    sprintf(this->time_Stage, "%d:%d.%d", minutes_s, seconds_s, mseconds_s);
    
    std::string overall = "";
    overall.append(this->time_Overall);
    
    std::string stage = "";
    stage.append(this->time_Stage);
    
    this->text_Time_Overall.setString(overall);
    this->text_Time_Stage.setString(stage);
}

void ProgramGui::handleInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        this->sumTime = 0;
        printf("%f %f\n", this->stageTimeValue, this->sumTime);
    }
}

void ProgramGui::pointerSetup()
{
    this->moduleBase = GetModuleBaseAddress(this->m_procId, &this->m_exeName);
    this->hProcess = OpenProcess(PROCESS_VM_READ, NULL, this->m_procId);
    this->dynamicPtrBaseAddress = this->moduleBase + SECOND_BASE;
    this->stageTimeAddress = FindDMAAddy(this->hProcess, this->dynamicPtrBaseAddress, this->stageTimeOffsets);
}

void ProgramGui::windowSetup()
{
    this->window.create(sf::VideoMode(450, 140), "SF Time Counter", sf::Style::Close);
    this->window.setFramerateLimit(60);
    this->window.setKeyRepeatEnabled(false);
    
    this->font_LCDSolid.loadFromMemory(LCD_Solid.bytes, LCD_Solid.bytes_Count);
    
    this->text_Time_Overall.setFont(this->font_LCDSolid);
    this->text_Time_Overall.setCharacterSize(70);
    this->text_Time_Overall.setOutlineThickness(3);
    this->text_Time_Overall.setFillColor(sf::Color(0x0, 0xA1, 0x08));
    this->text_Time_Overall.setOutlineColor(sf::Color(0x0, 0x61, 0x05));
    this->text_Time_Overall.setPosition(10, 5);

    this->text_Time_Stage.setFont(this->font_LCDSolid);
    this->text_Time_Stage.setCharacterSize(50);
    this->text_Time_Stage.setOutlineThickness(2);
    this->text_Time_Stage.setFillColor(sf::Color(0xA1, 0, 0x08));
    this->text_Time_Stage.setOutlineColor(sf::Color(0x61, 0, 0x05));
    this->text_Time_Stage.setPosition(10, 80);

}

void ProgramGui::poolEvents()
{
    while(this->window.pollEvent(this->event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::R)
                {
                    //this->sumTime = 0;
                    //printf("%f %f\n", this->stageTimeValue, this->sumTime);  
                }
            break;
        }
    }
}

void ProgramGui::draw()
{
    this->window.clear(sf::Color::Transparent);
    
    this->window.draw(this->text_Time_Overall);
    this->window.draw(this->text_Time_Stage);
    
    this->window.display();
}