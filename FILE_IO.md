Advanced programming in the Unix Environment
===

Chapter 3
---
- 3.1 Introduction
  - most IO with files can be done with just open(), read(), write(), lseek(), and close()
  - this chapter is for *unbuffered* io
  - also covers dup(), fcntl(), sync(), fsync(), and ioctl() 

- 3.2 File Descriptors
  - kernel refers to all open files by file descriptors (non-negative integer)
  - file descriptor 0 => standard input (use STDIN_FILENO) defined in `<unistd.h>`
  - file descriptor 1 => standard output (use STDOUT_FILENO) defined in `<unistd.h>`
  - file descriptor 2 => standard error (use STDERR_FILENO) defined in `<unistd.h>`
  - file descriptors range from 0 to OPEN_MAX-1, use sysconf(_SC_OPEN_MAX) from `<unistd.h>` to find this value
    - see 2.5.4 for more info

- 3.3 getting new file descriptors (always the lowest-numbered unused file descriptor)
  - int open(const char* path, int oflag) or int open(const char* path, int oflag, mode_t mode) 
    - defined in `<fcntl.h>`
    - returns -1 on error
  - int openat(int dirfd, const char* path, int oflag) or int openat(int dirfd, const char* path, int oflag, mode_t mode)
    - also defined in `<fcntl.h>`
    - returns -1 on error
    - dirfd is a file descriptor of a specific directory to use as the beginning of a relative path.  If it's 'AT_FDCWD' or path is absolute then the absolute path is used or the current working directory is used as the directory
    - Useful in avoiding time-of-check-to-time-of-use errors (TOCTTOU)
  - options specified by oflag are ORed together:
    - exactly one of these must be specified
      - O_RDONLY: for reading only  //usually implemented as 0
      - O_WRONLY: for writing only  //usually implemented as 1
      - O_RDWR: for reading and writing //usually implemented as 2
      - O_EXEC: open for execute only
      - O_SEARCH: open for search only //applies to directories
        - this is a new option, which isn't commonly implemented yet.
        - this is for evaluating search permissons when the directory is opened, which will not be reevaluated on further operations
    - optional options
      - O_APPEND: append to the end of the file on each write
      - O_CLOEXEC: set FD_CLOEXEC file descriptor flag //section 3.14
      - O_CREAT: create the file if it doesn't exist, uses mode_t mode to specify access permission bits of the new file
      - O_DIRECTORY: generate an error if path isn't a directory
      - O_EXCL: generate an error if O_CREAT was used and the file exists, atomic operation //section 3.11
      - O_NOCTTY: if path is a terminal, do not allocate the device as the controlling terminal for the process //section 9.6
      - O_NOFOLLOW: generate an error if *path* refers to a symbolic link //section 4.17
      - O_NONBLOCK: if *path* is a fifo, block special file, or special character file, this sets nonblocking mode for both the opening of the file and further IO operations //section 14.2
      - O_SYNC: have each write wait for physical IO to complete, including IO necessary to update file attributes modified by the write //example in section 3.14
      - O_TRUNC: if the file exists and is successfully opened for either write-only or read-write, truncate its length to 0
      - O_TTY_INIT: when opening a terminal device not already open, set nonstandard termios parameters to values that result in behavior conforming to the Single Unix Specification.  //see chapter 18
      - O_DSYNC: used in synchronized IO
        - have each write wait for physical IO to complete, but don't wait for file attributes to be updated if they don't  affect the ability to read the data just written
        - subtly different to O_SYNC, O_DSYNC updates a file's attributes only when needed to reflect a change in the data, where O_SYNC updates data and attributes at the same time
      - O_RSYNC: used in synchronized IO
        - have each read op on the file descriptor wait until any pending writes for the same portion of the file are complete
  - Filename and pathname truncation
    - use long fpathconf(int fd, _PC_NAME_MAX) or long pathconf(const char* pathname, _PC_NAME_MAX) to get the maximum length of the a filename, not including null terminator
    - use long fpathconf(int fd, _POSIX_NO_TRUNC) or long pathconf(const char* pathname, _POSIX_NO_TRUNC) to see whether long pathnames are silently truncated or an error is thrown for a certain directory
      - if _POSIX_NO_TRUNC is in effect, errno is set to ENAMETOOLONG and an error is returned if any filename componeent of the pathname exceeds NAME_MAX

- 3.4 creat Function
  - int creat(const char* path, mode_t mode);
    - creates new file
    - returns file descriptor opened for write-only or -1 on error
    - equivalent to open(path,O_WRONLY | O_CREAT | O_TRUNC, mode);
      - open(path, O_RDWR | O_CREAT | O_TRUNC, mode); //even better when we want to be able to read what we wrote
    - defined in `<fcntl.h>`
    - used to be necessary because of fewer options in the second argument but now everything can be done with open()
- 3.5 close Function
  - int close(int fd); //defined in `<unistd.h>`
    - returns 0 if OK and -1 on error
    - when a process terminates, all of its open files are closed automatically by the kernel
    - also releases any record locks the process may have on the file //see section 14.3
- 3.6 lseek Function
  - off_t lseek(int fd, off_t offset, int whence); //defined in `<unistd.h>`
    - set's the file's offset
    - what is done with *offset* depends on *whence*
      - whence == SEEK_SET `=>` the file's offset is set to *offset* bytes from the beginning of te file
      - whence == SEEK_CUR `=>` the file's offset is set to it's current value plus *offset*
      - whence == SEEK_END `=>` the file's offset is set to the size of the file plus *offset*
      - *offset* can be positive or negative
    - we can seek 0 bytes from the current position to get the current file offset
```
            off_t currpos;
            currpos = lseek(fd, 0, SEEK_CUR);
```

 
