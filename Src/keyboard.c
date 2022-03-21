#include "main.h"

extern TIM_HandleTypeDef htim6;
extern uint8_t tim6_counter;

int delay_for_pressed_button = 250000;
char total_number [4] = {' ',' ',' ',' '};
int count = 0;
char comparsion1 = '0';
char comparison = ' ' ;
//total_number[0]=comparison;

__STATIC_INLINE void DelayMicro(uint32_t __IO micros)
{
  micros *=(SystemCoreClock/1000000)/8;
  while(micros--);
}

void CheckFirstButtonPressed ()
{
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_SET);
	
	DelayMicro(delay_for_pressed_button/2);
	
	while(1)
	{
		
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1 || HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==1
			|| HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1 || HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==1)
		{

		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
		break;
		}	
	}	
}

void Show_total_number (char *pressed_button) //*pressed_button - ��� �������� �����
{
	//������������� ����� � �� ��� ����� ��������
	CS_ACTIVE();
	TFT9341_SetTextColor(TFT9341_WHITE); //���������� ���������� ����� � �� ��� ����� ��� ������� 
	TFT9341_SetBackColor(TFT9341_BLACK);
	TFT9341_SetFont(&Font48);
	
	
	//���������, ��� �������� �������� �������� ����� ���� ����
	if (count < 0)
	{
		count = 0;
	}
	
	//��������� ������ � ������ ������ "0" � ������ ��������
	if (count == 0 && *pressed_button == comparsion1)
	{
		TFT9341_DrawChar(100,135,' ');
		count--; // ������ ��� �����	
	}
	
	if (count < 4 )//&& count>=0)
	{
		total_number[count] = *pressed_button; //����������� �������� ������� �������� 
		
		for (int i=0;i<=count;i++)
		{
		//���������� �� ����� ������ ������, � �� ������, ����� �� �������� �����
		TFT9341_DrawChar(100+i*30,135,*&total_number[i]); //���������� ������� ������, �� ������ ������ ��������� ���������� ��������� ����� �� ���������	
		}
		
		for (int j=count+1;j<4;j++)//���, ��� ���� �� Count - �������
		{
			TFT9341_String(100+j*30,135," ");
		}
	}
	else if(count >= 4)
	{
	count = 3;
	}	
	
	count++;
	//DelayMicro(delay_for_pressed_button);
}


void keyboard_default_waiting()
{
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4, GPIO_PIN_SET);
	
	//������ ������� (����� ������)
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1)   //112
	{
		Draw_c112call_page ();
		count=4; //����� ������ ���� ������� ��������	
		DelayMicro(600000);     //��� ����� ����� "�����"
		
		CS_ACTIVE();
		
		TFT9341_SetTextColor(TFT9341_RED); //������ ����� � �� ��� �������� ������
		TFT9341_SetBackColor(TFT9341_WHITE);
		TFT9341_SetFont(&Font24);
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_SET);//���������� ��� ��� �������� ������� �
		while (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)!=1) 
			//���� �� ����� ������ ������ "�"
		{
		TFT9341_String(220,137,".");		
		DelayMicro(600000);
		//TFT9341_String(220,137," ");
		TFT9341_String(227,137,".");
		DelayMicro(600000);	
		//TFT9341_String(227,137," ");
		TFT9341_String(234,137,".");
		DelayMicro(600000);
		TFT9341_String(220,137," ");
		TFT9341_String(227,137," ");
		TFT9341_String(234,137," ");
		DelayMicro(600000);
		}
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
		
		DelayMicro(delay_for_pressed_button);		
	}
	
	if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==1)  //����� ����������
	{
		Draw_concierge_page ();	
		count=4; //����� ������ ���� ������� ��������		
		DelayMicro(delay_for_pressed_button);		
	}
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1)   //����� ���������
	{
		Draw_concierge_page ();		
		count=4; //����� ������ ���� ������� ��������
		DelayMicro(delay_for_pressed_button);
	}
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==1)  //����� ���
	{
		//Draw_callODS_page ();	
		Draw_concierge_page ();	
		count=4; //����� ������ ���� ������� ��������
		DelayMicro(delay_for_pressed_button);
	}
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4, GPIO_PIN_RESET);
	
	//������ ������� ������
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3, GPIO_PIN_SET);
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1)
	{
		Show_total_number ("3");	
		DelayMicro(delay_for_pressed_button);
	}
	if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==1)
	{
		Show_total_number ("6");		
		DelayMicro(delay_for_pressed_button);
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1)
	{
		Show_total_number ("9");		
		DelayMicro(delay_for_pressed_button);
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==1)  //   ����� ��������
	{
		if (total_number[0]!=comparison)
		{
		Draw_call_page();
		CS_ACTIVE();
		
		TFT9341_SetTextColor(TFT9341_WHITE); //������ ����� � �� ��� �������� ������
		TFT9341_SetBackColor(TFT9341_BLACK);
		TFT9341_SetFont(&Font24);
		
		for (int i=0;i<count;i++)
		{
		//���������� �� ����� ������ ������, � �� ������, ����� �� �������� �����
		TFT9341_DrawChar(215+i*15,168,*&total_number[i]);//������� ����� ��������
		}
		
		count = 4; //������ ������ ���� ������� ��������
		//DelayMicro(delay_for_pressed_button);
		
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_SET);//���������� ��� ��� �������� ������� �
		while (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)!=1) 
			//���� �� ����� ������ ������ "�"
			{
		DelayMicro(600000);     //��� ����� ����� "�����"
		TFT9341_String(180,2,".");		
		DelayMicro(600000);
		TFT9341_String(180,2," ");
		TFT9341_String(187,2,".");
		DelayMicro(600000);	
		TFT9341_String(187,2," ");
		TFT9341_String(194,2,".");
		DelayMicro(600000);
		TFT9341_String(194,2," ");
			}
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
		}
	}
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3, GPIO_PIN_RESET);
	
	
	//������ ������� ������
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET);
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1)
	{
		Show_total_number ("2");		
		DelayMicro(delay_for_pressed_button);
			
	}
	if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==1)
	{
		Show_total_number ("5");		
		DelayMicro(delay_for_pressed_button);
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1)
	{
		Show_total_number ("8");		
		DelayMicro(delay_for_pressed_button);	
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==1)
	{
		Show_total_number ("0");		
		DelayMicro(delay_for_pressed_button);
	}
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET);
	
	
	//��������� ������� (������ �����)
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_SET);
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0)==1)
	{
		Show_total_number ("1");		
		DelayMicro(delay_for_pressed_button);	
			
	}
	if (HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==1)
	{
		Show_total_number ("4");		
		DelayMicro(delay_for_pressed_button);
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1)
	{
		Show_total_number ("7");		
		DelayMicro(delay_for_pressed_button);		
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_8)==1)  // ������   "C" 
	{	
		Draw_main_page();
		DelayMicro(delay_for_pressed_button);
		count=0;
		total_number [0]= ' ';
		total_number [1]= ' ';
		total_number [2]= ' ';
		total_number [3]= ' ';
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
		keyboard_default_waiting();
		
		
	}
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_RESET);
	
}
