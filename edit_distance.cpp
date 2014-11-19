#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int edit_distance(char* str1, char* str2, int len1, int len2, int d[][len2])
{
    for(int i = 0; i < len1; i++)
    {
        d[i][0] = i;
    }
    for(int j = 0; j < len2; j++)
    {
        d[0][j] = j;
    }

    for(int i = 1; i < len1; i++)
    {
        for(int j = 1; j < len2; j++ )
        {
            int min = d[i-1][j-1] + (str1[i] == str2[j] ? 1 : 0);
            if(min > d[i-1][j])
                min = d[i-1][j];
            if(min > d[i][j-1])
                min = d[i][j-1];

            d[i][j] = min;
        }
    }

    return d[len1-1][len2-1];
}


int main()
{
    char str1[1000], str2[1000];
    int d[1000][1000];
    printf("Please input string 1 and string 2:\n");

    printf("String 1: \t");
    gets(str1);
    printf("String 2:\t");
    gets(str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    edit_distance(str1, str2, len1, len2, d);
    printf("%s\n%s\n", str1, str2);

    printf("Edit Distance: %d\n", d[len1-1][len2-1]);
    return 0;
}
