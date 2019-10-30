/* @socketLibC
**
** A simple and easy to use TCP Linux socket programming library
** https://github.com/hasindu2008/socketLibC
** @author: Hasindu Gamaarachchi (hasindu@unsw.edu.au)
** @@
******************************************************************************/
/*MIT License

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

/*******************************Blocking send and receive***********************************/

/*Send the number of bytes to be sent. Then send the actual data.*/
void send_full_msg(int socket, void *buffer, int length);

/*First receive the number of bytes to be received. Then receive the actual data to the buffer.*/
int recv_full_msg(int socket, void *buffer, int length);



/***************************Server side*******************************************************/

/*Create a TCP socket, bind and then listen*/
int TCP_server_init(int PORT);

/*Accept a client*/    
int TCP_server_accept_client(int listenfd);

/*Disconnect a connected client*/    
void TCP_server_disconnect_client(int connectfd);

/*Close down the listening socket*/    
void TCP_server_shutdown(int listenfd);



/********************************Client side***************************************************/

/* Connect to a TCP server at PORT at ip*/
int TCP_client_connect(char *ip, int PORT);

/* Disconnect*/
void TCP_client_disconnect(int socketfd);



/************************************Internal Functions*****************************************/

/*Die on error. Print the error and exit if the return value of the previous function is -1*/
void errorCheck(int ret,char *msg);

/*Send length number of bytes from the buffer. This is a blocking call.*/
void send_all(int socket, void *buffer, int length);

/*Receive length number of bytes to the buffer. This is a blocking call. Make sure that buffer is big enough.*/
void recv_all(int socket, void *buffer, int length);