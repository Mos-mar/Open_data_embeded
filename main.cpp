#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <gd.h>
#include <gdfonts.h>
#include"nlohmann/json.hpp"
#include<gdfontl.h>


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


void histogramme_CO2(const string& filename,const vector<string>& days, const vector<int>& taux)
{
    const int image_width =1000;
    const int image_height = 600;

    gdImagePtr im = gdImageCreateTrueColor(image_width, image_height);
    int white = gdImageColorAllocate(im, 255, 255, 255);
    gdImageFill(im, 0, 0, white);

    int barColor = gdImageColorAllocate(im, 0, 0, 0); // Black color
    int textColor = gdImageColorAllocate(im, 0, 0, 0); // Black color
    int barWidth = 50;
    int barSpacing = 40;
    int startX = 50;
    int startY = 500;

    // Draw the title
    gdImageString(im, gdFontGetLarge(), 300, 50, (unsigned char*)"Estimated carbon emissions generated by electricity production in France", textColor);


    // Draw the Y-axis label
    gdImageStringUp(im, gdFontGetSmall(), 20, startY - 250, (unsigned char*)"CO2 rate (g/kWh)", textColor);
    gdImageLine(im, startX, startY, startX, startY - 400, barColor);

    // Draw the X-axis line
    gdImageLine(im, startX, startY, startX + (barWidth + barSpacing) * days.size(), startY, barColor);

    for (int i = 0; i < days.size(); i++) {
        int barHeight = taux[i] * 4;
        int x1 = startX + (barWidth + barSpacing) * i;
        int y1 = startY - barHeight;
        int x2 = x1 + barWidth;
        int y2 = startY;

        gdImageFilledRectangle(im, x1, y1, x2, y2, barColor);

        gdImageString(im, gdFontGetSmall(), x1 + barWidth / 2 - 10, startY + 20, (unsigned char*)days[i].c_str(), textColor);

    }

    FILE* out = fopen(filename.c_str(), "wb");
    gdImagePng(im, out);
    fclose(out);

    gdImageDestroy(im);

}



int main()
{
    getJson();
    cout << "Download complete  " << json_filename << " has been retrieved." << endl;
    ifstream file(json_filename);
    json data;
    file >> data;

    vector<int> taux;
    vector<string> days;

    for (int i = 0; i < 200; i+=20)
    {
        if (data[i]["fields"].contains("taux_co2"))
        {
            taux.push_back(data[i]["fields"]["taux_co2"].get<int>());
        }

    }
    sort(taux.begin(), taux.end());

    for(int i = 0; i < 200; i+=20)
    {


        days.push_back(data[i]["fields"]["date"].get<string>());


    }
    sort(days.begin(), days.end());



    histogramme_CO2("emissionCO2.png",days,taux);




    return 0;
}
