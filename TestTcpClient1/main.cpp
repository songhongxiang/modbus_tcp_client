#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include <iostream>
#include "modbus.h"


#define LOOP 1 //循环次数
#define SERVER_ID	1	//从端设备地址
#define ADDRESS_START 0  //测试寄存器起始地址
#define ADDRESS_END		99//测试寄存器结束地址



using namespace std;

int main(void)
{
	modbus_t *ctx;
	int rc;
	int nb_fail;
	int nb_loop;
	int addr;
	int nb=10;

	uint16_t tab_reg[20];

	/*TCP*/
	ctx = modbus_new_tcp("192.168.191.1",502);	//创建TCP类型的容器
	modbus_set_debug(ctx, TRUE);				//设置debug模式

	if (modbus_connect(ctx) == -1)
	{
		fprintf(stderr, "Connection failed:%d\n", modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}

	rc = modbus_read_registers(ctx, 0, nb, tab_reg);
	if (rc == -1)
	{
		fprintf(stderr, "%s\n", modbus_strerror(errno));
		return -1;
	}

	for (int i = 0; i < nb; i++)
	{
		printf("reg[%d]=%d \n", i, tab_reg[i]);
	}






	modbus_close(ctx);
	modbus_free(ctx);

	return 0;
}