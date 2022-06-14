#include "execute.h"

bool isEmptyPath(const struct dc_posix_env *env, const char *path) {
    size_t counter = 0;
    size_t nullCounter = 0;
    bool isEmpty = false;

    if (path) {
        for (size_t i = 0; path[i]; i++) {
            if (path[i] == '/') {
                counter++;
            } else if (!path[i]) {
                nullCounter++;
            }
        }
    } else {
        isEmpty = true;
    }

    if (counter == 1 && nullCounter >= 1) {
        isEmpty = true;
    }

    return isEmpty;

}

int handle_run_error(const struct dc_posix_env *env, struct dc_error *err) {
    int errorCode;

    switch(err->err_code) {
        case E2BIG: {
            errorCode = 1;
            break;
        }
        case EACCES: {
            errorCode = 2;
            break;
        }
        case EINVAL: {
            errorCode = 3;
            break;
        }
        case ELOOP: {
            errorCode = 4;
            break;
        }
        case ENAMETOOLONG: {
            errorCode = 5;
            break;
        }
        case ENOENT: {
            errorCode = 127;
            break;
        }
        case ENOTDIR: {
            errorCode = 6;
            break;
        }
        case ENOEXEC: {
            errorCode = 7;
            break;
        }
        case ENOMEM: {
            errorCode = 8;
            break;
        }
        case ETXTBSY: {
            errorCode = 9;
            break;
        }
        default: {
            errorCode = 125;
            break;
        }
    }

    return errorCode;
}

void redirect(const struct dc_posix_env *env, struct dc_error *err, struct command *command) {
    if (command->stdin_file != NULL) {
        int stdinFile;
        stdinFile = open(command->stdin_file, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (stdinFile > 0) {
            dc_dup2(env, err, stdinFile, STDIN_FILENO);
            if (dc_error_has_error(err)) {
                dc_close(env, err, stdinFile);
                return;
            }
        }
    }

    if (command->stdout_file != NULL) {
        int stdoutFile;
        if (command->stdout_overwrite) {
            stdoutFile = open(command->stdout_file, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        } else {
            stdoutFile = open(command->stdout_file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        if (stdoutFile > 0) {
            dc_dup2(env, err, stdoutFile, STDOUT_FILENO);
            if (dc_error_has_error(err)) {
                dc_close(env, err, stdoutFile);
                return;
            }
        }
    }

    if (command->stderr_file != NULL) {
        int stderrFile;
        if (command->stderr_overwrite) {
            stderrFile = open(command->stderr_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        } else {
            stderrFile = open(command->stderr_file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        if (stderrFile > 0) {
            dc_dup2(env, err, stderrFile, STDERR_FILENO);
            if (dc_error_has_error(err)) {
                dc_close(env, err, stderrFile);
                return;
            }
        }
    }
}

void runCommand(const struct dc_posix_env *env, struct dc_error *err, struct command *command, char **path) {
    char *cmd;

    if (dc_strstr(env, command->command, "/")) {
        command->argv[0] = command->command;
        dc_execv(env, err, command->argv[0], command->argv);
    } else {
        if (isEmptyPath(env, *path)) {
            err->err_code = ENOENT;
        } else {
            for (size_t i = 0; path[i]; i++) {
                cmd = dc_malloc(env, err, dc_strlen(env, path[i]) + dc_strlen(env, command->command) + 1);
                sprintf(cmd, "%s/%s", path[i], command->command);
                command->argv[0] = cmd;
                dc_execv(env, err, command->argv[0], command->argv);
                if (err->err_code != ENOENT) {
                    break;
                }
            }
        }
    }
}

void execute(const struct dc_posix_env *env, struct dc_error *err, struct command *command, char **path) {
    pid_t pid;
    pid_t status;
    int statusLoc;

    pid = dc_fork(env, err);

    if (pid == 0) {
        // This is a child process
        redirect(env, err, command);

        if (dc_error_has_error(err)) {
            exit(126);
        }

        runCommand(env, err, command, path);

        status = handle_run_error(env, err);
        exit(status);
    } else {
        waitpid(pid, &statusLoc, WUNTRACED);
        command->exit_code = WEXITSTATUS(statusLoc);
    }
}

