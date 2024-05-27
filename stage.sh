#!/usr/bin/bash 
# ============================
# This file puts all the other files of the project into the ./staged.d/ directory so they can be properly uploaded to jutge.org
# ============================
directory="./tmp-stage.sh-$$"

mkdir $directory

cp ./src/* "$directory/" 
cp ./Makefile_jutge "$directory/Makefile"
# cp ./README.md "$directory/README.md"
cp ./Doxyfile_jutge "$directory/Doxyfile"

cd $directory
tar -cvf "../practica.tar" * 
cd ..

rm -rf $directory
unset directory
