#pragma once

#include <stdio.h>
#include <stdlib.h>

void *read_file(const char *path, size_t *size_out) {
    if (!path || !size_out) {
        return NULL;
    }

    FILE *fd = fopen(path, "rb");
    if (!fd) {
        return NULL;
    }

    if (fseek(fd, 0, SEEK_END) != 0) {
        fclose(fd);
        return NULL;
    }

    long file_size = ftell(fd);
    if (file_size < 0) {
        fclose(fd);
        return NULL;
    }

    *size_out = (size_t)file_size;

    unsigned char *data = malloc(*size_out + 1);

    if (!data) {
        fclose(fd);
        return NULL;
    }

    rewind(fd);

    size_t bytes_read = fread(data, 1, *size_out, fd);
    if (bytes_read != *size_out) {
        free(data);
        data = NULL;
        fclose(fd);
        return NULL;
    }

    data[*size_out] = '\0';

    fclose(fd);
    return data;
}
