for file in "./samples/*.inp";
do	
	name = $(basename -s .inp $file)
	./target/program < file > "./target/${name}.out"
done
for file in "./samples/*.cor";
do
	name = $(basename -s .cor $file)
	echo "[=] Running diff on $name:"
	diff ./target/${name}.out $file > "./target/${name}.diff" && echo "[-] Error: Output didn't match test samples" || echo "[+] Matched expected output"
done 


