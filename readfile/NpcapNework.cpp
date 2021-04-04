#include "NpcapNework.h"

int CAPTURE_SETUP_SUCCESS = 0;

NcapRetCodes NpcapNework::findNewrokDevices(int &listNum)
{
    /* Retrieve the device list */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        return NcapRetCodes::retr_list;
    }

    /* Print the list */
    for (d = alldevs; d; d = d->next)
    {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
    }

    return NcapRetCodes::Ok;
}

NcapRetCodes NpcapNework::setupSelectedAdapter(int& adapterChoise)
{
    if (adapterChoise < 1 || adapterChoise > i)
    {
        printf("\nInterface number out of range.\n");
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return NcapRetCodes::out_of_range;
    }
    inum = adapterChoise;

    /* Jump to the selected adapter */
    for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

    /* Open the device */
    /* Open the adapter */
    if ((adhandle = pcap_open_live(d->name,	// name of the device
        65536,			// portion of the packet to capture. 
                       // 65536 grants that the whole packet will be captured on all the MACs.
        1,				// promiscuous mode (nonzero means promiscuous)
        1000,			// read timeout
        errbuf			// error buffer
    )) == NULL)
    {
        fprintf(stderr, "\nUnable to open the adapter. %s is not supported by Npcap\n", d->name);
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return NcapRetCodes::open_adapter_err;
    }

    printf("\nlistening on %s...\n", d->description);

    /* At this point, we don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);

    return NcapRetCodes::Ok;
}

NcapRetCodes NpcapNework::lisseningdAdapter(callback fn)
{
     /* start the capture */
    pcap_loop(adhandle, 0, fn, NULL);
    return NcapRetCodes::Ok;
}
