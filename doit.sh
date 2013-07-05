#!/bin/bash
#
#
#    Thomas "Mr Men" Etcheverria
#    <tetcheve (at) gmail .com>
#
#    Created on : 09-05-2013 13:56:08
#    Time-stamp: <05-07-2013 01:55:57>
#
#    File name : /home/mrmen/QTabVar/src/doit.sh
#
#    Description : This file allow you to modify
#     path according to your compile option
#
DEBUG=0
newpath="${1}/share/QTabVar"

if [ ${1} == "debug" ]; then
    newpath="."
fi


log(){
    if ((DEBUG==1)); then
	echo $1
    fi
}

if (($#!=1)); then
    log "No path given. Choosing . for you."
    if [ $(uname) != "Darwin" ]; then
	sed -i '8i\#define PATH \".\"' PScode.cpp
    fi
    exit 0
fi

log "Your install path is :  $newpath"
log "Modify source files to access postscript skel"

rValue=$(grep '#define PATH' PScode.cpp)

if [ -z "$rValue" ]; then
    log "Path definition not found. Adding it on line 8"
    if [ $(uname) != "Darwin" ]; then
	sed -i '8i\#define PATH \"'$newpath'\"' PScode.cpp
    fi
    exit 0
else
    log "Path definition found. Exiting."
    exit 0
fi
