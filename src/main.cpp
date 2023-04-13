#include <iostream>
#include <curl/curl.h>
#include <stdio.h>
#include <unistd.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

string lowercase(string text){
    for(auto & c : text){
        if(c >= 65 && c <= 90){
            c += 32;
        }
    }
    return text;
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


string learner_webster(string search){
    try{
        CURL *curl;
        // CURLcode res;
        search = lowercase(search);
        std::string readBuffer;
        std::string key = "60a0e1ee-b2cc-40f4-9210-787f278c8964";
        std::string link = "https://www.dictionaryapi.com/api/v3/references/learners/json/" + search + "?key=" + key;
        curl = curl_easy_init();
        if(curl){
            curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            // res = curl_easy_perform(curl); 
            curl_easy_perform(curl); 
            curl_easy_cleanup(curl);
        }
        // ofstream dic_log("dic_log", ios::app);
        try{
            json j = json::parse(readBuffer);
            stringstream out;
           // dic_log << "-------------------------------------------------\n";
           cout<<"=========================================================\n";
            for(unsigned entry = 0; entry < j.size(); entry++){
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
                           cout<<"Searched term: \t"<<entry_title << endl;
                            out << " " << formatter(entry_title)<<functional_label<< ": \n" << " ";
                            for(unsigned def = 0; def < j[entry]["meta"]["app-shortdef"]["def"].size(); def++){
                                string app_def_title;
                                if("" == j[entry]["meta"]["app-shortdef"]["def"][def]){
                                    out << " " << formatter(j[entry]["shortdef"][def].get<string>()) << "\n";
                                    break;
                                }
                                app_def_title = j[entry]["meta"]["app-shortdef"]["def"][def].get<string>();
                                out << formatter(app_def_title);
                                // dic_log << "\tdebug:\t" << entry << "\t" << app_def_title << endl;
                                cout<<" " << entry << "" << app_def_title << endl;
                                if(!j[entry]["shortdef"][0].empty()){
                                    string def_title = j[entry]["shortdef"][0].get<string>();
                                    if(string("{/it}") == app_def_title.substr(app_def_title.size() - 5)){
                                        out << " " << formatter(def_title);
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
            return "Not found :(";
        }
    }catch(...){
        return "Sorry, Bot couldn't work correctly for this word.\nWe'll work to fix it as soon as possible";
    }
}

int main(){

    std::string qurey;
    cout<<"Enter a word to search: ";
    cin>>qurey;
    cout<<learner_webster(qurey)<<endl;

    


    return 0;

}

