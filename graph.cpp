


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
    TGraph* graphtot = new TGraph(9,fluxin, meanTotal);


    TCanvas *c1 = new TCanvas("","",1000,700);
    c1->Divide(2,2);
    c1->cd(1);
    
    graph1->SetTitle("Road 1");
    graph1->SetMarkerSize(0.5);
    graph1->SetMarkerStyle(21);
    graph1->SetLineColor(40);
    graph1->SetLineWidth(2);
    graph1->Draw("ALP");

    c1->cd(2);
    
    graph2->SetTitle("Road 2");
    graph2->SetMarkerSize(0.5);
    graph2->SetMarkerStyle(21);
    graph2->SetLineColor(30);
    graph2->SetLineWidth(2);
    graph2->Draw("ALP");

    c1->cd(3);  
    
    graph3->SetTitle("Road 3");
    graph3->SetMarkerSize(0.5);
    graph3->SetMarkerStyle(21);
    graph3->SetLineColor(46);
    graph3->SetLineWidth(2);
    graph3->Draw("ALP");

    c1->cd(4);
    
    graph4->SetTitle("Road 4");
    graph4->SetMarkerSize(0.5);
    graph4->SetMarkerStyle(21);
    graph4->SetLineColor(42);
    graph4->SetLineWidth(2);
    graph4->Draw("ALP");


    TCanvas* c2 = new TCanvas("","",800,700);
    c2->Divide(1,2);
    c2->cd(1);
    graph1->Draw("ALP");
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
    graphtot->SetTitle("Mean value (all road considered)");
    graphtot->SetMarkerSize(0.5);
    graphtot->SetMarkerStyle(21);
    graphtot->SetLineWidth(2);
    graphtot->Draw("ALP");
    

    c1->Print("/home/lorenzo17/Roundabout2/histopdf/graphicMeanRoads.pdf");
    c1->Print("/home/lorenzo17/Roundabout2/histopdf/graphicMeanRoads.tex");
    c2->Print("/home/lorenzo17/Roundabout2/histopdf/graphicTwo.pdf");
    c2->Print("/home/lorenzo17/Roundabout2/histopdf/graphicTwo.tex");
}