#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv)
{
    int c;
    struct stat s;
    char* output = NULL;

    while ((c = getopt(argc, argv, "vo:")) != -1) {
        switch (c) {
            case 'v':
                printf("DungeonBlog\n(c)2023 Joss \"Sleppo04\"\n");
                return 0;
            case 'o':
                output = optarg;
                break;
            case '?':
                // We assume that getopt() printed an error message for us
                // TODO: proper error handling
                return -1;
        }
    }
    
    // check if output dir is a directory
    if (stat(output, &s)) {
        if (errno == EACCES)
            printf("Permission error while accessing output dir.\n");
        else if (errno == ENOENT)
            printf("Could not find the specified output dir.\n");
        else
            printf("Unknown error while accessing output dir.\n");
        return -1;
    }

    if (!S_ISDIR(s.st_mode)) {
        printf("The specified output path is not a directory.\n");
        return -1;
    }

    return 0;
}
