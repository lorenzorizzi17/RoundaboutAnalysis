#include<iostream>
#include<fstream>
#include"TGraph.h"

void timeseries() {
    TGraph* graph = new TGraph("timeseries.dat", "%lg %lg");
    graph->SetName("Mean number of cars");
    TCanvas* c1 = new TCanvas("","",800,500);
    c1->cd(1);
    graph->Draw();
    TF1* fit = new TF1("fit", "[0]*x");
    fit->SetParameter(0,0.001);
    graph->Fit("fit");
    std::cout << "\nIl fit restituisce " << fit->GetParameter(0) <<'\n';
    gStyle->SetOptFit(0000);
    c1->Print("timeseries_21_6.pdf");
}