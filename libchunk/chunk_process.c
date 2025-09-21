#include "chunk.h"
#include<stdlib.h>
const float RAZA_STEA = 1.5f;
const char BLOCK_NEUTRU = 7;

char*** chunk_fill_sphere_unique(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        int block_init = 0;
        block_init = chunk[x][y][z];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if ((float)((i - x)*(i-x)+(j-y)*(j-y)+(k-z)*(k-z)) <= RAZA_STEA * RAZA_STEA) {
                        if (chunk[i][j][k] != block_init) {
                            chunk_place_block(chunk, width, height, depth, i, j, k, BLOCK_NEUTRU);
                        }
                    }
                }
            }
        }
    return chunk;
}

char*** chunk_shell(
    char*** chunk, int width, int height, int depth,
    char target_block, char shell_block) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (chunk[i][j][k] == target_block) {
                        chunk_fill_sphere_unique(chunk, width, height, depth, i, j, k, shell_block);
                    }
                }
            }
        }
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (chunk[i][j][k] == BLOCK_NEUTRU) {
                        chunk_place_block(chunk, width, height, depth, i, j, k, shell_block);
                    }
                }
            }
        }
     return chunk;
}

void cautare_drum(char*** chunk, int width, int depth, int x, int y, int z, char block, char ** elem_vizitate) {
    if (x < 0 || x >= width || z < 0 || z >= depth || chunk[x][y][z] != block || elem_vizitate[x][z]) {
        return;
    }
    elem_vizitate[x][z] = 1;
    cautare_drum(chunk, width, depth, x + 1, y, z, block, elem_vizitate);
    cautare_drum(chunk, width, depth, x - 1, y, z, block, elem_vizitate);
    cautare_drum(chunk, width, depth, x, y, z + 1, block, elem_vizitate);
    cautare_drum(chunk, width, depth, x, y, z - 1, block, elem_vizitate);
}

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        char **elem_vizitate = NULL;
        elem_vizitate = calloc(width, sizeof(char *));
        for (int i = 0; i < width; i++) {
            elem_vizitate[i] = calloc(depth, sizeof(char));
        }
        char block_init = chunk[x][y][z];
        cautare_drum(chunk, width, depth, x, y, z, block_init, elem_vizitate);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < depth; j++) {
                if (elem_vizitate[i][j]) {
                    chunk[i][y][j] = block;
                }
            }
        }
        for (int i = 0; i < width; i++) {
            free(elem_vizitate[i]);
            elem_vizitate[i] = NULL;
        }
        free(elem_vizitate);
        elem_vizitate = NULL;
        return chunk;
}



void cautare_drum_3D(char*** chunk, int width, int height, int depth,
int x, int y, int z, char block, char ***elem_vizitate_3D) {
    if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth
    || chunk[x][y][z] != block || elem_vizitate_3D[x][y][z]) {
        return;
    }
    elem_vizitate_3D[x][y][z] = 1;
    cautare_drum_3D(chunk, width, height, depth, x, y - 1, z, block, elem_vizitate_3D);
    cautare_drum_3D(chunk, width, height, depth, x, y + 1, z, block, elem_vizitate_3D);
    cautare_drum_3D(chunk, width, height, depth, x + 1, y, z, block, elem_vizitate_3D);
    cautare_drum_3D(chunk, width, height, depth, x - 1, y, z, block, elem_vizitate_3D);
    cautare_drum_3D(chunk, width, height, depth, x, y, z + 1, block, elem_vizitate_3D);
    cautare_drum_3D(chunk, width, height, depth, x, y, z - 1, block, elem_vizitate_3D);
}

char*** chunk_fill(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        if (x < 0 || x >= width || y < 0 || y >= height || z < 0 || z >= depth) {
            return chunk;
        }
        char ***elem_vizitate_3D = NULL;
        elem_vizitate_3D = calloc(width, sizeof(char **));
        for (int i = 0; i < width; i++) {
            elem_vizitate_3D[i] = calloc(height, sizeof(char*));
            for (int j = 0; j < height; j++) {
                elem_vizitate_3D[i][j] = calloc(depth, sizeof(char));
            }
        }
        char block_init = chunk[x][y][z];
        cautare_drum_3D(chunk, width, height, depth, x, y, z, block_init, elem_vizitate_3D);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (elem_vizitate_3D[i][j][k]) {
                        chunk[i][j][k] = block;
                    }
                }
            }
        }
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                free(elem_vizitate_3D[i][j]);
                elem_vizitate_3D[i][j] = NULL;
            }
            free(elem_vizitate_3D[i]);
                elem_vizitate_3D[i] = NULL;
        }
        free(elem_vizitate_3D);
        elem_vizitate_3D = NULL;
        return chunk;
}
