#/usr/bin/env bash

../configure $@ 

if [ "$1" != "-h" ]; then
    if [ ! -f Makefile ]; then
        echo
        echo "Configuration has failed. No Makefile has been generated"
        exit
    fi
    echo
    echo " -------- Compiling SmartHistos --------"
    make
    echo " -------- Installing SmartHistos --------"
    make install
fi
