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
 *         Name:  Interrupt Handler
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
    uint32_t user_input;
    uint16_t buffLen = 64;
    char buff[buffLen];

    /* catch ctrl-c so we can print on exit */
	signal(SIGINT, int_handler);

    printf("\n\n\n\t<< IP converter from decimal to string >>\n\thttps://github.com/AlbertDM/networking_tools\n");

    while (!quit_signal_app) {
        printf ("\n\n\tInsert IP address in decimal format.\n\t> ");
        scanf ("%d", &user_input);
        user_input = htonl(user_input);
        memset(buff, 0, buffLen);
        inet_ntop (AF_INET, &user_input, buff, buffLen );
        printf ("\tIP address in string format is:\n\t%s", buff);

        /* catch ctrl-c so we can print on exit */
    }

    return 0;
}
