//
//  main.cpp
//  bit-parallel approximate string
//
//  Created by gangliao on 10/9/14.
//  Copyright (c) 2014 gangliao. All rights reserved.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;

#define INDEX(c)    (c)
#define BIT 1 << 31


//according to the pattern p, initializing all the positions into the set container
void initSet(string p /*pattern*/, unsigned int* set)
{
    for (int i = 0; i < 31; i++) {
        set[INDEX(p[i])] = set[INDEX(p[i])] | (1 << (31-i));
    }
    
}

void read_data(char *filename, char *buffer, int num){
    FILE *fh;
    fh = fopen(filename, "r");
    fread(buffer, 1, num, fh);
    buffer[num] = '\0';
    fclose(fh);
}

int main(int argc, const char * argv[])
{
    
    clock_t start, end;
    char* filename = "/the local address of data sets";
    int n;										//input size
    char *text;									//data set pointer
    double runTime;
    
    printf("Please input the size of dataset you want to evaluate: \t");
    scanf("%d", &n);
    
    text = (char *) malloc((n+1)*sizeof(char));
    read_data(filename, text, n);
    
    //pattern length = 32
    string pattern = "Project Gutenberg Etexts are usually created from multiple editions";

  
    //asuume the numbers of error k is 10
    int k = 1; // allowed errors
    
    unsigned int set[256]; // all the postions of each character c in pattern p
    
    memset(set, 0, sizeof(int)*256); // set zeroes into this array
    
    start = clock();
    
    initSet(pattern, set);
    
    int pre = 0, cur = 1;
    
    //int R[2][n+1];
    
    char* R[2];
    for(int i=0; i<2; i++)
        R[i] = new char[n+1];
    
    
    R[pre][0] = 0; //if the length of the text == 0 and error k == 0
    
    //firstly , we need to get R0 table using shift-and algorithm
    //under bit-parallel
    for(int i = 1 ; i <= n; i++){
        
        R[pre][i] = ((R[pre][i - 1] >> 1) | BIT) & set[INDEX(text[i - 1])];
    }
    
    //R0 -> R1 -> R2 ... -> Rk
    for(int i = 1; i <= k; i++)
    {
        R[cur][0] = 0;
        for(int j = 0; j < i; j++) {
            R[cur][0] |= (1 << (31 - j)); //if the length of the text == 0 and error k == i
        }
        
        //O(kn*(m/w)) = O(kn)
        //m = 32 = 4 bytes = one integer  (n = 256, k = 10)
        for(int j = 1; j <= n; j++){
            
            R[cur][j] = ((R[cur][j - 1] >> 1) & set[INDEX(text[j - 1])]) |
                        (R[pre][j - 1]) | /*insertion*/
                        (R[pre][j] >> 1) | /*deletion*/
                        (R[pre][j - 1] >> 1) /*substitution*/ | BIT;
    
        }

        cur = !cur;  //exchange the index, 1 to 0 or 0 to 1
        pre = !pre;  //exchange the index, 1 to 0 or 0 to 1
        
    }
    
    end = clock();								//record the end time
    runTime = (end - start) / (double) CLOCKS_PER_SEC ;   //run time
    
    cout << "NUM: "<< n <<"\t Time: " << runTime << " Sec"<<endl;
    
    return 0;
}

