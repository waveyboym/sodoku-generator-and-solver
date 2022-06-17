# sudoku-generator-and-solver

can generate a new sudoku puzzle and solve it. The number of open spots can also be changed in the main files for both the C++ and Java version.
the code may only be compiled and run in a linux environment

#if you dont want to compile on your device and want a quick run click here:
1. java: https://onlinegdb.com/2zbOA9wfL (click the run button in order to run the file)
2. c++ : https://onlinegdb.com/MZjAj-l8b (click the run button in order to run the file)

#to run this code you will need to install: 
1. make: https://linuxhint.com/install-make-ubuntu/
2. valgrind: https://wiki.ubuntu.com/Valgrind
3. gcc: https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/
4. zip(optional): https://speedysense.com/zip-and-unzip-command-in-ubuntu-terminal/
5. unzip(optional): https://speedysense.com/zip-and-unzip-command-in-ubuntu-terminal/
6. gdb: http://www.gdbtutorial.com/tutorial/how-install-gdb
7. jre: https://ubuntu.com/tutorials/install-jre#1-overview


#to run the code:

1. open a terminal in the directory where the file is located, so if you wanted to test run the c++ version, you would open a terminal in a directory like so: "parent_directory/child_directory/c++"
2. type in the command make to compile the files
3. type in the command make run to run the files
4. type in make clean to clear out compilation files after running

#shared commands
1. make - compiles files
2. make run - runs the compiled files
3. make clean - cleans out the compiled files

#c++ commands
1. make vangaurd - checks for memory leaks and reports if any are found
2. make gdb - opens up the gdb debugging tool in the terminal

#java commands
1. make jdb - opens up the jdb debugging tool in the terminal
