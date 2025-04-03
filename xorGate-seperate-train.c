#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float sigmoidf(float x)
{
    return 1.f / (1.f + expf(-x));
}

typedef float sample[3];

// gate train data
sample or_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}, 
};

sample and_train[] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

sample nand_train[] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample *train = or_train;
#define train_count 4

float rand_float()
{
    // srand(time(0));
    srand(time(0));
    return (float) rand() / (float) RAND_MAX; // return random float from 0 to 1
}

float loss(float w1, float w2, float b)
{
    float result = 0.0f;
    for (int i = 0; i < train_count; i++)
    {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf((w1 * x1) + (w2 * x2) + b);
        float d = y - train[i][2];
        result += d*d;
        // printf("actual: %f, expected: %f \n", y, train[i][1]);
    }
    result /= train_count; // Mean Square Error 
    return result;
}

float* orGate_train()
{
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-1;
    float rate = 1e-1;

    train = or_train;

    for (int i = 0; i < 100000; i++)
    {
        float c = loss(w1, w2, b);

        float dw1 = (loss(w1 + eps, w2, b) - c)/eps;
        float dw2 = (loss(w1, w2 + eps, b) - c)/eps;
        float db = (loss(w1, w2, b + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b -= rate*db;
    }

    float* params = (float*)malloc(sizeof(float) * 3);
    params[0] = w1;
    params[1] = w2;
    params[2] = b;

    return params;
}

float* andGate_train()
{
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-1;
    float rate = 1e-1;

    train = and_train;

    for (int i = 0; i < 100000; i++)
    {
        float c = loss(w1, w2, b);

        float dw1 = (loss(w1 + eps, w2, b) - c)/eps;
        float dw2 = (loss(w1, w2 + eps, b) - c)/eps;
        float db = (loss(w1, w2, b + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b -= rate*db;
    }

    float* params = (float*)malloc(sizeof(float) * 3);
    params[0] = w1;
    params[1] = w2;
    params[2] = b;

    return params;
}

float* nandGate_train()
{
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();

    float eps = 1e-1;
    float rate = 1e-1;

    train = nand_train;

    for (int i = 0; i < 100000; i++)
    {
        float c = loss(w1, w2, b);

        float dw1 = (loss(w1 + eps, w2, b) - c)/eps;
        float dw2 = (loss(w1, w2 + eps, b) - c)/eps;
        float db = (loss(w1, w2, b + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b -= rate*db;
    }

    float* params = (float*)malloc(sizeof(float) * 3);
    params[0] = w1;
    params[1] = w2;
    params[2] = b;

    return params;
}


int main()
{
    float* orGate_params = orGate_train();
    float w1_orGate = orGate_params[0];
    float w2_orGate = orGate_params[1];
    float b_orGate = orGate_params[2];

    float* andGate_params = andGate_train();
    float w1_andGate = andGate_params[0];
    float w2_andGate = andGate_params[1];
    float b_andGate = andGate_params[2];

    float* nandGate_params = nandGate_train();
    float w1_nandGate = nandGate_params[0];
    float w2_nandGate = nandGate_params[1];
    float b_nandGate = nandGate_params[2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            float x = sigmoidf(i * w1_orGate + j * w2_orGate + b_orGate); // OR Gate result
            float y =  sigmoidf(i * w1_nandGate + j * w2_nandGate + b_nandGate); // NAND Gate result

            printf("%d | %d = %f \n", i, j, sigmoidf(x * w1_andGate + y * w2_andGate + b_andGate));
        }
    }

    printf("---------------------\n");
    printf("OR NEURON \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d | %d = %f\n", i, j, sigmoidf(i * w1_orGate + j * w2_orGate + b_orGate));
        }
    }

    printf("---------------------\n");
    printf("NAND NEURON \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("~(%d & %d) = %f\n", i, j, sigmoidf(i * w1_nandGate + j * w2_nandGate + b_nandGate));
        }
    }

    printf("---------------------\n");
    printf("AND NEURON \n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d & %d = %f\n", i, j, sigmoidf(i * w1_andGate + j * w2_andGate + b_andGate));
        }
    }

    return 0;
}
