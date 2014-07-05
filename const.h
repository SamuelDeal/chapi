#ifndef CONST_H
#define CONST_H

#define CONFIG_FILE             "/home/sam/cfg.ini"

#define ___str(x) #x
#define STRINGIFY(x) ___str(x)


#define CHAPI_TCP_PORT              13013
#define CHAPI_BROADCAST_PORT        13014

#define VIDEOHUB_PORT               9990
#define ATEM_PORT                   9910

#define DEV_CHAPI_SERVER            "server"
#define DEV_CHAPI_DEVICE            "chapi"

#define VIDEOHUB_STR                "VIDEO OUTPUT ROUTING:"

#define CURRENT_VERSION             "1.0"

#define VH_RECONNECT_DELAY          1000000 //in usec
#define VH_PING_DELAY               500000 //in usec

#define VH_PING_LOST_TOLERANCE      2

#endif // CONST_H
