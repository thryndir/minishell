#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[1024];
    ssize_t bytes;

    dprintf(2, "Test program: Starting (PID: %d)\n", getpid());

    // Si on est le second programme (celui de droite, premier exécuté)
    if (argc > 1 && strcmp(argv[1], "read") == 0) {
        dprintf(2, "Test program: Reader mode\n");
        while ((bytes = read(0, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';
            dprintf(2, "Test program: Read %zd bytes: %s", bytes, buffer);
        }
    }
    // Si on est le premier programme (celui de gauche, second exécuté)
    else {
        dprintf(2, "Test program: Writer mode\n");
        dprintf(1, "Hello from test program!\n");
    }

    dprintf(2, "Test program: Exiting\n");
    return 0;
}