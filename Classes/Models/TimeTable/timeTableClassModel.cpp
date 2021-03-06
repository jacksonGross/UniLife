//
//  timeTableClassModel.cpp
//  Timetabler
//
//  Created by James Glennan on 29/06/2014.
//  Copyright (c) 2014 JamesGlennan. All rights reserved.
//

#include "timeTableClassModel.h"
#include <ctime>
#include <cstdlib>
#include "SqlHelper.h"
#include "cocos2d.h"
#include <string>


timeTableClassModel::timeTableClassModel(int dCode, int year){
    
    degreeCode = dCode;
    currYear = year;
    
    classQueue = SqlHelper::getBlocks( SqlHelper::getClasses(degreeCode, currYear));
    
    for(int i = 0; i < classQueue.size(); i++)
    {
        classQueue[i].setAssessments(SqlHelper::getAssignments(classQueue[i].getNameString()));
    }
}

vector<subjectBlockClassModel> timeTableClassModel::getClassQueue()
{
    return this->classQueue;
}

int timeTableClassModel::randomAllocationInt(subjectBlockClassModel ins)
{
    
    int timeInt = -1;
    /*
    int dayInt = -1;
    //bool checker = false;
    unsigned int key = 0;
    srand(static_cast<unsigned int>(time(NULL)));
    
    do{
        timeInt = rand()%(DAYEND-DAYSTART);
        dayInt = rand()%3;
        key = dayInt*100+timeInt;
    }while(!checkTimeBool(key));
    
    classTable.insert(std::pair<unsigned int, subjectBlockClassModel>(key, ins));
    
    for (int i = 1; i < ins.getTotalTimeInt(); ++i) {
        classTable.insert(std::pair<unsigned int, subjectBlockClassModel>(i, subjectBlockClassModel()));
    }
    //insertSubj(ins, timeInt, dayInt);
     
     */
    
    
    
    return timeInt;
}

bool timeTableClassModel::checkTimeBool(unsigned int key){
    
    if (classTable.count(key)==0) {
        return true;
    }else{
        return false;
    }
    
}


void timeTableClassModel::printAll(){
    
    for(int i = 0; i < classQueue.size(); i++)
    {
        cout << classQueue[i] << endl;
    }
    
    /*
    for ( std::map< unsigned int, subjectBlockClassModel, std::less< int > >::const_iterator iter = classTable.begin();
         iter != classTable.end(); ++iter ){
        cout << iter->first << '\t' << iter->second << '\n';
    }
     */
    
    
}

/*
timeTableClassModel::timeTableClassModel(){
    
    totalTimeInt = 0;
    currentDayInt = 0;
    currentTimeInt = DAYSTART;
    //init 2d array for days and timeblocks
    timetableClassArray = new subjectBlockClassModel*[NUMBERDAYS];
    for(int i = 0; i < DAYEND-DAYSTART; ++i)
        timetableClassArray[i] = new subjectBlockClassModel[DAYEND-DAYSTART];


}
*/


/*

timeTableClassModel::~timeTableClassModel(){
    
    for(int i = 0; i < DAYEND-DAYSTART; ++i)
        delete [] timetableClassArray[i];
    
    delete [] timetableClassArray;
    
}

void timeTableClassModel::push(subjectBlockClassModel obj){
    
    obj.putStartVoid(currentTimeInt);
    
    //classQueue.push(obj);
    timetableClassArray[currentDayInt][currentTimeInt-DAYSTART-1] = obj;
    totalTimeInt += obj.getTotalTimeInt();
    currentTimeInt += obj.getTotalTimeInt();
    
    if (currentTimeInt==12) {
        push(subjectBlockClassModel(1, "Lunch"));
    }else if (currentTimeInt >= DAYEND-DAYSTART && currentDayInt < NUMBERDAYS-1){
        currentDayInt++;
        currentTimeInt = DAYSTART;
    }
    
    return;
}
*/



subjectBlockClassModel timeTableClassModel::popClass(){
    
    //subjectBlockClassModel obj = classQueue.front();
    //classQueue.pop();
    
    //totalTimeInt-=obj.getTotalTimeInt(); //not really sure why i'm doing this- but hey its there
    
  
    
    return *new subjectBlockClassModel;
}

//use an array- where a class runs over longer than an hour, point the elements back to the start of itself



subjectBlockClassModel timeTableClassModel::getObjAtTime(unsigned int day, unsigned int hour){
    
    int testTime = DAYEND-DAYSTART;
    
    if(day-1<NUMBERDAYS && hour-DAYSTART < testTime){
        int tmptime = day*100+hour;
        return classTable.find(tmptime)->second;
    //    return timetableClassArray[day-1][hour-DAYSTART];
    }else{
            return subjectBlockClassModel();}

}





void timeTableClassModel::insertSubj(subjectBlockClassModel ins, int timeInt, int dayInt){
    
  //  timetableClassArray[dayInt][timeInt] = ins;
    
    for (int i = timeInt; i<ins.getTotalTimeInt()+timeInt; ++i) {
     //   timetableClassArray[dayInt][timeInt] = subjectBlockClassModel(1, "BLOCKED");
    }
    
    return;
}

bool timeTableClassModel::freeSpaceCheck(subjectBlockClassModel ins, int timeInt, int dayInt){
    
    if (timeInt+ins.getTotalTimeInt()+DAYSTART > DAYEND) {
        return false;
    }
    /*
    for (int i = timeInt; i<ins.getTotalTimeInt()+timeInt; ++i) {
        if (timetableClassArray[dayInt][i].getNameString()!="NO CLASS"){
            return false;
        }
    }
    */
    return true;
}

