**************************
*  Alexandros Angelakis  *
*  csd4334@csd.uoc.gr    *
*  Αssignment1 - hy345   *
**************************

To compile and run the shell, simply type "make" and then "./csd4334sh" or "make run".

-There are 2 hardcoded commands: 1) "cd" and 2) "exit"

-All the commands in order to work properly, they need to be seperated by spaces (one or more) like: ls ; pwd ; whoami or echo "Hello world" | wc -w,
    but the same commands with no spaces will not work. For example if you have the command ls;pwd;whoami it won't work properly. The same goes to the 
    command echo "Hello world"|wc -w.

-Shell supports the execution of sequences of commands like: ls ; pwd ; whoami or ls -l ; mkdir test ; cd test.

-Shell supports multiple and simple pipes like: echo "Hello world" | wc -w or cat test.txt | sort | head -2.

-Shell supports only single redirections like cat < data.txt or ping -c 5 google.com > ping.txt,  but does not support multiple redirections like:
    cat < test.txt > test1.txt

All in all, the shell works as intended.