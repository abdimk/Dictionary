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


string formatter(string text){
    string first, second;
    size_t pos;
    
    first = "{bc}";
    second = "<strong>: </strong>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{it}";
    second = "<i>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{/it}";
    second = "</i>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{b}";
    second = "<strong>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{/b}";
    second = "</strong>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }

    first = "{phrase}";
    second = "<strong>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{/phrase}";
    second = "</strong>";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{ldquo}";
    second = "\"";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }
    
    first = "{rdquo}";
    second = "\"";
    while(string::npos != (pos = text.find(first))){
        text.replace(pos, first.size(), second);
    }

    return text;
}

int main(){
    CURL * curl;
    CURLcode res;
    
    //search = lowercase(search);
    
    std::string search = "dog";
    std::string response;
    std::string key = "60a0e1ee-b2cc-40f4-9210-787f278c8964";
    std::string link = "https://www.dictionaryapi.com/api/v3/references/learners/json/" + search + "?key=" + key;
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, link.c_str());
    
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
    
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    //curl_easy_strerror(res)

    //cout<<response<<endl;


    // Format the JSON object as a string with indentation
    json data = response;
    std::string formatted_data = data.dump(4);

    // Print the formatted JSON string to the console
    std::cout << formatted_data << std::endl;

    std:: string val = formatter(formatted_data);
    cout<<val<<endl;

    char* url;
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
    string urlStr(url);
    cout << "\nFinal URL: " << urlStr << endl;

    //curl_easy_perform(curl); 
    curl_easy_cleanup(curl);

    return 0;

}

