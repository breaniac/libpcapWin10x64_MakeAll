#include <iostream>
#include <pcap/pcap.h>
#include "Pcap.h"
//#include "NpcapNework.h"
#include "utils.h"

#include <fstream>
#include <csignal>

using namespace std;

#if 0
void my_callback(u_char* args, const struct pcap_pkthdr* pkthdr, const u_char*
    packet)
{
    static int count = 1;
    fprintf(stdout, "%3d, ", count);
    fflush(stdout);
    count++;
}

void another_callback(u_char* arg, const struct pcap_pkthdr* pkthdr,
    const u_char* packet)
{
    int i = 0;
    static int count = 0;

    printf("Packet Count: %d\n", ++count);    /* Number of Packets */
    printf("Recieved Packet Size: %d\n", pkthdr->len);    /* Length of header */
    printf("Payload:\n");                     /* And now the data */
    for (i = 0; i < pkthdr->len; i++) {
        if (isprint(packet[i]))                /* Check if the packet data is printable */
            printf("%c ", packet[i]);          /* Print it */
        else
            printf(" . ", packet[i]);          /* If not print a . */
        if ((i % 16 == 0 && i != 0) || i == pkthdr->len - 1)
            printf("\n");
    }
}

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
    struct tm* ltime;
    char timestr[16];
    time_t local_tv_sec;

    /*
     * unused parameters
     */
    (VOID)(param);
    (VOID)(pkt_data);

    /* convert the timestamp to readable format */
    local_tv_sec = header->ts.tv_sec;
    ltime = localtime(&local_tv_sec);
    strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

    printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);

    if (GetKeyState(VK_ESCAPE) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        return;
    }

}
#endif

int main(int argc, char** argv)
{
#ifdef _DEBUG
    //Pcap p;
    //for (int i = 1; i <= argc; i++) {
    //    if (p.init(argc1)) {
    //        p.loop();
    //    }
    //}
    //NpcapNework userNetwork;
    Pcap p;

    int iRetValue = 0;
    if (NcapRetCodes::Ok == p.findNewrokDevices(iRetValue))// userNetwork.findNewrokDevices(iRetValue))
    {
        printf("Enter the interface number (1-%d):", iRetValue);
        int ret = scanf("%d", &iRetValue);
    }
    else
    {
        printf("Error during of finding of nework devices.\n");
    }

    if (NcapRetCodes::Ok == p.setupSelectedAdapter(iRetValue))
    {
        //userNetwork.lisseningdAdapter(packet_handler);
        p.loop();
    }
    else
    {
        printf("Error during of SetUP of the selected adapter.\n");
    }

    system("PAUSE");

#else
    Pcap p;

    int iRetValue = 0;
    if (NcapRetCodes::Ok == p.findNewrokDevices(iRetValue))
    {
        printf("Enter the interface number (1-%d):", iRetValue);
        int ret = scanf("%d", &iRetValue);
    }
    else
    {
        printf("Error during of finding of nework devices.\n");
    }

    if (NcapRetCodes::Ok == p.setupSelectedAdapter(iRetValue))
    {
        p.loop();
    }
    else
    {
        printf("Error during of SetUP of the selected adapter.\n");
}
#endif


    return 0;
}

