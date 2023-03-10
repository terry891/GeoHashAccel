//
//  geohash_test.c
//  libgeohash
//
//  Created by Derek Smith on 10/6/09.
//  Copyright 2009 SimpleGeo. All rights reserved.
//

#include "geohash.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void check_coords(GeoCoord coord, GeoCoord expected) {
 
    char* valueTitle = NULL;
    double expectedValue;
    double value;
    
    if(coord.latitude != expected.latitude) {
        
        valueTitle = "latitude";
        expectedValue = expected.latitude;
        value = coord.latitude;
        
    } else if(coord.longitude != expected.longitude) {

        valueTitle = "longitude";
        expectedValue = expected.longitude;
        value = coord.longitude;
        
        
    } else if(coord.north != expected.north) {

        valueTitle = "north";
        expectedValue = expected.north;
        value = coord.north;
        
        
    } else if(expected.south != coord.south) {

        valueTitle = "south";
        expectedValue = expected.south;
        value = coord.south;
        
    } else if(coord.east != expected.east) {

        valueTitle = "east";
        expectedValue = expected.east;
        value = coord.east;
        
    } else if(expected.west != coord.west) {

        valueTitle = "west";
        expectedValue = expected.west;
        value = coord.west;
        
    }
    
    if(valueTitle)
        printf("Error: Expected %.16f but was %.16f for %s\n", expectedValue, value, valueTitle);
    
}

void checkHashes(char* hash, char* expected) {
    
    if(strcmp(hash, expected) != 0) {
        printf("Error: Expected hash = %s. (%s)\n", expected, hash);
    }
}

void checkNeighbors(char** neighbors, char** expectedNeighbors) {
    int i;
    for(i = 0; i < 8; i++)
        if(strcmp(neighbors[i], expectedNeighbors[i]) != 0)
            printf("Error: Expected hash = %s at index %i. (%s)\n", expectedNeighbors[i], i, neighbors[i]);
}

void encoder_tester(int n, int precision, int isPrint){
    srand(time(NULL));
    if (isPrint)
        printf("Encoder: \n");
    
    clock_t start = clock();
    for (int i = 0; i < n; i++){
        float random_long, random_lat;
        random_long = (float)rand()/RAND_MAX * 360 - 180;
        random_lat =  (float)rand()/RAND_MAX * 180 - 90;
        char* hash = geohash_encode(random_lat, random_long, precision);
        if (isPrint)
            printf("Test: %d, Hash: %s, Lat: %.3f, Long: %.3f\n", i, hash, random_lat, random_long);
    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Encoder time taken: %.3fms\n", cpu_time_used * 1000);

    // char* hash = geohash_encode(42.60498046875, -5.60302734375, 5);
    // checkHashes(hash, "ezs42");
    // hash = geohash_encode(40.018141, -105.274858, 12);
    // checkHashes(hash, "9xj5smj4w40m");
    // hash = geohash_encode(40.018141, -105.274858, 2);
    // checkHashes(hash, "9x");
    // hash = geohash_encode(40.018141, -105.274858, 0);
    // checkHashes(hash, "9xj5sm");
}

void decoder_tester(int n, int precision, int isPrint){
    srand(time(NULL));
    if (isPrint)
        printf("Decoder:\n");
    static char char_map[32] =  "0123456789bcdefghjkmnpqrstuvwxyz";    
    char random_hash[precision + 1];
    
    clock_t start = clock();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < precision; j++) {
            int random_index = rand() % (sizeof(char_map) - 1);
            random_hash[j] = char_map[random_index];
        }
        random_hash[precision] = '\0';
        GeoCoord coord = geohash_decode(random_hash);
        if (isPrint)
            printf("Test: %d, Hash: %s, Lat: %.3f, Long: %.3f\n", i, random_hash, coord.latitude, coord.longitude);
    }
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Decoder time taken: %.3fms\n", cpu_time_used * 1000);

    // GeoCoord coord = geohash_decode("ezs42");
    // GeoCoord expectedCoord = {42.60498046875, -5.60302734375, 42.626953125, -5.5810546875, 42.5830078125, -5.625};
    // check_coords(coord, expectedCoord);
    // coord = geohash_decode("ezs42gx");
    // expectedCoord = (GeoCoord){42.602920532226562, -5.5817413330078125, 42.603607177734375, -5.581054687500000, 42.60223388671875, -5.582427978515625};
    // check_coords(coord, expectedCoord);
    // coord = geohash_decode("9xj5smj4w40");
    // expectedCoord = (GeoCoord){40.018140748143196, -105.27485780417919, 40.01814141869545, -105.27485713362694, 40.018140077590942, -105.27485847473145};
    // check_coords(coord, expectedCoord);
}

void neighbor_test(){
    // Neighbors
    char** neighbors = geohash_neighbors("ezs42");

    char* expectedNeighbors[8] = {"ezs48", "ezs49", "ezs43", "ezs41", "ezs40", "ezefp", "ezefr", "ezefx"};
    checkNeighbors(neighbors, expectedNeighbors);
    
    expectedNeighbors[0] = "9xj5smj4w40q"; expectedNeighbors[1] = "9xj5smj4w40w";
    expectedNeighbors[2] = "9xj5smj4w40t"; expectedNeighbors[3] = "9xj5smj4w40s";
    expectedNeighbors[4] = "9xj5smj4w40k"; expectedNeighbors[5] = "9xj5smj4w40h";
    expectedNeighbors[6] = "9xj5smj4w40j"; expectedNeighbors[7] = "9xj5smj4w40n";
    
    neighbors = geohash_neighbors("9xj5smj4w40m");
    checkNeighbors(neighbors, expectedNeighbors);
}

int main() {

    int iteration = 10;
    int precision = 40;
    int isPrint = 0;

    printf("Number of data: %d, Precision: %d\n", iteration, precision);
    encoder_tester(iteration, precision, isPrint);
    decoder_tester(iteration, precision, isPrint);

    return 0;
}






