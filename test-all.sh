num_files=18

# removes any remnants of old tests
rm -f hw1.out;
gcc hw1.c -o hw1.out;

# iterates through our test files
for i in $(eval echo {1..$num_files})
do
    echo "[Test Case] Checking $i";

    # generates filenames
    infile=asn1-sampleio/set${i}_process.in
    outfile=asn1-sampleio/set${i}_process.out
    expected_out=asn1-sampleio/set${i}_processes.out

    # executes the program given infile and generates the outfile
    ./hw1.out $infile;

    # if we have an expected output file, diff with it
    if test -f $expected_out; then
        diff -i $outfile $expected_out > /dev/null
        diff_val=$?
        if [[ $diff_val != 0 ]]; then
            echo "fail (output does not match)"
        else
            echo "PASS!"
        fi
    fi

    # removes remnants
    rm -f $outfile;
done