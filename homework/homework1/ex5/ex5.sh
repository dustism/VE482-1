#bin/bash
# 1. Create a new user
useradd newuser
# 2. List all the currently running processes
ps -e
# 3. Display the characteristics of the CPU and the available memory
top
# 4. Redirect some random output into two different files
od /dev/urandom | head | tee 1.txt > 2.txt
# 5. Concatenate the two previous files
cat 1.txt 2.txt > 3.txt
# 6. Read the content of the resulting file as hexdecimal values (in other words find a command to read a file as hexadecimal values)
od -t x 3.txt
# 7. Use a single command to find all the files in /usr/src with the word semaphore in their name and containing the word ddekit sem down
find /usr/src -name '*semaphore*' | xargs grep -lw 'ddekit_sem_down'
