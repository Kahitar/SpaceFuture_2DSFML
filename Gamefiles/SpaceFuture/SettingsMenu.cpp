#include "SettingsMenu.hpp"
#include "Framework.hpp"
#include "ResourceManager.hpp"
#include <string>
#include <sstream>

SettingsMenu::SettingsMenu()
{
    uielements.addButton(sf::Vector2f(500,500),sf::Vector2f(200,50),"BackButton","Back");

    uielements.addSlider(sf::Vector2f(700,300),sf::Vector2f(200,50),"ForceSlider","This is a slider:");
    uielements.getSlider("ForceSlider").setNumberOfPositions(100);
    uielements.getSlider("ForceSlider").setMinMax(0,100000000); //setMinMax must be BEFORE setValue on Sliders. Otherwise the Value gets changed
    uielements.getSlider("ForceSlider").setValue(ResourceManager::getAcceleratingForce());

    uielements.addTextBox("SliderDescriptor", "Accelerating Force: ", sf::Vector2f(300,300));

    uielements.addTextBox("ActualForceBox");
}

SettingsMenu::~SettingsMenu()
{
    //dtor
}

void SettingsMenu::update(Framework &frmwrk)
{
    int value = ResourceManager::getAcceleratingForce();
    std::stringstream ssvalue;
    ssvalue << value;
    std::string svalue = ssvalue.str();
    uielements.getTextBox("ActualForceBox").setText(svalue);

    uielements.update(frmwrk);
    ResourceManager::setAcceleratingForce(uielements.getSlider("ForceSlider").getSliderValue());
}

void SettingsMenu::handle(Framework &frmwrk)
{
    uielements.handle(frmwrk);

    if(frmwrk.spMainEvent->type == sf::Event::MouseButtonPressed
       && frmwrk.spMainEvent->mouseButton.button == sf::Mouse::Left)
    {
        if (uielements.getButton("BackButton").getMouseOnButton()){
            frmwrk.ChangeState(Framework::gameStates::MAINMENU);
        }
    }
}

void SettingsMenu::render(Framework &frmwrk)
{
    uielements.render(frmwrk);
}