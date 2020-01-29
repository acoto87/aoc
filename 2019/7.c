#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define arrayLength(arr) (sizeof(arr)/sizeof((arr)[0]))

const int32_t program[] = { 3,8,1001,8,10,8,105,1,0,0,21,38,63,72,85,110,191,272,353,434,99999,3,9,102,4,9,9,101,2,9,9,102,3,9,9,4,9,99,3,9,1001,9,4,9,102,2,9,9,1001,9,5,9,1002,9,5,9,101,3,9,9,4,9,99,3,9,1001,9,2,9,4,9,99,3,9,1001,9,3,9,102,2,9,9,4,9,99,3,9,101,2,9,9,102,2,9,9,1001,9,2,9,1002,9,4,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,99 };

#define NUMBER_OF_AMPLIFIERS 5

typedef struct
{
  int32_t opcode;
  int32_t modes[3];
} IntCodeInstruction;

typedef struct
{
    int32_t pointer;
    int32_t length;
    int32_t* memory;
} IntCodeComputer;

typedef struct
{
    bool halt;
    int32_t output;
} IntCodeResult;

IntCodeComputer createComputer(int32_t length)
{
    IntCodeComputer computer = (IntCodeComputer){0};
    computer.pointer = 0;
    computer.length = length;
    computer.memory = (int32_t*)calloc(length, sizeof(int32_t));
    return computer;
}

void initMemory(IntCodeComputer* computer, const int32_t program[], int32_t length)
{
    computer->pointer = 0;
    memcpy(computer->memory, program, length * sizeof(int32_t));
}

IntCodeInstruction getInstruction(IntCodeComputer* computer)
{
    int32_t pointer = computer->pointer;
    int32_t* memory = computer->memory;
    int32_t instruction = memory[pointer];
    return (IntCodeInstruction)
    {
        instruction % 100,
        {
            (instruction / 100) % 10,
            (instruction / 1000) % 10,
            (instruction / 10000) % 10
        }
    };
}

int32_t getArg(IntCodeComputer* computer, int32_t param, int32_t mode)
{
    int32_t pointer = computer->pointer;
    int32_t* memory = computer->memory;
    return mode == 0
        ? memory[memory[pointer + param + 1]]
        : memory[pointer + param + 1];
}

IntCodeResult runProgram(IntCodeComputer* computer, int32_t inputs[], int32_t inputsLength)
{
    int32_t output;
    int32_t inputIndex = 0;

    while (computer->pointer < computer->length)
    {
        IntCodeInstruction instruction = getInstruction(computer);

        if (instruction.opcode == 99)
        {
            return (IntCodeResult){true, output};
        }

        if (instruction.opcode == 1)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);
            int32_t arg2 = getArg(computer, 2, 1);

            computer->memory[arg2] = arg0 + arg1;

            computer->pointer += 4;
        }
        else if (instruction.opcode == 2)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);
            int32_t arg2 = getArg(computer, 2, 1);

            computer->memory[arg2] = arg0 * arg1;

            computer->pointer += 4;
        }
        else if (instruction.opcode == 3)
        {
            if (inputIndex >= inputsLength)
                return (IntCodeResult){false, output};

            int32_t arg0 = getArg(computer, 0, 1);

            computer->memory[arg0] = inputs[inputIndex++];

            computer->pointer += 2;
        }
        else if (instruction.opcode == 4)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);

            output = arg0;

            computer->pointer += 2;
        }
        else if (instruction.opcode == 5)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);

            computer->pointer = arg0 ? arg1 : computer->pointer + 3;
        }
        else if (instruction.opcode == 6)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);

            computer->pointer = !arg0 ? arg1 : computer->pointer + 3;
        }
        else if (instruction.opcode == 7)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);
            int32_t arg2 = getArg(computer, 2, 1);

            computer->memory[arg2] = arg0 < arg1;

            computer->pointer += 4;
        }
        else if (instruction.opcode == 8)
        {
            int32_t arg0 = getArg(computer, 0, instruction.modes[0]);
            int32_t arg1 = getArg(computer, 1, instruction.modes[1]);
            int32_t arg2 = getArg(computer, 2, 1);

            computer->memory[arg2] = arg0 == arg1;

            computer->pointer += 4;
        }
    }

    return (IntCodeResult){false, output};
}

typedef struct
{
    int32_t phase;
    bool initialized;
    IntCodeComputer computer;
} Amplifier;

int32_t startProgram(Amplifier amplifiers[], int32_t numberOfAmplifiers)
{
    IntCodeResult result = (IntCodeResult){false, 0};

    while (!result.halt)
    {
        for (int32_t i = 0; i < numberOfAmplifiers; i++)
        {
            Amplifier* amplifier = &amplifiers[i];
            if (!amplifier->initialized)
            {
                int32_t inputs[] = { amplifier->phase, result.output };
                result = runProgram(&amplifier->computer, inputs, arrayLength(inputs));
                amplifier->initialized = true;
            }
            else
            {
                int32_t inputs[] = { result.output };
                result = runProgram(&amplifier->computer, inputs, arrayLength(inputs));
            }
        }
    }

    return result.output;
}

void swapPhase(Amplifier amplifiers[], int32_t i, int32_t j)
{
    int32_t t = amplifiers[i].phase;
    amplifiers[i].phase = amplifiers[j].phase;
    amplifiers[j].phase = t;
}

int32_t tryCombinations(Amplifier amplifiers[], int32_t numberOfAmplifiers, int32_t index)
{
    if (index >= numberOfAmplifiers)
    {
        for (int32_t i = 0; i < numberOfAmplifiers; i++)
        {
            Amplifier* amplifier = &amplifiers[i];
            amplifier->initialized = false;
            initMemory(&amplifier->computer, program, arrayLength(program));
        }

        return startProgram(amplifiers, numberOfAmplifiers);
    }

    int32_t maxTrust = 0;

    for (int32_t i = index; i < numberOfAmplifiers; i++)
    {
        swapPhase(amplifiers, i, index);

        int32_t trust = tryCombinations(amplifiers, numberOfAmplifiers, index + 1);
        if (trust > maxTrust)
            maxTrust = trust;

        swapPhase(amplifiers, i, index);
    }

    return maxTrust;
}

int32_t part1()
{
    Amplifier amplifiers[NUMBER_OF_AMPLIFIERS];
    for (int32_t i = 0; i < arrayLength(amplifiers); i++)
    {
        amplifiers[i].initialized = false;
        amplifiers[i].phase = i;
        amplifiers[i].computer = createComputer(arrayLength(program));
    }

    int32_t result = tryCombinations(amplifiers, arrayLength(amplifiers), 0);

    for (int32_t i = 0; i < arrayLength(amplifiers); i++)
        free(amplifiers[i].computer.memory);

    return result;
}

int32_t part2()
{
    Amplifier amplifiers[NUMBER_OF_AMPLIFIERS];
    for (int32_t i = 0; i < arrayLength(amplifiers); i++)
    {
        amplifiers[i].initialized = false;
        amplifiers[i].phase = 5 + i;
        amplifiers[i].computer = createComputer(arrayLength(program));
    }

    int32_t result = tryCombinations(amplifiers, arrayLength(amplifiers), 0);

    for (int32_t i = 0; i < arrayLength(amplifiers); i++)
        free(amplifiers[i].computer.memory);

    return result;
}

int main()
{
    printf("part 1: %d\n", part1());
    printf("part 2: %d\n", part2());

    return 0;
}