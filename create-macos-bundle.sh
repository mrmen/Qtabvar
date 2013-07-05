#!/bin/bash

echo "Copying skel.ps to QTabVar.app/Contents/Ressources"
cp skel.ps QTabVar.app/Contents/Resources/
echo "Copying skel-variation.ps to QTabVar.app/Contents/Ressources"
cp skel-variation.ps QTabVar.app/Contents/Resources/

echo "Generate contents with macdeploy : macdeployqt QTabVar.app/ -dmg"
macdeployqt QTabVar.app/ -dmg

