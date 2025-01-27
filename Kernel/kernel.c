#include <stdio.h>
#include <Kernel/kernel.h>
#include <Kernel/Devices/spp.h>
#include <CLI/cli.h>

const char cyos_banner[] =
   "\n____       ___  ____"
   "\n/ ___|   _ / _ \\/ ___|"
   "\n| |  | | | | | | \\___ \\"
   "\n| |__| |_| | |_| |___) |"
   "\n\\____\\__, |\\___/|____/"
   "\n    |___/\n"
   "by Cyrus Brunner\n";

const char cyos_copyright[] =
        "\nCyOS (https://github.com/cyrusbuilt/CyOS)"
        "\nCopyright (c) 2025 - Cyrus Brunner"
        "\nMIT License"
        "\n"
        "\nFull license at https://github.com/cyrusbuilt/CyOS/blob/master/LICENSE";

/**
 * Kernel bootstrap routine.
 */
void kernel_main(void) {
    printf("\n\n");

    spp_init(true);

    // TODO Just something to verify we can boot and run. Replace with cli_init()
    PANIC("%s: hello world!", VERSION);
}

/**
 * Kernel entry point.
 */
int main(void) {
    printf(cyos_banner);

    // Should never return.
    kernel_main();
    return 0;
}
