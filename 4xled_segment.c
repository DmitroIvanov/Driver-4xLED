//4xled.c
//19.05.2018 ������� ��� ������ � 4�LED-����������� ��� ������������ ������������
//********************************************************
#include <4xled.h>
//********************************************************
//���������� � ������� �������� ������� �������� �������� ��������
static volatile SEGMENT_t segment = SEG_A;
//�������� ������������ �������
SEGMENT_t getSegment(void)
{
	return segment;
}
//���������� ��������� �������
void setSegment(SEGMENT_t newSegment)
{
	segment = newSegment;
}

//********************************************************
void gpio_4xled_init(void)
{
//--------GPIO_Init---------------------------------
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOFEN;
	//PA0 - SEG_G (output)
	GPIOA->MODER |= GPIO_MODER_MODER0_0;
	//PA1 - SEG_C (output)
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	//PA2 - SEG_DP (output)
	GPIOA->MODER |= GPIO_MODER_MODER2_0;
	//PA3 - SEG_D (output)
	GPIOA->MODER |= GPIO_MODER_MODER3_0;
	//PA4 - SEG_E (output)
	GPIOA->MODER |= GPIO_MODER_MODER4_0;
	//PA5 - SEG_B (output)
	GPIOA->MODER |= GPIO_MODER_MODER5_0;	
	//PA6 - SEG_F (output)
	GPIOA->MODER |= GPIO_MODER_MODER6_0;
	//PA7 - SEG_A (output)
	GPIOA->MODER |= GPIO_MODER_MODER7_0;
	
	//PF1 - R1 (output)
	GPIOF->MODER |= GPIO_MODER_MODER1_0;
	//PF0 - R2 (output)
	GPIOF->MODER |= GPIO_MODER_MODER0_0;
	//PA10 - R3 (output)
	GPIOA->MODER |= GPIO_MODER_MODER10_0;
	//PA9 - R4 (output)
	GPIOA->MODER |= GPIO_MODER_MODER9_0;
	
//-----�������� �������� ��� - ��� ����------------------------------
	R1_OFF; R2_OFF; R3_OFF; R4_OFF;
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
//*******************************************************************
//������� ���������� ���������� ����������
void display_off()//�������� ��� ��������
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_A()//��� �������� �
{
	SEG_A_ON; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;	
}
void display_on_B()//��� �������� B
{
	SEG_A_OFF; SEG_B_ON; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_C()//��� �������� C
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_D()//��� �������� D
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_ON; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_E()//��� �������� E
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_ON; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_F()//��� �������� F
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_ON; SEG_G_OFF; SEG_DP_OFF;
}
void display_on_G()//��� �������� G
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
}
void display_on_DP()//��� �������� DP
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_ON;
}

//*******************************************************************
//����� ������� ��������� ���������� ����� (uint16_t num) �� �������
void razradCalculate(uint16_t num, uint8_t *razradDigits)
{
		if (num >9999) {num = 0;} //���������� ��������� �� ������������(uint16_t num_���=65535)
		uint8_t razr = 0;//�������� ��������
		//--- ������� �� ������� � ������� ���������� ----
		while(num >= 1000)
		{
			num -= 1000;
			razr++;//�������� ����� 4 �������
		}
		razradDigits[3] = razr;
		razr =0;		
		
		while(num >= 100)
		{
			num -= 100;
			razr++;//�������� ����� 3 �������
		}
		razradDigits[2] = razr;
		razr = 0;

		while(num >= 10)
		{
			num -= 10;
			razr++;//�������� ����� 2 �������
		}
		razradDigits[1] = razr;
		razr = 0;

		razr = num;
		razradDigits[0] = razr;
}
//******************************************************************
//���������� �������� ���������� (��� �������� ����������)
//��� ���� �� 0 �� 9
//-----------------------------------------------------------
void setRazradForSegmentA (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==4)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� �
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_A();//��������� ������� �
}
void setRazradForSegmentB (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==5 || razradDigits[i]==6)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� B
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_B();//��������� ������� B
}
void setRazradForSegmentC (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==2)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� C
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_C();//��������� ������� C
}
void setRazradForSegmentD (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==4 || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� D
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_D();//��������� ������� D
}
void setRazradForSegmentE (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==0 || razradDigits[i]==2 || razradDigits[i]==6 || razradDigits[i]==8)
		{
			razradFlag[i] = 1;
		}
		else {razradFlag[i] = 0;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� E
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_E();//��������� ������� E
}
void setRazradForSegmentF (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==1 || razradDigits[i]==2  || razradDigits[i]==3 || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� F
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_F();//��������� ������� F
}
void setRazradForSegmentG (uint8_t *razradDigits)
{
	uint8_t razradFlag[4];//���� ��� i-�� �������
	int i;
	for(i=0; i<4; i++)
	{
		if(razradDigits[i]==0 || razradDigits[i]==1  || razradDigits[i]==7)
		{
			razradFlag[i] = 0;
		}
		else {razradFlag[i] = 1;}
	}
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� G
	if(razradFlag[0] == 1) {R1_ON;}
	else {R1_OFF;}
	if(razradFlag[1] == 1) {R2_ON;}
	else {R2_OFF;}
	if(razradFlag[2] == 1) {R3_ON;}
	else {R3_OFF;}
	if(razradFlag[3] == 1) {R4_ON;}
	else {R4_OFF;}
	display_on_G();//��������� ������� G
}
void setRazradForSegmentDP (uint8_t point)
{
	display_off();//�������� ��������� ����� ������ ����������
	//��� ������� ��� �������� DP
	if(point == 1) 		{R1_ON;   R2_OFF;  R3_OFF;  R4_OFF;}//���������� ����� � 1-� �������(�������)
	else if(point == 2) {R1_OFF;  R2_ON;   R3_OFF;  R4_OFF;}//���������� ����� �� 2-� �������
	else if(point == 3) {R1_OFF;  R2_OFF;  R3_ON;   R4_OFF;}//���������� ����� � 3-� �������
	else if(point == 4) {R1_OFF;  R2_OFF;  R3_OFF;  R4_ON;}//���������� ����� � 4-� �������
	display_on_DP();//��������� ������� DP
}
//******************************************************************
//--------������������ ����������---------------------
//������ ����� ������� ����������� 1� ������� ���� �������� ����������.
//����� ������� ������� 8-� ��� ��� �� ��������� ��� �����(�� �������� �� ����������� ����������)
void display(uint8_t *razradDigits)
{//� ������� razradDigits[4] - �������� �������� �������� ����������.
		switch (getSegment())
		{
			        case SEG_A:
						{
							setRazradForSegmentA (razradDigits);//��� ������� �������� � & ��������� ������� �
							setSegment(SEG_B);
							break;
						}
					case SEG_B:
						{
							setRazradForSegmentB (razradDigits);//��� ������� �������� B & ��������� ������� B
							setSegment(SEG_C);
							break;
						}
					case SEG_C:
						{
							setRazradForSegmentC (razradDigits);//��� ������� �������� C & ��������� ������� C
							setSegment(SEG_D);
							break;
						}
					case SEG_D:
						{
							setRazradForSegmentD (razradDigits);//��� ������� �������� D
							setSegment(SEG_E);
							break;
						}
					case SEG_E:
						{
							setRazradForSegmentE (razradDigits);//��� ������� �������� E
							setSegment(SEG_F);
							break;
						}
					case SEG_F:
						{
							setRazradForSegmentF (razradDigits);//��� ������� �������� F
							setSegment(SEG_G);
							break;
						}
					case SEG_G:
						{
							setRazradForSegmentG (razradDigits);//��� ������� �������� G
							setSegment(SEG_DP);
							break;
						}
					case SEG_DP:
						{
							setRazradForSegmentDP (3);//��� ������� �������� DP
							setSegment(SEG_A);
							break;
						}
		}
}
//******************************************************************
