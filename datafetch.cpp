#include "datafetch.h"
#include <curl/curl.h>

DataFetch::DataFetch()
{

}

// Callback function to write the response data into the private attribute string response
    size_t write_data(void* contents, size_t size, size_t n_memb, std::string* response) {
    size_t total_size = size * n_memb;
    response->append((char*)contents, total_size);
    return total_size;
}


//Method that uses curl to retrieve data from API and write it into response
void DataFetch::getJson() {
    CURL* curl;
    CURLcode result;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, data_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            std::cerr << "Download error with curl: " << curl_easy_strerror(result) << std::endl;
        }
        //std::cout << response << std::endl;  used for debug to see if we wrote the data correctly from the url

        curl_easy_cleanup(curl);
    }
}



