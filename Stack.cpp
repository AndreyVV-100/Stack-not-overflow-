#include "Stack.h"

void StackConstructor (Stack* stk, size_t max_size)
{
	assert (stk);

	stk->buffer = (stk_type*) calloc (max_size, sizeof (stk_type));
	assert (stk->buffer);

	for (size_t i = 0; i < max_size; i++) *(stk->buffer + i) = STK_POISON;

	stk->capacity     = max_size;
	stk->min_capacity = max_size;

	return;
}

void StackDestructor (Stack* stk)
{
	assert (stk);
	assert (stk->buffer);
	assert (stk->buffer != ERR_FREE);
	
	for (size_t i = 0; i < stk->capacity; i++) *(stk->buffer + i) = STK_POISON;

	free (stk->buffer);

	stk->buffer = ERR_FREE;
	stk->size = 0;
	stk->capacity = 0;

	return;
}

void StackPush (Stack* stk, stk_type elem)
{
	ASSERT_OK

	if (stk->size == stk->capacity) StackResizeUp(stk);
	stk->buffer[stk->size++] = elem;

	ASSERT_OK

	return;
}

stk_type StackPop (Stack* stk)
{
	ASSERT_OK

	if (stk->capacity >  stk->min_capacity &&
		stk->capacity >= STK_RESIZE * STK_RESIZE * stk->size)
			StackResizeDown(stk);

	stk_type poped = stk->buffer[--stk->size];

	ASSERT_OK
	return poped;
}

void StackResizeUp (Stack* stk)
{
	ASSERT_OK

	stk->buffer = (stk_type*) realloc(stk->buffer, stk->capacity * STK_RESIZE);

	ASSERT_OK
}

void StackResizeDown (Stack* stk)
{
	ASSERT_OK

	if (stk->capacity >= STK_RESIZE * stk->size && 
		stk->capacity >= STK_RESIZE * stk->min_capacity)
			stk->buffer = (stk_type*) realloc (stk->buffer, stk->capacity / STK_RESIZE);

	ASSERT_OK
}

int StackError(Stack* stk)
{
	if (!stk) return STK_NULL;
	else if (stk->buffer == ERR_FREE)
	{
		stk->status_error = STK_DEL;
		return STK_DEL;
	}
	else if (!stk->buffer)
	{
		stk->status_error = BUF_NULL;
		return BUF_NULL;
	}
	else if (stk->size > stk->capacity)
	{
		stk->status_error = BAD_SIZE;
		return BAD_SIZE;
	}
	else if (stk->capacity < stk->min_capacity)
	{
		stk->status_error = BAD_CAP;
		return BAD_CAP;
	}

	return 0;
}

void StackLog(Stack* stk)
{
	printf("There are errors!");
	return;
}