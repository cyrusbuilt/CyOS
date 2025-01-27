#include <stdio.h>
#include <string.h>
#include <CLI/cli.h>
#include <CLI/impl.h>

typedef struct {
   int ord;
   const char* name;
   const char* args;
   const char* desc;
   const char* next;
} cli_command_t;

const char cli_commands[] =
//  Name        Args         Description
   "about\0"    "\0"         "CyOS copyrights and licenses\0"
   "help\0"     "\0"         "list available commands\0";

void cli_about(int argc, char *argv[]) {
    printf("%S\n%S\n", cyos_banner, cyos_copyright);
}

cli_command_t cli_parse_command(const char* start) {
    cli_command_t cmd;
    cmd.ord = -1;
    cmd.name = NULL;
    cmd.args = NULL;
    cmd.desc = NULL;
    cmd.next = NULL;
    if (strlen(start) != 0) {
        cmd.name = start;
        cmd.args = cmd.name + strlen(cmd.name) + 1;
        cmd.desc = cmd.args + strlen(cmd.args) + 1;
        cmd.next = cmd.desc + strlen(cmd.desc) + 1;
        if (strlen(cmd.next) != 0) {
            cmd.next = NULL;
        }
    }

    return cmd;
}

cli_command_t cli_find_command(const char* commands, const char* name) {
    cli_command_t cmd;
    cmd.next = commands;
    for (int i = 0; cmd.next != NULL; i++) {
        cmd = cli_parse_command(cmd.next);
        if (strcmp(name, cmd.name) == 0) {
            cmd.ord = i;
            return cmd;
        }
    }

    cmd.ord = -1;
    cmd.name = NULL;
    cmd.args = NULL;
    cmd.desc = NULL;
    cmd.next = NULL;
    return cmd;
}

void cli_help(int argc, char *argv[]) {
    cli_command_t cmd;
    cmd.next = cli_commands;
    while (cmd.next != NULL) {
        cmd = cli_parse_command(cmd.next);
        if (strlen(cmd.desc) != 0) {
            printf("%S %S\n\t%S\n", cmd.name, cmd.args, cmd.desc);
        }
    }
}

void cli_dispatch(char *buf) {

}

void cli_loop(void) {

}

void cli_init(void) {
    printf("\n\ntype help to list commands; about for credits\n");
    // TODO Call autoexec here?
    cli_loop();
}