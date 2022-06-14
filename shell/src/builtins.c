#include "builtins.h"

void builtin_cd(const struct dc_posix_env *env, struct dc_error *err, struct command *command, FILE *errstream) {
    char *path;
    char *string;

    if (!command->argv[1]) {
        path = dc_strdup(env, err, "~/");
    } else {
        path = dc_strdup(env, err, command->argv[1]);
    }

    if (dc_strstr(env, path, "~")) {
        dc_expand_path(env, err, &path, "~");
    }

    dc_chdir(env, err, path);

    if(dc_error_has_error(err)) {
        switch (err->err_code) {
            case EACCES: case ELOOP: case ENAMETOOLONG: {
                string = dc_malloc(env, err, dc_strlen(env, command->command) + dc_strlen(env, err->message) + 5);
                sprintf(string, "%s: %s: %s", command->command, path, err->message);
                fprintf(errstream, "%s\n", string);
                break;
            }
            case ENOENT: case ENOTDIR: {
                string = dc_malloc(env, err, dc_strlen(env, path) + dc_strlen(env, err->message) + 5);
                sprintf(string, "%s: %s: %s", command->command, err->message, path);
                fprintf(errstream, "%s\n", string);
                break;
            }
            default: {
                break;
            }
        }
        command->exit_code = 1;
    } else {
        command->exit_code = 0;
    }
    dc_fflush(env, err, errstream);
}
