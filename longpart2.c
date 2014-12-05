#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 2000


char *reverse(char *str){   
    int len = strlen(str);   
    if(len > 1){   
	char temp =str[0];   
        str[0] = str[len-1];      
        str[len-1] = '\0';   
        reverse(str+1);    
        str[len-1] = temp;   
    }   
    return str;   
}

int digcheck(char *theno){
    int len = strlen(theno);
    if(len>0){
	if(!(*theno >= '0' && *theno <= '9')){
	   printf("The number is invalid\n");
           exit(0);
    }
 	digcheck(theno+1);
    }
    return 1;
}

char *add2(char *n1, char *n2){
    int max,min,temp;
    static int carry=0;
    static char str3[MAX_DIGITS*2];//static string as output
    static int index=0;

    max=strlen(n1);
    min=strlen(n2);
    if(max>0){		//algorithm
        if(min>0){
	    temp=((int)*n1 + (int)*n2 -96)%10+carry;
	    if(temp<10){
	        str3[index]=(char)(temp+48);
                carry = ((int)*n1 + (int)*n2 -96)/10;
	    }
	    else{
		temp%=10;
	        str3[index]=(char)(temp+48);
                carry = ((int)*n1 + (int)*n2 -96)/10+1;
	    }
            index++;
	    add2(n1+1,n2+1);	    
         }
	else{
	    str3[index]=(char)(((int)*n1-48+carry)%10+48);
            carry = (carry+(int)*n1-48)/10;
            index++;
	    add2(n1+1,n2);
        }
    }
    if(carry!=0)
	str3[index]=(char)(carry+48);
    carry=0;
    index=0;
    temp=0;//back to 0!
    return str3;
}

char *smult(char *n1, int d){
    int len=strlen(n1);
    static int temp=0;
    static int carry=0;
    static char str3[MAX_DIGITS*2];//static string as output
    static int index=0;
    
    temp=((int)*n1-48)*d%10+carry;
    if(len>0){
	if(temp<10){
	    str3[index]=(char)(temp+48);
	    carry = ((int)*n1 -48)*d/10;
	}
	else{
	    temp%=10;
	    str3[index]=(char)(temp+48);
	    carry = ((int)*n1 -48)*d/10+1;
	}  
    index++;
    smult(n1+1,d);
    } 
    if(carry!=0)
	str3[index]=(char)(carry+48);
    carry=0;
    temp=0;
    index=0;//back to 0!
    return str3; 
}

int readString(char *s){
    int i=0;
    char c;
    scanf("%c",&c);
    while ((int)c != 10){
        s[i]=c;
        scanf("%c",&c);
	i += 1;
    }
    digcheck(s);
    return strlen(s);
}

void addzero(char *n,int d){
    int len=strlen(n),i;
    if(d==0)
	return;
    reverse(n);
    for(i=len;i<len+d;i++)
	n[i]='0';
    reverse(n);
}

char *longmult(char *num1, char *num2,char *accum){
    int len=strlen(num2);    
    static int index=0;
    char *t1;
    char *t2;
    if(len>0){
        t1=smult(num1,((int)*num2-48));
        addzero(t1,index);
        t2=add2(t1,accum);
        strcpy(accum,t2);
        memset(t2,0,(MAX_DIGITS*2));//memory need to refresh!!!
        index++;
        memset(t1,0,(MAX_DIGITS*2));//refresh t
	longmult(num1,num2+1,accum);
    }
    return (accum);
}


int main()
{
    char str1[MAX_DIGITS];
    char str2[MAX_DIGITS];
    char prod[MAX_DIGITS*2];
    int i;

    printf("Enter first number >");;
    readString(str1);//read data

    printf("Enter second number >");
    readString(str2);//read data

    printf("1st num is  %s",str1);
    printf("\n2nd num is  %s\n",str2);

    reverse(str1);
    reverse(str2);//reverse for easy calculation,for convience, all string will be stored reversely!

    char *str3;
    if(strlen(str1)>=strlen(str2))//find out who is bigger in length
	str3=add2(str1,str2);
    else
	str3=add2(str2,str1);
    reverse(str3);//reverse back!!

    printf("The sum is  %s\n",str3);
    
    memset(str3, 0, (MAX_DIGITS+1));

    for(i=2;i<10;i++){
	str3=smult(str1,i);
        reverse(str3);
        reverse(str1);//for display use
	printf("%s times %d is %s\n",str1,i,str3);
        memset(str3, 0, (MAX_DIGITS+1));//memory!
        reverse(str1);// reverse back!!
}
    str3=prod;
    if(strlen(str1)>strlen(str2))//find out who is bigger in length
	str3=longmult(str1,str2,str3);
    else
	str3=longmult(str2,str1,str3);

    reverse(str3);
    printf("The prod is %s\n",str3);
  
    return 0;
}
 
