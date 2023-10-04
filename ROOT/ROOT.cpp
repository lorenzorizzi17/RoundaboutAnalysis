#include<iostream>
#include<fstream>
#include<vector>
#include"TGraph.h"

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
    
    std::ifstream myfile1 ("/home/lorenzo17/Roundabout2/data/road0.dat", std::ifstream::in);
    std::ifstream myfile2 ("/home/lorenzo17/Roundabout2/data/road1.dat", std::ifstream::in);
    std::ifstream myfile3 ("/home/lorenzo17/Roundabout2/data/road2.dat", std::ifstream::in);
    std::ifstream myfile4 ("/home/lorenzo17/Roundabout2/data/road3.dat", std::ifstream::in);

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

    //c1->Print("/home/lorenzo17/Roundabout2/histopdf/histo4_13_6.pdf");
}


void timeseries() {


    std::ofstream timeelaborati1("/home/lorenzo17/Roundabout2/data/time0el.dat", std::ifstream::out);
    std::ofstream timeelaborati2("/home/lorenzo17/Roundabout2/data/time1el.dat", std::ifstream::out);
    std::ofstream timeelaborati3("/home/lorenzo17/Roundabout2/data/time2el.dat", std::ifstream::out);
    std::ofstream timeelaborati4("/home/lorenzo17/Roundabout2/data/time3el.dat", std::ifstream::out);


    std::ifstream myfile1("/home/lorenzo17/Roundabout2/data/time0.dat", std::ifstream::in);
    std::ifstream myfile2("/home/lorenzo17/Roundabout2/data/time1.dat", std::ifstream::in);
    std::ifstream myfile3("/home/lorenzo17/Roundabout2/data/time2.dat", std::ifstream::in);
    std::ifstream myfile4("/home/lorenzo17/Roundabout2/data/time3.dat", std::ifstream::in);
    int t=1;
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
    std::string name = "/home/lorenzo17/Roundabout2/data/time";
    for(int i = 0;i<4;i++){
        std::string string = name + std::to_string(i) + "el.dat";
        char const *graphName = string.c_str();
        graph[i] = new TGraph(graphName,"%lg %lg");
        graph[i]->GetYaxis()->SetRangeUser(0,150);
        graph[i]->SetTitle("Input stream = ??");
        graph[i]->GetXaxis()->SetTitle("Time");
        graph[i]->GetYaxis()->SetTitle("N. of car");
        graph[i]->SetName("Number of cars");
        graph[i]->GetYaxis()->SetRangeUser(0,500);
    }
    

    TCanvas* c = new TCanvas("","",800,600);
    c->Divide(2,2);
    
    for (int i = 0; i < 4; i++)
    {
        c->cd(i+1);
        graph[i]->Draw();
    }

    TF1* fit = new TF1("fit", "[0]*x");
    fit->SetParameter(0,0.001);
    for (int i = 0; i < 4; i++)
    {
        graph[i]->Fit("fit");
        std::cout << "\nIl fit restituisce " << fit->GetParameter(0) <<'\n';
    }
    
    gStyle->SetOptFit(0000);
    //c1->Print("/home/lorenzo17/Roundabout2/timeseriespdf/timeseries_14_6.pdf");
}

void graph(){
    gStyle->SetMarkerStyle(8);

    double fluxin[11] = {8,8.5,9,9.5,10,10.5,11,11.5,12,12.5,13};
    double meanRoad1[11] = {0.620598,0.7238345 ,0.852251,1.008175444, 1.222,1.503866,1.907,2.52679,3.562701,5.931321,13.74465};
    double semiAmpRoad1[11] = {0.003053,0.005801 ,0.006576,0.0123105, 0.01722,0.00663,0.03128,0.0476,0.07987,0.247045,0.72615};
    double meanRoad2[11] = {0.618775,0.7269142,0.851732,1.012612222 ,1.221623,1.501808,1.889608,2.471776,3.500057,5.607215,13.29274};
    double semiAmpRoad2[11] = {0.003847,0.0039205,0.006563,0.00997,0.011155,0.020365,0.02449,0.020555,0.084,0.172485,0.76875};
    double meanRoad3[11] = {0.608778182, 0.7117248, 0.835109364, 0.996477889 ,1.20375, 1.477438, 1.858783,2.433182, 3.433704,5.520023,14.20815};
    double semiAmpRoad3[11] = {0.005467, 0.0089435,0.007178, 0.013115, 0.0146795 ,0.01752, 0.029265, 0.03621 ,0.07834,0.179695 ,1.2555};
    double meanRoad4[11] = {0.610477909, 0.7099107, 0.837770909, 0.992789444, 1.197315, 1.484943, 1.852592, 2.42866, 3.419182,5.485656,11.8854};
    double semiAmpRoad4[11] = {0.0045395, 0.00523 ,0.0087435, 0.012514, 0.01132, 0.02151, 0.026795,0.031185,0.0804,0.30718, 0.92615};
    
    double meanTotal[11];
    for(int i=0;i<11;i++){
        double b=0;
        b+= meanRoad1[i];
        b+= meanRoad2[i];
        b+= meanRoad3[i];
        b+= meanRoad4[i];
        meanTotal[i] = b/4;
    }

    TGraphErrors* graph1 = new TGraphErrors(11, fluxin, meanRoad1, 0, semiAmpRoad1);
    TGraphErrors* graph2 = new TGraphErrors(11, fluxin, meanRoad2, 0, semiAmpRoad2);
    TGraphErrors* graph3 = new TGraphErrors(11, fluxin, meanRoad3, 0, semiAmpRoad3);
    TGraphErrors* graph4 = new TGraphErrors(11, fluxin, meanRoad4, 0, semiAmpRoad4);
    TGraph* graphtot = new TGraph(11,fluxin, meanTotal);


    TCanvas *c1 = new TCanvas("","",1000,700);
    c1->Divide(2,2);
    c1->cd(1);
    
    graph1->SetTitle("Road 1");
    graph1->GetXaxis()->SetTitle("Input flow");
    graph1->GetYaxis()->SetTitle("Mean n. of cars");
    graph1->SetMinimum(-1);
    graph1->SetMaximum(15);
    graph1->SetMarkerSize(0.5);
    graph1->SetMarkerStyle(21);
    graph1->SetLineColor(40);
    graph1->SetLineWidth(2);
    graph1->Draw("ALP");

    c1->cd(2);
    
    graph2->SetTitle("Road 2");
    graph2->GetXaxis()->SetTitle("Input flow");
    graph2->GetYaxis()->SetTitle("Mean n. of cars");
    graph2->SetMinimum(-1);
    graph2->SetMaximum(15);
    graph2->SetMarkerSize(0.5);
    graph2->SetMarkerStyle(21);
    graph2->SetLineColor(30);
    graph2->SetLineWidth(2);
    graph2->Draw("ALP");

    c1->cd(3);  
    
    graph3->SetTitle("Road 3");
    graph3->GetXaxis()->SetTitle("Input flow");
    graph3->GetYaxis()->SetTitle("Mean n. of cars");
    graph3->SetMinimum(-1);
    graph3->SetMaximum(15);
    graph3->SetMarkerSize(0.5);
    graph3->SetMarkerStyle(21);
    graph3->SetLineColor(46);
    graph3->SetLineWidth(2);
    graph3->Draw("ALP");

    c1->cd(4);
    
    graph4->SetTitle("Road 4");
    graph4->GetXaxis()->SetTitle("Input flow");
    graph4->GetYaxis()->SetTitle("Mean n. of cars");
    graph4->SetMinimum(-1);
    graph4->SetMaximum(15);
    graph4->SetMarkerSize(0.5);
    graph4->SetMarkerStyle(21);
    graph4->SetLineColor(42);
    graph4->SetLineWidth(2);
    graph4->Draw("ALP");


    TCanvas* c2 = new TCanvas("","",800,700);
    c2->Divide(1,2);
    c2->cd(1);
    graph1->Draw("ALP");
    graph1->SetTitle("Mean value vs input stream (all road displayed)");
    graph2->Draw("SAME");
    graph3->Draw("SAME");
    graph4->Draw("SAME");

    TLegend* leg = new TLegend(0.1,0.7,0.2,0.5);
    leg->SetHeader("Legend","C");
    leg->AddEntry(graph1, "Road 1");
    leg->AddEntry(graph2, "Road 2");
    leg->AddEntry(graph3, "Road 3");
    leg->AddEntry(graph4, "Road 4");
    leg->Draw();
    
    c2->cd(2);
    graphtot->SetTitle("Mean value vs input stream (mean of all road)");
    graphtot->GetXaxis()->SetTitle("Input flow");
    graphtot->GetYaxis()->SetTitle("Mean n. of cars");
    graphtot->SetMinimum(-1);
    graphtot->SetMaximum(15);
    graphtot->SetMarkerSize(0.5);
    graphtot->SetMarkerStyle(21);
    graphtot->SetLineWidth(2);
    graphtot->Draw("ALP");
    

    c1->Print("/home/lorenzo17/Roundabout2/data/graphicMeanRoads.pdf");
    c1->Print("/home/lorenzo17/Roundabout2/data/graphicMeanRoads.tex");
    c2->Print("/home/lorenzo17/Roundabout2/data/graphicTwo.pdf");
    c2->Print("/home/lorenzo17/Roundabout2/data/graphicTwo.tex");
}





void graphMeanSd(){
    int const N = 19;
    double mean[N] = {0,0.015603708, 0.032685895, 0.051219263, 0.07160916, 0.093947878, 0.118479325, 0.1454545, 0.175279175,0.208777875, 0.24655315, 0.289263375, 0.338111286, 0.3932684, 0.455113577, 0.614657295, 0.844215636, 1.20866, 1.876921};
    double sd[N] = {0,0.1248972, 0.180946925, 0.2268108, 0.26885495,0.309031525, 0.348625825, 0.388930875, 0.4299058, 0.4738901,0.521466825, 0.573076175, 0.631343036, 0.694298775,0.763543423, 0.93665, 1.18482, 1.57711, 2.277444};
    double sd2[N];
    double numeri[N]={0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,8,9,10,11};
    for(int i=0;i<N;i++){
        double a = sd[i]*sd[i];
        sd2[i]=a;
    }
    TCanvas* c = new TCanvas(""," ",800,600);
    TGraph* graph = new TGraph(N,numeri,mean);
    graph->SetTitle("Mean-Variance analysis");
    graph->GetXaxis()->SetTitle("Input flow");
    graph->GetYaxis()->SetTitle("Mean/Variance of the distributuon");
    graph->SetMinimum(-0.2);
    graph->SetMaximum(2.5);
    graph->SetMarkerSize(.5);
    graph->SetMarkerStyle(21);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);
    graph->Draw("ALP");

    TGraph* graph2 = new TGraph(N,numeri,sd2);
    graph2->SetMinimum(-0.2);
    graph2->SetMaximum(2.5);
    graph2->SetMarkerSize(.7);
    graph2->SetMarkerStyle(22);
    graph2->SetLineColor(kRed);
    graph2->SetLineWidth(2);
    graph2->Draw("PL,SAME");

    TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    leg->AddEntry(graph,"Mean values as obtained");
    leg->AddEntry(graph2, "Variance values as obtained");
    leg->Draw();
    c->Print("home/lorenzo17/Roundabout2/data/Mean_Variance_Analysis.pdf");
}