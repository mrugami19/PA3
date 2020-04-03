#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_myV2p(void)
{
  int instr = 0;
  char *va;
  
  argstr(0, &va);
  argint(1, &instr);


  int *physical_address;
  pde_t *pgdir,*pgtab,*pde;
  pgdir = myproc()->pgdir;

    //must initialise pgdir

    pde = &pgdir[PDX(va)];
    if(*pde & PTE_P){
    pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
    }
    else
    {
    cprintf("\n PTE Not Present! - Invalid Virtual address\n");
    return -1;
    }
    cprintf("\n ----------------- \n");
    cprintf(" Page Directory Entry (PDE): %d\n",*pde);
    cprintf(" PTE_P : %d\n",PTE_P);
    cprintf("\n ----------------- \n");

    if(instr){
      if(*pde & PTE_W){
        pte_t *pte;
        pte = &pgtab[PTX(va)];
       physical_address=(int*)V2P(PTE_ADDR(*pte));

       cprintf(" --PHYSICAL ADDRESS-- %x\n", &physical_address);
      }
      else
      {
        cprintf("error, not writable");
      }
      
    }
    else{
      pte_t *pte;
    pte = &pgtab[PTX(va)];
    physical_address=(int*)V2P(PTE_ADDR(*pte));

    cprintf(" --PHYSICAL ADDRESS-- %d\n",physical_address);
    }

  

    return 0;

  /*
  pde_t *pde;
  pte_t *pgtab, *pgdir;
  pgdir = myproc()->pgdir;

  unsigned offset = (int)va % 4096; //last 12 bits 

  //unsigned offset = (int)va & ((1u<<12)-1); 
  // cprintf("")
  pde = &pgdir[PDX(va)];
  if(*pde & PTE_P)
  {
  	pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
  cprintf("\npagedir:  %d\n", pgdir);
	cprintf("\npagetb:  %d\n", pgtab);
  cprintf("\noffset:  %x\n", offset);
  }
  else
  {
	cprintf("\n Invalid Virtual Address! \n");
	return -1;
  }
	*/



  //return 0;
}