#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3){
        errno = EACCES;
        perror("Usage: ./sorter [inputFile] [outputFile]\nExit Status: ");
        exit(EXIT_FAILURE);
    }
    
    int a = -1, b = -1, a1 = -1, b1 = -1;
    int result[100];
    int left_a[25], right_a[25], left_b[25], right_b[25];
    int readFD = 0, writeFD = 1, openFlags;
    mode_t mode;
    int* buffer;
    ssize_t rwAmmt;


    openFlags = O_RDONLY;
    
    mode = S_IRUSR | S_IWUSR | 
           S_IRGRP | S_IWGRP | 
           S_IROTH | S_IWOTH;


    readFD = open(argv[1], openFlags, mode);
    writeFD = open(argv[2], O_WRONLY, mode);

    for(int i = 0; i < 100; i++)
    {
       read(readFD, &result[i], sizeof(int));
       //cout << buffer << endl;
    }


    int count = 0;
    for(int i = 0; i < 100; i++)
    {   
        if(count == 25)
            count = 0;

        if(i < 25)
            left_a[count] = result[i];
        else if(i < 50)
            right_a[count] = result[i];
        else if(i < 75)
            left_b[count] = result[i];
        else if(i < 100)
            right_b[count] = result[i];

        count++;
    }
    
    /*for(int i = 0; i < 100; i++){
        if(count == 25)
            count = 0;

        
        if(i < 25)
            cout << left_a[count] << endl; 
        else if(i < 50)
            cout << right_a[count] << endl;
        else if(i < 75)
            cout << left_b[count] << endl;
        else if(i < 100)
            cout << right_b[count] << endl;
           
        count++;
    }*/

    a = fork();

    if(a == 0){
        b = fork();

        if(b == 0){
            b1 = fork();

            if(b1 == 0){
                cout << "\n\n\n\nthis is b1\n\n\n\n";
            }
            else
                cout << "\n\nt\n\nhis is b\n\n\n\n";
        }
        else {
            a1 = fork();

            if(a1 == 0){
                cout << "\n\n\n\nthis is a1\n\n\n\n";
            }
            else
                cout << "\n\n\n\nthis is a\n\n\n\n";
        }
           
    }
       

   

    /*for(int i = 0; i < 100; i++){
        if(count == 25){
            count = 0;
            cout << endl << endl;
        }

        
        if(i < 25)
            cout << left_a[count] << endl; 
        else if(i < 50)
            cout << right_a[count] << endl;
        else if(i < 75)
            cout << left_b[count] << endl;
        else if(i < 100)
            cout << right_b[count] << endl;
           
        count++;
    }*/

    return 0;
}
