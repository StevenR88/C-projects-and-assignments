#include "shell_impl.h"

int init_state(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    // Setting state->max_line_length to _SC_ARG_MAX.
    state->max_line_length = (size_t) dc_sysconf(env, err, _SC_ARG_MAX);

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    // Setting Regex values.
    compileRegex(env, err, state);

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    // Getting PATH environment variables and splitting into array. Stored to state->path.
    char *path;
    char **pathArray;

    path = get_path(env, err);
    pathArray = parse_path(env, err, path);
    dc_free(env, path, sizeof(path));
    state->path = pathArray;

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    // Getting the PS1 environment variables and setting to state->prompt.
    char *ps1;
    ps1 = get_prompt(env, err);
    state->prompt = ps1;

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    // Setting all uninitialized variables to 0.
    state->current_line = 0;
    state->current_line_length = 0;
    state->command = 0;
    state->fatal_error = false;

    next_state = READ_COMMANDS;

    return next_state;
}

int destroy_state(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    // Freeing Regex
    if (state->in_redirect_regex != NULL) {
        dc_regfree(env, state->in_redirect_regex);
    }
    if (state->out_redirect_regex != NULL) {
        dc_regfree(env, state->out_redirect_regex);
    }
    if (state->err_redirect_regex != NULL) {
        dc_regfree(env, state->err_redirect_regex);
    }

    state->in_redirect_regex = NULL;
    state->out_redirect_regex = NULL;
    state->err_redirect_regex = NULL;

    // Freeing Path Array
    if (state->path != NULL) {
        for(size_t i = 0; state->path[i]; i++) {
            dc_free(env, state->path[i], sizeof(&state->path[i]));
        }
        dc_free(env, state->path, sizeof(&state->path));

        state->path = NULL;
    }

    // Freeing Prompt
    if (state->prompt != NULL) {
        dc_free(env, state->prompt, sizeof (&state->prompt));
        state->prompt = NULL;
    }

    state->max_line_length = 0;

    // Freeing current line
    if (state->current_line != NULL) {
        dc_free(env, state->current_line, sizeof(state->current_line));
        state->current_line = NULL;
    }

    state->current_line_length = 0;

    // Freeing state->command struct
    if (state->command != NULL) {
        destroy_command(env, state->command);
        state->command = NULL;
    }

    state->fatal_error = false;

    next_state = DC_FSM_EXIT;

    return next_state;
}

int reset_state(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    do_reset_state(env, err, state);

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    next_state = READ_COMMANDS;
    return next_state;
}

int read_commands(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = arg;

    char *cwd;
    char *str;
    char *currentLine;
    size_t currentLineLength;
    size_t *currentLineLengthPointer = &currentLineLength;

    cwd = dc_get_working_dir(env, err);
    str = dc_malloc(env, err, 1 + dc_strlen(env, cwd) + 1 + 2 + dc_strlen(env, state->prompt) + 1);

    sprintf(str, "[%s] %s", cwd, state->prompt);
    fprintf(state->stdout, "%s", str);
    dc_fflush(env, err, state->stdout);

    dc_free(env, cwd, sizeof(cwd));
    dc_free(env, str, sizeof(str));

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    // Don't forget that read_command_line returns dynamically allocated string
    currentLine = read_command_line(env, err, state->stdin, currentLineLengthPointer);
    state->current_line = currentLine;

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    if (is_empty(state->current_line)) {
        next_state = RESET_STATE;
        return next_state;
    }

    state->current_line_length = currentLineLength;

    next_state = SEPARATE_COMMANDS;
    return next_state;
}

int separate_commands(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    state->command = dc_calloc(env, err, 1, sizeof(struct command));
    state->command->argv = NULL;

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    state->command->line = dc_strdup(env, err, state->current_line);

    next_state = PARSE_COMMANDS;
    return next_state;

}

int parse_commands(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    parse_command(env, err, state, state->command);

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    next_state = EXECUTE_COMMANDS;
    return next_state;
}

int execute_commands(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    if (state->command->command) {
        if(dc_strcmp(env, state->command->command, "cd") == 0) {
            builtin_cd(env, err, state->command, state->stderr);
        } else if(dc_strcmp(env, state->command->command, "exit") == 0) {
            next_state = EXIT;
            return next_state;
        } else {
            execute(env, err, state->command, state->path);
            if(dc_error_has_error(err)) {
                state->fatal_error = true;
                next_state = ERROR;
                return next_state;
            }
        }
    }

    if (state->command->exit_code == 0 || state->command->exit_code == 1) {
        fprintf(state->stdout, "%d\n", state->command->exit_code);
    } else {
        fprintf(state->stdout, "command: %s: not found\n", state->command->command);
        fprintf(state->stdout, "%d\n", state->command->exit_code);
    }

    if (state->fatal_error) {
        next_state = ERROR;
        return next_state;
    }

    next_state = RESET_STATE;
    return next_state;
}

int do_exit(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    do_reset_state(env, err, state);

    if(dc_error_has_error(err)) {
        state->fatal_error = true;
        next_state = ERROR;
        return next_state;
    }

    next_state = DESTROY_STATE;
    return next_state;
}

int handle_error(const struct dc_posix_env *env, struct dc_error *err, void *arg) {
    int next_state;
    struct state *state;
    state = (struct state *)arg;

    if (state->command->exit_code == 204) {
        fprintf(state->stdout, "unable to parse \"%s\"\n", state->command->line);
    }

    if (state->current_line == NULL) {
        fprintf(state->stderr, "internal error (%d) %s\n", err->err_code, err->message);
    } else {
        fprintf(state->stderr, "internal error (%d) %s: \"%s\"\n", err->err_code, err->message, state->current_line);
    }

    if (state->fatal_error) {
        next_state = DESTROY_STATE;
        return next_state;
    }

    next_state = RESET_STATE;
    return next_state;
}


