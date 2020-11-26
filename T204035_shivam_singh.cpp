#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <sys/ipc.h> 
#include <stdio.h>
// reading of the pipe using this function
void B(int readpipe1)
{
int n,i;
char str1[100];
// reading of the length of the message passed
n=read(readpipe1,str1,100);
str1[n]='\0';
i=0;
for(i=0;str1[i]!='\0';i++)
{
if(str1[i]>=65&&str1[i]<=90)
{
// if the word is in Uppercase convert it into lowercase
str1[i] = str1[i]+32;
}
// if space is used ignore this space
else if(str1[i]==' ')
{
    
continue;
}
else
{
// if the word is in lowercase convert it into Uppercase
str1[i] = str1[i]-32;
}
}

printf("Reverse case string is: %s",str1);
}
void A(int writepipe1)
{
int length;
char str[100];
printf("Enter a string :");
// storing the string in length of 100
fgets(str,100,stdin);
// extracting the length of the string
length=strlen(str);
// if newline is encountered the decrease the length
if(str[length-1]=='\n')
{
length--;
}

write(writepipe1,str,length);
}
int main()
{
int pipe1[2];
// create an array of size2 to store the pid
pid_t childpid;
pipe(pipe1);
// create a fork function to create a parent and child process
childpid=fork();
// following is the execution of child process
if(childpid==0)
{
// inorder to read close the write-end of the pipe
close(pipe1[1]);
// read from the pipe
B(pipe1[0]);
}
else
{
// inorder to write close the read-end of the pipe
close(pipe1[0]);
// write from the pipe
A(pipe1[1]);
}
}