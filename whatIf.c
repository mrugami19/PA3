#include "types.h"
#include "user.h"
#include "fcntl.h"
 
int main(int argc, char *argv[]){
   int filePassed=0;  //flag
   //int done=-1;
   // int fd=99;
 
   char *fileName = ""; //file to open
   if (argc==2) { //checks if file is given
       fileName = argv[1]; //assigns the file name to open
       filePassed=1; //file is passed
   }
   int ofileName= open (fileName, O_RDONLY | O_CREATE);  //open given file
   int cf = open("child.txt", O_WRONLY | O_CREATE ); //create child.txt
   int pf = open("parent.txt", O_WRONLY | O_CREATE); //create parent/txt
   int n =-1;
 
  while(1){
 
       char buf[512];  //to hold input file
       if (ofileName == -1){ //file not passed
           n = read(1,buf,sizeof buf); //read from stdin or terminal
          
           if(n==0){ //if we hit EOF break
              //done=1;
               break;
              
              
           }

           if(fork()==0){ //fork child process
               n = write(cf, buf, sizeof(buf)-1); //write to child.txt from buf
               exit();
           }
           else{
               n = write(pf, buf, sizeof(buf)-1); //write to parent.txt from buf
               wait();
           }
        
       
       }
 
       if(filePassed==1){  //file was passed and opened succesfully
           n = read(ofileName, buf, sizeof(buf)); //read from said file
 
           if(n==0){ //if we hit EOF break
           break;
           }
 
           if(fork()==0){ //fork child process
               n = write(cf, buf, sizeof(buf)-1); //write to child.txt from buf
           }
           else{
               n = write(pf, buf, sizeof(buf)-1); //write to parent.txt from buf
               wait();
           }
       }

     //  close(fd);
      
   
}
}

