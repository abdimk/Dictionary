#include <iostream>
#include <cstring>
#include <curl/curl.h>


using namespace std;


// This callback function will be called by libcurl as soon as it receives any data
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *response = (string*)userdata;
    size_t total_size = size * nmemb;
    response->append(ptr, total_size);
    return total_size;

}

int main()
{

    

    string key = "60a0e1ee-b2cc-40f4-9210-787f278c8964"; // token
    string search = "computer"; //query

    string myurl = "https://www.dictionaryapi.com/api/v3/references/learners/json/"+ search + "?key=" + key;
    CURL * curl;
    CURLcode res;

    string response;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init(); // true or false


    if(curl){

        curl_easy_setopt(curl, CURLOPT_URL, myurl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);




        if(res == CURLE_OK){
            cout<<"response: "<<response<<endl; // returned json data
        }
        else{
            cout<<"some thing went wrong"<<endl;
            curl_easy_cleanup(curl);
        }

    }

    curl_global_cleanup();
    return 0;
}