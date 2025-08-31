#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LEN 4096
#define MAX_ARGS 64

typedef struct {
    const char *cmd;
    const char *exec;
    int requires_arg;
} Command;

static const Command commands[] = {
    {"install", "emerge -av", 1},
    {"remove", "emerge --depclean -av", 1},
    {"update", "eix-sync", 0},
    {"upgrade", "emerge -uDNva --with-bdeps=y @world", 0},
    {"search", "eix", 1},
    {"autoremove", "emerge --depclean -a", 0},
    {"autoclean", "eclean-dist -df", 0},
    {"clean", "eclean-dist -daf", 0},
    {"forceremove", "emerge --unmerge -av", 1},
    {"listfiles", "equery files", 1},
    {"listinstalled", "equery list '*'", 0},
    {"provides", "equery belongs", 1},
    {"verify", "equery check -o", 1},
    {"verifyall", "equery check -o '*'", 0},
    {"sysinfo", "emerge --info", 0},
    {"show", "eix -v", 1},
    {"depends", "equery depends", 1},
    {"uses", "equery uses", 1},
    {"moo", "emerge --moo", 0},
    {NULL, NULL, 0}
};

void print_help() {
    printf("Usage: epkg <command> [package(s)]\n\n"
           "A simple wrapper for Gentoo's package management tools.\n\n"
           "Commands:\n"
           "  install       Install packages\n"
           "  remove        Remove packages safely\n"
           "  update        Update package repository\n"
           "  upgrade       Upgrade all installed packages\n"
           "  search        Search for packages\n"
           "  show          Show detailed package information\n"
           "  autoremove    Remove orphaned packages\n"
           "  autoclean     Clean old source files\n"
           "  clean         Clean all source files\n"
           "  forceremove   Force remove packages (unsafe)\n"
           "  listfiles     List files in package\n"
           "  listinstalled List all installed packages\n"
           "  provides      Find package owning file\n"
           "  depends       Show package dependencies\n"
           "  uses          Show package USE flags\n"
           "  verify        Verify package integrity\n"
           "  verifyall     Verify all packages\n"
           "  sysinfo       Show system information\n");
}

const Command* find_command(const char *action) {
    for (int i = 0; commands[i].cmd; i++) {
        if (strcmp(action, commands[i].cmd) == 0) {
            return &commands[i];
        }
    }
    return NULL;
}

int build_command(char *buffer, size_t buffer_size, const Command *cmd, int argc, char *argv[]) {
    size_t len = strlen(cmd->exec);
    if (len >= buffer_size) return -1;
    
    strcpy(buffer, cmd->exec);
    
    if (cmd->requires_arg) {
        for (int i = 2; i < argc; i++) {
            size_t arg_len = strlen(argv[i]);
            if (len + arg_len + 2 >= buffer_size) return -1;
            
            strcat(buffer, " ");
            strcat(buffer, argv[i]);
            len += arg_len + 1;
        }
    }
    
    return 0;
}

int execute_command(const char *cmd) {
    if (access("/bin/sh", X_OK) != 0) {
        fprintf(stderr, "Error: Shell not accessible\n");
        return -1;
    }
    
    int ret = system(cmd);
    if (ret == -1) {
        perror("Command execution failed");
        return -1;
    }
    
    return WEXITSTATUS(ret);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    if (argc > MAX_ARGS) {
        fprintf(stderr, "Error: Too many arguments\n");
        return 1;
    }

    const Command *cmd_entry = find_command(argv[1]);
    if (!cmd_entry) {
        fprintf(stderr, "Error: Unknown command '%s'\n", argv[1]);
        return 1;
    }

    if (cmd_entry->requires_arg && argc < 3) {
        fprintf(stderr, "Error: Command '%s' requires package name(s)\n", argv[1]);
        return 1;
    }

    char command[MAX_COMMAND_LEN];
    if (build_command(command, sizeof(command), cmd_entry, argc, argv) != 0) {
        fprintf(stderr, "Error: Command too long\n");
        return 1;
    }

    return execute_command(command);
}
