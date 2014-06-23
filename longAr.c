//longArithmetic
// уменьшаемое[1] знак[2] вычитаемое[3] результат[4] бинарный[5] модуль[6]

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

class cur_new
{
	public:
	int flag;
	long int lenth;
	short int *mem;

	cur_new();
    ~cur_new();
};

int main(int argc, char* argv[])
{
	//system("clear");
	cur_new a, b, mod;
	long int maxlen, i;
	FILE *fp_a = NULL, *fp_b = NULL, *fp_mod = NULL;

//открываем файлы
	fp_a = fopen(argv[1], "r");
	fp_b = fopen(argv[3], "r");
	if(argv[6] != NULL)
	{
	  fp_mod = fopen(argv[6], "r");
	}
//если файл пуст, то ошибка
	if(fp_a == NULL || fp_b == NULL)
	{
		printf("ERROR");
		return 0;
	}
//проверяем на отрицательность
  if(fgetc(fp_a) == '-') 
  {
    a.flag = 1;
  }
	if(fgetc(fp_b) == '-') 
	{
	  b.flag = 1;
	}
//считаем длинну
	fseek(fp_a, 0, SEEK_END);
	a.lenth = ftell(fp_a) - 1 - a.flag;
	fseek(fp_a, 0, SEEK_SET);

	fseek(fp_b, 0, SEEK_END);
	b.lenth = ftell(fp_b) - 1 - b.flag;
	fseek(fp_b, 0, SEEK_SET);

	mod.lenth = 2147483647;
	if(fp_mod != NULL)
	{
		fseek(fp_mod, 0, SEEK_END);
		mod.lenth = ftell(fp_mod) - 1;
		fseek(fp_mod, 0, SEEK_SET);
	}
//находим максимальную длинну
	if(a.lenth >= b.lenth)
	{
	  maxlen = a.lenth;
  }
	else 
	{
	  maxlen = b.lenth;
  }
//выделяем память под числа
	a.mem = (short *) calloc(maxlen+2, sizeof(short));
	b.mem = (short *) calloc(maxlen+2, sizeof(short));
	if(fp_mod != NULL)
	{
	  mod.mem = (short *) calloc(mod.lenth + 1, sizeof(short));
	}
//ошибка выделения памяти
	if(a.mem == NULL || b.mem == NULL)
	{
		printf("ERROR");
		return 0;
	}
//записываем числа в массив
//это палево! надо исправлять
	int b5 = 48;
	if(argv[5] != NULL && strcmp(argv[5], "-b") == 0)
	{
	  b5 = 0;
	}
	fseek(fp_a, a.flag, SEEK_SET);
	fseek(fp_b, b.flag, SEEK_SET);
	for(i = a.lenth - 1; i >= 0; i--)
	{
	  a.mem[i] = fgetc(fp_a) - b5;
	}
	for(i = b.lenth - 1; i >= 0; i--)
	{
	  b.mem[i] = fgetc(fp_b) - b5;
	}
	if(fp_mod != NULL)
	{
	  for(i = mod.lenth - 1; i >= 0; i--)
	  {
	    mod.mem[i] = fgetc(fp_c) - b5;
	  }
	}

	fclose(fp_a);
	fclose(fp_b);
	if(fp_mod != NULL)
	{
		fclose(fp_mod);
	}
//выбераем операцию
//сложение и вычитание
	if(strcmp(argv[2],"+") == 0 || strcmp(argv[2],"-") == 0)
	{
		if(strcmp(argv[2],"-") == 0)
		{
		  b.flag = (b.flag + 1) % 2;
		}
		a.flag = a_add(a, b, maxlen);//change name!
		a.lenth = maxlen;
		s_write(a, argv[5], "+", argv[4]);//change name!
	}
//умножение
	if(strcmp(argv[2], "x") == 0)
	{
		cur_new rez;
		if((a.flag + b.flag) == 1)
		{
		  rez.flag = 1;
		}
		else 
		{
		  rez.flag = 0;
		}

		rez.mem = (short *) calloc(a.lenth + b.lenth + 1, sizeof(short));
		rez.lenth = a.lenth + b.lenth;
		a_mul(rez, a, b);//change name!
		s_write(rez, argv[5], "x", argv[4]);//change name!
	}
//деление
	if(strcmp(argv[2],"/") == 0)
	{
		cur_new rez;
		if((a.flag + b.flag) == 1) 
		{
		  rez.flag = 1;
		}
		else 
		{
		  rez.flag = 0;
		}

		rez.mem = (short *) calloc(maxlen+1, sizeof(short));
		rez.lenth = a_div(rez, a, b, maxlen);//change name!
		s_write(rez, argv[5], "/", argv[4]);//change name!
	}
//деление с остатком
	if(strcmp(argv[2],"%") == 0)
	{
		a.flag = 0;
		a_mod(a, b, maxlen);//change name!
		s_write(a, argv[5], "%", argv[4]);//change name!
	}
//возведение длинного числа в степень другого длинного числа
	if(strcmp(argv[2], "^") == 0)
	{
	  cur_new rez;
    if(a.flag == 1 && (b.mem[0] % 2) == 1)
    {
      rez.flag = 1;
    }
    else 
    {
      rez.flag = 0;
    }
    if(a.lenth == 1 && a.mem[0] == 0)
    {
      a.mem[0] = 1;
      a.flag = 0;
      s_write(a, argv[5], "^", argv[4]);//change name!
    }
    rez.mem = (short *) calloc(2*mod.lenth + 2, sizeof(short));
		a_pow(rez, a, b, mod);//change name!
    s_write(rez, argv[5], "^", argv[4]);//change name!
	}
	printf("\nOperation complete\n");
	return 0;
}
//конструктор
cur_new::cur_new()
{
	lenth = 0;
	flag = 0;
	mem  = NULL;
}
//деструктор
cur_new::~cur_new()
{
	free(mem);
}
