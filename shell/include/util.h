#ifndef DC_SHELL_UTIL_H
#define DC_SHELL_UTIL_H

/*
 * This file is part of dc_shell.
 *
 *  dc_shell is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Foobar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dc_shell.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "command.h"
#include "shell.h"
#include "state.h"
#include <ctype.h>
#include <dc_posix/dc_posix_env.h>
#include <dc_posix/dc_regex.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_unistd.h>
#include <dc_util/strings.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Counts amount of a certain character in a string.
 * @param string to check
 * @param c character to check
 * @return number of matches
 */
size_t count(const char *string, int c);

/**
 * Checks if a string is empty.
 * @param s the string to check
 * @return result of check
 */
int is_empty(const char *s);

/**
 * Validates regex values.
 * @param env the posix environment.
 * @param err the error object
 * @param status error code status
 * @param pattern regex pattern to validate
 */
void validateRegex(const struct dc_posix_env *env, struct dc_error *err, int status, regex_t pattern);

/**
 * Compiles regex values and stores to specified location.
 * @param env the posix environment.
 * @param err the error object
 * @param state struct
 */
void compileRegex(const struct dc_posix_env *env, struct dc_error *err, struct state *state);

/**
 * Get the prompt to use.

 * @param env the posix environment.
 * @param err the error object
 * @return value of the PS1 environ var or "$ " if PS1 not set.
 */
char *get_prompt(const struct dc_posix_env *env, struct dc_error *err);

/**
 * Get the PATH environ var.
 *
 * @param env the posix environment.
 * @param err the error object
 * @return the PATH environ var
 */
char *get_path(const struct dc_posix_env *env, struct dc_error *err);

/**
 * Separate a path (eg. PATH environ var) into separate directories.
 * Directories are separated with a ':' character.
 * Any directories with ~ are converted to the users home directory.
 *
 * @param env the posix environment.
 * @param err the error object.
 * @param path_str the string to separate.
 * @return The directories that make up the path.
 */
char **parse_path(const struct dc_posix_env *env, struct dc_error *err,
                  const char *path_str);

/**
 * Reset the state for the next read, freeing any dynamically allocated memory.
 *
 * @param env the posix environment.
 * @param err the error object
 */
void do_reset_state(const struct dc_posix_env *env, struct dc_error *err, struct state *state);

/**
 * Display the state values to the given stream.
 *
 * @param env the posix environment.
 * @param state the state to display.
 * @param stream the stream to display the state on,
 */
void display_state(const struct dc_posix_env *env, struct dc_error *err, const struct state *state, FILE *stream);

/**
 * Display the state values to the given stream.
 *
 * @param env the posix environment.
 * @param state the state to display.
 * @param stream the stream to display the state on,
 */
char *state_to_string(const struct dc_posix_env *env,  struct dc_error *err, const struct state *state);

#endif // DC_SHELL_UTIL_H
