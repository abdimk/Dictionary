#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include "Art.h"
#include <stdio.h>
#include <unistd.h>
#include "json.hpp"



using namespace std;
using json = nlohmann::json;



struct Merriam
{
    static size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
        ((string*)stream)->append((char*)ptr, 0, size*count);
        return size*count;
    }

    string formatter(string text){
        string first, second;
        size_t pos;
        
        first = "{bc}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{it}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{/it}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{b}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{/b}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }

        first = "{phrase}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{/phrase}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{ldquo}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }
        
        first = "{rdquo}";
        second = " ";
        while(string::npos != (pos = text.find(first))){
            text.replace(pos, first.size(), second);
        }

        return text;
    }

    string lowercase(string text){
        for(auto & c : text){
            if(c >= 65 && c <= 90){
                c += 32;
            }
        }
        return text;
    }

    // i wote this function in order to filter out "0{bc}" from the definition 
    // and this function is now working because the json parse have a problem with 0{bc} 
    string filter_string(string message){
        string filtered = "";
        string pattern = "0{bc}";
        size_t i = 0;

        while (i < message.length()) {
            if (message.substr(i, pattern.length()) == pattern) {
                i += pattern.length();
            } else {
                filtered += message[i];
                i++;
            }
        }

        return filtered;
    }
    // new function to check whether any file exists or not
    
    bool fileExists(const string &filename){
        ifstream file(filename.c_str());
        return file.good();
    }

    void history(string text, string def){
        if(this->fileExists("./mona/history.txt")){ // if the file exists
            fstream myfile;
            myfile.open("./mona/history.txt", ios::app);
            if(myfile.is_open()){
                myfile<<"\n";
                myfile<<"Term:"<<text<<"\n";
                myfile<<"Definition:"<<def<<"\n";
                myfile.close();
                myfile<<"\n";
                
            }
            else{
                cout<<"Error while opening a file"<<endl;
            }

        }
        else{ // create a new file 
            fstream myfile;
            myfile.open("./mona/history.txt", ios::app);
            if(myfile.is_open()){
                myfile<<"\n";
                myfile<<"Term:"<<text<<"\n";
                myfile<<"Definition:"<<def<<"\n";
                myfile.close();
                myfile<<"\n";
            }
            else{
                cout<<"Error while creating a file"<<endl;
            }
        }
    }
    string learner_webster(string search){
        try{
            CURL *curl;
            // CURLcode res;
            search = lowercase(search);
            
            std::string readBuffer;
            std::string key;
            fstream token;
            token.open("./mona/vars.txt", ios::in);
            if(token.good()){
                getline(token, key);
                token.close();
            }
            
            std::string link = "https://www.dictionaryapi.com/api/v3/references/learners/json/" + search + "?key=" + key;
            curl = curl_easy_init();
            if(curl){
                curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Merriam::write_to_string);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                // res = curl_easy_perform(curl); 
                curl_easy_perform(curl); 
                curl_easy_cleanup(curl);
            }
            // ofstream dic_log("dic_log", ios::app);
            try{
                json j = json::parse(readBuffer);
                stringstream out;
            
            
            //cout<<j.size()<<endl; // enter display 
                for(unsigned entry = 0; entry < (j.size() / 2); entry++){
                    try{
                        if(!j[entry]["meta"]["app-shortdef"].empty()){
                            string entry_title = j[entry]["meta"]["app-shortdef"]["hw"].get<string>();
                            if(string::npos != lowercase(entry_title).find(search)){ // check for exact related ones
                                entry_title = entry_title.substr(0, entry_title.find(":"));
                                string functional_label;
                                if (!j[entry]["meta"]["app-shortdef"]["fl"].empty()){
                                    functional_label = " (" + j[entry]["meta"]["app-shortdef"]["fl"].get<string>() + ")";
                                    
                                }
                            // dic_log << entry_title << endl;
                            
                            cout<<"\nSearching For: \t"<<entry_title << endl;
                            
                                out << "=> " << this->formatter(entry_title)<<functional_label<< ": \n" << " ";
                                for(unsigned def = 0; def < j[entry]["meta"]["app-shortdef"]["def"].size(); def++){
                                    string app_def_title;
                                    if("" == j[entry]["meta"]["app-shortdef"]["def"][def]){
                                        out << " " << this->formatter(j[entry]["shortdef"][def].get<string>()) << "\n";
                                        break;
                                    }
                                    app_def_title = j[entry]["meta"]["app-shortdef"]["def"][def].get<string>();
                                    out << this->formatter(app_def_title);
                                    // dic_log << "\tdebug:\t" << entry << "\t" << app_def_title << endl;
                                    cout<<" " << entry << "" << app_def_title << endl;
                                    if(!j[entry]["shortdef"][0].empty()){
                                        string def_title = j[entry]["shortdef"][0].get<string>();
                                        if(string("{/it}") == app_def_title.substr(app_def_title.size() - 5)){
                                            out << " " << this->formatter(def_title);
                                        }
                                    }
                                    out << "\n";
                                    
                                }
                            }
                        }
                    }catch(...){
                    // dic_log << "\nproblem happened here" << endl;
                    cout<<"\nproblem happened here"<<endl;
                    }
                }
                // dic_log.close();
                if(out.str().empty()){
                    return "Exact result not found :(\nTry to search different";
                }else{
                    return out.str();
                }
            }catch(...){
                return "Some thing went wrong! check weather your internet is working!";
            }
        }catch(...){
            return "Sorry, Bot couldn't work correctly for this word.\nWe'll work to fix it as soon as possible";
        }
    }

    // write a function to show the history 
    
};

int main()
{
    Art web;
    web.webster_big();
    Merriam Dictionary;
    cout<<"Devlopers: "<<"\n";
    cout<<"+Is Group #3 [Abdisa, Walid, Natnael.S, Natnael.D, Habiba]"<<"\n";
    cout<<"+ credits for Arash Nemat "<<"\n";
    string qurey;
    string current_definintion;
    while(true){
        cout<<"\n======================================================================================\n";
        cout<<"Enter a word to search: ";
        cin>>qurey;
        
        cout<<"\n======================================================================================\n";
        current_definintion = Dictionary.learner_webster(qurey);
        cout<<current_definintion<<"\n";
        cout<<"\n======================================================================================\n";
        Dictionary.history(qurey, current_definintion);

    }

    return 0;
}