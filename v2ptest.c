#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{

    const void *va;
    char i = '5';
    va = &i;

    printf(1, "\n Virtual address: %x\n", &va);
    myV2p(&va, 0);
    return 0;
    
  
}