//
//
//  FastMatch.cpp
//
//  Created by Wentao Hu on 11/21/14.
//  Copyright (c) 2014 wentao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;


//change the lower case letter to integer
//we suppose there are only lower case letters. Of course we can change the range to capital letters.
#define INDEX(c)    ((c) - 'a')

//the edit distance of string1 and string2
int edit_dist(string string1, string string2)
{
    
    int m = (int)string1.length();
    int n = (int)string2.length();
    int i,j;
    int edit[m+1][n+1];
    for (i=0; i<=m;i++)
        edit[i][0]=i;
    for (j=0; j<=n; j++)
        edit[0][j]=j;
    for (i=1;i<m+1;i++)
        for (j=1;j<n+1;j++)
            edit[i][j]=min(min(edit[i-1][j]+1,edit[i][j-1]+1),edit[i-1][j-1]+(int)(!(string1[i-1]==string2[j-1])));
    return edit[m][n];
}

// whether the edit distance between pattern and substrings of textWindow can be less than or equal to k
int edit_window(string textWindow,string pattern,int k)
{
    int length =(int) (textWindow.length()-pattern.length());
    for (int i=0; i<=length;i++)
        if (edit_dist(textWindow.substr(i,i+pattern.length()),pattern) <= k)
            return 1;
    return 0;
}



/* bcTable. Because we use lower case letters only, there are 26 different lower case letters.
 string p : the pattern
 unsigned int* bc : bcTable
 int seg_length : the smallest length of pattern segments
 */
void bcTable(string p, unsigned int* bc, int seg_length)
{
    int i;
    for (i = 0; i < p.length(); i++)
        bc[INDEX(p[i])] = bc[INDEX(p[i])] | (1 << (p.length()-i-1));
    for(i = 0;i<26;i++)
    {
        int j;
        int k;
        int value=seg_length+1;
       for(j=0;j<p.length();j=j+seg_length)
        {
            for(k=1;k<=seg_length+1;k++)
                if (((bc[i]>>j)&(1<<(k-1))) != 0) break;
            if(k<value) value=k;
        }
        
        bc[i]=value;
    }
}


// to calculate the edit distance limits of k during each step
vector<int> segLength(int k)
{
    vector<int> kl;
    for(;k!=0;k=k/2)
        kl.push_back(k);
    return kl;
}


/*main method: recursive function
 parameters:
 text, pattern : the original text and pattern
 textWindow, patternWindow : changes at each step
 textWindowStart, patternWindowStart : the start position of each window in original text and pattern
 kl: the segLength(k)
 n: used to find which the step the function is in
 
 returns the start position of textWindow in text, otherwise returns -1.
 */
int fastmach(string text,string pattern,string textWindow,string patternWindow,int textWindowStart,int patternWindowStart,vector<int> kl,int n)
{
    if (n==0 && edit_window(textWindow,pattern,kl[0])==1)
        return textWindowStart;
    else
        if (edit_window(textWindow,patternWindow,kl[n])==1)
        {
            string newPatternWindow;
            if (patternWindowStart%2==0)
                newPatternWindow = pattern.substr(patternWindowStart*patternWindow.length(),2*patternWindow.length());
            else
                newPatternWindow = pattern.substr((patternWindowStart-1)*patternWindow.length(),2*patternWindow.length());
            int end =(int)(textWindowStart+newPatternWindow.length()+kl[n-1]);
            if((textWindowStart = textWindowStart-kl[n-1])<0)
                textWindowStart =0;
            if(end > text.length())
                end = (int) text.length();
            textWindow = text.substr(textWindowStart,end-textWindowStart);
            return fastmach(text,pattern,textWindow,newPatternWindow,textWindowStart,patternWindowStart/2,kl,n-1);
        }
    return -1;
}


int main(int argc, const char * argv[]) {
    
    //pattern length must be power(2,integer), such as 4, 8, 16, 32, ...
    //pattern length = 32
    string pattern = "gttggcagcagtcgatcaaattgccgatccga";
    
    //text length = 256
    string text =   "gttggcagcagtcgatcaaattgccgatccgawwgttggcagcagtcgatcaaattgccgatccgagttggcagcagtcgatcaaattgccgatccgagtt"\
"ggcgtcgatcaaaatgcccatjjjjjcccacggttggcagcagtcgatcaaatcgaccaccgggcagcagtcgattgagtgcagtcgatcaaattgccgatccgagttgg"\
    "cagcagtcgatcaaattgccgatccgaagtctcaaattgccgatc";
    
    int k=3;   // the error limit: k
    
    unsigned int bc[26];   //bcTable
    for (int i=0;i<26;i++)
        bc[i] = 0;    // Initialize bcTable = 0;
    
    vector<int> kl = segLength(k);
    vector<int> value;
    
    int n=(int)kl.size();   // the steps we use in recursive function fastmach
    int segmentLength=(int)pattern.length()/pow(2, n); // the smallest length of pattern segments
    
    bcTable(pattern,bc,segmentLength); // calculate bcTable
    
    string textWindow;
    string patternWindow;
    int textWindowStart;
    
    printf("the length of pattern is %d \n",(int)pattern.length());
    printf("the length of text is %d \n",(int)text.length());
    cout << "the pattern is " + pattern <<endl;
    cout << "the text is " + text <<endl;
    
    
    cout << endl << "the bcTable is "<<endl;
    for (int i =0;i<26;i++)
        cout << bc[i] << " ";   // the results of bcTable
    
    cout << endl <<endl << "We list those textWindows which meet the requirements:" <<endl <<endl;
    for (int j=0; j<pow(2, n);j++)
    {
        int i = 0;
        patternWindow = pattern.substr(j*segmentLength,segmentLength);
        while (true)
        {
            textWindow = text.substr(i,patternWindow.length());
            if(edit_window(textWindow, patternWindow,0)==1)
            {
                if (j%2==0)
                    patternWindow = pattern.substr(j*segmentLength,2*segmentLength);
                else
                    patternWindow = pattern.substr((j-1)*segmentLength,2*segmentLength);
                if((textWindowStart = i-kl[n-1]) < 0)
                    textWindowStart =0;
                int end =i+(int)patternWindow.length()+kl[n-1];
                if(end > text.length())
                    end = (int)text.length();
                textWindow = text.substr(textWindowStart,end-textWindowStart);
                int start = fastmach(text,pattern,textWindow,patternWindow,textWindowStart,j/2,kl,n-1);
                if(start!=-1)
                {   int m=0;
                    for (;m<int(value.size());m++)
                        if(start == value[m]) break;
                    if (m==value.size())
                    {
                        value.push_back(start);
                        printf("The textWindow's start position in text is %d \n", start+1);
                        int textend = start+(int)pattern.length()+2*k;
                        if (textend > text.length())
                            textend = (int) text.length();
                        cout<< "the textWindow is " + text.substr(start,textend-start) <<endl<<endl;
                    }
                }
                
            }
            
            if (i+patternWindow.length()>text.length()-1)
                break;
            i=i+bc[INDEX(text[i+patternWindow.length()])];
            if ((i+patternWindow.length())>text.length()-1)
                break;
        }
    }
    
    return 0;
}
