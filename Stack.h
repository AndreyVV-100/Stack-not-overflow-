#pragma once

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma warning (disable : 4996)
//'fopen': This function or variable may be unsafe.Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.

#define ERR_FREE (stk_type*) 228
#define ASSERT_OK_B if (StackError (stk)) StackLog (stk); else {
#define ASSERT_OK_E }if (StackError (stk)) StackLog (stk);

enum stack_errors { STK_GOOD, STK_NULL, STK_DEL, BUF_NULL, BAD_SIZE_CAP, BAD_SIZE_ZERO, BAD_CAP};

typedef double stk_type;

const stk_type STK_POISON = NAN;
const size_t   STK_RESIZE = 2;

struct Stack
{
	stk_type* buffer = nullptr;
	size_t	size     = 0,
			capacity = 0,
		min_capacity = 0;
	int status_error = STK_GOOD;
};

void StackConstructor (Stack* stk, size_t max_size);

void StackDestructor  (Stack* stk);

void StackPush (Stack* stk, stk_type elem);

stk_type StackPop (Stack* stk);

void StackResizeUp (Stack* stk);

void StackResizeDown (Stack* stk);

int StackError (Stack* stk);

void StackLog (Stack* stk);
