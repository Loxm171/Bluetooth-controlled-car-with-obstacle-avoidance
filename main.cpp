#include "mbed.h"
#include "ultrasonic.h"

Serial pc(USBTX, USBRX);
Serial blue(D5, D4);

char c;
int Dis;

PwmOut ENA(D9);
PwmOut IN1(D10);
PwmOut IN2(A1);
PwmOut IN3(A2);
PwmOut IN4(A5);
PwmOut ENB(D6);
PwmOut buzzer(D3);

void forward(double v)
{
    ENA=ENB=1;
    IN1=v;
    IN2=0;
    IN3=v;
    IN4=0;
}
void reverse(double v)
{
    ENA=ENB=1;
    IN1=0;
    IN2=v;
    IN3=0;
    IN4=v;
}
void tleft()
{
    ENA=ENB=1;
    IN1=0;
    IN2=0;
    IN3=1;
    IN4=0;
}
void tright()
{
    ENA=ENB=1;
    IN1=1;
    IN2=0;
    IN3=0;
    IN4=0;
}
void circle()
{
    ENA=ENB=1;
    IN1=1;
    IN2=0;
    IN3=0;
    IN4=1;
}
void breakk()
{
    ENA=ENB=1;
    IN1=IN2=IN3=IN4=0;
}

void dist(int distance)
{

    Dis=distance;
    if(c=='c') 
        printf("Distance = %.1lf cm\r\n", distance*1.0/10);
    
    
    //wait_us(1000000);
}
ultrasonic mu(A6, D12, .1, 1, &dist); 

void sound()
{
    buzzer=1;
    buzzer.period(0.0005);
    wait_us(500000);
    buzzer=0;
}


int main()
{
	int i = 0;
    
    pc.baud(9600);                     
    pc.printf("Enter Command\n");   
    blue.baud(9600);                   
   
   
    mu.startUpdates();
    while(1)
    {
        char c;
        if(blue.readable()) c=blue.getc(),pc.putc(c);
        if(c=='w') 
        {
            forward(1.0);
            if(blue.readable()) c=blue.getc(),pc.putc(c);
            while(c!='b')
            {
                forward(1.0);
                if(blue.readable()) c=blue.getc(),pc.putc(c);
            }
        }
        if(c=='s')
        {
            reverse(1.0);
            if(blue.readable()) c=blue.getc(),pc.putc(c);
            while(c!='b')
            {
                reverse(1.0);
                if(blue.readable()) c=blue.getc(),pc.putc(c);
            }
        }
        if(c=='a')
        {
            tleft();
            if(blue.readable()) c=blue.getc(),pc.putc(c);
            while(c!='b')
            {
                tleft();
                if(blue.readable()) c=blue.getc(),pc.putc(c);
            }
        } 
        if(c=='d')
        {
            tright();
            if(blue.readable()) c=blue.getc(),pc.putc(c);
            while(c!='b')
            {
                tright();
                if(blue.readable()) c=blue.getc(),pc.putc(c);
            }
        }
        if(c=='z')
        {
            circle();
            if(blue.readable()) c=blue.getc(),pc.putc(c);
            while(c!='b')
            {
                circle();
                if(blue.readable()) c=blue.getc(),pc.putc(c);
            }
        }
        if(c=='b') breakk();
        mu.checkDistance(); 
        while(Dis<=50)
        {
            breakk();
            wait_us(500000);
            tright();
            sound();
            wait_us(500000);
            mu.checkDistance();
        }
        //sound=0;
    }
    return 0;
}
 