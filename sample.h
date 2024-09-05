/**
 * @file sample.h
 * @author n0connect
 * @brief 
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef SAMPLE_H
#define SAMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//--------------------------  //
#include "raylib.h"
#include "raymath.h"
#include "sample.h"

// Define used dataset ammount
#define DATASET_COUNT 3
#define K 3
#define COLOR_COUNT 12

#define SAMPLE_RADIUS 4.0f
#define MEAN_RADIUS 2*SAMPLE_RADIUS
#define MEAN_COLOR CLITERAL(Color){ 253, 249, 0, 255 }

// Define Windows Special's
#define MIN_X -20.0f
#define MAX_X 20.0f
#define MIN_Y -20.0f
#define MAX_Y 20.0f

/**
 * @brief Data Samples struct
 * 
 */
typedef struct
{
    Vector2 *items;
    size_t count;
    size_t capacity;

    Vector2 *center;
    float radius;

} Samples;

/**
 * @brief Dynamic Data append
 * 
 * @param samples Samples struct brief
 * @param sample Add sample brief
 */
void sample_da_append(Samples *samples, Vector2 sample);

/**
 * @brief Merge all dataset's to one dataset. 
 * 
 * @param list_of_dataset 
 * @return Samples 
 */
Samples merge_all_set(Samples *list_of_dataset[]);

/**
 * @brief Allocate memory for the struct
 * 
 * @param samples Dataset
 * @param count Sample count in the struct
 */
void sample_da_mem_alloc(Samples *samples ,size_t count);

/**
 * @brief Regenerate the values of the dataset
 * 
 * @param list_of_dataset list of the dataset's
 * @param dataset_count 
 */
void regenerate_values_dataset(Samples **list_of_dataset, Vector2 *means_ptr, const size_t dataset_count);

/**
 * @brief Generating dataset's for the spesific center, radius and count
 * 
 * @param center Spesific center vector
 * @param radius Spesific radius vector
 * @param count Dataset items count
 * @param samples Dataset pointer
 */
void spesific_dataset_generator(Vector2 center, float radius, const size_t count, Samples *samples);

/**
 * @brief Generate random float values beetwen 0-1.
 * 
 * @return float 
 */
float rand_float(void);

#endif // SAMPLE_H