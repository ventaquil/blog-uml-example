#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <unistd.h>

static int initialize(void) {
    // mount necessary directories
    if (mount("none", "/proc", "proc", MS_MGC_VAL, "") != 0) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    if (mount("none", "/sys", "sysfs", MS_MGC_VAL, "") != 0) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    if (mount("none", "/dev", "devtmpfs", MS_MGC_VAL, "") != 0) {
        fprintf(stderr, "error %d: %s\n", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    printf("init\n");
    for (int i = 1; i < argc; i++) {
        printf("\t%s\n", argv[i]);
    }

    if (initialize() != EXIT_SUCCESS) {
        sync();
        reboot(RB_POWER_OFF);

        return EXIT_FAILURE;
    }

    sync();
    reboot(RB_POWER_OFF);

    return EXIT_SUCCESS;
}
