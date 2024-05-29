// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <linux/uinput.h>
// #include <string.h>
// #include <termios.h>

// // Function to create the virtual mouse device
// int createVirtualMouse() {
//     int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
//     if (fd < 0) {
//         perror("Failed to open /dev/uinput");
//         return -1;
//     }

//     // Enable mouse events
//     ioctl(fd, UI_SET_EVBIT, EV_KEY);
//     ioctl(fd, UI_SET_EVBIT, EV_REL);
//     ioctl(fd, UI_SET_RELBIT, REL_X);
//     ioctl(fd, UI_SET_RELBIT, REL_Y);
//     ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
//     ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);
//     ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);

//     struct uinput_user_dev uidev;
//     memset(&uidev, 0, sizeof(uidev));
//     snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Virtual Mouse");
//     uidev.id.bustype = BUS_USB;
//     uidev.id.vendor = 0x1;
//     uidev.id.product = 0x1;
//     uidev.id.version = 1;
//     write(fd, &uidev, sizeof(uidev));

//     if (ioctl(fd, UI_DEV_CREATE) < 0) {
//         perror("ioctl UI_DEV_CREATE error");
//         close(fd);
//         return -1;
//     }

//     return fd;
// }

// // Function to destroy the virtual mouse device
// void destroyVirtualMouse(int fd) {
//     ioctl(fd, UI_DEV_DESTROY);
//     close(fd);
// }

// // Function to send mouse events
// void sendMouseEvent(int fd, int relX, int relY, int btn) {
//     struct input_event event;
//     memset(&event, 0, sizeof(event));

//     event.type = EV_REL;
//     event.code = REL_X;
//     event.value = relX;
//     write(fd, &event, sizeof(event));

//     event.type = EV_REL;
//     event.code = REL_Y;
//     event.value = relY;
//     write(fd, &event, sizeof(event));

//     if (btn == BTN_LEFT || btn == BTN_RIGHT) {
//         event.type = EV_KEY;
//         event.code = btn;
//         event.value = 1;
//         write(fd, &event, sizeof(event));

//         event.type = EV_SYN;
//         event.code = SYN_REPORT;
//         event.value = 0;
//         write(fd, &event, sizeof(event));

//         event.type = EV_KEY;
//         event.code = btn;
//         event.value = 0;
//         write(fd, &event, sizeof(event));

//         event.type = EV_SYN;
//         event.code = SYN_REPORT;
//         event.value = 0;
//         write(fd, &event, sizeof(event));
//     } else if (btn == 0) {
//         event.type = EV_SYN;
//         event.code = SYN_REPORT;
//         event.value = 0;
//         write(fd, &event, sizeof(event));
//     }
// }

// // Function to set terminal to non-canonical mode
// void setNonCanonicalMode() {
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// int main() {
//     // Create the virtual mouse device
//     int fd = createVirtualMouse();
//     if (fd < 0)
//         return 1;

//     // Set terminal to non-canonical mode
//     setNonCanonicalMode();

//     // Variables for storing input
//     int key;
//     int relX = 0, relY = 0;

//     // Main loop to read input and control the mouse
//     printf("Press 'q' to quit.\n");
//     while ((key = getchar()) != 'q') {
//         switch (key) {
//             case 'w':
//                 relY -= 10; // Move up
//                 break;
//             case 's':
//                 relY += 10; // Move down
//                 break;
//             case 'a':
//                 relX -= 10; // Move left
//                 break;
//             case 'd':
//                 relX += 10; // Move right
//                 break;
//             case ' ':
//                 // Simulate left mouse button click
//                 sendMouseEvent(fd, 0, 0, BTN_LEFT);
//                 break;
//             case 'c':
//                 // Simulate right mouse button click
//                 sendMouseEvent(fd, 0, 0, BTN_RIGHT);
//                 break;
//             default:
//                 break;
//         }
        
//         // Send mouse movement events
//         sendMouseEvent(fd, relX, relY, 0);

//         // Reset movement
//         relX = 0;
//         relY = 0;
//     }

//     // Restore terminal settings
//     struct termios term;
//     tcgetattr(STDIN_FILENO, &term);
//     term.c_lflag |= ICANON | ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);

//     // Destroy the virtual mouse device
//     destroyVirtualMouse(fd);

//     return 0;
// }











#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <string.h>
#include <termios.h>

// Function to create the virtual mouse device
int createVirtualMouse() {
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open /dev/uinput");
        return -1;
    }

    // Enable mouse events
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_RELBIT, REL_X);
    ioctl(fd, UI_SET_RELBIT, REL_Y);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);
    ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);

    struct uinput_user_dev uidev;
    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Virtual Mouse");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = 0x1;
    uidev.id.product = 0x1;
    uidev.id.version = 1;
    write(fd, &uidev, sizeof(uidev));

    if (ioctl(fd, UI_DEV_CREATE) < 0) {
        perror("ioctl UI_DEV_CREATE error");
        close(fd);
        return -1;
    }

    return fd;
}

// Function to destroy the virtual mouse device
void destroyVirtualMouse(int fd) {
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

// Function to send mouse events
void sendMouseEvent(int fd, int relX, int relY, int btn) {
    struct input_event event;
    memset(&event, 0, sizeof(event));

    event.type = EV_REL;
    event.code = REL_X;
    event.value = relX;
    write(fd, &event, sizeof(event));

    event.type = EV_REL;
    event.code = REL_Y;
    event.value = relY;
    write(fd, &event, sizeof(event));

    if (btn == BTN_LEFT || btn == BTN_RIGHT) {
        event.type = EV_KEY;
        event.code = btn;
        event.value = 1;
        write(fd, &event, sizeof(event));

        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        write(fd, &event, sizeof(event));

        event.type = EV_KEY;
        event.code = btn;
        event.value = 0;
        write(fd, &event, sizeof(event));

        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        write(fd, &event, sizeof(event));
    } else if (btn == 0) {
        event.type = EV_SYN;
        event.code = SYN_REPORT;
        event.value = 0;
        write(fd, &event, sizeof(event));
    }
}

int main() {
    // Create the virtual mouse device
    int fd = createVirtualMouse();
    if (fd < 0)
        return 1;

    // Create a FIFO pipe
    mkfifo("/tmp/mousepipe", 0666);

    // Open the FIFO pipe for reading
    int pipe_fd = open("/tmp/mousepipe", O_RDONLY);
    if (pipe_fd < 0) {
        perror("Failed to open named pipe");
        destroyVirtualMouse(fd);
        return 1;
    }

    // Variables for storing input
    char command;
    int relX = 0, relY = 0;

    int running = 1;
    while (running) {
        if (read(pipe_fd, &command, 1) > 0) {
            switch (command) {
                case 'w':
                    relY -= 10; // Move up
                    break;
                case 's':
                    relY += 10; // Move down
                    break;
                case 'a':
                    relX -= 10; // Move left
                    break;
                case 'd':
                    relX += 10; // Move right
                    break;
                case ' ':
                    // Simulate left mouse button click
                    sendMouseEvent(fd, 0, 0, BTN_LEFT);
                    break;
                case 'c':
                    // Simulate right mouse button click
                    sendMouseEvent(fd, 0, 0, BTN_RIGHT);
                    break;
                case 'q':
                    // Terminate the program
                    running = 0;
                    break;
                default:
                    break;
            }
            
            // Send mouse movement events
            sendMouseEvent(fd, relX, relY, 0);

            // Reset movement
            relX = 0;
            relY = 0;
        }
    }

    // Close the named pipe
    close(pipe_fd);

    // Destroy the virtual mouse device
    destroyVirtualMouse(fd);

    return 0;
}


