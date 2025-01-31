#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <CLI/cli.h>
#include <CLI/impl.h>

#define pgm_read_ptr(p) (*(p))

typedef struct {
   int ord;
   const char* name;
   const char* args;
   const char* desc;
   const char* next;
} cli_command_t;

const char cli_commands[] =
//  Name         Args                  Description
   "about\0"     "\0"                  "CyOS copyrights and licenses\0"
   "ascii\0"     "<char>\0"            "send ascii character\0"
   "cls\0"       "\0"                  "clear screen\0"
   "cursor\0"    "<on | off>\0"        "toggle cursor on or off\0"
   "esc\0"       "<codes>+\0"          "send escape sequences\0"
   "help\0"      "\0"                  "list available commands\0"
   "lprint\0"    "<string>\0"          "send string to standard parallel port\0"
   "screen\0"    "[width] [height]\0"  "set screen size\0"
   "time\0"      "\0"                  "print the current date and time\0";

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

void* const cli_functions[] = {
    &cli_about,
    &cli_ascii,
    &cli_cls,
    &cli_cursor_toggle,
    &cli_esc,
    &cli_help,
    &cli_lprint,
    &cli_screen,
    &cli_time
};

void cli_dispatch(char *buf) {
    char* argv[MAXARGS];
    int argc;
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = tolower(buf[i]);
    }

    if ((argv[0] = strtok(buf, WHITESPACE)) == NULL) {
        return;  // empty command
    }

    cli_command_t cmd;
    cmd = cli_find_command(cli_commands, argv[0]);
    if (cmd.name != NULL) {
        void (*cmd_func)(int, char*[]);
        cmd_func = pgm_read_ptr(&cli_functions[cmd.ord]);
        for (argc = 1; argc < MAXARGS; argc++) {
            if ((argv[argc] = strtok(NULL, WHITESPACE)) == NULL) {
                break;
            }
        }

        cmd_func(argc, argv);
    }  // TODO need an 'else if' scenario here eventually to fall back to executing .COM and .PRG files.
}

void cli_loop(void) {

}

void cli_init(void) {
    printf("\n\ntype help to list commands; about for credits\n");
    // TODO Call autoexec here?
    cli_loop();
}
