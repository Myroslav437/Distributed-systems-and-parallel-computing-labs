#!/bin/bash

for i in {1..50}
do
    echo $(./mpoint -t $i test.txt | grep time);
done

echo 
echo "Finished";