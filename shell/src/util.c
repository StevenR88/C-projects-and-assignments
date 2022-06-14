#include "util.h"

size_t count(const char *string, int c) {
    size_t number;
    number = 0;

    for(const char *temp = string; *temp; temp++) {
        if (*temp == c) {
            number++;
        }
    }
    return number;
}

int is_empty(const char *s) {
    while (*s != '\0') {
        if (!isspace((unsigned char)*s)) {
            return 0;
        }
        s++;
    }
    return 1;
}

void validateRegex(const struct dc_posix_env *env, struct dc_error *err, int status, regex_t pattern) {
    if (status != 0) {
        size_t size;
        char *msg;

        size = dc_regerror(env, status, &pattern, NULL, 0);
        msg = dc_malloc(env, err, size + 1);
        dc_regerror(env, status, &pattern, NULL, 0);
        dc_free(env, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
}

void compileRegex(const struct dc_posix_env *env, struct dc_error *err, struct state *state) {
    int status;

    state->in_redirect_regex = dc_malloc(env, err, sizeof(regex_t));
    status = dc_regcomp(env, err, state->in_redirect_regex, "[ \\t\\f\\v]<.*", REG_EXTENDED);
    validateRegex(env, err, status, *state->in_redirect_regex);

    state->out_redirect_regex = dc_malloc(env, err, sizeof(regex_t));
    status = dc_regcomp(env, err, state->out_redirect_regex, "[ \\t\\f\\v][1^2]?>[>]?.*", REG_EXTENDED);
    validateRegex(env, err, status, *state->out_redirect_regex);

    state->err_redirect_regex = dc_malloc(env, err, sizeof(regex_t));
    status = dc_regcomp(env, err, state->err_redirect_regex, "[ \\t\\f\\v]2>[>]?.*", REG_EXTENDED);
    validateRegex(env, err, status, *state->err_redirect_regex);
}

char *get_prompt(const struct dc_posix_env *env, struct dc_error *err) {
    char *prompt;
    char *result;

    prompt = dc_getenv(env, "PS1");
    if (prompt == NULL) {
        result = dc_strdup(env, err, "$ ");
    } else {
        result = dc_strdup(env, err, prompt);
    }

    return result;
}

char *get_path(const struct dc_posix_env *env, struct dc_error *err) {
    char *path;
    char *pathCopy;

    path = dc_getenv(env, "PATH");

    if (path) {
        pathCopy = dc_strdup(env, err, path);
    } else {
        pathCopy = NULL;
    }
    return pathCopy;
}

char **parse_path(const struct dc_posix_env *env, struct dc_error *err, const char *path_str) {
    char *pathPointer;
    char *token;
    size_t counter;
    char **pathArray;
    char *state;
    size_t pathArrayCounter;

    pathPointer = dc_strdup(env, err, path_str);
    state = pathPointer;

    counter = count(path_str, ':') + 1;
    pathArray = dc_malloc(env, err, (counter + 1) * sizeof(char *));
    pathArrayCounter = 0;

    while((token = dc_strtok_r(env, state, ":", &state)) != NULL) {
        pathArray[pathArrayCounter] = dc_strdup(env, err, token);
        pathArrayCounter++;
    }

    pathArray[pathArrayCounter] = NULL;

    dc_free(env, pathPointer, sizeof(pathPointer));

    return pathArray;
}

void do_reset_state(const struct dc_posix_env *env, struct dc_error *err, struct state *state) {
    compileRegex(env, err, state);

    // Freeing Prompt
    if (state->prompt != NULL) {
        dc_free(env, state->prompt, sizeof (&state->prompt));
    }
    char *ps1;
    ps1 = get_prompt(env, err);
    state->prompt = ps1;

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

    err->message = NULL;
    err->file_name = NULL;
    err->function_name = NULL;
    err->line_number = 0;
    err->type = 0;
    err->reporter = NULL;
    err->err_code = 0;
}

void display_state(const struct dc_posix_env *env, struct dc_error *err, const struct state *state, FILE *stream) {
    fprintf(stream, "%s\n", state_to_string(env, err, state));
}

char *state_to_string(const struct dc_posix_env *env,  struct dc_error *err, const struct state *state) {
    char str[1024];
    char *current_line;
    if (state->current_line == NULL) {
        current_line = dc_strdup(env, err, "NULL");
    } else {
        current_line = dc_malloc(env, err, sizeof(state->current_line) + 3);
        sprintf(current_line, "\"%s\"", state->current_line);
    }

    sprintf(str, "current_line = %s, fatal_error = %d", current_line, state->fatal_error);
    char *string = dc_strdup(env, err, str);

    return string;
}

