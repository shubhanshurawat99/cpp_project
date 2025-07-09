#ifndef TASK_HPP
#define TASK_HPP

#include<string>
#include<iostream>
#include "../fileHandling/IO.hpp"
#include <sstream>
using namespace std;

enum class Action {
ENCRYPT,
DECRYPT
};

struct Task{
   
    fstream f_stream;          // first
    Action action;             // second
    string filePath;           // third

    Task(fstream &&stream, Action act , string filePath):f_stream(move(stream)),action(act),filePath(filePath){}

    string toString(){
        ostringstream oss;
        oss<<filePath<<","<<(action==Action::ENCRYPT?"ENCRYPT":"DECRYPT");
        return oss.str();
    
    }

    static Task fromString (const string &taskData){
        istringstream iss(taskData);
        string filePath;
        string actionStr;
        if(getline(iss,filePath,',')&& getline(iss,actionStr)){
            Action action =(actionStr=="ENCRYPT"?Action::ENCRYPT:Action :: DECRYPT);
                IO io(filePath);
                fstream f_stream= move(io.getFileStream());
                if(f_stream.is_open())
                {
                    return Task(move(f_stream),action,filePath);

                }
                else{
                    throw runtime_error("Failed to open file: "+filePath);
                }
        }else{
            throw runtime_error("invalid task data format");
        }
    }

};


#endif