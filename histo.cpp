#include<iostream>
#include<fstream>

void histo() {
    TH1F* histo = new TH1F("Flux in: 10", "Mean n. of cars in roads", 160,0,40);
    histo->StatOverflows(true);
    TCanvas* c1 = new TCanvas("","",800,500);
    c1->cd(1);
    std::ifstream myfile ("/home/lorenzo17/Roundabout2/data.dat",std::ifstream::in);

    while(myfile.good()){
        double x =0;
        myfile >> x;
        //std::cerr << x << '\n';
        histo->Fill(x);
    }
    myfile.close();
    
    histo->Draw();
    
    std::cout << "\nLa media è: " << histo->GetMean() << '\n'; 
    c1->Print("histo_10_6.pdf");
}