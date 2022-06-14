#ifndef DC_SHELL_COMMAND_H
#define DC_SHELL_COMMAND_H

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

#include "state.h"
#include <ctype.h>
#include <dc_posix/dc_regex.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_wordexp.h>
#include <dc_util/path.h>
#include <dc_util/strings.h>
#include <wordexp.h>

#include <dc_posix/dc_posix_env.h>

/*! \struct command
    \brief The commands to enter, currently there is only one.

    The state passed around to the FSM functions.
*/
struct command
{
  char *line;               /**< the current command line */
  char *command;            /**< the program/builtin to runCommand */
  size_t argc;              /**< the number of arguments to the command */
  char **argv;              /**< the arguments to the command, arg[0] must be NULL */
  char *stdin_file;         /**< the file to redirect stdin from */
  char *stdout_file;        /**< the file to redirect stdout to */
  bool stdout_overwrite;    /**< append or overwrite the stdout file (true = overwrite) */
  char *stderr_file;        /**< the file to redirect strderr to */
  bool stderr_overwrite;    /**< append or overwrite the strerr file (true = overwrite) */
  int exit_code;            /**< the exit code from the program/builtin */
};

/**
 * Trims unwanted characters from the beginning of a string.
 * @param env the posix environment.
 * @param err the error object.
 * @param string the string representing a command
 */
void trim(const struct dc_posix_env *env, char* string);

/**
 * Performs regex matching and stores results to state.
 * @param env the posix environment.
 * @param err the error object.
 * @param redirect pointer to state regex values
 * @param command command struct
 * @param output pointer to command files
 * @param overwrite boolean result representing command stderr or stdout overwrites
 */
void match(const struct dc_posix_env *env, struct dc_error *err, regex_t *redirect, struct command *command, char **output, bool *overwrite);

/**
 * Parse the command. Take the command->line and use it to fill in all of the fields.
 *
 * @param env the posix environment.
 * @param err the error object.
 * @param state the current state, to set the fatal_error and access the command line and regex for redirection.
 * @param command the command to parse.
 */
void parse_command(const struct dc_posix_env *env, struct dc_error *err,
                   struct state *state, struct command *command);

/**
 *
 * @param env
 * @param command
 */
void destroy_command(const struct dc_posix_env *env, struct command *command);

#endif // DC_SHELL_COMMAND_H
