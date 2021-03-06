//
//  SqlHelper.h
//  UniLife
//
//  Created by Jackson Gross on 29/07/2014.
//
//

#ifndef UniLife_SqlHelper_h
#define UniLife_SqlHelper_h

#include "SqlHelper.h"
#include <string>
#include <vector>
#include "sqlite3.h"
#include "PlayerModel.h"
#include "PlayerStatsModel.h"
#include "AssessmentModel.h"
#include "cocos2d.h"
#include "subjectBlockClassModel.h"

class SqlHelper
{
    
private:
    
public:
    
    // open a connection to the database
    static sqlite3* openDatabase(std::string name);
    
    // close database connection
    static void closeDatabase(sqlite3* db);
    
    // seed the database
    static void initDatabase();
    
    // serialize a player to the database
    static int serialize(PlayerModel &player);
    
    // overwrite existing player data in database
    static void autosave(PlayerModel player);
    
    // saves the player's marks
    static void saveAssessments(PlayerModel &player);
    
    // updates the player's marks
    static void updateAssessments(PlayerModel player);
    
    // save the attendance records
    static void saveAttendance(PlayerModel &player);
    
    // update the attendance records
    static void updateAttendance(PlayerModel player);
    
    // get list of all players
    static std::vector<PlayerModel> getAllPlayers();
    
    // retrieve player data from database
    static PlayerModel getPlayer(int playerId);
    
    // builds a player object from a database query
    static void buildPlayerObjectFromDb(sqlite3_stmt *Stmnt, PlayerModel &p, PlayerStatsModel &s, TimeModel &t);

    // retrieve degree names from the database
    static std::vector<std::string> getDegrees();
    
    // get list of degrees for a faculty
    static std::vector<std::string> getDegrees(std::string faculty);
    
    static int getDegreeCode(std::string dname);
    
    //below code pulls class data from the database in order to allocate to timetable
    static std::vector<std::string> getClasses(int degnum, int year);
    
    static std::vector<subjectBlockClassModel> getBlocks(std::vector<std::string> code);
    
    // gets assignments for one subject
    static std::vector<AssessmentModel> getAssignments(std::string code);
    
    // attendance for a player
    static std::vector<AttendanceModel> getAttendance(int playerid);
   
    static std::vector<std::string> getFaculties();
    
    static std::vector<AssessmentModel> getAssessmentsForPlayer(int playerid);
    
    
};

#endif
