//4xled.c
//19.05.2018 ������� ��� ������ � 4 ��������� LED-����������� (Vmetr=0...30V)
//********************************************************
#include <4xled.h>

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
//������� ���������� ��������� ����������
void display_off()//�������� ��� �������
{
	R1_OFF; R2_OFF; R3_OFF; R4_OFF;
}
void display_on_1()//��� 1� ������
{
	R1_ON; R2_OFF; R3_OFF; R4_OFF;
}
void display_on_2()//��� 2� ������
{
	R1_OFF; R2_ON; R3_OFF; R4_OFF;
}
void display_on_3()//��� 3� ������
{
	R1_OFF; R2_OFF; R3_ON; R4_OFF;
}
void display_on_4()//��� 4� ������
{
	R1_OFF; R2_OFF; R3_OFF; R4_ON;
}
void set_zero()//��� ������ �����
{
	SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
}
//*******************************************************************
//���������� �������� ���������� (��� �������� ����������)
//-----------------------------------------------------------
void set_segment (uint8_t segment_simvol)
{
	//uint8_t segment_simvol - �����, ������� ����� ������� �� ��������� (������ ����� 8)
	switch (segment_simvol)
	{
		case 0: //����� 0
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 1: //����� 1
			{
				SEG_A_OFF; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 2: //����� 2
			{
				SEG_A_ON; SEG_B_ON; SEG_C_OFF; SEG_D_ON; SEG_E_ON; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 3: //����� 3
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 4: //����� 4
			{
				SEG_A_OFF; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 5: //����� 5
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 6: //����� 6
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 7: //����� 7
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_OFF; SEG_DP_OFF;
				break;
			}
		case 8: //����� 8
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 9: //����� 9
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_ON; SEG_E_OFF; SEG_F_ON; SEG_G_ON; SEG_DP_OFF;
				break;
			}
		case 10: //����� �
			{
				SEG_A_ON; SEG_B_ON; SEG_C_ON; SEG_D_OFF; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_ON;
				break;
			}
		case 11: //����� b
			{
				SEG_A_OFF; SEG_B_OFF; SEG_C_ON; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_ON; SEG_DP_ON;
				break;
			}
		case 12: //����� C
			{
				SEG_A_ON; SEG_B_OFF; SEG_C_OFF; SEG_D_ON; SEG_E_ON; SEG_F_ON; SEG_G_OFF; SEG_DP_ON;
				break;
			}
		default://����� � ��� �����
		    {
			    SEG_A_OFF; SEG_B_OFF; SEG_C_OFF; SEG_D_OFF; SEG_E_OFF; SEG_F_OFF; SEG_G_ON; SEG_DP_OFF;
		    }
	}
}
//******************************************************************
//����� ������� ��������� ���������� ����� (uint16_t num) �� ������� ��� ������ �� ���������
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
//--------������������ ����������---------------------
//������ ����� ������� ����������� 1� ������ ����������.
//����� ������� ������� 4-�� ���� ��� �� ��������� ��� ����� (4 �������)
void display(uint8_t *razradDigits)
{   	
	//� ������� razradDigits[4] - �������� �������� �������� ����������.
		static uint8_t razrad_num=0;//������� ��������(�������������) �������
		uint8_t segment_simvol;
		switch (razrad_num)
		{
			        case 0:
						{
							segment_simvol = razradDigits[0];
							display_off();//�������� ��������� ����� ������ ����������
							set_segment (segment_simvol);//��� �������� ������� 1
							display_on_1();//��������� 1-� ������
							break;
						}
					case 1:
						{
							segment_simvol = razradDigits[1];
							display_off();//�������� ��������� ����� ������ ����������
							set_segment (segment_simvol);//��� �������� ������� 2
							display_on_2();//��������� 2-� ������
							break;
						}
					case 2:
						{
							segment_simvol = razradDigits[2];
							display_off();
							set_segment (segment_simvol);
							SEG_DP_ON;//�������� ���������� ����� ����� 2�� �������							
							display_on_3();
							break;
						}
					case 3:
						{
							segment_simvol = razradDigits[3];
							if (segment_simvol == 0) {//����� �� �������� ����
								set_zero();
							}else {
								display_off();
								set_segment (segment_simvol);
							}
							display_on_4();						
							break;
						}
		}
			    //������� - ����� ������ �����������
				if (razrad_num == 3) {razrad_num = 0;}
			   	else {razrad_num++;}
}
//******************************************************************
