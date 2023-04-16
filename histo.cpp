#include<iostream>
#include<fstream>
#include <vector>


void histo() {
    gROOT->SetStyle("Plain");
    gStyle->SetPalette(57);
    gStyle->SetOptTitle(0);
    gStyle->SetStatBorderSize(4);
    gStyle->SetStatX(0.9);
    gStyle->SetStatY(0.9);
    gStyle->SetStatW(0.5); 
    gStyle->SetStatH(0.2);

    
    TH1F* histos[4];
    std::string name = "Number of cars in road n. ";
    for(int i = 0;i<4;i++){
        std::string string = name + std::to_string(i+1);
        char const *histName = string.c_str();
        histos[i] = new TH1F("", "",25,0,25);
        histos[i]->SetNameTitle(histName,"Flux in: 9");
        histos[i]->SetFillColor(kBlue);
        histos[i]->SetLineColor(kBlack);
        histos[i]->SetMarkerStyle(kFullCircle);
        histos[i]->SetMarkerSize(0.8);
        histos[i]->GetYaxis()->SetTitleOffset(1.2);
        histos[i]->GetXaxis()->SetTitleSize(0.04);
        histos[i]->GetYaxis()->SetTitleSize(0.04);
        histos[i]->GetXaxis()->SetTitle("N.of cars");
        histos[i]->GetYaxis()->SetTitle("Occurrences");
        histos[i]->StatOverflows(true);
        histos[i]->SetLabelSize(0.04);
    }

    TCanvas* c1 = new TCanvas("","",1000,700);
    c1->Divide(2,2);
    
    std::ifstream myfile1 ("/home/lorenzo17/Roundabout2/datas/road0.dat", std::ifstream::in);
    std::ifstream myfile2 ("/home/lorenzo17/Roundabout2/datas/road1.dat", std::ifstream::in);
    std::ifstream myfile3 ("/home/lorenzo17/Roundabout2/datas/road2.dat", std::ifstream::in);
    std::ifstream myfile4 ("/home/lorenzo17/Roundabout2/datas/road3.dat", std::ifstream::in);

    std::ofstream meanvalues("meanvalues.dat",std::ios::app);
    std::ofstream sdvalues("sdvalues.dat", std::ios::app);
    
    c1->cd(1);
    while(myfile1.good()){
        double x =0;
        myfile1 >> x;
        //std::cerr << x << '\n';
        histos[0]->Fill(x);
    }
    myfile1.close();
    std::cout << "\nLa media è: " << histos[0]->GetMean() << '\n'; 
    meanvalues << histos[0]->GetMean() << " ";
    std::cout << "\nLa SD è: " << histos[0]->GetRMS() << '\n'; 
    sdvalues << histos[0]->GetRMS() << " ";
    histos[0]->Draw();

    c1->cd(2);
    while(myfile2.good()){
        double x =0;
        myfile2 >> x;
        //std::cerr << x << '\n';
        histos[1]->Fill(x);
    }
    myfile2.close();
    std::cout << "\nLa media è: " << histos[1]->GetMean() << '\n'; 
    meanvalues << histos[1]->GetMean() << " ";
    std::cout << "\nLa SD è: " << histos[1]->GetRMS() << '\n'; 
    sdvalues << histos[1]->GetRMS() << " ";
    histos[1]->Draw();

    c1->cd(3);
    while(myfile3.good()){
        double x =0;
        myfile3 >> x;
        //std::cerr << x << '\n';
        histos[2]->Fill(x);
    }
    myfile3.close();
    std::cout << "\nLa media è: " << histos[2]->GetMean() << '\n'; 
    meanvalues << histos[2]->GetMean() << " ";
    std::cout << "\nLa SD è: " << histos[2]->GetRMS() << '\n'; 
    sdvalues << histos[2]->GetRMS() << " ";
    histos[2]->Draw();


    c1->cd(4);
    while(myfile4.good()){
        double x =0;
        myfile4 >> x;
        //std::cerr << x << '\n';
        histos[3]->Fill(x);
    }
    myfile4.close();
    std::cout << "\nLa media è: " << histos[3]->GetMean() << '\n'; 
    meanvalues << histos[3]->GetMean() << std::endl;
    std::cout << "\nLa SD è: " << histos[3]->GetRMS() << '\n';
    sdvalues << histos[3]->GetRMS() << std::endl; 
    histos[3]->Draw();

    meanvalues.close();
    sdvalues.close();

    c1->Print("/home/lorenzo17/Roundabout2/histopdf/histo4_13_6.pdf");
}