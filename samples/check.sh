#!/usr/bin/bash
for file in ./samples/*.inp;
do	
	name="$(basename "$file" .inp)"
	echo "[!] Running $name"
	./target/program < "./samples/$name.inp" > "./target/$name.out"
done
for file in ./samples/*.cor;
do
	name="$(basename "$file" .cor)"
	echo "[=] Running diff on $name:"
	diff "./target/$name.out" "./samples/$name.cor" > "./target/$name.diff"  && echo "[+] Matched expected output" || echo "[-] Error: Output didn't match test samples"
done 
