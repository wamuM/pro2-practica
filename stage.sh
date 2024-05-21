#!/usr/bin/bash 

# This file puts all the other files of the project into the ./staged.d/ directory so they can be properly uploaded to jutge.org

directory="./to_stage"
archive_name="./practica.tar"

mkdir $directory

cp ./src/* "$directory/" 
cp ./Makefile_jutge "$directory/Makefile"
cp ./README.md "$directory/README.md"
cp ./Doxyfile "$directory/Doxyfile"

tar -cvf $archive_name $directory/*
 
rm -rf $directory
unset directory

