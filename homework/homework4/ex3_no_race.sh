#!/bin/bash
if [ ! -f "ex3.txt" ]; then
    echo 0 > ex3.txt
fi
for ((i=0;i<100;++i)); do
    (
        flock 3
        num=$(tail -1 ex3.txt)
        let "num=num+1"
        echo $num >> ex3.txt
    )3<>ex3.txt
done
