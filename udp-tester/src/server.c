#include "server.h"

struct application_settings {
    struct dc_opt_settings opts;
    struct dc_setting_string *message;
    struct dc_setting_uint16 *port;
};

static struct dc_application_settings *create_settings(const struct dc_posix_env *env, struct dc_error *err);
static int destroy_settings(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings **psettings);
static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings);
static void error_reporter(const struct dc_error *err);
static void trace_reporter(const struct dc_posix_env *env, const char *file_name, const char *function_name, size_t line_number);

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

    static const uint16_t default_port = DEFAULT_PORT;

    DC_TRACE(env);
    settings = dc_malloc(env, err, sizeof(struct application_settings));

    if(settings == NULL) {
        return NULL;
    }

    settings->opts.parent.config_path = dc_setting_path_create(env, err);
    settings->message = dc_setting_string_create(env, err);
    settings->port = dc_setting_uint16_create(env, err);

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

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

void createServer(const struct dc_posix_env *env, struct dc_error *err, u_int16_t tcpPort) {
    int listenfd, connfd, udpfd, maxfdp1;
    char buffer[MAXLINE] = {0};
    char packet[MAXLINE] = {0};
    char clientIP[128] = {0};
    char clientID[6] = {0};
    u_int16_t clientPort;
    fd_set rset;
    socklen_t len;
    struct sockaddr_in cliaddr, servaddr;
    pid_t childPID;
    char clientPacketID[7] = {0};
    char *currentTimeString;
    time_t currentTime;
    int udpLogFD;
    int tcpLogFD;
    size_t idCounter = 0;

    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    dc_memset(env, &servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(tcpPort);

    // binding server addr structure to listenfd
    dc_bind(env, err, listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    dc_listen(env, err, listenfd, 10);
    dc_write(env, err, STDOUT_FILENO, "Server Listening for Connections...\n", sizeof ("Server Listening for Connections...\n"));

    /* create UDP socket */
    udpfd = dc_socket(env, err, AF_INET, SOCK_DGRAM, 0);
    // binding server addr structure to udp sockfd
    dc_bind(env, err, udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // clear the descriptor set
    FD_ZERO(&rset);

    // get maxfd
    maxfdp1 = max(listenfd, udpfd) + 1;
    for (;;) {
        tcpLogFD = dc_open(env, err, "../../logs/tcpLog.txt", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        udpLogFD = dc_open(env, err, "../../logs/udpLog.txt", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

        // set listenfd and udpfd in readset
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        // select the ready descriptor
        select(maxfdp1, &rset, NULL, NULL, NULL);

        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(listenfd, &rset)) {
            idCounter++;
            len = sizeof(cliaddr);
            connfd = dc_accept(env, err, listenfd, (struct sockaddr*)&cliaddr, &len);
            if ((childPID = dc_fork(env, err)) == 0) {
                dc_close(env, err, listenfd);
                dc_memset(env,buffer, 0, sizeof(buffer));

                inet_ntop(cliaddr.sin_family, &(cliaddr.sin_addr), clientIP, sizeof(clientIP));
                clientPort = ntohs(cliaddr.sin_port);

                dc_read(env, err, connfd, buffer, sizeof(buffer));

                sprintf(clientID, "%04zu", idCounter);
                dc_write(env, err, connfd, clientID, sizeof(clientID));

                sprintf(packet, "TCP Client %s:%s:%hu:%s", clientID, clientIP, clientPort, buffer);
                dc_write(env, err, tcpLogFD, packet, dc_strlen(env, packet));

                dc_close(env, err, connfd);
                dc_exit(env, 0);
            }
            int status;
            dc_waitpid(env, err, childPID, &status, WUNTRACED);
            dc_close(env, err, connfd);
        }

        // if udp socket is readable receive the message.
        if (FD_ISSET(udpfd, &rset)) {
            len = sizeof(cliaddr);
            dc_memset(env, buffer, 0, sizeof(buffer));
            dc_recvfrom(env, err, udpfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);

            for (size_t i = 0; i < 4; i++) {
                clientID[i] = buffer[i];
            }

            for (size_t i = 5; i < 11; i++) {
                clientPacketID[i - 5] = buffer[i];
            }

            time(&currentTime);
            currentTimeString = dc_strdup(env, err, ctime(&currentTime));
            currentTimeString[dc_strlen(env, currentTimeString) - 1] = '\0';

            inet_ntop(cliaddr.sin_family, &(cliaddr.sin_addr), clientIP, sizeof(clientIP));
            clientPort = ntohs(cliaddr.sin_port);

            sprintf(packet, "%s:%s:%s:%s:%hu\n", clientID, clientPacketID, currentTimeString, clientIP, clientPort);
            dc_write(env, err, udpLogFD, packet, dc_strlen(env, packet));
        }
        dc_close(env, err, udpLogFD);
    }
}

static int run(const struct dc_posix_env *env, struct dc_error *err, struct dc_application_settings *settings) {
    struct application_settings *app_settings;

    DC_TRACE(env);

    app_settings = (struct application_settings *)settings;
    u_int16_t tcpPort;
    tcpPort = dc_setting_uint16_get(env, app_settings->port);

    createServer(env, err, tcpPort);

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
