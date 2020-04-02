#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  int file = open("./test.txt", O_CREATE|O_RDWR); 
  int fd = fork(); 
  if(fd==0){
     alsoNice(50);
    
     
  	for(int i=0; i<1500; i++){
		write(file, "hi", sizeof("hi"));
	}
  	printf(1, "hey from: %d\n", getpid() );
  	

  }

  if(fd >0){
	for(int i=0; i<1500; i++){
		write(file, "ho", sizeof("ho"));
	} 
	printf(1, "hey from: %d\n", getpid() );
	wait(); 
  }
  close(file);
  exit();

  
}

