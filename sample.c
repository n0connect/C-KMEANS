/**
 * @file sample.c
 * @author n0connect
 * @brief 
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

//---------SAMPLE.C---------  //
#include "sample.h"


/**
 * @brief Dynamic Data append
 * 
 * @param samples Samples struct brief
 * @param sample Add sample brief
 */
void sample_da_append(Samples *samples, Vector2 sample){
    // Check Area full or not
    if(samples->capacity <= samples->count){
        // Allocate one more Vector2 area if capacity full.
        samples->capacity = samples->capacity + 2*sizeof(Vector2);
        samples->items = realloc(samples->items, samples->capacity); 
    }

    // Add the new sample
    samples->items[samples->count].x = sample.x;
    samples->items[samples->count].y = sample.y;
    samples->count++;
}

/**
 * @brief Merge all dataset's to one dataset. 
 * 
 * @param list_of_dataset 
 * @return Samples 
 */
Samples merge_all_set(Samples *list_of_dataset[]){
    Samples ret_set = {0};
    size_t ret_count = 0;

    for (size_t i = 0; i < DATASET_COUNT; i++)
    {
        ret_count += list_of_dataset[i]->count;
    }

    sample_da_mem_alloc(&ret_set, ret_count);
    ret_set.count = ret_count;

    size_t itter = 0;
    for (size_t i = 0; i < DATASET_COUNT; i++)
    {
        for (size_t set_itter = 0; set_itter < list_of_dataset[i]->count; set_itter++)
        {
            ret_set.items[itter] = list_of_dataset[i]->items[set_itter];
            itter++;
        }   
    }
    return ret_set;
}

/**
 * @brief Allocate memory for the struct
 * 
 * @param samples Data set
 * @param count Sample count in the struct
 */
void sample_da_mem_alloc(Samples *samples ,size_t count){
    // Allocate and calculate for the memory :)
    samples->capacity = count * sizeof(Vector2);
    samples->items    = (Vector2 *)malloc(count*sizeof(Vector2));
    samples->center   = (Vector2 *)malloc(sizeof(Vector2));
    samples->count    = 0;
    samples->radius   = -1.0F;  // Define first radius value negative.
}

/**
 * @brief Regenerate the values of the dataset
 * 
 * @param list_of_dataset list of the dataset's
 * @param dataset_count 
 */
void regenerate_values_dataset(Samples **list_of_dataset, Vector2 *means_ptr, const size_t dataset_count){
    for (size_t i = 0; i < dataset_count; i++) {
        // Random mean's point
        for(size_t i = 0; i < DATASET_COUNT; ++i){
            means_ptr[i].x = Lerp(MIN_X, MAX_X, rand_float());
            means_ptr[i].y = Lerp(MIN_Y, MAX_Y, rand_float());
        }

        // Save Current count count
        size_t ccount = list_of_dataset[i]->count;
        list_of_dataset[i]->count = 0;
        
        // Set the dataset pseudo-randomly
        spesific_dataset_generator(*list_of_dataset[i]->center, list_of_dataset[i]->radius, ccount, list_of_dataset[i]);
    }
}

/**
 * @brief Generating dataset's for the spesific center, radius and count
 * 
 * @param center Spesific center vector
 * @param radius Spesific radius vector
 * @param count Dataset items count
 * @param samples Dataset pointer
 */
void spesific_dataset_generator(Vector2 center, float radius, const size_t count, Samples *samples){
    srand(time(NULL));
    
    samples-> center->x = center.x;
    samples-> center->y = center.y;
    samples-> radius    = radius;

    for(size_t i = 0; i < count; i++){
        float angle = rand_float()*PI*2;
        float magnitude = rand_float();
        
        Vector2 sample = {
            .x = center.x + cosf(angle)*magnitude*radius,
            .y = center.y + sinf(angle)*magnitude*radius,
        };

        //sample_data_append(samples, i, sample.x, sample.y);
        sample_da_append(samples, sample);
    }
}

/**
 * @brief Generate random float values beetwen 0-1.
 * 
 * @return float 
 */
float rand_float(void){
    return (float)rand()/RAND_MAX;
}