/*
Single Author Info:
dvvira       Denil Vijay Vira

Group info:
dvvira       Denil Vijay Vira
prajago4     Priyadarshini Rajagopal
wli29        Wanqiu Li

*/


#define _GNU_SOURCE
#define __USE_GNU
#include<stdlib.h>
#include<stdio.h>
#include<sys/mman.h>
#include<ucontext.h>
#include <sys/reg.h>
#include<signal.h>
#include <string.h>

struct sigaction act;

void readString(char *s, int r);

/*
In the signal handler, the second parameter (siginfo_t*) can be used find the address where the SEGV occurred. This address is stored in
current_address. The third parameter (ucontext_t *) is used find the address of the stack pointer. This is stored in mycontext;
On receiving a SEGV signal, if the address where the SEGV occurred is that of readString, it implies that a call to the readString function has been made. However, the readString page was protected in the init_sandbox function, because of which the page is inaccessible now. Thus, the readString page is unprotected. Also, the return address of the function is stored in return_address by reading the value from the corresponding REG_RSP register and the corresponding page is protected to ensure only readString is executable. 
Once the readString completes execution, another SEGV signal is caught . If the originally stored return address matches the current address, the control can return back to the function that called readString. Thus the page that the readString call originated from is unprotected to resume execution of the program.
 */

void sig_handler(int signo, siginfo_t *info, void *context)
{
void *current_address = info->si_addr;
static void* return_address = NULL;
ucontext_t *mycontext = (ucontext_t *)context;

/*
 If the current address is that of readString, unprotect page on which readString resides and protect the page the call originated from
 */
if(current_address == readString)
   {
    //unprotect readString page
    mprotect((void*)((unsigned long)current_address & 0xfffffffffffff000), 1, PROT_READ | PROT_EXEC); 
    
    //protect the page which is the return address of readString
    return_address = (void*)(*(unsigned long*)mycontext->uc_mcontext.gregs[REG_RSP]);
    mprotect((void*)((unsigned long)return_address & 0xfffffffffffff000), 1, PROT_NONE ); 
    
    
   }
//SIGSEGV received when readString page completes execution and tries to return back to the function that called it
else if(return_address == current_address)
         mprotect((void*)((unsigned long)return_address & 0xfffffffffffff000), 1, PROT_READ|PROT_EXEC ); 

//If none of the above two cases apply, a malicious buffer overflow attack is detected-print and error and exit
else
  {
    printf("malicious buffer overflow detected, will exit!\n");
    exit(0);
  }
   

}

/*
The signal handler is set up with the SA_SIGINFO flag in order to pass the address where the SEGV occurs and the address of the stack pointer.Initially, the page with readString is protected to ensure that only one page is executable at a time. 
*/
void init_sandbox(void)
{

mprotect((void*)((unsigned long)readString & 0xfffffffffffff000), 1, PROT_NONE); 
sigemptyset(&act.sa_mask);

act.sa_handler = NULL;
act.sa_sigaction = sig_handler;
act.sa_flags = SA_RESTART | SA_SIGINFO;

sigaction(SIGSEGV,&act,NULL);



}
