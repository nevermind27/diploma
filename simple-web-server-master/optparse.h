
#ifndef SIMPLE_WEB_SERVER_OPTPARSE_H
#define SIMPLE_WEB_SERVER_OPTPARSE_H

#include <cstdint>
#include <netinet/in.h>

#define OPTION_MAX_LEN 255

struct options {
    char server_root[OPTION_MAX_LEN];
    //In network byte order
    in_addr server_ip;
    //In network byte order
    uint16_t server_port;
    uint16_t workers_count = 4;
    bool daemonize = true;
};

void show_usage(const char *ex_path);
int parse_args(int argc, char **argv, options &opts);

#endif //SIMPLE_WEB_SERVER_OPTPARSE_H
