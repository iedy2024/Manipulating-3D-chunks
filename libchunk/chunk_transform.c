#include "chunk.h"
#include<stdio.h>
#include<stdlib.h>

char*** chunk_rotate_y(
    char*** chunk, int width, int height, int depth) {
        char ***chunk_rotit = NULL;
        chunk_rotit = calloc(depth, sizeof(char **));
        for (int i = 0; i < depth; i++) {
            chunk_rotit[i] = calloc(height, sizeof(char*));
            for (int j = 0; j < height; j++) {
                chunk_rotit[i][j] = calloc(width, sizeof(char));
            }
        }
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                for (int k = 0; k < depth; k++) {
                    chunk_rotit[depth - 1 - k][j][i] = chunk[i][j][k];
                }
            }
        }
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                free(chunk[i][j]);
                chunk[i][j] = NULL;
            }
            free(chunk[i]);
                chunk[i] = NULL;
        }
        free(chunk);
        chunk = NULL;
        return chunk_rotit;
}

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height) {
        return chunk;
}

