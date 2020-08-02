#pragma once

#include <SDL2/SDL.h>
#include "savedgames.h"

class Scene
{
public:
    virtual void Init()       = 0;
    virtual void Activate()   = 0;
    virtual void Deactivate() = 0;
    virtual void Update()     = 0;
    virtual void Destroy()    = 0;
    virtual void HandleEvent(SDL_Event&) = 0;
    
    struct Settings
    {
        SavedGames::SavedGame loadGame;
        bool                  showStateSwitches;
        bool                  showRenderedObjectCount;
        
        Settings() : showStateSwitches(true), showRenderedObjectCount(true)
        {}
    };
    
    virtual void SetSettings(const Settings& settings)
    {
        previousSettings_ = settings_;
        settings_ = settings;
    }
    
    virtual const Settings& GetSettings() const
    {
        return settings_;
    }
protected:
    Settings settings_;
    Settings previousSettings_;
};
