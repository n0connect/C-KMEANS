/**
 * @file kmeans.c
 * @author n0connect
 * @brief 
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"
//--------------------------  //
#include "sample.h"

#if 0
// Better than comment line's ":)"
#endif

// Color for the 3 start point
Color colors[COLOR_COUNT] = {
GOLD       ,
GREEN     ,
PINK       ,
MAROON     ,
ORANGE      ,
LIME       ,
SKYBLUE    , 
BLUE       ,
PURPLE     ,
VIOLET     ,
BEIGE      ,
BROWN
};

// Important local global variables
Samples *list_of_dataset[DATASET_COUNT] = {0};
Vector2 means[DATASET_COUNT] = {0};
Vector2 *means_ptr = &means;

Samples cluster[K] = {0};

// -------------------------  // Need to Up

void sample_da_enj(Samples *samples, float x, float y);
static Vector2 sample_to_screen(Vector2 sample);
static void draw_the_dataset(Samples **sample);
void calculate_kmeans(Samples set);
void update_kmeans(void);


// Normalize the random points on the screen
static Vector2 sample_to_screen(Vector2 sample){
    float normal_x = (sample.x - MIN_X)/(MAX_X - MIN_X);
    float normal_y = (sample.y - MIN_Y)/(MAX_Y - MIN_Y);
    float h = GetScreenHeight();
    float w = GetScreenWidth();

    return CLITERAL(Vector2) {
        .x = w*normal_x,
        .y = h - normal_y*h,
    };
}

// Draw the circle's
static void draw_the_dataset(Samples **sample){
    for(size_t ca = 0; ca < DATASET_COUNT; ca++){   
        for(size_t i = 0; i < sample[ca]->count; ++i){

            Vector2 itter = {
                .x = sample[ca]->items[i].x,
                .y = sample[ca]->items[i].y
            };

            Vector2 itter_result = sample_to_screen(itter);
            DrawCircleV(itter_result, SAMPLE_RADIUS, BLUE);
        }
    }

    for(size_t i = 0; i < K; ++i){
        
        Color COLOR = colors[i%COLOR_COUNT];

        for (size_t j = 0; j < cluster[i].count; j++)
        {
            Vector2 it = sample_to_screen(cluster[i].items[j]);
            DrawCircleV(it, SAMPLE_RADIUS, COLOR);
        }

        DrawCircleV(sample_to_screen(means[i]), MEAN_RADIUS, COLOR);
    }
}

// For data appending the cluster
void sample_da_enj(Samples *samples, float x, float y) {
    // Check if we need to allocate more memory
    if (samples->count >= samples->capacity) {
        size_t new_capacity = samples->capacity == 0 ? 10 : samples->capacity * 2; // Start with 10, then double
        samples->items = realloc(samples->items, new_capacity * sizeof(Vector2));

        samples->capacity = new_capacity;
    }
    // Add the new sample
    samples->items[samples->count].x = x;
    samples->items[samples->count].y = y;
    samples->count++;
}


// ---------------------------  //
//          KMEANS              //
void calculate_kmeans(Samples set){
    for (size_t i = 0; i < K; i++)
    {
        cluster[i].count = 0;
    }
    
    for (size_t i = 0; i < set.count; i++)
    {
        Vector2 p = set.items[i];
        int k = -1;
        float s = __FLT_MAX__; 

        for (size_t j = 0; j < K; j++)
        {
            Vector2 m = means[j];
            float sm = Vector2LengthSqr(Vector2Subtract(p, m));

            if(sm < s){
                s = sm;
                k = j;
            }
        }
        
        sample_da_enj(&cluster[k], p.x, p.y);
    }
}

void update_kmeans(void){
    for(size_t i = 0; i < K; i++){
        if(0 < cluster[i].count){
            means[i] = Vector2Zero();
            for (size_t j = 0; j < cluster[i].count; j++)
            {
                means[i] = Vector2Add(means[i], cluster[i].items[j]);
            }
            means[i].x /= cluster[i].count;
            means[i].y /= cluster[i].count;
        } else {
            means[i].x = Lerp(MIN_X, MAX_X, rand_float());
            means[i].y = Lerp(MIN_Y, MAX_Y, rand_float());
        }
    }

}

int main(int argc, char** argv)
{
    // Set the window settings
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "K-MEANS ALGORITHM");

    // Creation data set's
    Samples set_1 = {0};
    Samples set_2 = {0};
    Samples set_3 = {0};

    // Memory allocation for the set's
    sample_da_mem_alloc(&set_1, 50);
    sample_da_mem_alloc(&set_2, 50);
    sample_da_mem_alloc(&set_3, 50);

    // Include sample pointer list
    list_of_dataset[0] = &set_1;
    list_of_dataset[1] = &set_2;
    list_of_dataset[2] = &set_3;

    // Set the dataset pseudo randomly
    spesific_dataset_generator(CLITERAL(Vector2){0}, 10.0f, 50, &set_1);
    spesific_dataset_generator(CLITERAL(Vector2){MIN_X*0.5f, MAX_Y*0.5f}, 5.0f, 50, &set_2);
    spesific_dataset_generator(CLITERAL(Vector2){MAX_X*0.5f, MAX_Y*0.5f}, 5.0f, 50, &set_3);

    // MERGE ALL DATASET
    Samples set = merge_all_set(list_of_dataset);

    // Random mean's point
    for(size_t i = 0; i < DATASET_COUNT; ++i){
        means[i].x = Lerp(MIN_X, MAX_X, rand_float());
        means[i].y = Lerp(MIN_Y, MAX_Y, rand_float());
    }
    
    // --------------------  FIRST STEP //
    calculate_kmeans(set);

    while(!WindowShouldClose()){
        BeginDrawing(); //----------------  //

        if (IsKeyPressed(KEY_R)){
            regenerate_values_dataset((Samples **)list_of_dataset, means_ptr, DATASET_COUNT);
            set = merge_all_set(list_of_dataset);
            calculate_kmeans(set);
        }
        if(IsKeyPressed(KEY_SPACE)){
            update_kmeans();
            calculate_kmeans(set);
        }
        ClearBackground(GetColor(0x181818AA));
        draw_the_dataset((Samples **)list_of_dataset);

        EndDrawing(); //----------------  //
    }
    CloseWindow();
    return 0;
}