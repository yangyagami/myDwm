#!/bin/bash

make -j4 && sudo make install
ln -sfr scripts $HOME/scripts
ln -sfr Wallpapers $HOME/Pictures/Wallpapers
