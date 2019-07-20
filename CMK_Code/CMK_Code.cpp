// CMK_Code.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma optimize( "", off )

#include "pch.h"
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <memory.h>


// MACROS
#define GET_FUNCTION_SIZE_A(functionName) \
    (const int)((DWORD)(void*)functionName##_end - (DWORD)(void*)functionName)

#define SAVE_FUNCTION_A(functionName, functionType, buffer, key) \
{ \
    const int func_size = GET_FUNCTION_SIZE_A(functionName); \
    for (int i = 0; i < func_size; i++) \
    { \
        buffer[i] = ((char*)functionName)[i] ^ key; \
    } \
}

#define LOAD_FUNCTION_A(functionName, functionType, buffer, ptrTo, key) \
{ \
    const int func_size = GET_FUNCTION_SIZE_A(functionName); \
    char* local_ptrTo_T = buffer; \
    for (int i = 0; i < func_size; i++) \
    { \
        local_ptrTo_T[i] = ((char*)buffer)[i] ^ key; \
    } \
    ptrTo = (functionType)local_ptrTo_T; \
}

#define UNLOAD_FUNCTION_A(functionName, buffer, key) \
{ \
    char* local_ptrTo_T = buffer; \
    for (int i = 0; i < GET_FUNCTION_SIZE_A(func_sum); i++) \
    { \
        local_ptrTo_T[i] = ((char*)buffer)[i] ^ key; \
    } \
}

#define GENERATE_FUNCTION_A(retType, name, params) \
    retType __cdecl name##params

#define GENERATE_FUNCTION_A_WITH_CODE(retType, name, params, code) \
    retType __cdecl name##params \
    code \
    void __cdecl name##_end() {};




// FUNCS
int summ_obs(int a, int b);
int sub_summ_obs_A(int a, int b);
GENERATE_FUNCTION_A(int, func_sum, (int a, int b));







#define FUNC_SUM_A(a, b) (a + 1 - b * 2 - 1 + b * 3)
#define FUNC_SUM_B(a, b) (2 + a + 5 - b * 4 - 1 + b * 5 - 6)
#define FUNC_SUM_C(a, b) (a * 2 - a + b)
#define FUNC_SUM_D(a, b) ((b + b + a * 2) / 2)
GENERATE_FUNCTION_A_WITH_CODE(int, func_sum, (int a, int b),
{
    int result = 0;
    switch (rand() % 4)
    {
        //case 0: result = sub_summ_obs(a, b); break;//return FUNC_SUM_A(a, b); // a + 1 - b * 2 - 1 + b * 3;
        case 0: result = sub_summ_obs_A(a, b); break; // a + 1 - b * 2 - 1 + b * 3;
        case 1: result = FUNC_SUM_B(a, b); break; //2 + a + 5 - b * 4 - 1 + b * 5 - 6;
        case 2: result = FUNC_SUM_C(a, b); break;//a * 2 - a + b;
        case 3: result = FUNC_SUM_D(a, b); break;//(b + b + a * 2) / 2;
    }
    return result;
}
);
#undef FUNC_SUM_A
#undef FUNC_SUM_B
#undef FUNC_SUM_C
#undef FUNC_SUM_D




int summ_obs(int a, int b)
{
    const int KEY_FOR_FUNC_SUM = (char)0x2F7A;

    int result;
    int(*_summ) (int a, int b);
    
    static char* buff = 0;
    if (!buff)
    {
        buff = malloc(GET_FUNCTION_SIZE_A(func_sum));
        
        SAVE_FUNCTION_A(func_sum,
            int(*) (int a, int b),
            buff,
            KEY_FOR_FUNC_SUM);
    }
    

    LOAD_FUNCTION_A(func_sum,
        int(*) (int a, int b),
        buff, _summ,
        KEY_FOR_FUNC_SUM);

    result = _summ(a, b);

    UNLOAD_FUNCTION_A(func_sum, buff, KEY_FOR_FUNC_SUM);
    return result;
}

GENERATE_FUNCTION_A_WITH_CODE(int, simpleSumm, (int a, int b),
{
    return a + b;
});

int sub_summ_obs_A(int a, int b)
{
    const int KEY_FOR_FUNC_SUM = (char)0x367B;

    int result = 0;
    int(*_summ) (int a, int b);

    static char* buff = 0;
    if (!buff)
    {
        buff = malloc(GET_FUNCTION_SIZE_A(simpleSumm));

        SAVE_FUNCTION_A(simpleSumm,
            int(*) (int a, int b),
            buff,
            KEY_FOR_FUNC_SUM);
    }


    LOAD_FUNCTION_A(simpleSumm,
        int(*) (int a, int b),
        buff, _summ,
        KEY_FOR_FUNC_SUM);

    result = _summ(a, b);

    UNLOAD_FUNCTION_A(simpleSumm, buff, KEY_FOR_FUNC_SUM);
    return result;
}



#define NEW_MY_CMK
#ifdef NEW_MY_CMK


void testTime( int(*fun)(int a, int b) )
{
    int result;

    time_t beginTime, endTime, elapsed;
    
    beginTime = time(0);
    for (int k = 0; k < 1024 * 8; k++)
    {
        for (int i = 0; i < 1024 * 8; i++)
        {
            result = fun(i, i * 3 - 1);
            //printf("Answear for %d + %d is %d     [ %s ]\n", i, i * 3 - 1, result, result == (i + i * 3 - 1) ? "TRUE" : "FALSE");
        }
    }
    endTime = time(0);
    elapsed = endTime - beginTime;
    printf("Time is %d min %d secs\n", localtime(&elapsed)->tm_min, localtime(&elapsed)->tm_sec);
};


int main(int argc, char* argv[])
{
    srand(time(0));
    int result;
    
    
    //char code[1024] = { 0 };// { 0x55, 0x8B, 0xEC, 0x8B, 0x45, 0x08, 0x03, 0x45, 0x0C, 0x5D, 0xC3 };
    
    
    testTime(func_sum);
    testTime(summ_obs);


    return 0;
}


#else

#endif // NEW_MY_CMK


