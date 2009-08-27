#!/bin/sh

FILE=intermediate_200.txt

echo "# Profiling using $FILE"
echo "# minsup win systime usrtime return"
for min_sup in `seq  0.00010 0.0001 0.001`
do
    for w_size in `seq 5 16`
    do
        echo -n $min_sup $w_size
        time -f " %S %U %x" python apriori_extragen.py $FILE -m $min_sup -w $w_size 3>&1 1>window_$min_sup\_$w_size.out 2>&3 3>&-
    done
done
