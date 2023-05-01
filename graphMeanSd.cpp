



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
    c->Print("Mean_Variance_Analysis.pdf");
}