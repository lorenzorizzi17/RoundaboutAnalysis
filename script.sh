#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10
do
sudo ./roundaboutng.out
root -b -l <<EOF
.L histo.cpp
histo();
EOF
done