#include "logParser.h"

struct application_settings {
    struct dc_opt_settings opts;
    struct dc_setting_string *message;
};

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);
static int destroy_settings(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings **psettings);
static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);
static void error_reporter(const struct dc_error *err);
static void trace_reporter(const struct dc_posix_env *env, const char *file_name, const char *function_name, size_t line_number);

Link createNode() {
    Link link = (Link) malloc(sizeof(struct Node));

    link->next = NULL;
    return link;
}

Link createNodeWithNextNode(Link next) {
    Link link = createNode();
    link->next = next;
    return link;
}

Link getTail(Link head) {
    if (!head) {
        return NULL;
    }

    if (!head->next) {
        return head;
    }

    return getTail(head->next);
}

Link addLast(Link *head) {
    Link newTail = createNode();
    if (!*head) {
        *head = newTail;
        return newTail;
    }

    Link currentTail = getTail(*head);
    currentTail->next = newTail;
    return newTail;
}

void deleteList(Link head_ref) {
    Link current = head_ref;
    Link next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    head_ref = NULL;
}

int main(int argc, char *argv[]) {
    dc_posix_tracer tracer;
    dc_error_reporter reporter;
    struct dc_posix_env env;
    struct dc_error err;
    struct dc_application_info *info;
    int ret_val;

    reporter = error_reporter;
    tracer = trace_reporter;
    tracer = NULL;
    dc_error_init(&err, reporter);
    dc_posix_env_init(&env, tracer);
    info = dc_application_info_create(&env, &err, "Settings Application");
    ret_val = dc_application_run(&env, &err, info, create_settings, destroy_settings, run, dc_default_create_lifecycle, dc_default_destroy_lifecycle, NULL, argc, argv);
    dc_application_info_destroy(&env, &info);
    dc_error_reset(&err);

    return ret_val;
}

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err) {
    struct application_settings *settings;

    DC_TRACE(env);
    settings = dc_malloc(env, err, sizeof(struct application_settings));

    if(settings == NULL) {
        return NULL;
    }

    settings->opts.parent.config_path = dc_setting_path_create(env, err);
    settings->message = dc_setting_string_create(env, err);

    struct options opts[] = {
            {(struct dc_setting *)settings->opts.parent.config_path,
                    dc_options_set_path,
                    "config",
                    required_argument,
                    'c',
                    "CONFIG",
                    dc_string_from_string,
                    NULL,
                    dc_string_from_config,
                    NULL},
            {(struct dc_setting *)settings->message,
                    dc_options_set_string,
                    "message",
                    required_argument,
                    'm',
                    "MESSAGE",
                    dc_string_from_string,
                    "message",
                    dc_string_from_config,
                    "Hello, Default World!"},
    };

    settings->opts.opts_count = (sizeof(opts) / sizeof(struct options)) + 1;
    settings->opts.opts_size = sizeof(struct options);
    settings->opts.opts = dc_calloc(env, err, settings->opts.opts_count, settings->opts.opts_size);
    dc_memcpy(env, settings->opts.opts, opts, sizeof(opts));
    settings->opts.flags = "m:";
    settings->opts.env_prefix = "DC_EXAMPLE_";

    return (struct dc_application_settings *)settings;
}

static int destroy_settings(const struct dc_posix_env *env, __attribute__((unused)) struct dc_error *err,
                            struct dc_application_settings **psettings) {
    struct application_settings *app_settings;

    DC_TRACE(env);
    app_settings = (struct application_settings *)*psettings;
    dc_setting_string_destroy(env, &app_settings->message);
    dc_free(env, app_settings->opts.opts, app_settings->opts.opts_count);
    dc_free(env, *psettings, sizeof(struct application_settings));

    if(env->null_free) {
        *psettings = NULL;
    }

    return 0;
}

size_t printMissingPackets(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs,
        size_t expectedPackets, size_t receivedPackets) {
    bool packetChecker[expectedPackets + 1];
    dc_memset(env, packetChecker, 0, sizeof(packetChecker));
    char packetsMessage[MAXLINE] = {0};
    size_t lostPacketsCounter = 0;

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "Packet Numbers Lost:\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    for (size_t i = 0; i < receivedPackets; i++) {
        packetChecker[packetIDs[i]] = true;
    }

    for (size_t i = 1; i <= expectedPackets; i++) {
        if (!packetChecker[i]) {
            printf("%06zu\n", i);
            lostPacketsCounter++;
        }
    }

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    return lostPacketsCounter;
}

size_t calculateMissingPacketsInSequence(const struct dc_posix_env *env, struct dc_error *err,
        const u_int16_t *packetIDs, size_t expectedPackets, size_t receivedPackets, const char *function) {
    bool packetChecker[expectedPackets + 1];
    dc_memset(env, packetChecker, 0, sizeof(packetChecker));
    size_t lostPacketsCounter = 0;
    size_t lostPackets[expectedPackets];
    dc_memset(env, lostPackets, 0, sizeof(lostPackets));
    size_t minLost = 0;
    size_t maxLost = 0;

    for (size_t i = 0; i < receivedPackets; i++) {
        packetChecker[packetIDs[i]] = true;
    }

    for (size_t i = 1; i <= expectedPackets; i++) {
        if (!packetChecker[i]) {
            lostPackets[lostPacketsCounter] = i;
            lostPacketsCounter++;
        }
    }

    if (lostPacketsCounter >= 1) {
        minLost = 1;
        maxLost = 1;
    }

    for (size_t i = 0; i < lostPacketsCounter; i++) {

        if(lostPackets[i + 1] == lostPackets[i] + 1) {
            maxLost++;
        }
    }
    if (dc_strcmp(env, function, "min") == 0) {
        return minLost;
    } else {
        return maxLost;
    }
}

void printOutOfOrderPackets(const struct dc_posix_env *env, struct dc_error *err, const u_int16_t *packetIDs, size_t receivedPackets) {
    char packetsMessage[MAXLINE] = {0};
    size_t packetsOutOfOrder = 0;

    for (size_t i = 0; i < receivedPackets - 1; i++) {
        if ((packetIDs[i + 1] < packetIDs[i])) {
            packetsOutOfOrder++;
        }
    }

    sprintf(packetsMessage, "Number of Packets Out Of Order: %zu\n", packetsOutOfOrder);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "Packet Numbers Out Of Order:\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    for (size_t i = 0; i < receivedPackets - 1; i++) {
        if ((packetIDs[i + 1] < packetIDs[i])) {
            printf("%06hu\n", packetIDs[i + 1]);
        }
    }

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));
}

size_t calculateOutOfOrderInSequence(const struct dc_posix_env *env, struct dc_error *err,
        const u_int16_t *packetIDs, size_t receivedPackets, const char *function) {
    size_t outOfOrderCounter = 0;
    size_t outOfOrderPackets[receivedPackets];
    dc_memset(env, outOfOrderPackets, 0, sizeof(outOfOrderPackets));
    size_t minOrder = 0;
    size_t maxOrder = 0;
    size_t arrayCounter = 0;

    for (size_t i = 0; i < receivedPackets - 1; i++) {
        if ((packetIDs[i + 1] < packetIDs[i])) {
            outOfOrderCounter++;
        }
    }

    for (size_t i = 0; i < receivedPackets - 1; i++) {
        if ((packetIDs[i + 1] < packetIDs[i])) {
            outOfOrderPackets[arrayCounter] = packetIDs[i + 1];
            arrayCounter++;
        }
    }

    if (outOfOrderCounter >= 1) {
        minOrder = 1;
        maxOrder = 1;
    }

    for (size_t i = 0; i < outOfOrderCounter; i++) {
        if(outOfOrderPackets[i + 1] == outOfOrderPackets[i] - 1) {
            maxOrder++;
        }
    }

    if (dc_strcmp(env, function, "min") == 0) {
        return minOrder;
    } else {
        return maxOrder;
    }
}

void parseLogStatistics(const struct dc_posix_env *env, struct dc_error *err) {
    int tcpLogFD;
    int udpLogFD;
    FILE *tcpLogFileDescriptor;
    FILE *udpLogFileDescriptor;
    uint16_t packetCounter;
    char *logStorage = NULL;
    size_t lineSize = 0;
    char *endPointer;
    size_t clientCounter = 0;
    char buffer[MAXLINE] = {0};
    char packetsMessage[MAXLINE] = {0};
    size_t lostPacketsTotal = 0;
    double lostPackageAverage;
    size_t tempMinLost = 0;
    size_t tempMaxLost = 0;
    size_t minLost = 0;
    size_t maxLost = 0;
    size_t tempMinOrder = 0;
    size_t tempMaxOrder = 0;
    size_t minOrder = 0;
    size_t maxOrder = 0;

    tcpLogFD = dc_open(env, err, "../../logs/tcpLog.txt", O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    tcpLogFileDescriptor = dc_fdopen(env, err, tcpLogFD, "r");

    // Creating a linked list of all the clients in the tcp log.
    Link clientHead = NULL;
    while(dc_getline(env, err, &logStorage, &lineSize, tcpLogFileDescriptor) > 0) {
        Link currentLink;
        currentLink = addLast(&clientHead);
        dc_strtok_r(env, logStorage, " ", &endPointer);
        dc_strtok_r(env, endPointer, " ", &endPointer);
        currentLink->clientID = dc_strdup(env, err, dc_strtok_r(env, endPointer, ":", &endPointer));
        dc_strtok_r(env, endPointer, ":", &endPointer);
        dc_strtok_r(env, endPointer, ":", &endPointer);
        dc_strtok_r(env, endPointer, ":", &endPointer);
        currentLink->expectedNumberOfPackets = (u_int16_t) dc_strtol(env, err, endPointer, &endPointer, 10);
        dc_strtok_r(env, endPointer, ":", &endPointer);
        currentLink->packetSize = (u_int16_t) dc_strtol(env, err, endPointer, &endPointer, 10);
        clientCounter++;

        dc_memset(env, logStorage, 0, sizeof(logStorage));
    }

    while (clientHead) {
        packetCounter = 0;
        clientHead->packetIDs = dc_calloc(env, err, clientHead->expectedNumberOfPackets, sizeof(u_int16_t));
        udpLogFD = dc_open(env, err, "../../logs/udpLog.txt", O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        udpLogFileDescriptor = dc_fdopen(env, err, udpLogFD, "r");
        while(dc_getline(env, err, &logStorage, &lineSize, udpLogFileDescriptor) > 0) {
            if (dc_strcmp(env, dc_strtok_r(env, logStorage, ":", &endPointer), clientHead->clientID) == 0) {
                clientHead->packetIDs[packetCounter] = (u_int16_t) dc_strtol(env, err, endPointer, &endPointer, 10);
                packetCounter++;
            }
        }
        clientHead->receivedNumberOfPackets = packetCounter;
        sprintf(buffer, "Client %s:\nPackets Expected = %hu\nPackets Received = %hu\nPackets Lost = %d\n",
                clientHead->clientID, clientHead->expectedNumberOfPackets, packetCounter, clientHead->expectedNumberOfPackets - packetCounter);
        dc_write(env, err, STDOUT_FILENO, buffer, dc_strlen(env, buffer));
        lostPacketsTotal += printMissingPackets(env, err, clientHead->packetIDs, clientHead->expectedNumberOfPackets,
                            clientHead->receivedNumberOfPackets);
        tempMinLost = calculateMissingPacketsInSequence(env, err, clientHead->packetIDs, clientHead->expectedNumberOfPackets,
                                          clientHead->receivedNumberOfPackets, "min");
        if (tempMinLost > minLost) {
            minLost = tempMinLost;
        }

        tempMaxLost = calculateMissingPacketsInSequence(env, err, clientHead->packetIDs, clientHead->expectedNumberOfPackets,
                                          clientHead->receivedNumberOfPackets, "max");
        if (tempMaxLost > maxLost) {
            maxLost = tempMaxLost;
        }

        tempMinOrder = calculateOutOfOrderInSequence(env, err, clientHead->packetIDs,
                                                     clientHead->receivedNumberOfPackets, "min");
        if (tempMinOrder > minOrder) {
            minOrder = tempMinOrder;
        }

        tempMaxOrder = calculateOutOfOrderInSequence(env, err, clientHead->packetIDs,
                                                     clientHead->receivedNumberOfPackets, "max");
        if (tempMaxOrder > maxOrder) {
            maxOrder = tempMaxOrder;
        }

        printOutOfOrderPackets(env, err, clientHead->packetIDs, clientHead->receivedNumberOfPackets);

        dc_close(env, err, udpLogFD);
        clientHead = clientHead->next;
    }

    sprintf(packetsMessage, "Minimum Lost Packets: %zu\n", minLost);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "Maximum Lost Packets: %zu\n", maxLost);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "Minimum Out Of Order Packets: %zu\n", minOrder);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "Maximum Out Of Order Packets: %zu\n", maxOrder);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    sprintf(packetsMessage, "----------------------------------------\n");
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    lostPackageAverage = (double)lostPacketsTotal / (double) clientCounter;
    sprintf(packetsMessage, "Average Number Of Lost Packets: %f\n", (double) lostPackageAverage);
    dc_write(env, err, STDOUT_FILENO, packetsMessage, dc_strlen(env, packetsMessage));
    dc_memset(env, packetsMessage, 0, sizeof(packetsMessage));

    deleteList(clientHead);
}

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings) {
    DC_TRACE(env);
    parseLogStatistics(env, err);

    return EXIT_SUCCESS;
}

static void error_reporter(const struct dc_error *err) {
    fprintf(stderr, "ERROR: %s : %s : @ %zu : %d\n", err->file_name, err->function_name, err->line_number, 0);
    fprintf(stderr, "ERROR: %s\n", err->message);
}

static void trace_reporter(__attribute__((unused)) const struct dc_posix_env *env, const char *file_name,
                           const char *function_name, size_t line_number) {
    fprintf(stdout, "TRACE: %s : %s : @ %zu\n", file_name, function_name, line_number);
}
