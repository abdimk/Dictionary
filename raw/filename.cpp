// writing a function that checks wether the file exists or not


#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool fileExists(const string &filename){
    ifstream file(filename.c_str());
    return file.good();
}

int main(){
    string myfile = "test.cpp";
    if(fileExists(myfile)){
        cout<<"true"<<endl;
    }
    else{
        cout<<"false"<<endl;
    }
    return 0;
}