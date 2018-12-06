#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void show(char* a,int num)
{int i;
int length=strlen(a);
printf("%d",length);
for(i=num;a[i]!='\0';i++)
printf("%c",a[i]);
printf("\n");
}
int main(void) {
	// your code goes here
	char a[10];
	gets(a);
	
	if(a[0]=='a'){
		
	printf("1");
	show(a,4);
	}
	else{
	printf("2");
	show(a,5);
	}
	return 0;
}

