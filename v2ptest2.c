#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{

    const void *va;
    char z = '7';
    va = &z;

    printf(1, "\n Virtual address: %x\n", &va);
    myV2p(&va, 1);
    return 0;
    
  
}