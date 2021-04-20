#ifndef TYPES_H
#define TYPES_H
#include "tjson.hpp"
#include <pcap/pcap.h>
#include <map>

template <typename T>
struct IParseable
{
    typedef  T type;
    type value;

    IParseable() {};

    IParseable(const T& ref) : value{ref} { }

};

struct Result_t
{
    enum TypeRFC
    {
        STUN,
        RTP,
        RTSP,
        UNKNOWN
    };

    const u_char* data;

    struct pcap_pkthdr out;

    TypeRFC type;

};

struct mapDataHistogram 
{
    std::map<std::string, int> mapStunStatistics;
    std::map<int, int> mapRtpStatistics;
};


#endif // TYPES_H
