
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *input;
int i=0;
int n,not;
char lasthandle[10],stack[50],handles[50][10],ters[50],nters[50];
char start,end[4],lastnt;
void f() 
{ 
    printf("Not operator grammar\n"); 
    exit(0); 
}
int top=0,l;
char prec[20][20];

//get index of non terminal in precedence table

int getindex(char c)
{
	for(int p=0;p<not;p++)
	 {
		 if(ters[p]==c)
			 return p;
	 }
    
    if(strcmp(stack,end)==0)
    {
    	printf("\nAccepted;\n");
    	exit(0);
    }
    else
    {
    	printf("\nNot Accepted\n");
    	exit(0); 
    }
}

// Shift Operation

int shift()
{
stack[++top]=*(input+i++);
stack[top+1]='\0';
}

// Reduce Operation

int reduce()
{
int i,len,found,t;
for(i=0;i<n;i++)
    {
    len=strlen(handles[i]);
    if(stack[top]==handles[i][0]&&top+1>=len)
        {
        found=1;
        for(t=0;t<len;t++)
            {
            if(stack[top-t]!=handles[i][t])
                {
                found=0;
                break;
                }
            }
        if(found==1)
            {
            stack[top-t+1]=nters[i];
            top=top-t+1;
            strcpy(lasthandle,handles[i]);
            lastnt=nters[i];
            
            int z=strlen(lasthandle);
            char str3[50];
            strcpy(str3,lasthandle);
            
            for(int i=z-1;i>=0;i--)
            {
            	lasthandle[z-1-i]=str3[i];
            }
            
            stack[top+1]='\0';
            return 1; //successful reduction
            }
        }
   }
return 0;  // Can not be reduced
}

//Display stack Symbols

void dispstack()
{
	int j;
	for(j=0;j<=top;j++)
     printf("%c",stack[j]);
}

// Display Input buffer Data

void dispinput()
{
int j;
for(j=i;j<l;j++)
    printf("%c",*(input+j));
}

char topter()
{
	int t1=top;
	while(t1>=0)
	{
		char c1=stack[t1];
		for(int t2=0;t2<not;t2++)
		{
			if(c1==ters[t2])
			{
				return c1;
			}
		}
		t1--;
	}
	return '$';
}

void main()
{
	 printf("All the operators should be one character long.\n");
	 printf("\nEnter the no. of Terminals in Your Operator Precedence Grammar:-\n");
	 
    scanf("%d",&not);
    
    printf("Enter Terminals :\n");
    for (int k = 0; k < not; k++)
    {
    		scanf(" %c",&ters[k]);
    }
	 ters[not++]='$';
	 printf("Enter Precedence Relation :\n");
	 for(int p=0;p<not;p++)
	 {
	 	for(int q=0;q<not;q++)
	 	{
	 		printf("Between %c %c:",ters[p],ters[q]);
	 		scanf(" %c",&prec[p][q]);
	 		printf("\n");
	 	}
	 }
	 
	 printf("Precedence table:\n");
    printf(" \t");
    for(int p=0;p<not;p++)
    {
    	printf("%c\t",ters[p]);
    }
    printf("\n");
    for(int p=0;p<not;p++)
    {
    	printf("%c\t",ters[p]);
    	for(int q=0;q<not;q++)
    	{
    		printf("%c\t",prec[p][q]);
    	}
    	printf("\n");
    }
	 
	 printf("\nEnter the no. of Productions in Your Operator Precedence Grammar-\n");
    scanf("%d",&n);
    char str1[50],str2[50];
	 
    printf("Enter Productions\n");
    for (int k = 0; k < n; k++)
    {
    		
    		scanf("%s",str1);
    		nters[k]=str1[0];
    		if(k==0)
    		{
    			start=str1[0];
    		}
    		int c=strlen(str1)-1,j=0;
    		while (c>=2)
   		{
      		str2[j++] = str1[c];
      		c--;
   		}
   		str2[j] = '\0';
    		strcpy(handles[k],str2);
    }
    //checking whether the grammar is operator precedence or not;
     int flag;
    for (int k = 0; k < n; k++)
    {
    			
        		for(int p=0;p < not;p++)
        		{
        			if((ters[p]==handles[k][1])||(handles[k][0]==')' && handles[k][2]=='(')||(handles[k][1]=='\0'))
        			{
        				flag=1;
        				break;
        			}
        		}
        		
            if(flag==0)
            {
            	
                f(); 
            }
    }
    if(flag==0)
            {
                f(); 
            }
   printf("Valid Operator grammar\n");
   int j;
	
	end[0]=end[2]='$';
	end[1]=start;
	end[3]='\0';
	
	
	input=(char*)malloc(50*sizeof(char));
	
	printf("\nEnter the String To be Parsed\n");
	scanf("%s",input);
	
	input=strcat(input,"$");    //Appending $ at the end of input string
	l=strlen(input);
	
	strcpy(stack,"$");   
			
	printf("\nSTACK\t\tINPUT\t\tACTION");
	printf("\n");
	
	dispstack();
	
	printf("\t\t");
	
	dispinput();
	
while(i<=l)
	{
	shift();
	printf("\n");
	
	dispstack();
	
	printf("\t\t");
	
	dispinput();
	
	printf("\t\tShift");
	
	if(prec[getindex(stack[top])][getindex(input[i])]=='>')  // Checking Precedence
		{
		while(prec[getindex(topter())][getindex(input[i])]=='>')
			{
			if(reduce())
			{
			printf("\n");
			dispstack();
			
			printf("\t\t");
			
			dispinput();
			printf("\t\tReduced: %c->%s",lastnt,lasthandle);
			}
			
			else
			{
				break;
			}
			}
		}
	}

if(strcmp(stack,end)==0)
    {
    	printf("\nAccepted;\n");
    }
else
    {
    	printf("\nNot Accepted;\n");
    }
}
