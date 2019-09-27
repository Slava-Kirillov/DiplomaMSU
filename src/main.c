#include <stdio.h>
#include <bits/types/FILE.h>

int main(int argc, char **argv) {
    FILE *file = fopen("../resource/data/test_file", "wb");
    if (file == NULL) {
        printf("File reading error\n");
    }

    return 0;
}