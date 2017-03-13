#include <iostream>
#include <sys/types.h>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>



using namespace std;

const int BUFFSIZE = 1024;



int main(int argc, char* argv[])
{
    int readFD = 0, writeFD = 1, openFlags;
    string filename;
    mode_t mode;
    size_t rwAmmt;
    bool anscii = false;
    bool begin = false;
    bool end = false;
    int offset;

   openFlags = O_WRONLY | O_APPEND;
   mode = S_IRUSR | S_IWUSR | 
          S_IRGRP | S_IWGRP | 
          S_IROTH | S_IWOTH;


    if(argc == 1)
    {
        errno = EACCES;
        perror("Usage: ./xd [.. ] [filename]\n./xd -c --begin [offset] --end [offset] [filename]");
        exit(EXIT_FAILURE);
    }

    if(argc > 5)
    {
        perror("Usage: ./xd -c --begin [offset] --end [offset]\n");
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }

    if(argv[1] == "-c")
        anscii = true;
    
    if(argv[1] == "--begin" || argv[2] == "--begin")
        begin = true; 
    else if(argv[1] == "--end" || argv[2] == "--end")
        end == true;

    if(anscii && (begin || end)){
        offset = atoi(argv[3]);
        filename = argv[4];
    }
    else if(begin || end){
        offset = atoi(argv[2]);
        filename = argv[3];
    }
    else if(anscii){
        filename = argv[2];
    }
    else if(argc == 2){
        filename = argv[1];
    }
    

    readFD = open(filename.c_str(), openFlags, mode); 
    
    if(!readFD){
        errno = ENOENT;
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    if(begin)
        lseek(readFD, offset, SEEK_SET);
    else if(end)
        lseek(readFD, offset, SEEK_END);

    
    return 0;
}

    

