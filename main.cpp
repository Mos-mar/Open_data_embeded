#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <gd.h>
#include <gdfonts.h>
#include"nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;
const string data_url = "https://www.data.gouv.fr/fr/datasets/r/f0eb039b-0859-4df7-933b-58361c112919";
const string json_filename = "CO2_data.json";

void getJson()
{
    const string command = "wget --no-check-certificate  -O " + json_filename + " " + data_url;
    int result = system(command.c_str());

    if (result != 0)
    {
        cerr << "Error: Failed to download file." << endl;

    }

}


// taux_co2[int]
// Date: date[text]
// Heure: heure[text]
// Date - Heure: date_heure[datetime]

void histogram_CO2(const string& filename,const vector<string>& date, const vector<int>& taux)
{
    const int width = 2400;
    const int height = 1600;
    const int barWidth = width / date.size();

    gdImagePtr im = gdImageCreateTrueColor(width, height);
    gdImageColorAllocate(im, 255, 255, 255);
    int black = gdImageColorAllocate(im, 0, 0, 0);
    int white = gdImageColorAllocate(im, 255, 255, 255);
    gdImageFill(im, 0, 0, white);

    for (size_t i = 0; i < date.size(); i++)
    {
        int percent = (100 * taux[i]) / taux.size();
        int barHeight = (height * percent) / 100;
        int color = gdImageColorAllocate(im, rand() % 255, rand() % 255, rand() % 255);

        gdImageFilledRectangle(im, i * barWidth, height - barHeight, (i+1) * barWidth, height, color);
        gdImageLine(im, 0, height - 1, width, height - 1, black);  //absic
        gdImageLine(im, 0, 0, 0, height, black);  //Axe des y

        FILE* out = fopen(filename.c_str(), "wb");
        gdImagePng(im, out);
        fclose(out);

        gdImageDestroy(im);


    }

}

int main()
{
    getJson();
    cout << "Download complete  " << json_filename << " has been retrieved." << endl;
    ifstream file(json_filename);
    json data;
    file >> data;

    vector<int> taux;
    vector<string> date;

    //for(auto&   )


    //cout << "taux_co2[50]:  " << data[50]["taux_co2"] << endl;
    //cout << "taux_co2[int]:  " << data["taux_co2"]  << endl;
    //    cout << "Date: date[text] : " << data["date"]<< endl;
    //    cout << "Heure: heure[text] : " << data["heure"] << endl;
    //    cout << "date_heure[datetime] : " << data["date_heur"] << endl;



    return 0;
}
