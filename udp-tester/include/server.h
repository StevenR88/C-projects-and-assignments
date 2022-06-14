#ifndef ASSIGNMENT_2_SERVER_H
#define ASSIGNMENT_2_SERVER_H

#include <arpa/inet.h>
#include <bits/types/struct_timeval.h>
#include <dc_application/command_line.h>
#include <dc_application/config.h>
#include <dc_application/defaults.h>
#include <dc_application/environment.h>
#include <dc_application/options.h>
#include <dc_fsm/fsm.h>
#include <dc_network/common.h>
#include <dc_network/options.h>
#include <dc_network/server.h>
#include <dc_posix/dc_fcntl.h>
#include <dc_posix/dc_stdio.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_unistd.h>
#include <dc_posix/sys/dc_socket.h>
#include <dc_posix/sys/dc_wait.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>

#define DEFAULT_PORT 4981
#define MAXLINE  1024

/**
 * Finds maximum value between two input parameters.
 * @param x as an int
 * @param y as an int
 * @return int maximum value
 */
int max(int x, int y);

/**
 * Creates a server that listens for TCP and UDP connections. Prints
 * received data to log files.
 * @param env
 * @param err
 * @param tcpPort from program arguments
 */
void createServer(const struct dc_posix_env *env, struct dc_error *err, u_int16_t tcpPort);

const char connectionTerminated[27] = "TCP Connection Terminated\n\n";

#endif //ASSIGNMENT_2_SERVER_H
