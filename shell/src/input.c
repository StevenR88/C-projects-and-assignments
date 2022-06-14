#include "input.h"

char *read_command_line(const struct dc_posix_env *env, struct dc_error *err, FILE *stream, size_t *line_size) {
    char *commandLine;

    commandLine = dc_malloc(env, err, sizeof(char *));
    dc_getline(env, err, &commandLine, line_size, stream);

    dc_str_trim(env, commandLine);

    *line_size = dc_strlen(env, commandLine);

    return commandLine;
}

