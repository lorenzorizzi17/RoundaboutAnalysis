


void graph(){

    double x[10] = {8,9,9.5,10,10.5,11,11.5,12,12.5,13};
    double y[10] = {0.6,0.819, 0.982,1.182,1.458,1.822,2.411,3.41,6.09,15.49};

    TGraph* graph = new TGraph(10, x, y);
    graph->Draw("AC*");
}