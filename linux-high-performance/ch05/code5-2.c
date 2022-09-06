#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
int main(){
   in_addr_t addrees;
   addrees = inet_addr("255.255.255.25");
   printf("Networked ordered integer addr:%d \n",addrees);
   printf("Networked ordered integer addr:%x \n",addrees);
}