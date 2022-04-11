#define true 1
#define false 0

const unsigned int MIN_TB = 0;
const unsigned int MAX_TB = 1000;

const unsigned int MIN_TI = 0;
const unsigned int MAX_TI = 1000;

typedef struct {
    unsigned int num_oxygen;
    unsigned int num_hydrogen;
    unsigned int TI;
    unsigned int TB;
} arguments_t;

arguments_t* arguments_create(int num_oxygen_, int num_hydrogen_, int TI_, int TB_);
