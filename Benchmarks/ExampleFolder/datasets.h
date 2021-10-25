#ifdef SMALL_DATASET
#define INPUT 625000
#endif
#ifdef LARGE_DATASET
#define INPUT 2500000
#endif

#ifndef SMALL_DATASET
  #ifndef LARGE_DATASET
    #ifndef MEDIUM_DATASET
      #define MEDIUM_DATASET
    #endif
  #endif
#endif

#ifdef MEDIUM_DATASET
#define INPUT 1250000
#endif