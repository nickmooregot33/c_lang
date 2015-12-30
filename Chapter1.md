1 Introduction
===
typical stuff.  OSes provided services, like opening files, executing programs, allocating memory, etc

2. Unix Architecture
===
- OS controls the hardware, and provides environment where programs can run.
- This is the kernel (small and at the center). Software interacts with the kernel with system calls.  
- Libraries are built on top of system calls, but we don't need to use libraries

- The shell provides an interface for running other applications.

3. Logging in
===
- Enter your login name, then your password
- system looks up the name in password file, usually: /etc/passwd

/etc/passwd
---
- 7 fields delimited by :

login-name:x-denotes-space-for-encrypted-password:numeric-user-ID:numeric-group-ID:comment:home-directory:default-shell

ex: sar: x:205:105:Nick Moore:/home/nick:/bin/bash

encrypted passwords are in a different file now, hence the x

Shells
---
common shells:
- Bourne:               sh
- Bourne-again-shell:   bash
- C shell:              csh
- Korn shell:           ksh
- TENEX C shell:        tcsh
  
- in linux, sh and csh link to bash and tcsh respectively
  
4. Files and Directories
===
/ is top of file tree, everything is a file

**directory:**
    file that contains directory entries
    
**directory entry:**
    has a filename and a structure of info describing the file attributes
    
**file attributes:**
- type of file: [regular, directory]
- filesize
- file owner
- file permissions
- file's last modification time
    
**functions that return file attributes of a file:**
- stat, fstat
    
filename
---
- disallowed characters: / and ' '
- every directory includes filenames . and .. (current directory and parent directory)

Pathname
---
- absolute paths -- begin with /
- relative paths -- begin with directory name other than /

Working Directory
---
- every process has one
- all relative pathnames are based on this
- use * **chdir** *function to change working directory

Home Directory
---
- working directory is set to this on login
- home directory is pulled from the user's entry in /etc/passwd

5. Input and Output
===
File Descriptors
---
- non-negative integers
- usually small
- kernel uses them to identify the files being accessed by a particular process
- whenever it opens an existing file or creates a new one, the kernel returns a file descriptor we use when we read or write the file

Standard Input, Output, and Error
---
- these are file descriptors, and all shells open all three whenever a new program is run
- all three are by default connected to terminal
- can be redirected to a different stream

Unbuffered IO
---
**provided by the following functions, which all work with file descriptors:**
- open
- read
- write
- lseek
- close

