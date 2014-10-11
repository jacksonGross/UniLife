//
//  PlayerModel.cpp
//  UniLife
//
//  Created by Jackson Gross on 29/07/2014.
//
//

#include <string>
#include "PlayerModel.h"
#include "PlayerStatsModel.h"
#include "SqlHelper.h"
#include "timeTableClassModel.h"
// default constructor
PlayerModel::PlayerModel()
{
    Id = 0;
    name = "";
    degree = "";
}

// new player constructor with values
PlayerModel::PlayerModel(std::string name, std::string degree, PlayerStatsModel stats, std::string scene, TimeModel gameTime)
{
    this->Id = -1;
    this->name = name;
    this->degree = degree;
    this->stats = stats;
    this->scene = scene;
    this->gameTime = gameTime;
    
    for(int i = 0; i < 3; i++)
    {
        timeTableClassModel* t = new timeTableClassModel(SqlHelper::getDegreeCode(degree), i + 1);
        this->timetable.push_back(t);
    }
}

/********************************
            Getters
 *******************************/

int PlayerModel::getId()
{
    return Id;
}

std::string PlayerModel::getName()
{
    return name;
}

std::string PlayerModel::getDegree()
{
    return degree;
}

PlayerStatsModel PlayerModel::getStats()
{
    return stats;
}

std::string PlayerModel::getScene()
{
    return scene;
}


TimeModel PlayerModel::getGameTime()
{
    return gameTime;
}

std::vector<timeTableClassModel*> PlayerModel::getTimeTable()
{
    return timetable;
}

/********************************
            Setters
 *******************************/
void PlayerModel::setId(int Id)
{
    this->Id = Id;
}

void PlayerModel::setName(std::string name)
{
    this->name = name;
}

void PlayerModel::setDegree(std::string degree)
{
    this->degree = degree;
}

void PlayerModel::setStats(PlayerStatsModel stats)
{
    this->stats = stats;
}

void PlayerModel::setScene(std::string scene)
{
    this->scene = scene;
}

void PlayerModel::setGameTime(TimeModel gameTime)
{
    this->gameTime = gameTime;
}
