#ifndef ASSIGNMENT_2_LOGPARSER_H
#define ASSIGNMENT_2_LOGPARSER_H

#include <dc_application/command_line.h>
#include <dc_application/config.h>
#include <dc_application/defaults.h>
#include <dc_application/environment.h>
#include <dc_posix/dc_fcntl.h>
#include <dc_application/options.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_unistd.h>
#include <dc_posix/dc_stdio.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE  1024

struct Node {
    const char *clientID;
    u_int16_t expectedNumberOfPackets;
    u_int16_t receivedNumberOfPackets;
    u_int16_t packetSize;
    u_int16_t *packetIDs;
    struct Node* next;
};

typedef struct Node* Link;

Link createNode(void);
Link createNodeWithNextNode(Link next);
Link getTail(Link head);
Link addLast(Link *head);
void deleteList(Link head_ref);
size_t printMissingPackets(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs, size_t expectedPackets, size_t receivedPackets);
size_t calculateMissingPacketsInSequence(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs,
        size_t expectedPackets, size_t receivedPackets, const char *function);
void printOutOfOrderPackets(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs, size_t receivedPackets);
size_t calculateOutOfOrderInSequence(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs,
        size_t receivedPackets, const char *function);
void parseLogStatistics(const struct dc_posix_env *env, struct dc_error *err);

#endif //ASSIGNMENT_2_LOGPARSER_H
