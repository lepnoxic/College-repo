# Lab 2

* Execute all the commands explained in this section and write the output.
  * grep
    ```
    $ cat something.txt
    ini mini maini mo
    hello world
    $ grep world something.txt
    hello world
    ```
  * sort
    ```
    $ sort something.txt
    hello world
    ini mini maini mo
    ```
  * wc
  * cut
  * sed
  * tr
    ```
    $ echo "hello world" | tr 'a-z' 'A-Z'
    HELLO WORLD
    ```
  * ps
    ```
    $ ps
      PID TTY          TIME CMD
     2919 pts/0    00:00:00 bash
     3962 pts/0    00:00:00 ps
    ```
  * kill
    ```
    $ cat - &
    [1] 4006
    $ kill -9 4006

    [1]+  Stopped                 cat -
    [1]+  Killed                  cat -
    ```
  * chmod
    ```
    $ echo "echo 'script successful'" > myscript.sh
    $ ./myscript.sh
    bash: ./myscript.sh: Permission denied
    $ chmod +x ./myscript.sh 
    $ ./myscript.sh 
    script successful
    ```
  * echo
  * bc
  * vi
* Write grep commands to do the following activities:
  * To select the lines from a file that have exactly two characters. 
  * To select the lines from a file that start with the upper case letter.
  * To select the lines from a file that end with a period.
  * To select the lines in a file that has one or more blank spaces.
  * To select the lines in a file and direct them to another file which has digits as one of the characters in that line.  
* Create file studentInformation.txt using vi editor which contains details in the following format:
  RegistrationNo:Name:Department:Branch:Section:Sub1:Sub2:Sub3
  1234:XYZ:ICT:CCE:A:80:60:70
  1) Display the number students (only count) belonging to ICT department.
  2) Replace all occurences of IT branch with "Information Technology" and save the output to ITStudents.txt
  3) Display the average marks of student with the given registration number "1234" (or any specific existing number).
