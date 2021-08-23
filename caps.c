#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <X11/XKBlib.h>

int get_dwmblocks_pid() {
    char line[1024];
    FILE *f = popen("pidof dwmblocks", "r");

    fgets(line, 1024, f);
    pclose(f);

    char *end;
    long pid = strtol(line, &end, 10);
    printf("%d\n", end == line);

    if(end == line) {
        return -1;
    }

    return pid;
}

int main () {
    int event_code, error_return, reason_return;
    Display* display;

    if(!XInitThreads()) {
        printf("failed to init x threads");
        goto fail;
    }
    display = XkbOpenDisplay(NULL, &event_code, &error_return, NULL, NULL, &reason_return);

    if(XkbSelectEvents(
        display,
        XkbUseCoreKbd,
        XkbIndicatorStateNotifyMask | XkbIndicatorMapNotifyMask | XkbNewKeyboardNotifyMask | XkbMapNotifyMask,
        XkbIndicatorStateNotifyMask | XkbIndicatorMapNotifyMask | XkbNewKeyboardNotifyMask | XkbMapNotifyMask
        /* XkbIndicatorStateNotifyMask | XkbIndicatorMapNotifyMask */
    ) == False) {
        printf("Failed to select shit\n");
        goto fail;
    };
        printf("2\n");

    if(XkbSelectEventDetails(
        display,
        XkbUseCoreKbd,
        /*event_type=*/XkbStateNotify,
        /*bits_to_change=*/XkbAllStateComponentsMask,
        /*values_for_bits=*/XkbGroupStateMask
    ) == False) {
        printf("Failed to select event details\n");
        goto fail;
    }
        printf("starting loop\n");

    while (1) {
        XEvent event = {0};
        XNextEvent(display, &event);

        XkbAnyEvent ev1;
        memcpy(&ev1, &event, sizeof(ev1));

        if(ev1.xkb_type == XkbIndicatorStateNotify) {
            int dwmblocks_pid = get_dwmblocks_pid();

            if (dwmblocks_pid > 1) {
                kill(dwmblocks_pid, SIGRTMIN+5);
            } else {
                printf("no dwmblocks %d\n", dwmblocks_pid);
            }
        }
    }

fail:
    if(display) {
        XCloseDisplay(display);
    }

    return 0;
}
