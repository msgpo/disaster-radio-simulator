#!/bin/bash

set -e

rm -rf libs

mkdir -p libs
cd libs/

git clone https://github.com/sudomesh/LoRaLayer2
cd LoRaLayer2/
git checkout 3f650076c1e1ff97d33c8aab20fb844528822542
cd ../

git clone https://github.com/sudomesh/disaster-radio
cd disaster-radio/
git checkout 875396a7c679d5105ec5e587ba295c2a486609b5
cd ../

git clone https://github.com/bombela/backward-cpp
cd backward-cpp
git checkout v1.5
cd ../..
