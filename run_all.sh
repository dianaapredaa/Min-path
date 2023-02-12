#!/bin/bash

runTest=$1

for file in in/*; do
    cp $file "test.in"

    ./$runTest

    outName=${file%".in"}
    outName=${outName#"in/"}
    mv "test.out" "out/$runTest/$outName.out"
done