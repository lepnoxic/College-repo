# Lab 1

Lab Exercises
1. Execute and write output of all the commands explained so far in this manual.
- man
```sh
$ man man
MAN(1)                                                      Manual pager utils                                                      MAN(1)

NAME
       man - an interface to the system reference manuals

SYNOPSIS
```
- ls
```
$ ls
Desktop  Documents  Downloads  Music  Pictures  Public  snap  Templates  Videos
```
- cat
```
$ cat test.txt
Hello world!
```
- cd
```
~$ cd ..
/home$ cd ..
/$ 
```
- pwd
```
/$ pwd
/
/$ cd /usr/lib
/usr/lib$ pwd
/usr/lib
```
- touch
```
$ touch test.txt
$ ls
test.txt
```
- file
```
$ file OS_Lab1.pdf 
OS_Lab1.pdf: PDF document, version 1.7
```
- head
```
$ head cathelp.txt 
Usage: cat [OPTION]... [FILE]...
Concatenate FILE(s) to standard output.

With no FILE, or when FILE is -, read standard input.

  -A, --show-all           equivalent to -vET
  -b, --number-nonblank    number nonempty output lines, overrides -n
  -e                       equivalent to -vE
  -E, --show-ends          display $ at end of each line
  -n, --number             number all output lines
```
- tail
```
$ tail cathelp.txt
      --help     display this help and exit
      --version  output version information and exit

Examples:
  cat f - g  Output f's contents, then standard input, then g's contents.
  cat        Copy standard input to standard output.

GNU coreutils online help: <https://www.gnu.org/software/coreutils/>
Full documentation at: <https://www.gnu.org/software/coreutils/cat>
or available locally via: info '(coreutils) cat invocation'
```
- cp
```
$ ls
README.md
$ ls ..
lab1 test.txt
$ cp ../test.txt .
$ ls
README.md  test.txt
$ ls ..
lab1 test.txt
```
- mv
```
$ ls
README.md
$ ls ..
lab1 test.txt
$ mv ../test.txt .
$ ls
README.md  test.txt
$ ls ..
lab1
```
- rm
```
$ ls
README.md  test.txt
$ rm test.txt
$ ls
README.md
```
- mkdir
```
$ pwd
/home/STUDENT/Documents/220911590/lab1
$ mkdir testdir
$ cd testdir
$ pwd
/home/STUDENT/Documents/220911590/lab1/testdir
```
- rmdir
```
$ ls
README.md  testdir
$ rmdir testdir
$ ls
README.md
```
- which
```
$ which sh
/usr/bin/sh
```
- whereis
```
$ whereis sh
sh: /usr/bin/sh /usr/share/man/man1/sh.1.gz
```
- locate
```
$ locate cron.list
/var/lib/dpkg/info/anacron.list
/var/lib/dpkg/info/cron.list
```
- find
```
$ find *a*
cathelp.txt
lab1
lab1/README.md
OS_Lab1.pdf
```

2. Explore the following commands along with their various options. (Some of the options are specified in the bracket)
  - cat (variation used to create a new file and append to existing file)
  - head and tail (-n, -c )
  - cp (-n, -i, -f)
  - mv (-f, -i) [try (i) mv dir1 dir2 (ii) mv file1 file2 file3 ... directory]
  - rm (-r, -i, -f)
  - rmdir (-r, -f)
  - find (-name, -type)
3. List all the file names satisfying following criteria
  - has the extension .txt.
  - containing atleast one digit.
  - having minimum length of 4.
  - does not contain any of the vowels as the start letter.
