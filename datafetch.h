#ifndef DATAFETCH_H
#define DATAFETCH_H

#include <iostream>
#include <string>

class DataFetch
{
public:
    DataFetch();
    void getJson();



private:
    const std::string data_url = "https://www.data.gouv.fr/fr/datasets/r/f0eb039b-0859-4df7-933b-58361c112919";
    const std::string json_filename = "CO2_data.json";

};

#endif // DATAFETCH_H
