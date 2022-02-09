#include <stdlib.h>
#include <stdio.h>

#define BUFF_SIZE 6

int buff[BUFF_SIZE];
int wr;
int rd;
int length;


void wr_buffer(int data);
int rd_buffer();



void wr_buffer(int data){
    if(wr == BUFF_SIZE) //Buffer is full
	wr = 0;

    buff[wr] = data;

    wr++;
    length++;
}


int rd_buffer(){
    if(rd == BUFF_SIZE) //Buffer empty
	rd = 0;

    int rd_data = buff[rd];

    rd++;
    length--;

    return rd_data;
}

int main(){
    wr = 0;
    rd = 0;
    length = 0;

    int i;
    for(i = 0; i <= 9; i++){
	wr_buffer(i);
    }

    for(i = 0; i < BUFF_SIZE; i++){
	int d = rd_buffer();
	printf("%d ", d);
    }
    printf("\n");
}
