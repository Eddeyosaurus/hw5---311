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


const int BUFFMAX = 1024;

using namespace std;

int main(int argc, char* argv[])
{
    
    int readFD = 0, writeFD = 1, openFlags;
    mode_t mode;
    int* buffer;
    ssize_t rwAmmt;


    openFlags = O_RDONLY;
    
    mode = S_IRUSR | S_IWUSR | 
           S_IRGRP | S_IWGRP | 
           S_IROTH | S_IWOTH;

    if(argc > 2){
        errno = EACCES;
        perror("Usage: ./dumpArray [filename]\nExit Status: ");
        exit(EXIT_FAILURE);
    }

    if(argc == 2){
        readFD = open(argv[1], openFlags, 0);
    }
    
    //cout << "before while loop\n\n";
    rwAmmt = read(readFD, buffer, sizeof(int));
    

    while(rwAmmt){
        //write(writeFD, buffer, rwAmmt);
        cout << *buffer << endl;
        rwAmmt = read(readFD, buffer, sizeof(int));
    }



    return 0;
}
