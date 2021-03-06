#RSHELL 

Shell Terminal for UCR CS100 Software Construction Course


##Install
To install and run rshell, enter the following into a terminal: 

```
1. git clone http://www.github.com/markasfour/rshell.git

2. cd rshell

3. git checkout hw0

4. make

5. bin/rshell
```

##Program Features
Rshell runs all bash commands

Rshell supports the use of connectors such as ```;```, ```&&```, and ```||```

Rshell supports left to right connector logic sequencing (i.e. ```ls && pwd || exit``` would result in ```ls``` being evaluated first, ```pwd``` being evaluated next, and ```exit``` being evaluated last) 

Rshell provides proper error messages for use of improper syntax and invalid commands

Rshell allows for the use of commenting through the use of ```#```

Rshell trims excess spaces in the command line

Rshell has a custom exit command allowing the user to exit by running ```exit``` 

Rshell displays the the user name and the host name in the ready prompt

##Dependencies
The ```boost``` library is required to run the tokenizing method in Rshell


##Bugs and Limitations
Host name is limited to 64 characters

Commands such as ```cd``` are not supported in this make of Rshell

Piping is not supported in this make of Rshell

Colors for files, directories, etc. are not supported in this make of Rshell

Text navigation (such as arrow keys) is not supported by this make of Rshell

Up arrow key does not run the previous command

```echo "hello world"``` will include the quotation marks


#LS

Terminal command that lists files and directories that can have `-a`, `-l`, and `-R` flags.


##Install
To install and run `ls`, enter the following into a terminal: 

```
1. git clone http://www.github.com/markasfour/rshell.git

2. cd rshell

3. git checkout hw1

4. make

5. bin/ls
```

##Program Features
`ls` can display all files and directories.

File and directory arguments can be passed in with optional flag arguments.

`ls` can display hidden files and directories with the `-a` flag.

`ls` can display information about files and directories with the `-l` flag.

`ls` can be used recursively with the `-R` flag.

Flags can be mixed and matched such as `-a -l` or `-al`.

Flags can be used multiple times for the same effect (`-a` is the same as `-aaaa`).

Output is color coded to indicate hidden files with a grey background, directories with blue text, and executables with green text.

Output is formatted into equal column widths.

Output is formatted in alphabetical order from left to right.


##Bugs and Limitations
Terminal width is assumed to be 80 characters wide.

Unlike the actual `ls` program, only the `-a`, `-l`, and `-R` flags can be used.

Passing in an improper flag will terminate the program.

Issue with UCR's `hammer` server causes the error `do_ypcall: clnt_call: RPC: Unable to send; errno = Operation not permitted` on random occassions.

Multiple `-` in a parameter will be ignored (`--a` will work the same as `-a`)

The grey background for hidden files extends the full width of its column.
