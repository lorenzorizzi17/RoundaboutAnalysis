#include<iostream>
#include<fstream>
#include"TGraph.h"

void timeseries() {

    TGraph* graph[4];
    std::string name = "/home/lorenzo17/Roundabout2/timeseries/time";
    for(int i = 0;i<4;i++){
        std::string string = name + std::to_string(i) + ".dat";
        char const *graphName = string.c_str();
        graph[i] = new TGraph(graphName,"%lg %lg");
        graph[i]->SetTitle("Input stream = 15");
        graph[i]->GetXaxis()->SetTitle("Time");
        graph[i]->GetYaxis()->SetTitle("Mean n. of car");
        graph[i]->SetName("Mean number of cars");
    }

    TCanvas* c = new TCanvas("","",800,600);
    c->Divide(2,2);
    
    for (int i = 0; i < 4; i++)
    {
        c->cd(i+1);
        graph[i]->Draw();
    }

    /* TF1* fit = new TF1("fit", "[0]*x");
    fit->SetParameter(0,0.001);
    graph->Fit("fit");
    std::cout << "\nIl fit restituisce " << fit->GetParameter(0) <<'\n'; */
    gStyle->SetOptFit(0000);
    //c1->Print("/home/lorenzo17/Roundabout2/timeseriespdf/timeseries_14_6.pdf");
}