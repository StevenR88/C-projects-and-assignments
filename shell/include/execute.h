#ifndef DC_SHELL_EXECUTE_H
#define DC_SHELL_EXECUTE_H

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
#include <fcntl.h>
#include <dc_posix/dc_posix_env.h>
#include <dc_posix/dc_stdio.h>
#include <dc_posix/dc_stdlib.h>
#include <dc_posix/dc_string.h>
#include <dc_posix/dc_unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * Checks if a path is empty for the purposes of running commands.
 * @param env the posix environment.
 * @param err the err object
 * @return boolean for result of comparison
 */
bool isEmptyPath(const struct dc_posix_env *env, const char *path);

/**
 * Handles runCommand errors.
 * @param env the posix environment.
 * @param err the err object
 * @return integer for error code
 */
int handle_run_error(const struct dc_posix_env *env, struct dc_error *err);

/**
 * Handles redirection of streams.
 * @param env the posix environment.
 * @param err the err object
 * @param command struct
 */
void redirect(const struct dc_posix_env *env, struct dc_error *err, struct command *command);

/**
 * Handles the execution of commands by child processes.
 * @param env the posix environment.
 * @param err the err object
 * @param command struct
 * @param path the path to execute commands
 */
void runCommand(const struct dc_posix_env *env, struct dc_error *err, struct command *command, char **path);

/**
 * Create a child process, exec the command with any redirection, set the exit code.
 * If there is an err executing the command print an err message.
 * If the command cannot be found set the command->exit_code to 127.
 *
 * @param env the posix environment.
 * @param err the err object
 * @param command the command to execute
 * @param path the directories to search for the command
 */
void execute(const struct dc_posix_env *env, struct dc_error *err, struct command *command, char **path);

#endif // DC_SHELL_EXECUTE_H
