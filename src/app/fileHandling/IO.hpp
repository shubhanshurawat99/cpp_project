#ifndef IO_HPP
#define IO_HPP
using namespace std;

#include <fstream>
#include<string>
#include<iostream>

class IO{
    public:
    IO(const string &file_path);
    ~IO();
    fstream getFileStream();
    private:
     fstream file_stream;

};


#endif