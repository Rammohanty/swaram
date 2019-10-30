#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

/*******************definitions of values**********************/

#define NODES 16

#define BUFF_SIZE 1000

//#define DEBUG "comment to turn off"


/*******************definitions of formats and paths**********************/

#define READFORMAT "sr%ld"
#define PARTED_FILENAME_FORMAT "/genomics/scratch/parted%d.sam" 
#define PARTED_TARGET_FILENAME_FORMAT "/genomics/scratch/newparted%d.sam"
#define MY_ID "/genomics/myID.cfg"

#define INPUT_FILE_NAME "/genomics/scratch/aligned.sam"


/*******************global vars**********************/


//store the IPs
char node_ips[NODES][256] = {\
"192.168.1.100", "192.168.1.101", "192.168.1.102", "192.168.1.103",  \
"192.168.1.104", "192.168.1.105", "192.168.1.106", "192.168.1.107",  \
"192.168.1.108", "192.168.1.109", "192.168.1.110", "192.168.1.111",  \
"192.168.1.112", "192.168.1.113", "192.168.1.114", "192.168.1.115",  \
};
FILE *output_files[NODES];
int myid;


/*******************hepler macros and functions**********************/

/*Die on error. Print the error and exit if the return value of the previous function NULL*/
#define errorCheckNULL(ret) ({\
    if (ret==NULL){ \
        fprintf(stderr,"Error at File %s line number %d : %s\n",__FILE__, __LINE__,strerror(errno));\
        exit(EXIT_FAILURE);\
    }\
    })

/*Die on error. Print the error and exit if the return value of the previous function is -1*/
#define errorCheckNEG(ret) ({\
    if (ret<0){ \
        fprintf(stderr,"Error at File %s line number %d : %s\n",__FILE__, __LINE__,strerror(errno));\
        exit(EXIT_FAILURE);\
    }\
    })    
    

/*Die on error. Print the error and exit if the return value of the previous function NULL*/
void errorCheckNULL_pmsg(void *ret,char *msg){
        if(ret==NULL){
                perror(msg);
                exit(EXIT_FAILURE);
        }
}

void pthread_check(int ret){
    if(ret!=0){
        perror("Error creating thread");
        exit(EXIT_FAILURE);
    }
}

void errorCheckScanVal(int ret,char *msg){
    if(ret!=1){
        fprintf(stderr,"%s\n",msg);
		exit(EXIT_FAILURE);
    }  
    
}


/*******************System Functions**********************/


#define MAXARG 256
int system_async(char *buffer){
    
	int i=0;
	int pid; 				//process id
	char *arglist[MAXARG];	//store the arguments
	char *pch; 				//for strtok 
    
    pch=strtok(buffer," \n"); 	//Initiate breaking into tokens


    for(i=0;i<MAXARG;i++){		//fill the argument list
        
        /*if there is a tokened argument add it to the argument list*/
        if(pch!=NULL){								
            arglist[i]=malloc(sizeof(char)*256);
            strcpy(arglist[i],pch);
            pch=strtok(NULL," \n");
        }
        
        /*If end of scanned string make the entries in argument list null*/
        else{
            arglist[i]=NULL;
            break;
        }	
    } 

    /* fork a new process. If child replace the binary. Wait parent till child exists */
    pid=fork();
    
    if(pid<0){
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid==0){
        int check=execv(arglist[0],arglist);
        if(check==-1){ /* If cannot execute print an error and exit child*/
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    }
    else{
        return pid;
        //int status;
        //wait(&status); /*parent waits till child closes*/
    }    
    return pid;
}

void wait_async(int pid){
    int status=0;
    int ret=waitpid(pid,&status,0);
    if(ret<0){
        perror("Waiting failed. Premature exit of a child?");
        exit(EXIT_FAILURE);
    }
}






/*******************Program Functions**********************/


int to_which_device(char *chrom, int pos){
    
   //pasting starts here *****************************
    if(strcmp(chrom,"1")==0 && pos>=1 && pos <=15578163){
     return 0;
    }
    else if(strcmp(chrom,"1")==0 && pos>=15578164 && pos <=31156326){
     return 1;
    }
    else if(strcmp(chrom,"1")==0 && pos>=31156327 && pos <=46734489){
     return 2;
    }
    else if(strcmp(chrom,"1")==0 && pos>=46734490 && pos <=62312652){
     return 3;
    }
    else if(strcmp(chrom,"1")==0 && pos>=62312653 && pos <=77890815){
     return 4;
    }
    else if(strcmp(chrom,"1")==0 && pos>=77890816 && pos <=93468978){
     return 5;
    }
    else if(strcmp(chrom,"1")==0 && pos>=93468979 && pos <=109047141){
     return 6;
    }
    else if(strcmp(chrom,"1")==0 && pos>=109047142 && pos <=124625304){
     return 7;
    }
    else if(strcmp(chrom,"1")==0 && pos>=124625305 && pos <=140203467){
     return 8;
    }
    else if(strcmp(chrom,"1")==0 && pos>=140203468 && pos <=155781630){
     return 9;
    }
    else if(strcmp(chrom,"1")==0 && pos>=155781631 && pos <=171359793){
     return 10;
    }
    else if(strcmp(chrom,"1")==0 && pos>=171359794 && pos <=186937956){
     return 11;
    }
    else if(strcmp(chrom,"1")==0 && pos>=186937957 && pos <=202516119){
     return 12;
    }
    else if(strcmp(chrom,"1")==0 && pos>=202516120 && pos <=218094282){
     return 13;
    }
    else if(strcmp(chrom,"1")==0 && pos>=218094283 && pos <=233672445){
     return 14;
    }
    else if(strcmp(chrom,"1")==0 && pos>=233672446 && pos <=249250621){
     return 15;
    }
   
   //pasting ends here ********************************
   
    else{
        fprintf(stderr,"Some invalid chromosome or position %s:%d\n",chrom,pos);
        exit(EXIT_FAILURE);
    }   
    
}



void separate(char *inputname){
    
    FILE *input = fopen(inputname,"r");
    errorCheckNULL(input);
    
    char output_filename[1000];
    //divided outputs
    int i;
    for(i=0;i<NODES;i++){
        sprintf(output_filename,PARTED_FILENAME_FORMAT,i);
        output_files[i]=fopen(output_filename,"w");
        errorCheckNULL(output_files[i]); 
    }
 
    char *buffer = malloc(sizeof(char)*BUFF_SIZE);
    errorCheckNULL(buffer);
    char *buffercpy = malloc(sizeof(char)*BUFF_SIZE);
    errorCheckNULL(buffercpy);
    

    size_t bufferSize = BUFF_SIZE;
    
    char * pch;
    int ret;
    int readlinebytes=0;
    long readID = 0;
    //int flag = 0;
    //int mapq;
    
    char chrom[1000];
    int pos;
    int device;
    int flag;
    
    while(1){
        
        readlinebytes=getline(&buffer, &bufferSize, input); 
        //file has ended
        if(readlinebytes == -1){
            break;
        }            
        
        //ignore header lines  //empty new lines? //but write them
        if(buffer[0]=='@' || buffer[0]=='\n'){
            for(i=0;i<NODES;i++){
                fprintf(output_files[i],"%s",buffer); 
            }
            continue;
        }
        
        //copy buffer
        if(readlinebytes>=BUFF_SIZE){
            fprintf(stderr,"Need to implement realloc\n");
            exit(EXIT_FAILURE);
        }
        strcpy(buffercpy,buffer);
        
        //read ID (QNAME)
        pch = strtok (buffer,"\t\r\n"); 
        errorCheckNULL_pmsg(pch,"A bad samfile. No QNAME in line?");
        //printf("%s\n",pch);
        ret=sscanf(pch,READFORMAT,&readID);
        errorCheckScanVal(ret,"Bad read ID format");
        
        //FLAG        
        pch = strtok (NULL,"\t\r\n");
        ret=sscanf(pch,"%d",&flag);
        errorCheckScanVal(ret,"Bad flag");
        
        //if unmapped or secondary mapped or supplymentary mapped
        if((flag & 0x04) || (flag & 0x100) || (flag & 0x800)){
            //mapq_array[devno][read_array_index] = 0;
            continue;
        }
        //RNAME
        pch = strtok (NULL,"\t\r\n");
        errorCheckNULL_pmsg(pch,"A bad samfile. No RNAME in line?");    
        strcpy(chrom,pch);    
        
        //POS
        pch = strtok (NULL,"\t\r\n"); 
        errorCheckNULL_pmsg(pch,"A bad samfile. No POSITION in line?");
        ret=sscanf(pch,"%d",&pos);
        errorCheckScanVal(ret,"Bad POSITION");
        assert(pos>0);
        
        //get the device number which the read belong
        device=to_which_device(chrom, pos);
        assert(device>=0 && device<NODES);
        
        fprintf(output_files[device],"%s",buffercpy); 
        
    }    
 
    
    free(buffer);
    free(buffercpy);
    fclose(input);
 
    for(i=0;i<NODES;i++){
        fclose(output_files[i]);   
    }        
    
    
}


int main(int argc, char **argv){
     
    int ret ,i;
    char inputfilename[256];   
    sprintf(inputfilename,"%s",INPUT_FILE_NAME);
    
    //ID of the self
    int myid=-1;
    FILE *config = fopen(MY_ID,"r");
    errorCheckNULL(config);   
    fscanf(config,"%d",&myid);
    fclose(config);    
    assert(myid>=0 && myid<NODES);
    
    //write new files for each device
    separate(inputfilename);

    //remove main sam file
    //ret=remove(inputfilename);
    //errorCheckNEG(ret);    
 
    //now we can send the files
    char command[2000];
    char source_filename[1000];
    char target_filename[1000];
    
    int pids_scp[NODES];
    
    for(i=0;i<NODES;i++){
        sprintf(source_filename,PARTED_FILENAME_FORMAT,i);
        sprintf(target_filename,PARTED_TARGET_FILENAME_FORMAT,myid);
        if(i!=myid){
            sprintf(command,"/usr/bin/scp %s odroid@%s:%s",source_filename, node_ips[i],target_filename);
            fprintf(stderr,"%s\n",command);
            pids_scp[i]=system_async(command);
        }
        else{
            sprintf(command,"/bin/mv %s %s",source_filename, target_filename);
            fprintf(stderr,"%s\n",command);
            pids_scp[i]=system_async(command);
        }
    }
    
    
    //wait for scps
    for(i=0;i<NODES;i++){
        wait_async(pids_scp[i]);
    }
    
    //delete files
    // for(i=0;i<NODES+1;i++){
        // sprintf(source_filename,PARTED_FILENAME_FORMAT,i);
        // if(i!=myid){
            // int ret=remove(source_filename);
            // errorCheckNEG(ret);
        // }
    // }  
    
    return 0;
    
}
