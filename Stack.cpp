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

void StackPush(Stack* stk, stk_type elem)
{
	ASSERT_OK_B

		if (stk->size == stk->capacity) StackResizeUp(stk);
	*(stk->buffer + (stk->size)++) = elem;

	ASSERT_OK_E

	return;
}

stk_type StackPop(Stack* stk)
{
	ASSERT_OK_B
	
	if (stk->size == 0)
	{
		stk->status_error = BAD_SIZE_ZERO;
		StackLog(stk);
	}
	else
	{
		if (stk->capacity > stk->min_capacity &&
			stk->capacity >= STK_RESIZE * STK_RESIZE * stk->size)
			StackResizeDown(stk);

	stk_type poped = stk->buffer[--(stk->size)];
	*(stk->buffer + stk->size) = STK_POISON;

	if (StackError (stk)) StackLog (stk);
	return poped;
	}}
}

void StackResizeUp (Stack* stk)
{
	ASSERT_OK_B

	stk->buffer = (stk_type*) realloc (stk->buffer, 
		sizeof (stk_type) * (stk->capacity) * STK_RESIZE);

	(stk->capacity) *= STK_RESIZE;

	for (int i_buf = stk->size + 1; i_buf < stk->capacity; i_buf++)
		*(stk->buffer + i_buf) = STK_POISON;

	ASSERT_OK_E
}

void StackResizeDown (Stack* stk)
{
	ASSERT_OK_B

	if (stk->capacity >= STK_RESIZE * stk->size && 
		stk->capacity >= STK_RESIZE * stk->min_capacity)
			stk->buffer = (stk_type*) realloc (stk->buffer, 
				sizeof (stk_type) * (stk->capacity) / STK_RESIZE);

	stk->capacity /= STK_RESIZE;

	ASSERT_OK_E
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
		stk->status_error = BAD_SIZE_CAP;
		return BAD_SIZE_CAP;
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
	//system ("dir & pause");
	FILE* file = fopen ("stklog.txt", "a");

	struct tm* mytime = nullptr;
	time_t alltime = 0;
	time (&alltime);
	mytime = localtime (&alltime);
	fprintf (file, "\n%s", asctime (mytime));

	if (!stk)
	{
		fprintf (file, "Stack [STK_NULL] : The address of stack is null.\n\n");
		
		fclose(file);
		
		return;
	}
	switch (stk->status_error)
	{
		case STK_GOOD:
			fprintf (file, "Stack [STK_GOOD] : Nice!\n");
			break;
		case STK_DEL:
			fprintf (file, "Stack [STK_DEL] : Stack was deleted.\n");
			break;
		case BUF_NULL:
			fprintf (file, "Stack [BUF_NULL] : The address of buffer is nullptr.\n");
			break;
		case BAD_SIZE_CAP:
			fprintf (file, "Stack [BAD_SIZE_CAP] : The size of stack is more then capacity.\n");
			break;
		case BAD_SIZE_ZERO:
			fprintf(file,  "Stack [BAD_SIZE_ZERO] : StackPop was called when size was zero.\n");
			break;
		case BAD_CAP:
			fprintf (file, "Stack [BAD_CAP] : The capacity of stack is less then minimal capacity.\n");
			break;
		default:
			fprintf (file, "Stack [UNK] : Unknown error.\n");
			break;
	};
	fprintf(file, "size = %d\n" "capacity = %d\n" "min_capacity = %d\n" "buffer:\n", 
			  stk->size,	stk->capacity,	  stk->min_capacity);
	for (int element = 0; element < stk->capacity; element++)
		fprintf (file, "[%d] = %lf\n", element, stk->buffer[element]);

	fprintf (file, "\n");
	fclose (file);

	return;
}
