read -p "[?] Please enter sample input name (withouth .inp) :" file
./correct_bin < "./$file.inp" > "./$file.cor"
echo "[+] Sample properly generated"
