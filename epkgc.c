#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LEN 512

void print_help() {
    printf("Usage: epkg command [package(s)]\n\n"
    "epkg is a simple wrapper around portage, gentoolkit, and eix that provides an\n"
    "apt-get/yum-alike interface to these commands, to assist people transitioning from\n"
    "Debian/RedHat-based systems to Gentoo.\n\n"
    "Commands [equivalent Gentoo command]:\n"
    "    install       - Install new packages [emerge -av package(s)]\n"
    "    remove        - Remove packages safely [emerge --depclean -av package(s)]\n"
    "    update        - Retrieve updated portage tree [eix-sync]\n"
    "    upgrade       - Update installed packages [emerge -NDuav --with-bdeps=y @system world]\n"
    "    search        - Search for packages [eix package]\n"
    "    autoremove    - Remove packages that are no longer needed [emerge --depclean -a]\n"
    "    autoclean     - Remove sources for packages no longer installed [eclean-dist -df]\n"
    "    clean         - Remove *ALL* package sources [rm -rf $DISTDIR/*]\n"
    "    forceremove   - *Unsafely* remove packages [emerge --unmerge -av package(s)]\n"
    "    listfiles     - List the files belonging to a package [equery files package]\n"
    "    listinstalled - List installed packages [equery list '*']\n"
    "    provides      - List the installed package(s) which own the indicated file [equery belongs file]\n"
    "    verify        - Verify a package's installed files match the checksum and timestamp they had when first installed [equery check -o package]\n"
    "    verifyall     - Same as above, but against all installed packages [equery check -o '*']\n"
    "    sysinfo       - Display information about installed core packages and portage configuration [emerge --info]\n");
}

void execute_command(const char *command) {
    int ret = system(command);
    if (ret == -1) {
        perror("Error executing command");
    }
}

void build_and_execute_command(const char *base_command, int argc, char *argv[]) {
    char command[MAX_COMMAND_LEN] = {0};
    strncpy(command, base_command, MAX_COMMAND_LEN - 1);

    for (int i = 2; i < argc; ++i) {
        strncat(command, " ", MAX_COMMAND_LEN - strlen(command) - 1);
        strncat(command, argv[i], MAX_COMMAND_LEN - strlen(command) - 1);
    }

    execute_command(command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    const char *action = argv[1];

    if (strcmp(action, "search") == 0 || strcmp(action, "-s") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'search' requires a package name.\n");
            return 1;
        }
        build_and_execute_command("eix", argc, argv);
    } else if (strcmp(action, "install") == 0 || strcmp(action, "-i") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'install' requires at least one package.\n");
            return 1;
        }
        build_and_execute_command("emerge -av", argc, argv);
    } else if (strcmp(action, "remove") == 0 || strcmp(action, "uninstall") == 0 || strcmp(action, "-r") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'remove' requires at least one package.\n");
            return 1;
        }
        build_and_execute_command("emerge --depclean -av", argc, argv);
    } else if (strcmp(action, "update") == 0) {
        execute_command("eix-sync");
    } else if (strcmp(action, "upgrade") == 0 || strcmp(action, "dist-upgrade") == 0) {
        execute_command("emerge -uDvaN --with-bdeps=y @system world");
    } else if (strcmp(action, "autoremove") == 0) {
        execute_command("emerge --depclean -a");
    } else if (strcmp(action, "autoclean") == 0) {
        execute_command("eclean-dist -df");
    } else if (strcmp(action, "clean") == 0) {
        execute_command("rm -rf $(portageq distdir)");
    } else if (strcmp(action, "forceremove") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'forceremove' requires at least one package.\n");
            return 1;
        }
        build_and_execute_command("emerge --unmerge -av", argc, argv);
    } else if (strcmp(action, "listfiles") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'listfiles' requires a package name.\n");
            return 1;
        }
        build_and_execute_command("equery files", argc, argv);
    } else if (strcmp(action, "listinstalled") == 0) {
        execute_command("equery list '*'");
    } else if (strcmp(action, "provides") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'provides' requires a file name.\n");
            return 1;
        }
        build_and_execute_command("equery belongs", argc, argv);
    } else if (strcmp(action, "verify") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: 'verify' requires a package name.\n");
            return 1;
        }
        build_and_execute_command("equery check -o", argc, argv);
    } else if (strcmp(action, "verifyall") == 0) {
        execute_command("equery check -o '*'");
    } else if (strcmp(action, "moo") == 0) {
        execute_command("emerge --moo");
    } else if (strcmp(action, "sysinfo") == 0) {
        execute_command("emerge --info");
    } else {
        fprintf(stderr, "Error: Unknown command '%s'.\n\n", action);
        print_help();
        return 1;
    }

    return 0;
}
