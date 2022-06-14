#include "command.h"

void trim(const struct dc_posix_env *env, char* string) {
    size_t i = 0;

    if (string != NULL) {
        while (isspace(string[i]) || string[i] == '2' || string[i] == '>' || string[i] == '<') {
            i++;
        }
        if (i > 0) {
            size_t length;
            length = dc_strlen(env, string);
            dc_memmove(env, string, &string[i], length + 1 - i);
        }
    }
}

void match(const struct dc_posix_env *env, struct dc_error *err, regex_t *redirect, struct command *command, char **output, bool *overwrite) {
    int matched;
    regmatch_t match;
    wordexp_t expand;

    matched = dc_regexec(env, redirect, command->line, 1, &match, 0);
    if (matched == 0) {
        char *str;
        char *finalString;
        regoff_t length;

        if (dc_strstr(env, command->line, ">>")) {
            if (overwrite) {
                *overwrite = true;
            }
        }

        length = match.rm_eo - match.rm_so;
        str = dc_malloc(env, err, (size_t) length + 1);
        dc_strncpy(env, str, &command->line[match.rm_so], (size_t) length);
        command->line[match.rm_so] = '\0';
        str[length] = '\0';

        trim(env, str);
        if (dc_strstr(env, str, "~")) {
            dc_wordexp(env, err, str, &expand, 0);
            finalString = dc_strdup(env, err, expand.we_wordv[0]);
            *output = finalString;
        } else {
            *output = str;
        }
    }
}

void parse_command(const struct dc_posix_env *env, struct dc_error *err, struct state *state, struct command *command) {
    wordexp_t expanded;
    char *commandLine;

    commandLine = dc_strdup(env, err, command->line);

    match(env, err, state->err_redirect_regex, command, &command->stderr_file, &command->stderr_overwrite);
    match(env, err, state->out_redirect_regex, command, &command->stdout_file, &command->stdout_overwrite);
    match(env, err, state->in_redirect_regex, command, &command->stdin_file, NULL);

    dc_wordexp(env, err, command->line, &expanded, 0);

    if (dc_error_has_no_error(err)) {
        command->argc = expanded.we_wordc;
        command->argv = dc_malloc(env, err, (expanded.we_wordc + 2));

        command->argv[0] = NULL;

        if (command->argc > 1) {
            for (size_t i = 1; i < expanded.we_wordc; i++) {
                command->argv[i] = dc_strdup(env, err, expanded.we_wordv[i]);
            }
        }
        command->argv[expanded.we_wordc] = NULL;
        command->line = commandLine;
        command->command = dc_strdup(env, err, expanded.we_wordv[0]);
    } else {
        command->exit_code = 204;
    }
}

void destroy_command(const struct dc_posix_env *env, struct command *command) {
    // Freeing command->line
    if (command->line != NULL) {
        dc_free(env, command->line, sizeof(command->line));
        command->line = NULL;
    }

    command->argc = 0;

//     Freeing command->argv
    if (command->argv != NULL) {
        for(size_t i = 0; command->argv[i]; i++) {
            dc_free(env, command->argv[i], sizeof(&command->argv[i]));
        }
        dc_free(env, command->argv, sizeof(&command->argv));
        command->argv = NULL;
    }

//     Freeing command->command
    if (command->command != NULL) {
        dc_free(env, command->command, sizeof(command->command));
        command->command = NULL;
    }

    command->stderr_overwrite = false;
    command->stdout_overwrite = false;
    command->stdout_file = NULL;
    command->stdin_file = NULL;
    command->stderr_file = NULL;
}

