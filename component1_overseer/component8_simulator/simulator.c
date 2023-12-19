#include "aid8.h"

void runBinaryFile(const char *filename) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == 0) {
        // This is the child process
        execl(filename, filename, NULL);
        // If execl fails, it will return here
        perror("exec failed");
        exit(1);
    } else if (child_pid > 0) {
        // This is the parent process
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            printf("%s executed successfully\n", filename);
        } else {
            printf("%s execution failed\n", filename);
        }
    }
}

void *runBinaryFilesInThreads(void *filename) {
    runBinaryFile((const char *)filename);
    pthread_exit(NULL);
}

int main() {
    DIR *dir;
    struct dirent *ent;
    char *path = ".";
    printf("Simulator started\n");

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            struct stat st;
            char filename[400];
            snprintf(filename, sizeof(filename), "./%s", ent->d_name);
            
            if (stat(filename, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
                // Check if the file is an ELF binary
                FILE *file = fopen(filename, "r");
                if (file) {
                    char header[4];
                    fread(header, 1, 4, file);
                    if (memcmp(header, "\x7F\x45\x4C\x46", 4) == 0) {
                        if (strcmp(ent->d_name, "component1_overseer") != 0) {
                            pthread_t thread;
                            int result = pthread_create(&thread, NULL, runBinaryFilesInThreads, filename);
                            if (result != 0) {
                                fprintf(stderr, "Thread creation failed for %s\n", filename);
                            }
                        } else {
                            runBinaryFile(filename);
                            sleep(5);
                            break;
                        }
                    }
                    fclose(file);
                }
            }
        }
        closedir(dir);
    } else {
        perror("Unable to open directory");
        return 1;
    }

    // Wait for all threads to complete
    pthread_exit(NULL);
}
