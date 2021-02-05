#include "blackdos.h"

void main()
{
    char* ch;
    int isVowel = 0;

    //    printf("Enter an alphabet: ");
    PRINTS("Enter an alphabet: ");
    //    scanf("%c",&ch);
    SCANS(ch);

    if(ch=='a'||ch=='A'||ch=='e'||ch=='E'||ch=='i'||ch=='I'
    		||ch=='o'||ch=='O'||ch=='u'||ch=='U')
    {
    	isVowel = 1;

    }
    if (isVowel == 1)
      {
	PRINTS(ch);
        PRINTS(" is a Vowel");
        //printf("%c is a Vowel", ch);
      }
    else
      {
	PRINTS(ch);
        PRINTS(" is a Consonant\r\n");
	// printf("%c is a Consonant", ch);
      }
    //return 0;
    END;
}
