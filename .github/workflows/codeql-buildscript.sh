#!/usr/bin/env bash

sudo apt-get install -y libfftw3-dev
sudo apt-get install -y libconfig-dev
sudo apt-get install -y libasound2-dev
sudo apt-get install -y libpulse-dev
mkdir build && cd build
cmake ../
make
