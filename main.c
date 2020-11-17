#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int ran(){
    int n;
    int fin = open("/dev/random",O_RDONLY);
    int e = read(fin,&n,sizeof(int));
    if(e < 0){
        printf("Error Number %d: %s\n",errno,strerror(errno));
        close(fin);
        return -1;
    }
    close(fin);
    return n;
}

int main(){
    int i;
    int arr[10];
    int arr1[10];
    int e;
    for(i = 0; i < 10; i++){
        arr[i] = ran();
    } 
    for(i = 0; i < 10; i++){
        printf("%d\n",arr[i]);
    }
    printf("\n\n");
    int fout = open("file.txt",O_WRONLY);
    e = write(fout,&arr,10 * sizeof(int));
    if(e < 0){
        printf("Error Number %d: %s\n",errno,strerror(errno));
        return 0;
    }
    close(fout);
    int fin = open("file.txt",O_RDONLY);
    e = read(fin,&arr1,10 * sizeof(int));
    if(e < 0){
        printf("Error Number %d: %s\n",errno,strerror(errno));
        return 0;
    }
    for(i = 0; i < 10; i++){
        printf("%d\n",arr1[i]);
    }
    close(fin);
    return 0;
}