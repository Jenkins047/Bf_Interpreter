#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <vector>

typedef struct
{
    unsigned int lBracket;
    unsigned int rBracket;
}matching;

unsigned int findClosingParen(std::string text, unsigned int openPos) {
    int closePos = openPos;
    int counter = 1;
    while (counter > 0) {
        char c = text[++closePos];
        if (c == '[') {
            counter++;
        }
        else if (c == ']') {
            counter--;
        }
    }
    return closePos;
}


int main(int argc, char* args[])
{
    std::string program = "", buf = "";
    std::ifstream file(args[1]);

    while(getline(file, buf))
        program += buf;
    
    file.close();

    int* lBracketCount = new int;
    int* rBracketCount = new int;

    *lBracketCount = 0;
    *rBracketCount = 0;

    for(unsigned int i = 0; i < program.length(); i++)
    {
        if(program[i] == '[')
            (*lBracketCount)++;

        if(program[i] == ']')
            (*rBracketCount)++;
    }

    if(*rBracketCount != *lBracketCount)
    {
        std::cout<<"Brackets don't match up!"<<std::endl;
        delete lBracketCount;
        delete rBracketCount;

        return -1;
    }

    
    delete rBracketCount;

    matching brackets[*lBracketCount];

    int* j = new int;
    *j = 0;

    for(unsigned int i = 0; i < program.length(); i++)
    {
        if(program[i] == '[')
        {
            brackets[*j].lBracket = i;
            brackets[*j].rBracket = findClosingParen(program, i);
            (*j)++;
        }
    }

    delete j;
    
    unsigned int MEM_SIZE = 10000;
    std::vector<char> memory;

    for(unsigned int i = 0; i < MEM_SIZE; i++)
    {
        memory.push_back(0);
    }

    unsigned int programPointer = 0, memoryPointer = 128;
    char command = program[programPointer];

    while(programPointer < program.length())
    {
        command = program[programPointer];
        switch (command)
        {
        case '+':
            memory[memoryPointer]++;
            programPointer++;
            break;

        case '-':
            memory[memoryPointer]--;
            programPointer++;
            break;

        case '<':
            memoryPointer--;
            programPointer++;
            break;

        case '>':
            if(memoryPointer < MEM_SIZE)
                memoryPointer++;
            else
                {
                    for(unsigned int i = 0; i < MEM_SIZE; i++)
                        {
                            memory.push_back(0);
                        }
                        MEM_SIZE *= 2;
                        break;
                }
            programPointer++;
            break;

        case ',':
            std::cin>>memory[memoryPointer];
            programPointer++;
            break;

        case '.':
            std::cout<<memory[memoryPointer]<<std::flush;
            programPointer++;
            break;

        case '[':
                if(memory[memoryPointer])
                {
                    programPointer++;
                }
                else
                {
                    for(int i = 0; i < *lBracketCount; i++)
                    {
                        if(brackets[i].lBracket == programPointer)
                            programPointer = brackets[i].rBracket + 1;
                    }
                }
            break;

        case ']':
            for(int i = 0; i < *lBracketCount; i++)
                    {
                        if(brackets[i].rBracket == programPointer)
                            programPointer = brackets[i].lBracket;
                    }

            break;
        default:
            programPointer++;
            break;
        }
    }
    delete lBracketCount;
    return 0;
}