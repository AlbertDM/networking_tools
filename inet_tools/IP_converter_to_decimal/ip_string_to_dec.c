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
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#if defined(_WIN32)
#define MALLOC malloc
#define FREE free
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <tchar.h>
#include <string.h>
#include <pcap.h>
#include <tchar.h>

#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <netinet/in.h>
#include <ifaddrs.h>

#endif  // _WIN32



/*-----------------------------------------------------------------------------
 * Define
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Types
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Globals
 *-----------------------------------------------------------------------------*/

volatile uint8_t quit_signal_app;

/*-----------------------------------------------------------------------------
 * Functions
 *-----------------------------------------------------------------------------*/

/*
 * ===  FUNCTION  ==============================================================
 *         Name:  main
 *  Description:  
 * =============================================================================
 */
static void
int_handler(int sig_num)
{
	printf("\n\tExiting ...\n\n");
    quit_signal_app = 1;
    exit(1);
}

/*
 * ===  FUNCTION  ==============================================================
 *         Name:  main
 *  Description:  
 * =============================================================================
 */
int main ()
{
    uint16_t buffLen = 64;
    char buff[buffLen];
    uint32_t output = 0;

    /* catch ctrl-c so we can print on exit */
	signal(SIGINT, int_handler);

    printf("\n\n\n\t<< IP converter from string to decimal >>\n\thttps://github.com/AlbertDM/networking_tools\n");

    while (!quit_signal_app) {
        memset(buff, 0, buffLen);
        printf ("\n\n\tInsert IP address in string format.\n\t> ");
        scanf ("%s", buff);
        inet_pton  (AF_INET, buff, &output);
        output = htonl(output);
        printf ("\tIP address in decimal format is:\n\t%d", output);
        output = htonl(output);

        /* catch ctrl-c so we can print on exit */
    }

    return 0;
}
