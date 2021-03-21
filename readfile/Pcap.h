#ifndef PCAP_H
#define PCAP_H
#include "defs.h"
#include "types.h"
#include "tjson.hpp"
#include <memory>
#include <pcap/pcap.h>
#include <optional>

class Pcap
{

public:


    Pcap();

    ~Pcap();

    bool init(const char* fname);

    void operator++();

    Result_t& next();

    bool hasNext() const;

    void loop();

protected:

    template<typename T, typename Return_T>
    Return_T packetHandlerT(u_char *userData, const Result_t& res, T protocol)
    {
        (void)userData; //reserved userdata...
        return protocol(res);
    }

    template<typename T>
    T packetHandlerT(T protocol)
    {
        return protocol();
    }

    int packetCount;
    pcap_t* p_Cap;

    char errbuf[PCAP_ERRBUF_SIZE];

    Result_t m_nextRes;

private:

    tjson::JsonSerializer serializer;

    Result_t VParse()
    {
        return {};
    }

    template <typename T, class...Args>
    auto VParse(T value, Args&&...FArgs)// -> decltype (value)
    {
        T resultready = packetHandlerT(value);
        if (resultready.valid()) {
            value.value.type = resultready.type();
            serializer.add(resultready.jsonb);
            return value.value;
        }
        // how to not pass the result ready here?
        else {
            return VParse(std::forward<Args>(FArgs)...);
        }
    }


};

#endif // PCAP_H