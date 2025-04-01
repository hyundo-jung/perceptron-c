#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float train[][2] = {
    {0, 0},
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},    
};

#define train_count sizeof(train) / sizeof(train[0])

float rand_float()
{
    // srand(time(0));
    srand(66);
    return (float) rand() / (float) RAND_MAX; // return random float from 0 to 1
}

float loss(float w)
{
    float result = 0.0f;
    for (int i = 0; i < train_count; i++)
    {
        float x = train[i][0];
        float y = w * x;
        float d = y - train[i][1];
        result += d*d;
        printf("actual: %f, expected: %f \n", y, train[i][1]);
    }
    result /= train_count;
    return result;
}

// y = w*x;
int main() 
{
    float w = rand_float() * 10.0f;

    float eps = 1e-3;
    printf("%f \n", loss(w));
    printf("%f \n", loss(w + eps));

    return 0;
}
