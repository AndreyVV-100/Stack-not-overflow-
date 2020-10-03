#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define ERR_FREE (stk_type*) 228
#define ASSERT_OK 	if (StackError (stk)){	\
						StackLog (stk);		\
						exit(1);			\
					}		

enum stack_errors { STK_NULL = 1, STK_DEL, BUF_NULL, BAD_SIZE, BAD_CAP};

typedef double stk_type;

const stk_type STK_POISON = NAN;
const size_t   STK_RESIZE = 2;

struct Stack
{
	stk_type* buffer = nullptr;
	size_t	size = 0,
			capacity = 0,
		min_capacity = 0;
	int status_error = 0;
};

void StackConstructor (Stack* stk, size_t max_size);

void StackDestructor  (Stack* stk);

void StackPush (Stack* stk, stk_type elem);

stk_type StackPop (Stack* stk);

void StackResizeUp (Stack* stk);

void StackResizeDown (Stack* stk);

int StackError (Stack* stk);

void StackLog (Stack* stk);
