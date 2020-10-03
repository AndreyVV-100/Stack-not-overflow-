#define stk_poision NAN
typedef double stk_type;

struct Stack
{
	stk_type* buffer = nullptr;
	size_t	caparacity = 0,
		max_caparacity = 0;

};

void StackConstructor (Stack* stk);

void StackDestructor  (Stack* stk);

void StackPush (Stack stk, stk_type elem);

stk_type StackPop (Stack stk);