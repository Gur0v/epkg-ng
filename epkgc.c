#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) { return argc < 2 ? (printf("Usage: epkg command [package(s)]\n"), 1) : (!strcmp(argv[1], "search") || !strcmp(argv[1], "-s") ? system((char[]){"eix ", argv[2]}) : !strcmp(argv[1], "install") || !strcmp(argv[1], "-i") ? system((char[]){"emerge -av ", argv[2]}) : !strcmp(argv[1], "remove") || !strcmp(argv[1], "-r") ? system((char[]){"emerge --depclean -av ", argv[2]}) : !strcmp(argv[1], "update") ? system("eix-sync") : !strcmp(argv[1], "upgrade") ? system("emerge -uDvaN --with-bdeps=y @system world") : !strcmp(argv[1], "sysinfo") ? system("emerge --info") : (printf("Usage: epkg command [package(s)]\n"), 1)); }
