#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define arrayLength(arr) (sizeof(arr)/sizeof((arr)[0]))

const int opcodes[] =
{
    1,0,0,3,
    1,1,2,3,
    1,3,4,3,
    1,5,0,3,
    2,10,1,19,
    2,9,19,23,
    2,13,23,27,
    1,6,27,31,
    2,6,31,35,
    2,13,35,39,
    1,39,10,43,
    2,43,13,47,
    1,9,47,51,
    1,51,13,55,
    1,55,13,59,
    2,59,13,63,
    1,63,6,67,
    2,6,67,71,
    1,5,71,75,
    2,6,75,79,
    1,5,79,83,
    2,83,6,87,
    1,5,87,91,
    1,6,91,95,
    2,95,6,99,
    1,5,99,103,
    1,6,103,107,
    1,107,2,111,
    1,111,5,0,
    99,
    2,14,0,0
};

void runProgram(int* memory, int length)
{
    for (int i = 0; i < length; i += 4)
    {
        int opcode = memory[i];
        if (opcode == 99)
            break;

        if (opcode == 1)
        {
            int addr1 = memory[i + 1];
            int addr2 = memory[i + 2];
            int addr3 = memory[i + 3];
            memory[addr3] = memory[addr1] + memory[addr2];
        }
        else if (opcode == 2)
        {
            int addr1 = memory[i + 1];
            int addr2 = memory[i + 2];
            int addr3 = memory[i + 3];
            memory[addr3] = memory[addr1] * memory[addr2];
        }
    }
}

int part1()
{
    int length = arrayLength(opcodes);

    int* memory = (int*)malloc(length * sizeof(int));
    memcpy(memory, opcodes, length * sizeof(int));

    memory[1] = 12;
    memory[2] = 2;
    runProgram(memory, length);

    int result = memory[0];
    free(memory);
    return result;
}

int part2()
{
    int length = arrayLength(opcodes);

    int* memory = (int*)malloc(length * sizeof(int));
    memcpy(memory, opcodes, length * sizeof(int));

    for (int n = 0; n < 100; n++)
    {
        for (int v = 0; v < 100; v++)
        {
            memcpy(memory, opcodes, length * sizeof(int));

            memory[1] = n;
            memory[2] = v;
            runProgram(memory, length);

            if (memory[0] == 19690720)
            {
                free(memory);
                return 100 * n + v;
            }
        }
    }

    free(memory);
    return 0;
}

int main()
{
    printf("part 1: %d\n", part1());
    printf("part 2: %d\n", part2());
    return 0;
}