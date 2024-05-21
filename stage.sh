#!/usr/bin/bash 

# This file puts all the other files of the project into the ./staged.d/ directory so they can be properly uploaded to jutge.org

directory="to_stage"
archive_name="./practica.tar"

mkdir "./$directory"

cp ./src/* "./$directory_name/" 
cp ./Makefile_jutge "./$directory_name/Makefile"
cp ./README.md "./$directory_name/README.md"
cp ./Doxyfile "./$directory_name/Doxyfile"

cd $directory
tar -cvf "../$archive_name" *
cd ..

rm -r "./$directory"
unset directory

