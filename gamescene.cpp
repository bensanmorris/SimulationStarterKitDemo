#include "gamescene.h"

extern bool haveGame;

GameScene::GameScene()
:
    scene_(nullptr),
    needsRestart_(false)
{}

GameScene::~GameScene()
{}

void GameScene::Init()
{
    Init(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, -1.f));
}

void GameScene::Init(const Vector3& cameraPos, const Vector3& cameraLookAt)
{
    // TODO - load the game scene
    try
    {
#if FIREFLY_PLATFORM == PLATFORM_LINUX
        scene_ = SDK::GetInstance().Load("MyScene.msf");
#elif FIREFLY_PLATFORM == PLATFORM_MACOS
        char buff[FILENAME_MAX];
        getcwd(buff, FILENAME_MAX);
        std::string current_working_dir(buff);
        scene_ = SDK::GetInstance().Load(current_working_dir + "/../../MyScene.msf");
#else
        scene_ = SDK::GetInstance().Load(GetFireflyDir() + "MyScene.msf");
#endif
    }
    catch(const Exception& e)
    {
        std::cout << e.GetDescription() << std::endl;
        exit(1);
    }

    if(scene_ != nullptr)
        SDK::GetInstance().SetScene(scene_);

    Camera* camera = CameraManager::GetInstance().GetDefaultCamera();
    if(camera)
        camera->Activate();

    // Apply settings
    std::vector<FrameCounter*> found;
    scene_->Find<FrameCounter>(found);
    if(!found.empty())
    {
        found[0]->SetShowRenderedObjectCount(GetSettings().showRenderedObjectCount);
        found[0]->SetShowStateSwitches(GetSettings().showStateSwitches);
    }
    
    haveGame = true;
}

void GameScene::Destroy()
{
    if(scene_)
        scene_->Release();
    scene_ = nullptr;
    SDK::GetInstance().Reset();
}

void GameScene::Activate()
{
    if(needsRestart_)
    {
        Destroy();
        Init();
        needsRestart_ = false;
    }
    else
    {
        switch(action_)
        {
            case Action::NewGame:
            {
                Destroy();
                Init();
                break;
            }
            case Action::ResumeGame:
            {
                // do nothing, resume game
                break;
            }
            case Action::LoadGame:
            {
                Destroy();
                LoadGame(settings_.loadGame);
                break;
            }
            default: 
            {
                break;
            }
        }
    }
}

void GameScene::Deactivate()
{
}

void GameScene::Update()
{
    SDK::GetInstance().Update(*scene_);
}

void GameScene::HandleEvent(SDL_Event&)
{}

void GameScene::SetSettings(const Settings& settings)
{
    Scene::SetSettings(settings);
    
    // TODO - determine if you need to restart or not

    needsRestart_ = true;
}

const Scene::Settings& GameScene::GetSettings() const
{
    return Scene::GetSettings();
}

void GameScene::SetAction(Action a)
{
    action_ = a;
}

void GameScene::LoadGame(const SavedGames::SavedGame& save)
{
    Init(save.pos, save.lookAt);
}

void GameScene::Serialize(Archive& ar)
{
    if(ar.IsLoading())
    {
    }
    else
    {
    }
}

