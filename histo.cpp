#include<iostream>
#include<fstream>

void histo() {
    TH1F* histo = new TH1F("Histo", "Histo", 40,0,10);
    std::ifstream myfile ("/home/lorenzo17/Roundabout2/data.dat",std::ifstream::in);

    while(myfile.good()){
        double x =10;
        myfile >> x;
        //std::cerr << x << '\n';
        histo->Fill(x);
    }
    myfile.close();
    histo->Draw();
    std::cout << "\nLa media è: " << histo->GetMean() << '\n'; 

}