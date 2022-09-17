input_files=("set1_process" "set2_process" "set3_process" "set4_process");

rm hw1.out;
gcc hw1.c -o hw1.out;

for i in "${input_files[@]}"
do
    echo "[Test Case] Checking $i";
    ./hw1.out asn1-sampleio/${i}.in;
    diff -i asn1-sampleio/${i}.out asn1-sampleio/${i}es.out > /dev/null
    diff_val=$?
    if [[ $diff_val != 0 ]]; then
        echo "fail (output does not match)"
    else
        echo "PASS!"
    fi
    rm asn1-sampleio/${i}.out;
done