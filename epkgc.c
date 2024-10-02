#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help() {
    printf("Usage: epkg command [package(s)]\n\n"
           "epkg is a simple wrapper around portage, gentoolkit, and eix that provides an\n"
           "apt-get/yum-alike interface to these commands, to assist people transitioning from\n"
           "Debian/RedHat-based systems to Gentoo.\n\n"
           "Commands [equivalent Gentoo command]:\n"
           "    install - Install new packages [emerge -av package(s)]\n"
           "    remove - Remove packages safely [emerge --depclean -av package(s)]\n"
           "    update - Retrieve updated portage tree [eix-sync]\n"
           "    upgrade - Update installed packages [emerge -NDuav --with-bdeps=y @system world]\n"
           "    search - Search for packages [eix package]\n"
           "    autoremove - Remove packages that are no longer needed [emerge --depclean -a]\n"
           "    autoclean - Remove sources for packages no longer installed [eclean-dist -df]\n"
           "    clean - Remove *ALL* package sources [rm -rf $DISTDIR/*]\n"
           "    forceremove - *Unsafely* remove packages [emerge --unmerge -av package(s)]\n"
           "    listfiles - List the files belonging to a package [equery files package]\n"
           "    listinstalled - List installed packages [equery list '*']\n"
           "    provides - List the installed package(s) which own the indicated file [equery belongs file]\n"
           "    verify - Verify a package's installed files match the checksum and timestamp they had when first installed [equery check -o package]\n"
           "    verifyall - Same as above, but against all installed packages [equery check -o '*']\n"
           "    sysinfo - Display information about installed core packages and portage configuration [emerge --info]\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    char *action = argv[1];
    char command[512] = {0};

    if (strcmp(action, "search") == 0 || strcmp(action, "-s") == 0) {
        snprintf(command, sizeof(command), "eix %s", argv[2]);
    } else if (strcmp(action, "install") == 0 || strcmp(action, "-i") == 0) {
        snprintf(command, sizeof(command), "emerge -av %s", argv[2]);
    } else if (strcmp(action, "remove") == 0 || strcmp(action, "uninstall") == 0 || strcmp(action, "-r") == 0) {
        snprintf(command, sizeof(command), "emerge --depclean -av %s", argv[2]);
    } else if (strcmp(action, "update") == 0) {
        snprintf(command, sizeof(command), "eix-sync");
    } else if (strcmp(action, "upgrade") == 0 || strcmp(action, "dist-upgrade") == 0) {
        snprintf(command, sizeof(command), "emerge -uDvaN --with-bdeps=y @system world");
    } else if (strcmp(action, "autoremove") == 0) {
        snprintf(command, sizeof(command), "emerge --depclean -a");
    } else if (strcmp(action, "autoclean") == 0) {
        snprintf(command, sizeof(command), "eclean-dist -df");
    } else if (strcmp(action, "clean") == 0) {
        snprintf(command, sizeof(command), "rm -rf $(portageq distdir)");
    } else if (strcmp(action, "forceremove") == 0) {
        snprintf(command, sizeof(command), "emerge --unmerge -av %s", argv[2]);
    } else if (strcmp(action, "listfiles") == 0) {
        snprintf(command, sizeof(command), "equery files %s", argv[2]);
    } else if (strcmp(action, "listinstalled") == 0) {
        snprintf(command, sizeof(command), "equery list '*'");
    } else if (strcmp(action, "provides") == 0) {
        snprintf(command, sizeof(command), "equery belongs %s", argv[2]);
    } else if (strcmp(action, "verify") == 0) {
        snprintf(command, sizeof(command), "equery check -o %s", argv[2]);
    } else if (strcmp(action, "verifyall") == 0) {
        snprintf(command, sizeof(command), "equery check -o '*'");
    } else if (strcmp(action, "moo") == 0) {
        snprintf(command, sizeof(command), "emerge --moo");
    } else if (strcmp(action, "sysinfo") == 0) {
        snprintf(command, sizeof(command), "emerge --info");
    } else {
        print_help();
        return 1;
    }

    int ret = system(command);
    if (ret == -1) {
        perror("Error executing command");
        return 1;
    }

    return 0;
}
