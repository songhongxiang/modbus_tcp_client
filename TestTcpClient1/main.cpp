#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include <iostream>
#include "modbus.h"


#define LOOP 1 //ѭ������
#define SERVER_ID	1	//�Ӷ��豸��ַ
#define ADDRESS_START 0  //���ԼĴ�����ʼ��ַ
#define ADDRESS_END		99//���ԼĴ���������ַ



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
	ctx = modbus_new_tcp("192.168.191.1",502);	//����TCP���͵�����
	modbus_set_debug(ctx, TRUE);				//����debugģʽ

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