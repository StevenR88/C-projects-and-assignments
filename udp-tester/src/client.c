#include "client.h"

struct application_settings {
    struct dc_opt_settings opts;
    struct dc_setting_string *message;
    struct dc_setting_string *server;
    struct dc_setting_uint16 *port;
    struct dc_setting_string *start;
    struct dc_setting_uint16 *packets;
    struct dc_setting_uint16 *packetSize;
    struct dc_setting_uint16 *delay;
};

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);
static int destroy_settings(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings **psettings);
static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);
static void error_reporter(const struct dc_error *err);
static void trace_reporter(const struct dc_posix_env *env, const char *file_name, const char *function_name, size_t line_number);
static int createSocket(const struct dc_posix_env *env, struct dc_error *err, void *arg);
static int sendTCPInformation(const struct dc_posix_env *env, struct dc_error *err, void *arg);
static int sendToServer(const struct dc_posix_env *env, struct dc_error *err, void *arg);
static int closeConnection(const struct dc_posix_env *env, struct dc_error *err, void *arg);

int main(int argc, char *argv[]) {
    dc_posix_tracer tracer;
    dc_error_reporter reporter;
    struct dc_posix_env env;
    struct dc_error err;
    struct dc_application_info *info;
    int ret_val;

    reporter = error_reporter;
//    tracer = trace_reporter;
    tracer = NULL;
    dc_error_init(&err, reporter);
    dc_posix_env_init(&env, tracer);
    info = dc_application_info_create(&env, &err, "Settings Application");
    ret_val = dc_application_run(&env, &err, info, create_settings, destroy_settings,
                                 run, dc_default_create_lifecycle, dc_default_destroy_lifecycle,
                                 NULL, argc, argv);
    dc_application_info_destroy(&env, &info);
    dc_error_reset(&err);

    return ret_val;
}

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err) {
    struct application_settings *settings;

    static const char *default_server = DEFAULT_SERVER_ADDRESS;
    static const uint16_t default_port = DEFAULT_PORT;
    static const uint16_t default_packetSize = DEFAULT_PACKET_SIZE;
    static const uint16_t default_packets = DEFAULT_PACKETS;
    static const uint16_t default_delay = DEFAULT_DELAY;

    DC_TRACE(env);
    settings = dc_malloc(env, err, sizeof(struct application_settings));

    if(settings == NULL) {
        return NULL;
    }

    settings->opts.parent.config_path = dc_setting_path_create(env, err);
    settings->message = dc_setting_string_create(env, err);
    settings->server = dc_setting_string_create(env, err);
    settings->port = dc_setting_uint16_create(env, err);
    settings->start = dc_setting_string_create(env, err);
    settings->packets = dc_setting_uint16_create(env, err);
    settings->packetSize = dc_setting_uint16_create(env, err);
    settings->delay = dc_setting_uint16_create(env, err);

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
            {(struct dc_setting *)settings->server,
                    dc_options_set_string,
                    "server",
                    required_argument,
                    's',
                    "SERVER",
                    dc_string_from_string,
                    "server",
                    dc_string_from_config,
                    default_server},
            {(struct dc_setting *)settings->port,
                    dc_options_set_uint16,
                    "port",
                    required_argument,
                    'p',
                    "PORT",
                    dc_uint16_from_string,
                    "port",
                    dc_uint16_from_config,
                    &default_port},
            {(struct dc_setting *)settings->start,
                    dc_options_set_string,
                    "start",
                    required_argument,
                    't',
                    "START",
                    dc_string_from_string,
                    "start",
                    dc_string_from_config,
                    DEFAULT_START},
            {(struct dc_setting *)settings->packets,
                    dc_options_set_uint16,
                    "packets",
                    required_argument,
                    'a',
                    "PACKETS",
                    dc_uint16_from_string,
                    "packets",
                    dc_uint16_from_config,
                    &default_packets},
            {(struct dc_setting *)settings->packetSize,
                    dc_options_set_uint16,
                    "pSize",
                    required_argument,
                    'z',
                    "PacketSize",
                    dc_uint16_from_string,
                    "pSize",
                    dc_uint16_from_config,
                    &default_packetSize},
            {(struct dc_setting *)settings->delay,
                    dc_options_set_uint16,
                    "delay",
                    required_argument,
                    'd',
                    "DELAY",
                    dc_uint16_from_string,
                    "delay",
                    dc_uint16_from_config,
                    &default_delay},
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

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings) {
    struct application_settings *app_settings;
    int ret_val;

    DC_TRACE(env);

    struct dc_fsm_info *fsm_info;
    static struct dc_fsm_transition transitions[] = {
            {DC_FSM_INIT,           SEND_TCP,              sendTCPInformation},
            {SEND_TCP,              CREATE_UDP_CONNECTION, createSocket},
            {SEND_TCP,              CLOSE,                 closeConnection},
            {CREATE_UDP_CONNECTION, SEND_TO_SERVER,        sendToServer},
            {CREATE_UDP_CONNECTION, CLOSE,                 closeConnection},
            {SEND_TO_SERVER,        CLOSE,                 closeConnection},
            {CLOSE,                 DC_FSM_EXIT, NULL}
    };

    ret_val = EXIT_SUCCESS;
    fsm_info = dc_fsm_info_create(env, err, "Client");

    app_settings = (struct application_settings *)settings;

    if(dc_error_has_no_error(err)) {
        struct client client;
        int from_state;
        int to_state;

        client.server = dc_setting_string_get(env, app_settings->server);
        client.port = dc_setting_uint16_get(env, app_settings->port);
        client.start = dc_setting_string_get(env, app_settings->start);
        client.packets = dc_setting_uint16_get(env, app_settings->packets);
        client.packetSize = dc_setting_uint16_get(env, app_settings->packetSize);
        client.delay = dc_setting_uint16_get(env, app_settings->delay);

        ret_val = dc_fsm_run(env, err, fsm_info, &from_state, &to_state, &client, transitions);
        dc_fsm_info_destroy(env, &fsm_info);
    }

    return ret_val;
}

static void error_reporter(const struct dc_error *err) {
    fprintf(stderr, "ERROR: %s : %s : @ %zu : %d\n", err->file_name, err->function_name, err->line_number, 0);
    fprintf(stderr, "ERROR: %s\n", err->message);
}

static void trace_reporter(__attribute__((unused)) const struct dc_posix_env *env, const char *file_name,
                           const char *function_name, size_t line_number) {
    fprintf(stdout, "TRACE: %s : %s : @ %zu\n", file_name, function_name, line_number);
}

char* getCurrentTime(const struct dc_posix_env *env, struct dc_error *err) {
    char *currentTimeString;
    char *endPointer;
    time_t currentTime;

    time(&currentTime);
    currentTimeString = dc_strdup(env, err, ctime(&currentTime));
    dc_strtok_r(env, currentTimeString, " ", &endPointer);
    dc_strtok_r(env, endPointer, " ", &endPointer);
    dc_strtok_r(env, endPointer, " ", &endPointer);
    endPointer[5] = '\0';

    dc_memset(env, currentTimeString, 0, sizeof(currentTimeString));
    currentTimeString = endPointer;

    return currentTimeString;
}

static int sendTCPInformation(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct client *client;
    client = (struct client *)arg;

    const char* ipVersion = "IPv4";
    struct addrinfo hints;
    struct addrinfo *result;
    int family;
    socklen_t size;
    size_t message_length;
    uint16_t converted_port;
    char buffer[MAXLINE] = {0};

    char tcpCommand[MAXLINE]= {0};
    sprintf(tcpCommand, "Packets:%hu Size:%hu\n", client->packets, client->packetSize);

    if(dc_strcmp(env, ipVersion, "IPv4") == 0) {
        family = PF_INET;
    }
    else {
        if(dc_strcmp(env, ipVersion, "IPv6") == 0) {
            family = PF_INET6;
        }
        else {
            assert("Can't get here" != NULL);
            family = 0;
        }
    }

    dc_memset(env, &hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    dc_getaddrinfo(env, err, client->server, NULL, &hints, &result);

    if(dc_error_has_error(err)) {
        return -1;
    }

    client->tcpSocketFD = dc_socket(env, err, result->ai_family, result->ai_socktype, result->ai_protocol);

    if(dc_error_has_error(err)) {
        return -1;
    }

    converted_port = htons(client->port);

    if(dc_strcmp(env, ipVersion, "IPv4") == 0) {
        struct sockaddr_in *sockaddr;

        sockaddr = (struct sockaddr_in *)result->ai_addr;
        sockaddr->sin_port = converted_port;
        size = sizeof(struct sockaddr_in);
    }
    else {
        if(dc_strcmp(env, ipVersion, "IPv6") == 0) {
            struct sockaddr_in6 *sockaddr;

            sockaddr = (struct sockaddr_in6 *)result->ai_addr;
            sockaddr->sin6_port = converted_port;
            size = sizeof(struct sockaddr_in);
        }
        else {
            assert("Can't get here" != NULL);
            size = 0;
        }
    }

    dc_connect(env, err, client->tcpSocketFD, result->ai_addr, size);

    if(dc_error_has_error(err)) {
        printf("Connection Error -> Closing Client\n");
        next_state = CLOSE;
        return next_state;
    }

    dc_write(env, err, STDOUT_FILENO, "Client Connected to Server...\n", sizeof ("Client Connected to Server...\n"));

    message_length = dc_strlen(env, tcpCommand);
    dc_write(env, err, client->tcpSocketFD, tcpCommand, message_length);
    dc_read(env, err, client->tcpSocketFD, buffer, sizeof(buffer));
    dc_write(env, err, STDOUT_FILENO, "TCP Message Sent.\n", sizeof ("TCP Message Sent.\n"));
    client->clientID = dc_strdup(env, err, buffer);

    dc_freeaddrinfo(env, result);

    next_state = CREATE_UDP_CONNECTION;
    return next_state;
}

static int createSocket(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct client *client;
    client = (struct client *)arg;

    client->udpSocketFD = dc_socket(env, err, AF_INET, SOCK_DGRAM, 0);
    if (dc_error_has_error(err)) {
        printf("UDP Socket Creation Failed -> Closing Client\n");
        next_state = CLOSE;
        return next_state;
    }

    memset(&client->serverAddress, 0, sizeof(client->serverAddress));

    client->serverAddress.sin_family = AF_INET;
    client->serverAddress.sin_port = htons(client->port);
    client->serverAddress.sin_addr.s_addr = INADDR_ANY;

    next_state = SEND_TO_SERVER;
    return next_state;
}

static int sendToServer(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct client *client;
    client = (struct client *)arg;

    char *packet;
    u_int16_t packetID = 1;
    char *packetBody;

    struct timespec ts;

    char *currentTime;
    currentTime = getCurrentTime(env, err);

    while ((dc_strcmp(env, client->start, "START") != 0) && (dc_strcmp(env, currentTime, client->start) != 0)) {
        printf("Client will send packets at %s.\nCurrent Time is %s\n", client->start, currentTime);
        dc_memset(env, currentTime, 0, sizeof(currentTime));
        currentTime = getCurrentTime(env, err);
        dc_sleep(env, 30);
    }

    packet = dc_calloc(env, err, client->packetSize, sizeof(char));
    packetBody = dc_calloc(env, err, (client->packetSize - 12), sizeof(char));

    for (size_t i = 0; i < client->packetSize - 12; i++) {
        packetBody[i] = '*';
    }

    for (int i = 0; i < client->packets; i++) {
        sprintf(packet, "%s:%06hu:%s\n", client->clientID, packetID, packetBody);
        dc_sendto(env, err, client->udpSocketFD, packet, client->packetSize, 0,
                  (const struct sockaddr *) &client->serverAddress, sizeof(client->serverAddress));

        if (dc_error_has_error(err)) {
            printf("UDP Send to Server Failed -> Closing Client\n");
            next_state = CLOSE;
            return next_state;
        }

        dc_memset(env, packet, 0, sizeof(packet));
        packetID++;

        if (client->delay >= 1000) {
            ts.tv_sec = client->delay / 1000;
            ts.tv_nsec = (client->delay % 1000) * 1000000;
        } else {
            ts.tv_sec = 0;
            ts.tv_nsec = client->delay * 1000000;
        }
        nanosleep(&ts, &ts);
    }

    next_state = CLOSE;
    return next_state;
}

static int closeConnection(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct client *client;
    client = (struct client *)arg;

    if (client->tcpSocketFD != -1) {
        dc_write(env, err, client->tcpSocketFD, connectionTerminated, sizeof(connectionTerminated));
        dc_close(env, err, client->tcpSocketFD);
    }

    if (client->udpSocketFD != -1) {
        dc_close(env, err, client->udpSocketFD);
    }

    next_state = DC_FSM_EXIT;
    return next_state;
}
