//陀螺仪数值转化
#include "gyro.h"
#include "sys.h"
#include "led.h"
#include "usart.h "

extern int TLY ,MODE;
extern double X,Y,Z;
int ANY,ANX,ANZ;
float z1,z2,z3,pout,P,I,D,En = 0,En_1 =0,En_2=0;



float RANGE (float a)
{
	if(a>=360)
		a=a-360;
	if(a<0)
		a=360+a;
	return a;
}

void ANGLEY()
{	
	static double nowy,agoy = 0,y=0;
	nowy = Y ;
	if( agoy >= 0 && agoy < 180)
	{
		if( nowy >= agoy && nowy < agoy +180)
		   y =  nowy - agoy;
		else if(nowy >= agoy +180 && nowy < 360) 
			 y = -(360 - nowy) - agoy;
		else 
			y = nowy - agoy;
	}
	else 
	{
		if( nowy > agoy - 180 && nowy <= agoy )
		  y = nowy - agoy ;
		else if ( nowy <= agoy - 180 && agoy > 0 )
		  y = 360 - agoy + nowy;
		else 
			y = nowy - agoy;
	}
	if( y > 0.8 )
		ANY = 2;
	else if ( y < -0.8 )
		ANY = 0;
	else 
		ANY = 1;
	agoy = nowy ;
}

void ANGLEX()
{	
	static double nowx,agox = 0,x=0;
	nowx = X ;
	if( agox >= 0 && agox < 180)
	{
		if( nowx >= agox && nowx < agox +180)
		   x =  nowx - agox;
		else if(nowx >= agox +180 && nowx < 360) 
			 x = -(360 - nowx) - agox;
		else 
			 x = nowx - agox;
	}
	else 
	{
		if( nowx > agox - 180 && nowx <= agox )
		  x = nowx - agox ;
		else if ( nowx <= agox - 180 && agox > 0 )
		  x = 360 - agox + nowx;
		else 
			x = nowx - agox;
	}
	if( x > 0.8 )
		ANX = 2;
	else if ( x < -0.8 )
		ANX = 0;
	else 
		ANX = 1;
	agox = nowx ;
}
void ANGLEZ()
{	
	static double nowz,agoz = 0,z=0;
	nowz = Z ;
	if( agoz >= 0 && agoz < 180)
	{
		if( nowz >= agoz && nowz < agoz +180)
		   z =  nowz - agoz;
		else if(nowz >= agoz +180 && nowz < 360) 
			 z = -(360 - nowz) - agoz;
		else 
			z = nowz - agoz;
	}
	else 
	{
		if( nowz > agoz - 180 && nowz <= agoz )
		  z = nowz - agoz ;
		else if ( nowz <= agoz - 180 && agoz > 0 )
		  z = 360 - agoz + nowz;
		else 
			z = nowz - agoz;
	}
	if( z > 0.08 )
		ANZ = 2;
	else if ( z < -0.08 )
		ANZ = 0;
	else 
		ANZ = 1;
	agoz = nowz ;
}




void anpid1 ( float yvding , float p ,float i,float d )
{
//	static float  p = 1.8  , i = 0.008, d = 50;
//		static float  p = 2.3  , i = 0.001, d = 29;//2.5 0.002 29
//	static float  p = 1.3  , i = 0.0, d = 0 , I = 0 , D = 0 ;
	float dk1,dk2;
	if( TLY < 5 )
		return ;
	else
	{
		TLY = 0;
		En = anerr1(yvding);
		dk1 = En - En_1;
		dk2 = En-2*En_1+En_2;
	  P = p*dk1;
	  I = (p*5)/i;
		I = I*En;
		D = ( p*d )/5;
		D = D*dk2;
		pout = P +I+ D;
	if ( pout >= 250 )
		pout = 250 ;
	if( pout <= -250 )
		pout = -250;
	if( pout <=40 && pout >=0 )
		pout = 40;
	if( pout >= -40 && pout<=0 )
		pout = -40;
  }
}

void anpid2 ( float yvding , float p ,float i,float d )
{
//	static float  p = 1.8  , i = 0.008, d = 50;
//		static float  p = 2.3  , i = 0.001, d = 29;//2.5 0.002 29
//	static float  p = 1.3  , i = 0.0, d = 0 , I = 0 , D = 0 ;
		if( TLY < 15 )
		return ;
	else
	{
	I = I + anerr2(yvding);
	pout = p * anerr2(yvding) + i * I + d * ( anerr2(yvding) - D );
	D = anerr2(yvding);
	if ( pout >= 450 )
		pout = 450 ;
	if ( pout <= -450 )
		pout = -450 ;
	if ( Z == yvding )
		I = 0;
	TLY = 0;
  }
}

void xuanzhuan( float yvding )
{
	anpid1 ( yvding ,2.8,120,4);

//		anpid1 ( yvding ,200,5000,4);
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 30;
		else 
			MODE = 31;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		  MODE = 31;
		else 
		  MODE = 30;
	}
}

void xuanzhuan2( float yvding )
{
//		anpid ( yvding ,2.3,0.003,27);
	anpid1 ( yvding ,3.95,0.0046,30);
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 30;
		else 
			MODE = 31;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		  MODE = 31;
		else 
		  MODE = 30;
	}
}

//void tlPID ( float yvding )
//{
////	static float  p = 10  , i = 0.0005, d = 120  ;
//	static float  p = 10  , i = 0.0005, d = 120  ;
//	if( TLY < 10 )
//		return;
//	else
//	{
//	I = I + anerr(yvding);
//	pout = p * anerr(yvding) + i * I + d * ( anerr(yvding) - D );
//	D = anerr(yvding);
//	if ( pout >= 450 )
//		pout = 450 ;
//	if ( Z == yvding )
//		D = 0;
//	TLY = 0;
//  }  
//}
void tlxj( float yvding )//880
{
//		anpid2 ( yvding ,10,0.0005,120);
	anpid2 ( yvding ,10,0.0005,120);
//		anpid1 ( yvding ,30,46,0);
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 32;
		else 
			MODE = 33;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		 MODE = 33;
		else 
		 MODE = 32;
	}
	
}

//void qiaoPID ( float yvding )
//{
//	float  p = 2  , i = 0, d = 20  ;
//	
//	if( TLY < 10 )
//		return;
//	else
//	{
//	I = I + anerr(yvding);
//	pout = p * anerr(yvding) + i * I + d * ( anerr(yvding) - D );
//	D = anerr(yvding);
//	if ( pout >= 200 )
//		pout = 200 ;
//	if ( Z == yvding )
//		D = 0;
//	TLY = 0;
//  }
//  
//}
void xqiao( float yvding )//920
{
		anpid2 ( yvding ,2,0,20);
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 34;
		else 
			MODE = 35;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		  MODE = 35;
		else 
		  MODE = 34;
	}
	
}

void zaxj( float yvding )//930
{
//		anpid ( yvding ,5,0.0005,20);
	anpid2 ( yvding ,0.5,0,20 );
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 36;
		else 
			MODE = 37;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		  MODE = 37;
		else 
		  MODE = 36;
	}
	
}
void lkxj( float yvding )//960
{
//		anpid ( yvding ,5,0.0005,20);
	anpid2 ( yvding ,10,0.0001,120 );
	if( yvding >= 0 && yvding < 180)
	{
		if( Z >= yvding && Z < yvding +180)
		  MODE = 36;
		else 
			MODE = 37;
	}
	else 
	{
		if( Z > yvding - 180 && Z <= yvding)
		  MODE = 37;
		else 
		  MODE = 36;
	}
	
}