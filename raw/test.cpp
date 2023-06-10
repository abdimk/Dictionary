#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;



size_t write_callback(char *ptr, size_t size, size_t nmemb, std::string *data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}


int main()
{

    CURL *curl;
    CURLcode res;
    string response;


    string key = "60a0e1ee-b2cc-40f4-9210-787f278c8964";//token
    string search = "computer";
    string my_url = "https://www.dictionaryapi.com/api/v3/references/learners/json/" + search + "?key=" + key;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();


    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, my_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);

        if(res == CURLE_OK){
            cout<<response<<endl;
        }
        else{
            cout<<"some thing went wrong"<<endl;
            curl_easy_cleanup(curl);
        }
    }

    curl_global_cleanup();
}