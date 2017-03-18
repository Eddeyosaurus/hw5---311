#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3){
        errno = EACCES;
        perror("Usage: ./sorter [inputFile] [outputFile]\nExit Status: ");
        exit(EXIT_FAILURE);
    }

    int a = -1, b = -1, a1 = -1, b1 = -1;
    int initArr[100];
    int left_a[25], right_a[25], left_b[25], right_b[25];
    int * bottom;
    int * top;
    int * result;
    int readFD = 0, writeFD = 1, openFlags;
    mode_t mode;
    int* buffer;
    ssize_t rwAmmt;

    bottom = (int*)mmap(NULL, sizeof(int)*50, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    top = (int*)mmap(NULL, sizeof(int)*50, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    result = (int*)mmap(NULL, sizeof(int)*100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    openFlags = O_RDONLY;

    mode = S_IRUSR | S_IWUSR |
           S_IRGRP | S_IWGRP |
           S_IROTH | S_IWOTH;


    readFD = open(argv[1], openFlags, mode);
    writeFD = open(argv[2], O_WRONLY, mode);

    for(int i = 0; i < 100; i++)
    {
       read(readFD, &initArr[i], sizeof(int));
       //cout << buffer << endl;
    }

    int count = 0;
    for(int i = 0; i < 100; i++)
    {
        if(count == 25)
            count = 0;

        if(i < 25)
            left_a[count] = initArr[i];
        else if(i < 50)
            right_a[count] = initArr[i];
        else if(i < 75)
            left_b[count] = initArr[i];
        else if(i < 100)
            right_b[count] = initArr[i];

        count++;
    }

    a = fork();


    if(a == 0){
        b = fork();

        if(b == 0){
            b1 = fork();

            if(b1 == 0){
              sort(left_b, left_b+25);
            }
            else{
              sort(right_b, right_b+25);
              waitpid(b1, NULL, 0);
              merge(left_b, left_b+25,right_b, right_b+25, top);
            }
        }
        else {
            a1 = fork();

            if(a1 == 0){
                sort(right_a, right_a+25);
            }
            else{
                sort(left_a, left_a+25);
                waitpid(a1, NULL, 0 );
                merge(left_a, left_a+25, right_a, right_a+25, bottom);
                waitpid(b, NULL, 0);
                waitpid(a1, NULL, 0);
                waitpid(b1, NULL, 0);
                merge(bottom, bottom+50, top, top+50, result);
              }

        }

    }



    for(int i = 0; i < 100; i++){
        cout << result[i] << endl;
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
