#include "Pcap.h"
#include "stun_t.h"
#include "rtp_t.h"
#include <string.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

using namespace stun;
using namespace rtp;

Pcap::Pcap()
{
    memset(&m_nextRes, 0, sizeof(m_nextRes));
    packetCount = 0;
}

Pcap::~Pcap()
{
    packetCount = 0;
}

bool Pcap::init(const char *fname)
{
    p_Cap = pcap_open_offline(fname, errbuf);
    if (!p_Cap) return false;
    return true;
}

void Pcap::operator ++()
{
    //m_nextRes.data = pcap_next(p_Cap, &m_nextRes.out);
    m_nextRes.data = pcap_next(adhandle, &m_nextRes.out);

#ifdef _DEBUG
//#else
    struct pcap_pkthdr* out;
    //while (int returnValue = pcap_next_ex(p_Cap, &out, &m_nextRes.data) >= 0)
    while (int returnValue = pcap_next_ex(adhandle, &out, &m_nextRes.data) >= 0)
    {
        // Print using printf. See printf reference:
        // http://www.cplusplus.com/reference/clibrary/cstdio/printf/

        // Show the packet number
        printf("Packet # %i\n", ++packetCount);

        // Show the size in bytes of the packet
        printf("Packet size: %ld bytes\n", out->len);

        // Show a warning if the length captured is different
        if (out->len != out->caplen)
            printf("Warning! Capture size different than packet size: %ld bytes\n", out->len);

        // Show Epoch Time
        printf("Epoch Time: %ld:%ld seconds\n", out->ts.tv_sec, out->ts.tv_usec);

        // loop through the packet and print it as hexidecimal representations of octets
        // We also have a function that does this similarly below: PrintData()
        for (u_int i = 0; (i < out->caplen); i++)
        {
            // Start printing on the next after every 16 octets
            if ((i % 256) == 0) printf("\n");

            // Print each octet as hex (x), make sure there is always two characters (.2).
            printf("%c", m_nextRes.data[i]); //"%.2x "
        }

        // Add two lines between packets
        printf("\n\n");
    }
#endif
}

Result_t& Pcap::next()
{
    operator++();
    return m_nextRes;
}

bool Pcap::hasNext() const
{
    if (DUMP_PAKETS == packetCount)
    {
        packetCount = 0;
        return false;
    }
    return true;
    //return  m_nextRes.data != nullptr;
}

/**
 * @brief Pcap::loop - example loop of packets...
 */
void Pcap::loop()
{
    //for(Result_t& res =  next(); hasNext(); operator++())
    while (1)
    {
        for (Result_t& res = next(); hasNext(); operator++())
        {
            auto resultNwork = VParse(StunRFC{ res },
                RtpRFC{ res });
            (void)resultNwork;
        }
        std::ofstream jsonfile;
        jsonfile.open("out.json");
        jsonfile << serializer.serialize();
        jsonfile.close();
    }
}






