/*
 * =============================================================================
 *
 *       Filename:  Npcap_list_Adapters.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  4.10.2022 15:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Albert Domingo
 *
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    char inputType[10];
    char input[50];

    printf("Enter the type of input 1:decimal or 2:IP address: ");
    fgets(inputType, sizeof(inputType), stdin);
    inputType[strcspn(inputType, "\n")] = '\0';  // Remove trailing newline

    if (strcmp(inputType, "1") == 0) {
        unsigned long decimal;
        printf("Enter the decimal number: ");
        fgets(input, sizeof(input), stdin);
        decimal = strtoul(input, NULL, 10);

        struct in_addr addr;
        addr.s_addr = htonl(decimal);
        char* ipAddress = inet_ntoa(addr);
        printf("IP Address: %s\n", ipAddress);
    } else if (strcmp(inputType, "2") == 0) {
        struct in_addr addr;
        printf("Enter the IP address: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

        if (inet_aton(input, &addr) == 0) {
            printf("Invalid IP address format.\n");
            return 1;
        }

        unsigned long decimal = ntohl(addr.s_addr);
        printf("Decimal: %lu\n", decimal);
    } else {
        printf("Invalid input type.\n");
        return 1;
    }

    return 0;
}

