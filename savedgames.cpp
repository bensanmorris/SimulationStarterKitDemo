#include "savedgames.h"
#include "gamescene.h"

#include "firefly.h"
using namespace firefly;

SavedGames::SavedGames()
{
}

void SavedGames::Add(const SavedGame& game)
{
    saves_.push_back(game);
}

void SavedGames::Remove(const SavedGame&)
{
    // TODO
}

void SavedGames::Load()
{
    File file(GetFireflyDir() + "game.save");
    if(!file.Open(IODevice::ReadOnly))
        return;
    Archive ar(file);
    ar.IsLoading(true);
    int savedGames = 0;
    ar.Read(savedGames);
    for(int i = 0; i < savedGames; ++i)
    {
        SavedGame save;
        save.Serialize(ar);
        saves_.push_back(save);
    }
}

void SavedGames::Save()
{
    if(saves_.empty())
        return;
    File file(GetFireflyDir() + "game.save");
    file.Open(IODevice::WriteOnly);
    Archive ar(file);
    ar.IsLoading(false);
    ar.Write((int)saves_.size());
    for(auto save : saves_)
        save.Serialize(ar);
}

void SavedGames::SavedGame::Serialize(Archive& ar)
{
    if(ar.IsLoading())
    {
        ar.Read(name);
        ar.Read(pos);
        ar.Read(lookAt);
    }
    else
    {
        ar.Write(name);
        ar.Write(pos);
        ar.Write(lookAt);
    }
}

const std::tstring SavedGames::GetSavesNames() const
{
    std::tstring list;
    int size = saves_.size();
    for(int i = 0; i < size; ++i)
    {
        list+=saves_[i].name;
        if(i < (size-1))
            list+='\0';
    }
    return list;
}
