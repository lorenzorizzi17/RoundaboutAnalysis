#include<iostream>
#include<fstream>
#include"TGraph.h"

void timeseries() {
    TGraph* graph = new TGraph("timeseries.dat", "%lg %lg");
    graph->Draw();

}