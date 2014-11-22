//
//  main.cpp
//  bit-parallel approximate string
//
//  Created by gangliao on 10/9/14.
//  Copyright (c) 2014 gangliao. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

#define INDEX(c)    ((c) - 'a')
#define BIT 1 << 31

//according to the pattern p, initializing all the positions into the set container
void initSet(string p /*pattern*/, unsigned int* set)
{
    for (int i = 0; i < 31; i++) {
        set[INDEX(p[i])] = set[INDEX(p[i])] | (1 << (31-i));
    }
    
}

int main(int argc, const char * argv[])
{

    //pattern length = 32
    string pattern = "gttggcagcagtcgatcaaattgccgatccga";
    //                gttggcagcttagtcgatcaaaatgcccatccca cggtt
    /*test data
    31: gttggcagcagtcgatcaaattgccgatccaa           error = 1
    53 : gttggcagcttagtcgatcaaaatgcccatcccacggtt    error = 10
    113: gttggcagcagtcgatcaaattgccgatccgaagtctcaaa  error = 9
    */
    //text length = 256
    string text = "gttggcagcagtcgatcaaattgccgatccgagttggcagcagtcgatcaaattgccgatccaatgataaattcggttggcagcttagtcgatcaaaatgcccatcccacggttggcagcagtcgatcaaatcgaccaccgatgcagatcggttggcagcagtcgatttgccgatccgagtgcagtcgatcaaattgccgatccgagttggcagcagtcgatcaaattgccgatccgaagtctcaaattgccgatc";
    //cout << text.length() << endl;
    //asuume the numbers of error k is 10
    int k = 1; // allowed errors
    
    unsigned int set[26]; // all the postions of each character c in pattern p
    
    memset(set, 0, sizeof(int)*26); // set zeroes into this array
    
    initSet(pattern, set);
    
   /*  test the correctness of initSet
    cout << set[INDEX('a')] << " " <<
            set[INDEX('c')] << " " << 
            set[INDEX('g')] << " " << 
            set[INDEX('t')] << endl;
    */
    
    int pre = 0, cur = 1;
    
    int R[2][257];
    
    
    R[pre][0] = 0; //if the length of the text == 0 and error k == 0
    
    //firstly , we need to get R0 table using shift-and algorithm
    //under bit-parallel
    for(int i = 1 ; i <= 256; i++){
        
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
        for(int j = 1; j <= 256; j++){
            
            R[cur][j] = ((R[cur][j - 1] >> 1) & set[INDEX(text[j - 1])]) |
                        (R[pre][j - 1]) | /*insertion*/
                        (R[pre][j] >> 1) | /*deletion*/
                        (R[pre][j - 1] >> 1) /*substitution*/ | BIT;
    
        }

        cur = !cur;  //exchange the index, 1 to 0 or 0 to 1
        pre = !pre;  //exchange the index, 1 to 0 or 0 to 1
        
    }
    
    int sum = 0;
    for(int i = 1; i <= 256; i++){
        
         if(R[pre][i] & 1)
         {
             sum++;
             cout << "#" << i << endl;
             for (int j = 0; j < i; j++) {
                 cout << text[j];
             }
             cout << endl;
         }
    }
    
    
    cout << "# approximate string with k error is " << sum << endl;
    return 0;
}

