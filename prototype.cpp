#include "GLWindow.h"
#include "glad/glad.h"

#include "firefly.h"
using namespace firefly;

#include "scene.h"
#include "guiscene.h"
#include "gamescene.h"

#include "savedgames.h"

Scene*  gGameScene    = nullptr;
Scene*  gGuiScene     = nullptr;
Scene*  gActiveScene  = nullptr;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

DrawMode drawMode = DrawMode::Undefined;
DrawMode GetDrawMode()
{
    return drawMode;
}

Action action = Action::NewGame;
Action GetAction()
{
    return action;
}
void SetAction(Action a)
{
    action = a;
}

SavedGames savedGames;

bool haveGame = false;

void SetDrawMode(DrawMode dm)
{
    if(dm != drawMode)
    {
        drawMode = dm;
        if(gActiveScene)
            gActiveScene->Deactivate();
        switch(GetDrawMode())
        {
            case Gui:
            {
                if(!gGuiScene)
                {
                    gGuiScene = new GuiScene;
                    gGuiScene->Init();
                }
                if(gGameScene)
                    gGuiScene->SetSettings(gGameScene->GetSettings());
                gActiveScene = gGuiScene;
                break;
            }
            case Game:
            {
                if(!gGameScene)
                {
                    gGameScene = new GameScene;
                }
                if(gGuiScene)
                    gGameScene->SetSettings(gGuiScene->GetSettings());
                static_cast<GameScene&>(*gGameScene).SetAction(action);
                gActiveScene = gGameScene;
                break;
            };
        };
        gActiveScene->Activate();
    }
}

#if FIREFLY_PLATFORM == PLATFORM_WIN32
int LoadScene(int argc, wchar_t* argv[])
#else
int LoadScene(int argc, char* argv[])
#endif
{
    savedGames.Load();

    firefly::SDK::Settings sdkSettings;
    sdkSettings.renderer = firefly::RendererManager::OPENGL;
    sdkSettings.device = 0;
    firefly::SDK::GetInstance().Initialise(sdkSettings);
    
    int err = gladLoadGL();
    if (!err)
        ThrowException("Failed to initialise OpenGL extensions");

    SDK::SceneSettings settings;
    settings.NormalPerVertex = true;
    SDK::GetInstance().SetSceneSettings(settings);

    SetDrawMode(DrawMode::Gui);
    return 0;
}

int DrawScene()
{
    gActiveScene->Update();
    return 0;
}

int DestroyScene()
{
    savedGames.Save();
    
    if(gGuiScene)
        gGuiScene->Destroy();
    if(gGameScene)
        gGameScene->Destroy();
    firefly::SDK::GetInstance().Destroy();
    return 0;
}

void SaveGame(const std::tstring& name)
{
    if(!gGameScene)
        return;

    savedGames.Save();
}
