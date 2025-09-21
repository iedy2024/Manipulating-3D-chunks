#include "chunk.h"
#include<stdio.h>

char*** chunk_place_block(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        int i = 0, j = 0, k = 0;
        if (x >= 0 && y >= 0 && z >= 0) {
            if (x < width && y < height && z < depth) {
                chunk[x][y][z] = block;
            }
        }
    return chunk;
}

char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth,
    int x0, int y0, int z0, int x1, int y1, int z1, char block) {
        int i = 0, j = 0, k = 0, schimb = 0;
        if (x0 > x1) {
            schimb = x0;
            x0 = x1;
            x1 = schimb;
        }
        if (y0 > y1) {
            schimb = y0;
            y0 = y1;
            y1 = schimb;
        }
        if (z0 > z1) {
            schimb = z0;
            z0 = z1;
            z1 = schimb;
        }
        for (int x = x0; x <= x1; x++) {
            for (int y = y0; y <= y1; y++) {
                for (int z = z0; z <= z1; z++) {
                    chunk_place_block(chunk, width, height, depth, x, y, z, block);
                }
            }
        }
    return chunk;
}

char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, double radius, char block) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (((i - x)*(i-x)+(j-y)*(j-y)+(k-z)*(k-z)) <= radius * radius) {
                        chunk_place_block(chunk, width, height, depth, i, j, k, block);
                    }
                }
            }
        }
    return chunk;
}
