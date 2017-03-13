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
#include <algorithm>
#include <bitset>

using namespace std;

const int ARRMAX = 100;

char* itoa(int val, char* result, int base);

int main(int argc, char* argv[])
{
    int arr[100];
    int outFD;
    int flag;
    mode_t mode;
    char buffer[100];

    if(argc == 2){
        string filename = argv[1];
        flag = O_CREAT | O_WRONLY | O_TRUNC;
        mode = S_IRUSR | S_IWUSR | 
               S_IRGRP | S_IWGRP | 
               S_IROTH | S_IWOTH;

        //close(1);
       outFD = open(filename.c_str(), flag, mode);  
    }
    else if(argc > 2){
        errno = EINVAL;
        perror("usage: ./makeArray [filename]: ");
        exit(EXIT_FAILURE);
    }
    else if(argc == 1){
        outFD = 1;
    }
   
    srand(time(NULL));

    for(int i = 0; i < ARRMAX; i++){
        arr[i] = rand() % 10000 + 1;          
    }
    
    

    

    for(int i = 0; i < ARRMAX; i++){
        //string binary = bitset<8>(arr[i]).to_string();
        //char newline [2] = "\n";
        //buff = arr[i];
        //char * buff;
        //itoa(arr[i], buffer, 2);
        write(outFD, &arr[i], sizeof(int));
        //write(outFD, newline, sizeof('\n'));
    }


    return 0;
}

char* itoa(int value, char* result, int base)
{
    if(base < 2 || base > 36){
        *result = '\0';
        return result;
    }

    char* out = result;
    int quotient = value;

    do{
        *out = "0123456789abcdef"[std::abs(quotient%base)];
        ++out;
        quotient /= base;
    }while(quotient);

    if(value < 0 && base == 10)
       *out++ = '-';

    std::reverse(result, out);
    
    *out = 0;

    return result;
}
