useradd newuser
ps -e
top
cat /dev/urandom | head -n 10 | tee 1.txt > 2.txt
cat 1.txt 2.txt > 3.txt
od -t x 3.txt
grep -lwr --include='*semaphore*' 'ddekit_sem_down' /usr/src