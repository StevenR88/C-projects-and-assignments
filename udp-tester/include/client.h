#ifndef ASSIGNMENT_2_CLIENT_H
#define ASSIGNMENT_2_CLIENT_H

#include <assert.h>
#include <dc_application/command_line.h>
#include <dc_application/config.h>
#include <dc_application/defaults.h>
#include <dc_application/environment.h>
#include <dc_application/options.h>
#include <dc_fsm/fsm.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_netdb.h>
#include <dc_posix/dc_unistd.h>
#include <dc_posix/sys/dc_socket.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_SERVER_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 4981
#define DEFAULT_START "START"
#define DEFAULT_PACKETS 100
#define DEFAULT_PACKET_SIZE 100
#define DEFAULT_DELAY 50
#define MAXLINE  1024

/**
 * Application States.
 */
enum application_states {
    SEND_TCP = DC_FSM_USER_START,
    CREATE_UDP_CONNECTION,
    SEND_TO_SERVER,
    CLOSE,
};

/**
 * Client Struct --> Passed around in FSM.
 */
struct client {
    const char* server;
    u_int16_t port;
    const char* start;
    u_int16_t packets;
    u_int16_t packetSize;
    u_int16_t delay;
    int tcpSocketFD;
    int udpSocketFD;
    const char* clientID;
    struct sockaddr_in serverAddress;
};

/**
 * Connection Terminated Signal.
 */
const char connectionTerminated[27] = "TCP Connection Terminated\n\n";

/**
 * Gets the current time as a readable string and parses it to separate into
 * needed output.
 * @param env
 * @param err
 * @return char* string
 */
char* getCurrentTime(const struct dc_posix_env *env, struct dc_error *err);

#endif //ASSIGNMENT_2_CLIENT_H
