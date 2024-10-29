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


/*
 * ===  FUNCTION  ==============================================================
 *         Name:  main
 *  Description:  
 * =============================================================================
 */
int main ()
{
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    int ifCtr = 0;
    UINT ip_addr;
    UINT net_mask;
    UINT ip_prefix;


    printf("\n\n\n\t<< Npcap Adapters list >>\nalbertdm.engineer@gmail.com\n");

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return 1;
    }
// Make an initial call to GetAdaptersInfo to get
// the necessary size into the ulOutBufLen variable
    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 1;
        }
    }
    
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {

            #if BC_UDP_RAW == 1
                net_mask = inet_addr(BROADCAST_MASK_24);
            #else
                net_mask = inet_addr(pAdapter->IpAddressList.IpMask.String);
            #endif
            int index = pAdapter->Index;
            printf("\n Adapter #%d Index:\t\t%ld", index, pAdapter->Index);
            printf("\n Adapter #%d Name:\t\t%s", index, &pAdapter->AdapterName[0]);
            printf("\n Adapter #%d MAC:\t\t", index);
            for (int mac_idx = 0; mac_idx < 6; mac_idx++) printf("%x ",pAdapter->Address[mac_idx]); // + sizeof(u_char)*mac_idx);
                
            printf("\n Adapter #%d IP Mask:\t\t%s", index, pAdapter->IpAddressList.IpMask.String);
            printf("\n Adapter #%d IP Address:  \t%s", index, pAdapter->IpAddressList.IpAddress.String);

            printf("\n");

                
            pAdapter = pAdapter->Next;
        }
    } else {
        printf("GetAdaptersInfo failed with error: %ld\n", dwRetVal);

    }
   
    if (pAdapterInfo)
        FREE(pAdapterInfo);

    return 0;
}
