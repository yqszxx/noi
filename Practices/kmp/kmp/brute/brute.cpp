#include <stdio.h>
#include <string.h>
int substring(char*str,char*str1);//函数原型
char str[30000];
char str1[30000];
int main(void)
{
	freopen("../data.in", "r", stdin);
	gets(str);//输入的原字符串
	gets(str1);//输入的字符串中的子串
	printf("%d\n", substring(str,str1));
	return 0;
}

int substring(char *str,char *str1)
{
	int x=0;
	char *p;//任意附个初始值
	do{
		p = strstr(str, str1);//1.p指针指向strstr的返回值。3.再一次循环到这里函数的参数发生变化，p重新指向strstr返回值，如此循环。
		if (p != NULL) {
			str = p + 1;//2.str同样指向strstr返回值p的下一个地址。
			x = x + 1;
		}
	} while(p != NULL);
	return x;
}

