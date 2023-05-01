#include<iostream>
#include<fstream>
#include"TGraph.h"

void timeseries() {


    std::ofstream timeelaborati1("/home/lorenzo17/Roundabout2/timeseries/time0el.dat", std::ifstream::out);
    std::ofstream timeelaborati2("/home/lorenzo17/Roundabout2/timeseries/time1el.dat", std::ifstream::out);
    std::ofstream timeelaborati3("/home/lorenzo17/Roundabout2/timeseries/time2el.dat", std::ifstream::out);
    std::ofstream timeelaborati4("/home/lorenzo17/Roundabout2/timeseries/time3el.dat", std::ifstream::out);


    std::ifstream myfile1("/home/lorenzo17/Roundabout2/timeseries/time0.dat", std::ifstream::in);
    std::ifstream myfile2("/home/lorenzo17/Roundabout2/timeseries/time1.dat", std::ifstream::in);
    std::ifstream myfile3("/home/lorenzo17/Roundabout2/timeseries/time2.dat", std::ifstream::in);
    std::ifstream myfile4("/home/lorenzo17/Roundabout2/timeseries/time3.dat", std::ifstream::in);
    int t=10;
    double x{0};
    double y{0};
    double sum{0};
    int control{0};
    while (myfile1.good())
    {
        myfile1 >> x >> y;
        sum += y;
        if(control%t ==0){
            timeelaborati1 << control << " " << sum/t <<std::endl;
            sum = 0;
        }
        control++;
    }
    x = 0;
    sum = 0;
    y=0;
    control = 0;
    while (myfile2.good())
    {
        myfile2 >> x >> y;
        sum+= y;
        if(control%t ==0){
            timeelaborati2 << control << " " << sum/t <<std::endl;
            sum = 0;
        }
        control++;
    }
    x = 0;
    y=0;
    sum = 0;
    control = 0;
    while (myfile3.good())
    {
        myfile3 >> x >> y;
        sum+= y;
        if(control%t ==0){
            timeelaborati3 << control << " " << sum/t <<std::endl;
            sum = 0;
        }
        control++;
    }
    x = 0;
    sum = 0;
    y = 0;
    control = 0;
    while (myfile4.good())
    {
        myfile4 >> x >> y;
        sum += y;
        if(control%t ==0){
            timeelaborati4 << control << " " << sum/t <<std::endl;
            sum = 0;
        }
        control++;
    }
    

    TGraph* graph[4];
    std::string name = "/home/lorenzo17/Roundabout2/timeseries/time";
    for(int i = 0;i<4;i++){
        std::string string = name + std::to_string(i) + "el.dat";
        char const *graphName = string.c_str();
        graph[i] = new TGraph(graphName,"%lg %lg");
        graph[i]->GetYaxis()->SetRangeUser(0,150);
        graph[i]->SetTitle("Input stream = 10.5");
        graph[i]->GetXaxis()->SetTitle("Time");
        graph[i]->GetYaxis()->SetTitle("N. of car");
        graph[i]->SetName("Number of cars");
    }
    graph[0]->GetYaxis()->SetRangeUser(0,500);

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