#include <iostream>
#include<filesystem>
#include "./src/app/processes/Task.hpp"
#include "./src/app/processes/ProcessManagement.hpp"
using namespace std;
namespace fs =std::filesystem;
int main(int argc,char*argv[]){
    string directory;
    string action;
    cout<<"enter the directory path:"<<endl;
    getline ( cin, directory);
    cout<<"enter the action (encrypt/ decrypt):"<<endl;
    getline(cin,action);
    try{
        if(fs::exists(directory)&&fs::is_directory(directory))
        {
            ProcessManagement processManagement;
            for(const auto & entry : fs:: recursive_directory_iterator(directory))
            {
                if(entry.is_regular_file()){
                string filePath= entry.path().string();
                IO io(filePath);
                fstream f_stream= move (io.getFileStream());
                if(f_stream.is_open()){
                    Action taskAction = (action=="ENCRYPT"?Action::ENCRYPT:Action::DECRYPT);
                    auto task = make_unique<Task>(move(f_stream),taskAction, filePath);
                    processManagement.submitToQueue(move(task));

                }else{
                    cout<<"Unable to open the file: "<< filePath<<endl;

                }

                }               

            }
                 processManagement.executeTasks();
        }else{
            cout<<"invalid directory path"<<endl;
        }
   
    }catch(const fs::filesystem_error &ex){
        cout<<"File system error: "<<ex.what()<<endl;


    }
}