#ifndef DATAFETCH_H
#define DATAFETCH_H

#include <iostream>
#include <string>

class DataFetch
{
public:
    DataFetch();
    void getJson();
    std::string response;

private:
    const std::string data_url = "https://odre.opendatasoft.com/api/explore/v2.1/catalog/datasets/eco2mix-national-tr/records?select=taux_co2%20%2C%20date%2C%20date_heure&limit=100";
    const std::string json_filename = "CO2_data.json";

};

#endif // DATAFETCH_H
