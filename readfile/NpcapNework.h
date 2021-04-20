#pragma once
#include <iostream>
#include <pcap/pcap.h>
//#include "Pcap.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <csignal>

#include <Windows.h>
#include <process.h>
#include <tchar.h>

enum class NcapRetCodes { Ok, retr_list, out_of_range, open_adapter_err, NA };

class NpcapNework
{
public:
    NpcapNework() : adhandle(NULL){};
   ~ NpcapNework() { 
       if(NULL != adhandle)
            pcap_close(adhandle);
   };

   typedef void(*callback)(u_char* arg, const struct pcap_pkthdr* pkthdr, const u_char* packet);
   
    NcapRetCodes findNewrokDevices(int& listNum);
    NcapRetCodes setupSelectedAdapter(int& adapterChoise);
    NcapRetCodes lisseningdAdapter(callback fn);

    //int getInum(void) { return inum; }
    //pcap_if_t* getAllDevs(void) { return alldevs; }
    //pcap_if_t* getDevice(void) { return d; }
    //pcap_t* getNewortHandle(void) {return adhandle; }
    //char* getErrNework(void) { return errbuf; }

protected:
    pcap_if_t* alldevs;
    pcap_if_t* d;
    int inum;
    int i = 0;
    pcap_t* adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];
};

