/*This is notes about stdio.h as taken from Kernighan and Ritchie ~1989 publication describing the C standard library*/


//fopen opens the named file, and returns a stream, or NULL if the attempt fails
FILE *fopen(const char* filename, const char* mode);

//freopen opens the file with the specified mode and associates the stream with it.
//
FILE* freopen(const char* filename, const char* mode, FILE* stream);
