#pragma once

#include "scene.h"

class GuiScene : public Scene
{
public:
    GuiScene();
    virtual ~GuiScene();
    
    virtual void Init();
    virtual void Activate();
    virtual void Deactivate();
    virtual void Update();
    virtual void Destroy();
    virtual void HandleEvent(SDL_Event&);
    virtual void SetSettings(const Settings&);
    virtual const Settings& GetSettings() const;
    
private:
    
    enum Screen
    {
        MainScreen,
        SettingsScreen,
        LoadScreen,
        SaveScreen
    };
    Screen activeScreen_;
};
