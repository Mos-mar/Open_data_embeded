# Open_data_embeded


This program allows to us to visualize the estimated CO2 emissions generated by electricity in France.
It retrieves data from a [source](https://www.data.gouv.fr/fr/datasets/donnees-eco2mix-nationales-temps-reel-1/#/resources) in JSON format.
 -Extracted data :
 
    -Date  Heure: date_heure[datetime]
    -Taux de CO2 (g/kWh): taux_co2[int] Estimation des émissions de carbone générées par la production d’électricité en France.

### Details
#### Data source
   -Data selected by [api](https://odre.opendatasoft.com/explore/dataset/eco2mix-national-tr/api/?disjunctive.nature)
   
   -Json format was used
   
   -Complete Data json [url](https://www.data.gouv.fr/fr/datasets/r/f0eb039b-0859-4df7-933b-58361c112919)
### Method
     -libcurl was used to retrieve the data from the api
     -The Json file is parsed to retrieved only the desired data
     -GD library is used to plot the data


# Buildroot and Qemu

   Buildroot config
        
        1. Access the dir where buildroot is located home/mariomoser/11_embeded_linux/buildroot/buildroot-2023.08
        2. use make xconfig  command
        3.Check required options :
                        -libcurl 
                        -libjsoncpp/sub> (BR2_PACKAGE_JSON_FOR_MODERN_CPP et BR2_PACKAGE_LIBJSON)
                        -Enable C++ support 
                        ->GD and gdtopng (BR2_PACKAGE_GD)
        4.Compiling with make
        5.Cross compilation : /home/mariomoser/11_embeded_linux/buildroot/buildroot-2023.08/output/host/bin/aarch64-linux-g++ -o prog_qemu main.cpp datafetch.cpp -lcurl -lgd -lpng  -lstdc++fs
