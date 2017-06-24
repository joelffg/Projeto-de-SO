#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctacs/ct_api.h>

#define CT          1
#define HOST        2
#define REMOTE_HOST 5

#define ICC1        0

unsigned char RESET_CT[] = {0x20, 0x11, 0x00, 0x00, 0x00};  
unsigned char REQ_ICC[] = {0x20, 0x12, 0x01, 0x00, 0x01, 0x05};  
unsigned char EJECT_ICC[] = {0x20, 0x15, 0x01, 0x03, 0x01, 0x05};  
unsigned char GET_STAT80[] = {0x20, 0x13, 0x00, 0x80, 0x00};  
unsigned char GET_STAT46[] = {0x20, 0x13, 0x00, 0x46, 0x00};  
unsigned char SELECT_MF[] = {0x00, 0xa4, 0x00, 0x0c, 0x02, 0x3f, 0x00};  
unsigned char SELECT_GDO[] = {0x00, 0xa4, 0x00, 0x0c, 0x02, 0x2f, 0x02};  
unsigned char READ_BINARY[] = {0x00, 0xb0, 0x00, 0x00, 63};  

void xdata (unsigned char *addr, int count)  
{  
    int i, j = 0;  
      
    if (count > 0)  
    {  
        for (j=0 ; j<=(count /16); j++)  
        {  
            printf(" %.2x: ", j*16);  
            for (i=0; i<16 ; i++)  
            {  
                if (j*16+i>=count)  
                    printf("   ");  
                else  
                    printf(" %.2x",addr[j*16+i]);  
            }  
            printf("   [");  
            for (i=0; i<16 ; i++)  
            {  
                if (j*16+i>=count)  
                    printf(" ");  
                else  
                    if (addr[j*16+i] >= 0x20)  
                        printf("%c",addr[j*16+i]);  
                    else  
                        printf(" ");  
  
            }  
            printf("]\n");  
        }  
        printf("\n");  
    }  
  
}  

int main(int argc, char *argv[])
{
    char retval;
    unsigned short ctn;
    unsigned short pn;
    unsigned char sad;
    unsigned char dad;
    // REQUEST ICC
    unsigned char command[] = { 0x00, 0xb0, 0x00, 0x00, 63};
    unsigned short lenc = sizeof(command);
    unsigned char response[300];
    unsigned short lenr = sizeof(response);
    unsigned short i;
    ctn = 1;
    pn = 1;
    // Initialize card terminal
    retval = CT_init(ctn, pn);
    if (retval != OK)
    {
        printf("Error: CT_init failed with error %d\n", retval);
        return 1;
    }
    printf("RESET_CT:\n");  
   memcpy(command, RESET_CT, sizeof(RESET_CT));  
   sad = HOST;  
   dad = CT;  
   lenr = 200;  
   lenc = sizeof(RESET_CT);  
     
   retval =CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("RESET_CT not successful\n");  
      exit (-1);  
   }  
   xdata(response, lenr);  
  
  
   printf("GET_STAT46:\n");  
   memcpy(command, GET_STAT46, sizeof(GET_STAT46));  
   sad = HOST;  
   dad = CT;  
   lenr = 200;  
   lenc = sizeof(GET_STAT46);  
     
   retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("GET_STAT46 not successful\n");  
      exit (-1);  
   }  
   xdata(response, lenr);  
  
   printf("GET_STAT80\n");  
   memcpy(command, GET_STAT80, sizeof(GET_STAT80));  
   sad = HOST;  
   dad = CT;  
   lenr = 200;  
   lenc = sizeof(GET_STAT80);  
  
   retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("GET_STAT80 not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);  
  
   printf("Please insert Card into Slot #1 within 5sec.\nREQ_ICC:\n");  
   memcpy(command, REQ_ICC, sizeof(REQ_ICC));  
   sad = HOST;  
   dad = CT;  
   lenr = 200;  
   lenc = sizeof(REQ_ICC);  
  
   retval =CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("REQ_ICC not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);  
  
   printf("SELECT MF\n");  
   memcpy (command, SELECT_MF, sizeof(SELECT_MF));  
   sad = HOST;  
   dad = ICC1;  
   lenr = 200;  
   lenc = sizeof(SELECT_MF);  
  
   retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("SELECT_MF not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);  
  
   
   printf("SELECT GDO\n");  
   memcpy (command, SELECT_GDO, sizeof(SELECT_GDO));  
   sad = HOST;  
   dad = ICC1;  
   lenr = 200;  
   lenc = sizeof(SELECT_GDO);  
  
   retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("SELECT_GDO not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);  
  
   printf("READ BINARY\n");  
   memcpy (command, READ_BINARY, sizeof(READ_BINARY));  
   sad = HOST;  
   dad = ICC1;  
   lenr = 200;  
   lenc = sizeof(READ_BINARY);  
  
   retval = CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != OK)  
   {  
      printf("READ BINARY not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);  
  
  
   printf("Please remove Card from Slot #1 within 5sec.\nEJECT_ICC:\n");  
   memcpy(command, EJECT_ICC, sizeof(EJECT_ICC));  
   sad = HOST;  
   dad = CT;  
   lenr = 200;  
   lenc = sizeof(EJECT_ICC);  
  
   retval =CT_data(ctn, &dad, &sad, lenc, command, &lenr, response);  
   if (retval != 0)  
   {  
      printf("EJCT_ICC not successful\n");  
      exit (-1);  
   }  
   xdata (response, lenr);
    // Close card terminal
    retval = CT_close(ctn);
    if (retval != OK)
        printf("Error: CT_close failed with error %d\n", retval);
    return 0;
}
