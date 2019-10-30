/* @dedupli
**
** spurious alignment removal and data distribution for swaram
** @author: Hasindu Gamaarachchi (hasindu@unsw.edu.au)
** @@
******************************************************************************/
/*
MIT License

Copyright (c) 2019 Hasindu Gamaarachchi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "socket.h"
#include "error.h"
#include <netdb.h> 
#include <arpa/inet.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>


/******************frequently changed definitions***************/
#define STACKS 3 
//peer stacks for SAM file distribution 
//(if total 4 stacks this is 3)
//(if total 3 stacks this is 2)
//(if total 2 stacks this is 1)
//(if only 1 stack this is 0)

#define INPUT_FILE_NAME "/genstore/DevSset.sam" 
//the location of the input SAM file (output of BWA)

#define PARTED_FILENAME_FORMAT "/genomics/scratch/parted%d.sam"
//where the partitioned sam files are temporarily stored

#define PARTED_TARGET_FILENAME_FORMAT "/genomics/scratch/newparted%d.sam"
//where the partition sam files will be copied to 

#define READFORMAT "sr%ld" 
//the format of the read ID 



/**************other infrequently changed definitions of values**********************/

#define NODES 3 //peer nodes for a BWA instance (to do SAR removal) - always 3 if 2GB RAM devices such as Odroid XU4 are used

#define BUFF_SIZE 1000
#define LOOPS 1

//#define STARTID 0
#define READS 400000000 //max reads

//#define DEBUG_DEDUPLI "comment to turn off"
//#define MANUAL_ARG "comment to turn off"  //if this is 1 make sure DEBUG_DEDUPLI is 0 and LOOPS os 1
#define NO_DEL_MAIN_SAM "comment to turn off"  //the main input sam file will not be deleted if this is on

/*******************other infrequently changed definitions of formats and paths**********************/

#define NEIGHBOUR_ROW_IP "/genomics/horizontal_topology.cfg"
#define NEIGHBOUR_COLUMN_IP "/genomics/vertical_topology.cfg"
#define MY_ROW_ID "/genomics/rowID.cfg"
#define START_READ_ID "/genomics/start_read_id.cfg"

#define DEBUG_FILE_NAME "/home/odroid/sorting_framework/data/debug%d.sam"
#define DEBUG_WHOLE_OUTPUT_NAME "/home/odroid/sorting_framework/data/dedupli%d.sam"

/*******************global vars**********************/

long STARTID = 0;

//store the IPs
char node_ips[NODES][256] = {};
char vertical_node_ips[NODES][256] = {};

//array for storing mapping quality of each read
unsigned char mapq_array[NODES+1][READS];

//conditional variable for notifying to send
pthread_cond_t send_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
char send_flag = 0;

//conditional variable for notify that data received 
pthread_cond_t rcvd_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t rcvd_mutex = PTHREAD_MUTEX_INITIALIZER;
char rcvd = 0;

//barrier to reset the send_flag variable
pthread_barrier_t mybarrier;
pthread_barrier_t mybarrier2;

//structure for storing the region data
// struct region_limit{
    // char filename[1000];
    // FILE *outfile;
    // int num;
    // int lowlimit[2];
    // int highlimit[2];
    // char chromosome[2][200];
    
// };

// struct region_limit region_limits[STACKS];

FILE *output_files[STACKS+1];

int iteration_number=0;



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




//a function to get ip using host name
int get_ip(char * hostname , char* ip) 
{  
   struct hostent *he;     
   struct in_addr **addr_list;     
   int i;     
   if ( (he = gethostbyname( hostname ) ) == NULL){ 
        herror("gethostbyname");         
        return 1;
   }     
   addr_list = (struct in_addr **) he->h_addr_list;
   for(i = 0; addr_list[i] != NULL; i++){   
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
   }
   return 1;
} 





/*******************Program Functions**********************/


/*
int to_which_device(char *chrom, int pos){
    
    if(strcmp(chrom,"1")==0 && pos>=1 && pos <=200000000){
        return 0;
    }
    else if(strcmp(chrom,"2")==0 && pos>=1 && pos <=200000000){
        return 1;
    }
    else if(strcmp(chrom,"3")==0 ){
        return 2;
    }
    else if(strcmp(chrom,"4")==0 ){
        return 3;
    }
    else if(strcmp(chrom,"1")==0 && pos>=200000001){
        return 4;
    }    
    else if(strcmp(chrom,"8")==0){
        return 4;    
    }
    else if(strcmp(chrom,"2")==0 && pos>=200000001){
        return 5;
    }     
    else if(strcmp(chrom,"7")==0){
        return 5;
    }    
    else if(strcmp(chrom,"6")==0 ){
        return 6;
    }
    else if(strcmp(chrom,"5")==0 ){
        return 7;
    } 
    else if(strcmp(chrom,"15")==0 || strcmp(chrom,"16")==0 ){
        return 8;
    }
    else if(strcmp(chrom,"9")==0 || strcmp(chrom,"22")==0 ){
        return 9;
    }
    else if(strcmp(chrom,"10")==0 || strcmp(chrom,"21")==0 ){
        return 10;
    }
    else if(strcmp(chrom,"11")==0 || strcmp(chrom,"19")==0 ){
        return 11;
    }
    else if(strcmp(chrom,"X")==0 || strcmp(chrom,"Y")==0 ){
        return 12;
    }    
    else if(strcmp(chrom,"14")==0 || strcmp(chrom,"17")==0 ){
        return 13;
    }     
     else if(strcmp(chrom,"13")==0 || strcmp(chrom,"18")==0){
        return 14;
    }
    else if(strcmp(chrom,"12")==0 || strcmp(chrom,"20")==0 ){
        return 15;
    }    

    else{
        fprintf(stderr,"Some invalid chromosome or position %s:%d\n",chrom,pos);
        exit(EXIT_FAILURE);
    }
}
*/

int to_which_row(char *chrom, int pos){
    
    //stack 0
    if(strcmp(chrom,"2")==0 || strcmp(chrom,"1")==0 || strcmp(chrom,"3")==0 || strcmp(chrom,"4")==0){
        if (STACKS==3) return 0;
		if (STACKS==2) return 0;
        if (STACKS==1) return 0;
        if (STACKS==0) return 0;
    }


    //stack 1
    else if(strcmp(chrom,"X")==0 || strcmp(chrom,"7")==0 || strcmp(chrom,"6")==0 || strcmp(chrom,"5")==0){
         if (STACKS==3) return 1;
		 if (STACKS==2) return 1;
         if (STACKS==1) return 0;
         if (STACKS==0) return 0;
    }    

    
    //stack 2 
    else if(strcmp(chrom,"12")==0 || strcmp(chrom,"11")==0 || strcmp(chrom,"8")==0 || strcmp(chrom,"10")==0 ){
         if (STACKS==3) return 2;
		 if (STACKS==2) return 2;
         if (STACKS==1) return 1;
         if (STACKS==0) return 0;
    }
    else if(strcmp(chrom,"19")==0 || strcmp(chrom,"Y")==0 || strcmp(chrom,"22")==0 || strcmp(chrom,"21")==0){
         if (STACKS==3) return 2;
		 if (STACKS==2) return 2;
         if (STACKS==1) return 1;
         if (STACKS==0) return 0;
    }

    
    //stack 3
    else if(strcmp(chrom,"15")==0 || strcmp(chrom,"14")==0 || strcmp(chrom,"13")==0 || strcmp(chrom,"9")==0){
        if (STACKS==3) return 3;
		if (STACKS==2) return 2;
        if (STACKS==1) return 1;
        if (STACKS==0) return 0;
    }    
    else if(strcmp(chrom,"18")==0 || strcmp(chrom,"16")==0  || strcmp(chrom,"17")==0 || strcmp(chrom,"20")==0){
        if (STACKS==3) return 3;
		if (STACKS==2) return 2;
        if (STACKS==1) return 1;
        if (STACKS==0) return 0;
    }     


    else{
        //fprintf(stderr,"Some invalid chromosome or position %s:%d\n",chrom,pos);
        //exit(EXIT_FAILURE);
        return -1;
    }   
    
}


//old way
// int to_which_row(char *chrom, int pos){
    
    // //row 0
    // if(strcmp(chrom,"1")==0 && pos>=1 && pos <=200000000){
        // return 0;
    // }
    // else if(strcmp(chrom,"2")==0 && pos>=1 && pos <=200000000){
        // return 0;
    // }
    // else if(strcmp(chrom,"3")==0 || strcmp(chrom,"4")==0 ){
        // return 0;
    // }

    
    // else if(strcmp(chrom,"1")==0 && pos>=200000001){
        // return 1;
    // }    
    // else if(strcmp(chrom,"2")==0 && pos>=200000001){
        // return 1;
    // }     
    // else if(strcmp(chrom,"8")==0 || strcmp(chrom,"7")==0 || strcmp(chrom,"6")==0 || strcmp(chrom,"5")==0){
        // return 1;    
    // }
    
     
    // else if(strcmp(chrom,"15")==0 || strcmp(chrom,"16")==0 ){
        // return 2;
    // }
    // else if(strcmp(chrom,"9")==0 || strcmp(chrom,"22")==0 ){
        // return 2;
    // }
    // else if(strcmp(chrom,"10")==0 || strcmp(chrom,"21")==0 ){
        // return 2;
    // }
    // else if(strcmp(chrom,"11")==0 || strcmp(chrom,"19")==0 ){
        // return 2;
    // }
    
    // else if(strcmp(chrom,"X")==0 || strcmp(chrom,"Y")==0 ){
        // return 3;
    // }    
    // else if(strcmp(chrom,"14")==0 || strcmp(chrom,"17")==0 ){
        // return 3;
    // }     
     // else if(strcmp(chrom,"13")==0 || strcmp(chrom,"18")==0){
        // return 3;
    // }
    // else if(strcmp(chrom,"12")==0 || strcmp(chrom,"20")==0 ){
        // return 3;
    // }    

    // else{
        // fprintf(stderr,"Some invalid chromosome or position %s:%d\n",chrom,pos);
        // exit(EXIT_FAILURE);
    // }   
    
// }

void encode_mapqarray(char *inputname, char *outputname, int devno){

    FILE *input = fopen(inputname,"r");
    F_CHK(input,inputname);

    
#ifdef DEBUG_DEDUPLI    
    FILE *output = fopen(outputname,"w");
    F_CHK(output,outputname);    
#endif
 
    char *buffer = malloc(sizeof(char)*BUFF_SIZE);
    MALLOC_CHK(buffer);
    char *buffercpy = malloc(sizeof(char)*BUFF_SIZE);
    MALLOC_CHK(buffercpy);
    
    memset(mapq_array[devno],0,READS);  //can handle inside the loop as all reads are in the input sam and hence all un mapped will be cleared to 0
    
    size_t bufferSize = BUFF_SIZE;
    
    char * pch;
    int ret;
    int readlinebytes=0;
    long readID = 0;
    int read_array_index = 0;
    int flag = 0;
    int mapq;
        
    
    while(1){
        readlinebytes=getline(&buffer, &bufferSize, input); 
        //file has ended
        if(readlinebytes == -1){
            break;
        }        
        //errorCheck(ret,"File has prematurely ended");
        
        //ignore header lines
        if(buffer[0]=='@' || buffer[0]=='\n'){
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
        //fprintf(stderr,"buffer : %s\n",buffer);
        errorCheckScanVal(ret,"Bad read ID format.");
      
        //array index
        read_array_index = (int )(readID - STARTID);
        
        //FLAG
        
        pch = strtok (NULL,"\t\r\n");
        errorCheckNULL_pmsg(pch,"A bad samfile. No FLAG in line?");
        ret=sscanf(pch,"%d",&flag);
        errorCheckScanVal(ret,"Bad flag");
        
        //if unmapped or secondary mapped or supplymentary mapped
        if((flag & 0x04) || (flag & 0x100) || (flag & 0x800)){
            //mapq_array[devno][read_array_index] = 0;
            continue;
        }

      
        //make efficient by scanning from back
      
        //RNAME
        pch = strtok (NULL,"\t\r\n"); 
        
        //POS
        pch = strtok (NULL,"\t\r\n"); 
        
        //MAPQ
        pch = strtok (NULL,"\t\r\n"); 
        //errorCheckNULL_pmsg(pch,"A bad samfile. No MAPQ in line?");
        //ret=sscanf(pch,"%d",&mapq);
        //mapq is a star
        //if(ret!=1 || mapq >=255 || mapq<=0){
            //mapq_array[devno][read_array_index] = 0;
            //continue;           
        //}
        /*if(mapq >=255 || mapq<=0){
            mapq_array[devno][read_array_index] = 0;
            continue;           
        }*/
        
        //CIGAR
        pch = strtok (NULL,"\t\r\n");
        
        //RNEXT
        pch = strtok (NULL,"\t\r\n");
        
        //PNEXT
        pch = strtok (NULL,"\t\r\n");
        
        //TLEN
        pch = strtok (NULL,"\t\r\n");
        
        //SEQ
        pch = strtok (NULL,"\t\r\n");
        
        //QUAL
        pch = strtok (NULL,"\t\r\n");
        
        //NM
        pch = strtok (NULL,"\t\r\n");
        
        //MD
        pch = strtok (NULL,"\t\r\n");
        
        //alignment score
        pch = strtok (NULL,"\t\r\n");
        errorCheckNULL_pmsg(pch,"A bad samfile. No Alignment Score in line?");
        ret=sscanf(pch,"AS:i:%d",&mapq);
        errorCheckScanVal(ret,"Bad alignment score format");
        if(mapq<0 || mapq>255){
            fprintf(stderr,"We have a problem. Alignment score has gone out of unsigned char limits\n");
            exit(EXIT_FAILURE);
        }
        
        //printf("Alignment score %s %d\n",pch,mapq);
        
        if(read_array_index>=READS){
            fprintf(stderr, "read_array_index is %d which is expected to be less than %d\n",read_array_index,READS);
        }
        
        mapq_array[devno][read_array_index] = (unsigned char)mapq;
      
#ifdef DEBUG_DEDUPLI 
        fprintf(output,"%s",buffercpy);  
#endif        
        
    } 

 
    //printf("%d %d %d %d\n", mapq_array[0][4179], mapq_array[1][4179], mapq_array[2][4179], mapq_array[3][4179]);
    
    free(buffer);
    free(buffercpy);
    fclose(input);
    
#ifdef DEBUG_DEDUPLI     
    fclose(output);
#endif 
    
}

void deduplicate(char *inputname, char *outputname){
    
    FILE *input = fopen(inputname,"r");
    F_CHK(input,inputname);

    //whole output
	#ifdef DEBUG_DEDUPLI
    FILE *output = fopen(outputname,"w");
    F_CHK(output,outputname);    
	#endif
    
    char output_filename[1000];
    //divided outputs
    int i;
    for(i=0;i<STACKS+1;i++){
        sprintf(output_filename,PARTED_FILENAME_FORMAT,i);
        output_files[i]=fopen(output_filename,"w");
        F_CHK(output_files[i],output_filename); 
    }
    
    //separated output
    // char filename[256];
    // for(i=0;i<STACKS;i++){
        // sprintf(filename,"dev%d.sam",i);
        // region_limits[i].outfile = fopen(filename,"w");
        // errorCheckNULL(region_limits[i].outfile);   
    // }
    
    
 
    char *buffer = malloc(sizeof(char)*BUFF_SIZE);
    MALLOC_CHK(buffer);
    char *buffercpy = malloc(sizeof(char)*BUFF_SIZE);
    MALLOC_CHK(buffercpy);
    

    size_t bufferSize = BUFF_SIZE;
    
    char * pch;
    int ret;
    int readlinebytes=0;
    long readID = 0;
    int read_array_index = 0;
    //int flag = 0;
    //int mapq;
    
    char chrom[1000];
    int pos;
    int row;
    int flag;
    
    while(1){
        
        readlinebytes=getline(&buffer, &bufferSize, input); 
        //file has ended
        if(readlinebytes == -1){
            break;
        }            
        
        //ignore header lines  //empty new lines? //but write them
        if(buffer[0]=='@' || buffer[0]=='\n'){
            for(i=0;i<STACKS+1;i++){
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
      
        //array index
        read_array_index = (int )(readID - STARTID);
        
        if(read_array_index>=READS){
            fprintf(stderr, "read_array_index is %d which is expected to be less than %d\n",read_array_index,READS);
        }
        
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
        
        //get the row number
        row=to_which_row(chrom, pos);
        assert(row>=-1 && row<4);
        
        if(row>=0){
            unsigned char mapq = mapq_array[0][read_array_index];
            unsigned char mapq1 = mapq_array[1][read_array_index];
            unsigned char mapq2 = mapq_array[2][read_array_index];
            unsigned char mapq3 = mapq_array[3][read_array_index];
            if(mapq!=0 && mapq >= mapq1 && mapq >= mapq2 && mapq >= mapq3){

    #ifdef DEBUG_DEDUPLI        
                fprintf(output,"%s",buffercpy); 
    #endif            
                fprintf(output_files[row],"%s",buffercpy); 
            }
        }
        
        //if(read_array_index==4179){
            //printf("%d %d %d %d\n",mapq,mapq1,mapq2,mapq3);
        //}
    }    
 
    
    free(buffer);
    free(buffercpy);
    fclose(input);
	#ifdef DEBUG_DEDUPLI	
    fclose(output);
	#endif
 
    for(i=0;i<STACKS+1;i++){
        fclose(output_files[i]);   
    }        
    
    
}

void *client_connection(void *arg)
{
	//sleep(1); //wait till servers are setup
    int id = *((int *)arg);
    
    //char ip[16];
    //get_ip(node_ips[id],ip);
    
    //Connect to the server given as argument on port 20000
    int socketfd = TCP_client_connect(node_ips[id], 20000);
    
    int i;
    for(i=0;i<LOOPS;i++){
    
        //need to wait till we get a signal to send data
        pthread_mutex_lock(&send_mutex);
        while (send_flag ==0){
            pthread_cond_wait(&send_cond, &send_mutex);
        }
        pthread_mutex_unlock(&send_mutex);
        
        //char buffer[BUFF_SIZE]="Hi! I am the client. Serve me please!";
        
        //send the message
        //send_full_msg(socketfd, buffer, strlen(buffer));
        send_full_msg(socketfd, mapq_array[0], READS);
        fprintf(stderr,"Message sent\n");
        
        //barrier
        pthread_barrier_wait(&mybarrier);
        pthread_barrier_wait(&mybarrier2);
    }
    
    //receive the message
	//int received = recv_full_msg(socketfd,buffer,BUFF_SIZE);
    
    //print the message
	//buffer[received]='\0';  //null character before priniting the string
	//fprintf(stderr,"Recieved : %s\n",buffer);
	
    //close the connection
	TCP_client_disconnect(socketfd); 

	return NULL;
}

//server thread
void *server_connection(void *arg)
{
	//sleep(1); //not needed
    
    int *arguments  = (int *)arg;
    int devno = arguments[0];
    int connectfd = arguments[1];
    
    //char buffer[BUFFER_SIZE];   
    
    //this keeps on listening
 
    int i=0;
    for(i=0;i<LOOPS;i++){
        //get message from client
        recv_full_msg(connectfd,mapq_array[devno],READS);    
        
        //print the message
        //buffer[received]='\0'; //null character before priniting the stringsince
        //fprintf(stderr,"Recieved : %s\n",buffer); 
     
        //need to say that we received stuff
        pthread_mutex_lock(&rcvd_mutex);
        rcvd ++;
        if(rcvd == NODES){
            pthread_cond_signal(&rcvd_cond);
        }
        pthread_mutex_unlock(&rcvd_mutex); 
        
        //barrier
        pthread_barrier_wait(&mybarrier);
        pthread_barrier_wait(&mybarrier2);

 
    }
 
    //Copy a string to buffer
    //strcpy(buffer,"Hi! This is the server reply.");
 
    //send a message to the client
    //send_full_msg(connectfd,buffer,strlen(buffer));

    //close doen the client connection
    TCP_server_disconnect_client(connectfd);
    
	return NULL;
}



int main(int argc, char **argv){
    
#ifdef MANUAL_ARG
    if(argc!=4){
        fprintf(stderr,"Usage : %s input.sam output.sam startID\n",argv[0]);
        exit(EXIT_FAILURE);
    }
#endif    
    
    int ret ,i;
    char inputfilename[256];
    char debugfilename[256];
    char outputfilename[256];
    
    
    //reading config file, Contains what other hosts should be connected
    FILE *config = fopen(NEIGHBOUR_ROW_IP,"r");
    F_CHK(config,NEIGHBOUR_ROW_IP);   
    for(i=0;i<NODES;i++){
        fgets(&node_ips[i][0], 256, config);  //check returned value, 
    }
    fclose(config);    
    
    //vertical hosts (where to send files)
    config = fopen(NEIGHBOUR_COLUMN_IP,"r");
    F_CHK(config,NEIGHBOUR_COLUMN_IP);   
    for(i=0;i<NODES;i++){
        fgets(&vertical_node_ips[i][0], 256, config);  //check returned value, 
        int len = strlen(&vertical_node_ips[i][0])-1; 
        if ((len > 0) && (vertical_node_ips[i][len] == '\n')) {vertical_node_ips[i][len] = '\0';}
    }
    fclose(config);      
    
    //row ID of the self
    int myrowid=-1;
    config = fopen(MY_ROW_ID,"r");
    F_CHK(config,MY_ROW_ID);   
    fscanf(config,"%d",&myrowid);
    fclose(config);    
    assert(myrowid>=0 && myrowid<=STACKS);
    
    
    
    //reading information on the regions in which each device should process on 
    // config = fopen("/etc/region_info","r");   
    // errorCheckNULL(config);
    // for(i=0;i<STACKS;i++){
        // fscanf(config,"%s %d %d",region_limits[i].chromosome,&(region_limits[i].lowlimit), &(region_limits[i].highlimit)); //check returned value
        // printf("%s %d %d\n",region_limits[i].chromosome,region_limits[i].lowlimit, region_limits[i].highlimit);
    // }
    // fclose(config);    
    
#if 1    
    //data structures for clients (connect to servers running on other ips)
    pthread_t client_thread[3];     
    int thread_id[NODES];
    
    //data structures for servers 
    pthread_t server_thread[3] ;       
    int connect_fd[NODES][2];
    

    //First create threads for clients
    for(i=0;i<NODES;i++){
        thread_id[i]=i;
        ret = pthread_create( &client_thread[i], NULL, client_connection, (void *)(&thread_id[i])) ;
        pthread_check(ret);
    }
    
    //create a listening socket on port 20000
	int listenfd=TCP_server_init(20000);
 
    //threads for server
    for(i=0;i<NODES;i++){
        connect_fd[i][0] = i+1;
        //accept a client connection
        connect_fd[i][1] = TCP_server_accept_client(listenfd); 
        ret = pthread_create( &server_thread[i], NULL, server_connection, (void *)(connect_fd[i])) ;
        pthread_check(ret);           
    }
    
    
    //init the barrier
    pthread_barrier_init(&mybarrier, NULL, NODES*2 + 1);
    pthread_barrier_init(&mybarrier2, NULL, NODES*2 + 1);
    
    for(i=0;i<LOOPS;i++){
        
        //generate filenames
        sprintf(inputfilename,INPUT_FILE_NAME);
#ifdef DEBUG_DEDUPLI
        sprintf(debugfilename,DEBUG_FILE_NAME,i);
        sprintf(outputfilename,DEBUG_WHOLE_OUTPUT_NAME,i); 
#endif  
           

#ifdef MANUAL_ARG
        strcpy(inputfilename,argv[1]);
        strcpy(outputfilename,argv[2]);
        STARTID = atol(argv[3]);
#else       
    STARTID=-1;    
    config = fopen(START_READ_ID,"r");
    F_CHK(config,START_READ_ID);   
    fscanf(config,"%ld",&STARTID);
    fclose(config);    
    assert(STARTID>=0);        
#endif        
      
        //need to read the files and create an array containing the quality score of each read
        fprintf(stderr,"Creating arrays\n");

        encode_mapqarray(inputfilename, debugfilename, 0);
        fprintf(stderr,"Finished creating arrays\n");
        
        //send client threads a signal to send the data
        pthread_mutex_lock(&send_mutex);
        send_flag = 1;
        pthread_cond_broadcast(&send_cond);
        pthread_mutex_unlock(&send_mutex);


        //need to wait until arrays from all the nodes have been received
        fprintf(stderr,"Waiting till all data is received\n");
        pthread_mutex_lock(&rcvd_mutex);
        while(rcvd<NODES){
             pthread_cond_wait(&rcvd_cond, &rcvd_mutex);
        } 
        pthread_mutex_unlock(&rcvd_mutex);
        fprintf(stderr,"All data received\n");
        
        
        //barrier
        pthread_barrier_wait(&mybarrier);
        send_flag = 0;
        rcvd = 0;    
        pthread_barrier_wait(&mybarrier2);        
        
        //write new files based on received information
        deduplicate(inputfilename, outputfilename);
        STARTID += READS;

    }

    //joining client side threads
    for(i=0;i<NODES;i++){
        ret = pthread_join ( client_thread[i], NULL );
        pthread_check(ret);
    }    
    
     //joining client side threads
    for(i=0;i<NODES;i++){
        ret = pthread_join ( server_thread[i], NULL );
        pthread_check(ret);
    }    
    
    //close the down the listening socket
    TCP_server_shutdown(listenfd);
    
#endif

#ifndef NO_DEL_MAIN_SAM
    //remove main sam file
    ret=remove(inputfilename);
    errorCheckNEG(ret);    
#endif 

#if 1    
    //now we can send the files
    char command[2000];
    char source_filename[1000];
    char target_filename[1000];
    
    int pids_scp[STACKS+1];
    
    int j=0;
    for(i=0;i<STACKS+1;i++){
        sprintf(source_filename,PARTED_FILENAME_FORMAT,i);
        sprintf(target_filename,PARTED_TARGET_FILENAME_FORMAT,myrowid);
        if(i!=myrowid){
            sprintf(command,"/usr/bin/scp %s odroid@%s:%s",source_filename, vertical_node_ips[j],target_filename);
            fprintf(stderr,"%s\n",command);
            pids_scp[i]=system_async(command);
            j++;
        }
        else{
            sprintf(command,"/bin/mv %s %s",source_filename, target_filename);
            fprintf(stderr,"%s\n",command);
            pids_scp[i]=system_async(command);
        }
    }
    
    
    //wait for scps
    for(i=0;i<STACKS+1;i++){
        wait_async(pids_scp[i]);
    }
    
    //delete files
#ifndef DEBUG_DEDUPLI
    for(i=0;i<STACKS+1;i++){
        sprintf(source_filename,PARTED_FILENAME_FORMAT,i);
        if(i!=myrowid){
            int ret=remove(source_filename);
            errorCheckNEG(ret);
        }
    }
     
#endif    
#endif

    
    return 0;
    
}
