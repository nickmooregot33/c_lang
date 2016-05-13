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
      - *offset* can be positive or negative but the file offset must be positive for regular files
        - because certain devices may allow negative file offset, testing for failure must explicitly use -1 instead of `test <0`
  - we can seek 0 bytes from the current position to get the current file offset, or see if the file is capable of seeking
    - if the descriptor refers to a pipe, FIFO, or socket, errno is set to ESPIPE and returns -1
      ```
          off_t currpos;
          currpos = lseek(fd, 0, SEEK_CUR);
      ```
  - setting the file offset past the end of the file just means the file will be extended on the next write
    - known as creating a hole in the file
    - hole in a file is not required to have storage for the empty bytes on disk, so different file system implementations will have different behavior
  - implementations are allowed to support whatever size off_t they want
    - find the implementation with the sysconf() function
      - _SC_V7_ILP32_OFF32 `=>` int, long, pointer, and off_t are all 32 bits
      - _SC_V7_ILP32_OFFBIG `=>` int, long, and pointer types are 32 bits; off_t types are ate least 64 bits
      - _SC_V7_LP64_OFF64  `=>` int types are 32 bits; long, pointer and aff_t types are 64 bits
      - _SC_V7_LP64-OFFBIG `=>` int tpes are at least 32 bits; long, pointer, and off_t types are at least 64 bits
  - lseed only modifies the current offset pointer in the file table entry.  no IO is done
  
- 3.7 read Function
  - ssize_t read(int fd, void* buf, size_t nbytes);
    - returns number of bytes read, 0 on EOF, and -1 on error
    - `#include <unistd.h>`
    - read data from an open file with read()
  - cases in which the number of bytes actually read is less than the amount requested
    - EOF is reached in a regular file before the requested number of bytes was read
    - when reading from a terminal device, normally up to 1 line is read at a time //see chapter 18
    - when reading from a network, buffering within the network may cause less than the requested amount to be returned
    - reading from a pipe or FIFO.  if the pipe contains fewer bytes than requested, read will return what is available
    - reading from a record-oriented device. some can return up to a single record at a time
    - when interrupted by a signal and a partial amount of data has already been read // see section 10.5
  - read starts at the file's current offset.  before it returns, the offset is incremented by the number of bytes read
  - old function prototype: `int read(int fd, char* buf, unsigned nbytes);`

- 3.8 write Function
  - `ssize_t write(int fd, const void* buf, size_t nbytes)`
    - `#include <unistd.h>`
    - returns: number of bytes written if OK, -1 on error
  - common cause for a write error
    - exceeding file size limit for a process // see exercise 10.11
    - filling up the disk //see section 7.11
  - write operation starts at the file's current offset 
  - if O_APPEND was used, the offset is set to the end of the file before each write operation
  - after a successful write, the offset is incremented by the number of bytes actually written
   
- 3.9 IO Efficiency
  - When dealing with IO buffers use a buffer size roughly equal to the block-size used in the file system for efficiency

- 3.10 File Sharing
  - This is a conceptual description.  Implementation details may differ
  - files opened in a program are represented by 3 data structures
    - process table entry (kernel implements the process table)
      - holds file descriptor flags //see section 3.14
      - holds a pointer to a file table entry
    - open file table entry (kernel maintains an open file table for all open files)
      - holds file status flags for the file (read, write, append, sync, nonblocking, etc)
      - holds current file offset `=>` every process will need its own offset pointer so every process gets its own entry for this file in the open file table
      - holds pointer to v-node table entry for the file
    - v-node structure (linux instead uses a generic i-node structure which is very similar.  This is part of the virtual file system)
      - holds information about the type of file and pointers to functions that operatie on the file (virtual file system stuff)
      - for most files the v-node contains a pointer to the inode table entry for the file's inode
      - two separate processes having the same file open will use the same v-node
  - subtleties arising from this system
    - after a write the current file offset is updated.  if this causes the file size to increase, the current file-size is updated in the i-node table entry
    - if a file is opened with O_APPEND, each time a write is performed, the file offset pointer is set to the current file size from the inode table entry, which forces every write to be appended to the end of the file
    - using lseek(fd,0,SEEK_END) causes the current file offset to be set to the current file size from the inode table entry
  - after a fork() parent and child share a same file table entry for each open descriptor
  - pay attention to the difference in scope for fd flags and file status flags.  file status flags are shared by all descriptors pointing to that file table entry, in case more than one descriptor is used for the same file, where fd flags are only for that file descriptor
  - understand surprises happen when multiple processes write to the same file

- 3.11 Atomic Operations
  - atomically read or write a file at a certain offset
    - ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);
      - `#include<unistd.h>`
      - returns number of bytes read, 0 on EOF, and -1 on error
      - does not update the current file offset
      - there is no way to interrupt the operation (acts like a critical section consisting of lseek, write, and then lseek back to where it was)
    - ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);
      - `#include<unistd.h>`
      - returns number of bytes read and -1 on error
      - does not update the current file offset
      - there is no way to interrupt the operation (acts like a critical section consisting of lseek, write, and then lseek back to where it was)
  - Creating a File
    - to create a file only if it does not exist, protecting the file that already exists:
      - `fd = open(path, O_WRONLY | O_CREAT | O_EXCL);`
      
- 3.12 dup and dup2 Functions
  - duplicate existing file descriptor
    - `int dup(int fd);`
      - `#include<unistd.h>`
      - returns new file descriptor if OK (lowest numbered unused file descriptor), -1 on error
    - `int dup2(int fd, int fd2);`
      - `#include<unistd.h>`
      - returns new file descriptor if OK (specified by fd2, which is closed if already open), -1 on error
      - if fd == fd2, dup2 returns fd2 without closing it.  
      - if fd2 != fd, FD_CLOEXEC file descriptor flag is cleared for fd2, so fd2 is left open if the process calls exec
      - dup2() is an atomic operation, so the close() followed by the open() kind of actions all happen without interruptions
    - returned file descriptor shares the same file table entry as the argument
  
  - 3.13 sync, fsync, and fdatasync Functions (for ensuring consistency of disk file with software buffer cache)
    - `void sync(void);`
      - normally called periodically (usually 30 second period) by a system daemon (often called 'update')
      - queues ALL modified block buffers for writing and returns
    - `int fsync(int fd);`
      - refers only to a single file and waits for disk writes to complete before returning
      - updates file attributes also
      - returns 0 if OK, -1 on error
    - `int fdatasync(int fd);`
      - similar to fsync(), bu affects only data portions of a file, not the file's attributes
      - returns 0 if OK, -1 on error

- 3.14 fcntl Function
  - `int fcntl(int fd, int cmd, ... /*int arg*/);`
    - returns -1 on error.  values for OK depend on the value of *cmd*
    - the third argument may be an integer or a pointer to a structure (used with records)
    - 'cmd' affects what fcntl() does
      - cmd == F_DUPFD or cmd == F_DUPFD_CLOEXEC: duplicate an existing descriptor
      - cmd == F_GETFD or cmd == F_SETFD: get or set file descriptor flags
      - cmd == F_GETFL or cmd == F_SETFL: get or set file status flags
      - cmd == F_GETOWN or cmd == F_SETOWN: get or set asynchronous IO ownership
      - cmd == F_GETLK or cmd == F_SETLK or cmd == F_SETLKW: get or set record locks
    - cmd possibilities
      - F_DUPFD
        - Duplicate the specified file descriptor and return the new one (lowest numbered one not already in use and is greater than the third argument to the function).  The new descriptor shares the same file table entry as fd, with its own file descriptor flags.  The FD_CLOEXEC file descriptor flag is cleared.
      - F_DUPFD_CLOEXEC
        - Duplicate the file descriptor and set the FD_CLOEXEC file descriptor flag associated with the new descriptor.  Returns the new file descriptor
      - F_GETFD
        - return the file descriptor flags for *fd*.  Currently, onle one file descriptor flag is defined: **FD_CLOEXEC**
      - F_SETFD
        - set the file descriptor flags for *fd*.  The new flag value is set from the third argument
      - F_GETFL
        - return the file status flags for *fd*. These were described in section 3.3
        - file status flags O_RDONLY, O_WRONLY, O_RDWR, O_EXEC, and O_SEARCH are mutually exclusive, and NOT 'one-hot', so to find out what was set of these, we have to use the O_ACCMODE mask to get the access-mode bits and then compare the result against any of the five values
      - F_SETFL
          - set the file status flags to the value of the third argument (integer).  The only flags that can be changed are O_APPEND, O_NONBLOCK, O_SYNC, O_DSYNC, O_RSYNC, O_FSYNC, and O_ASYNC.
      - F_GETOWN
        - get the process ID or process group ID currently receiving the SIGIO and SIGURG signals. //see section 14.5.2
      - F_SETOWN
        - set the process ID or process groUP ID to receive the SIGIO and SIGURG signals.  A positive *arg* specifies a process ID.  A negative *arg* implies a process group ID equal to the absolute value of *arg*.
       
    
