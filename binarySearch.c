#include<stdio.h>
#include<stdlib.h>
int main(){
    int arr[10];
    for( int i =0;i<10;i++){ // add contents for the array
        arr[i]=i;
    }
    for( int i =0;i<10;i++){
        printf("%d\t",arr[i]);
    }
    // head to point at begining , mid to middle and tail to end
    int head,tail, mid;
    head=0;
    tail=(sizeof(arr)/sizeof(int))-1; // get the length of the array and set tail as last index
    mid=tail/2 ;
    int search=8; // number to be searched
    int flag=0; // flag for error (0==not found)
    while(head<=tail){
        printf("\nhead: %d, mid: %d, tail: %d",head,mid,tail);
        if(arr[mid]==search){ // if mid index element is the element print and break out of loop
            printf("\n%d is on Index %d",search,mid);
            flag=1;
            break;
        }
        else if(arr[mid]<search){ // if element at mid is less than search set head to index one step forward of mid
            head=mid+1;
        }
        else if(arr[mid]>search){ // if element at mid is larger than search set tail to index one step lower of mid
            tail=mid-1;
        }
        else{
            printf("\nWTF!! %d , %d ,%d",head,mid,tail); // IDK for something that happened for some reasons i dont know?
            break;
        }
        mid=(tail-head)/2 + head; // set mid to Middle DUH
    }
    if(flag==0){
        printf("\n%d Not FOUND",search); // if not found / flag=0
    }
    return 0;
}