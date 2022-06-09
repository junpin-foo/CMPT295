/*
* Name: Jun Pin Foo
* Student number: 301414336
*/
#include <stdio.h>
#include <stdlib.h>


typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) { 
    size_t i;

    for (i = 0; i < len; i++){
		printf("0x%p", &start[i]); //print the memory address of the pointer
        printf("\t");
        printf("0x%.2x", start[i]); // print the value associcated with the address
        printf("\n");
    }
    printf("\n");
    return;	
}

//3b) The target machine is little endian because when showing the memory address and its 
//      content with function show_int(12345), which is 0x3039, we get 0x39 from the first memory 
//      address and 0x30 from the second. Thefore, the machine stores the Least Sig Bit in the lowest memory thus showing the little endian method. 

void show_bytes_2(byte_pointer start, size_t len) {
    size_t i;

    for (i = 0; i < len; i++){
        printf("0x%p", &*(start + i)); // using pointer notation to access the memory address and value in each address
        printf("\t");
        printf("0x%.2x", *(start + i)); 
        printf("\n");
    }
    printf("\n");
    return;		
}

void show_bits(int in) {

    char buffer[33] = {"00000000000000000000000000000000"}; //0-31 + \n //create 2 char array with all 0s to use as padding and storing bits
    char binary[33] = {"00000000000000000000000000000000"};

    int index = 31;
    int negative = 0;

    if(in < 0){ //flag to capture if the input value is negative as we need to do B2T
        in = abs(in);
        negative = 1;
    }

    while(in != 0){ //turning int to binary by using modulo 2 and keeping the remainder 1 bits starting from index 31 as it is the LSB
        if(in % 2 == 0)
            {binary[index] = '0';}
        else
            {binary[index] = '1';}

        index--;
        in = in/2;
    }

    if(negative == 1){ //doing twos complement by 

        for(int k = 0; k < 32; k++){ //flipping 1 to 0 and 0 to 1, using buffer to store flipped bits
            if(binary[k] == '0'){
                buffer[k] = '1';}
            else if(binary[k] == '1'){
                buffer[k] = '0';}
        }

        int carryIn = 1;

        for(int j = 31; j != -1 ; j--){ //and adding 1
        if(buffer[j] == '1' && carryIn == 1){
            binary[j] = '0';
        }
            else if(buffer[j] == '0' && carryIn == 1){
                binary[j] == '1';
                carryIn = 0;
            }
            else{
                binary[j] = buffer[j];
            }
        }
    }

    printf ("%s\n",binary); //if binary is positive just return binary normally but if negative we convert to 2s complement
}

int  mask_LSbits (int in){ //we first check the validity of input (whether it is >= w or is <= 0, these are the special cases)
    int max = sizeof(int) * 8;
    if(in >= max){
        in = 0x7fffffff; //is n >= w we assign input as the largest possible number represented by 32 bits
    }
    else if(in <= 0) //if its smaller we assign it as 0 
        in = 0;

    int masked = ( 1 << in ) - 1; //we shift 1 by input value as this is similar to 2^input, this puts a 1 in the bit after 2^input. Since binary is a bits multiplied by 2 and a single 1 bit, the MSB will always be 1 larger than the rest,
                                    // we take this largest 2^input bit and minus 1. Thus resulting in the masked value.
    return masked;

}

void show_int(int x) {
	printf("\nival = %d\n", x); 
    show_bytes((byte_pointer) &x, sizeof(int)); 
	show_bytes_2((byte_pointer) &x, sizeof(int)); 
	return;	
}

void show_float(float x) {
    printf("fval = %f\n", x); 	
    show_bytes((byte_pointer) &x, sizeof(float));
    show_bytes_2((byte_pointer) &x, sizeof(float)); 
    return;	
}

void show_pointer(void *x) {
	printf("pval = %p\n", x); 
    show_bytes((byte_pointer) &x, sizeof(void *));
    show_bytes_2((byte_pointer) &x, sizeof(void *));
	return;	
}
