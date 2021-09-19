#include "step.h"
#include "led.h"
#include "pid.h"
#include "gyro.h"
#include "timer.h"
#include "usart.h"

extern double X,Y,Z;
int process=0 ,delay=0,q,mode1,mode2;
float H,keep,keepy,keepz;
extern int ANY,ANX,ANZ,MODE,mangzou_bz,safe,step,jilu1,jilu2,jilu3,tlpid,temp[8],i[8],kaiguan;
extern float z1,z2,z3,pout,I,D;
void chujia()
{
	switch(process)
	{
		case 0:
			MODE = 5;
		  if( Y >= 339 && Y<= 345 )
			{
				process ++;
			}
		  break;
		case 1:
			MODE = 2;
		  if(ANY == 2)
				process = 2;
		  break;
		case 2:
			MODE = 2;
		  if ( Y <= 5 || Y >= 355 )
			{
			    process ++;
			}
		  break;
		case 3:
			MODE = 20;
		  if(( Y >= 357.5 || Y <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 4:
			  MODE = 3;
				jilu1 = 1;
				process = 0;
			  step++;		
	}
}
void qiao(void)
{
	switch(process)
	{
		case 0:
			wending(3,3);
		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8)
			{
				kaiguan = 0;
				tlpid = 0;
				jilu1 = 0;
				pout = 0 ;
				I=0;
				D=0;
				process++ ;
				if(z1 == 0)
					z1 = Z;
			}
		break;
		case 1:
			tlpid = 1;
      if ( SEL == 0 )
			{
        MODE = 7;
      }	
      else if ( SER == 0 )
			{
        MODE = 8;
      }
			else if( SEL == 1 && SER == 1)
			{
				xqiao(z1);
			}
      if (Y < 20 && Y >10)
			{
				process ++;
			}				
		  break;
		case 2:
			if ( SEL == 0 )
			{
        MODE = 7;
      }	
      else if ( SER == 0 )
			{
        MODE = 8;
      }
			else if( SEL == 1 && SER == 1)
			{
				tlxj(z1);
			}
			if( ANY == 0 )
			{
				process++;
			}
			break;
		case 3:
			if ( SEL == 0 )
			{
        MODE = 7;
      }	
      else if ( SER == 0 )
			{
        MODE = 8;
      }
			else if( SEL == 1 && SER == 1)
			{
				xqiao(z1);
			}
			if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 )
			{
				tlpid = 0;
				pout = 0 ;
				I=0;
				D=0;
				process++;
			}
			break;
		case 4:
			MODE = 10;
		delay++;
		if( delay == 10 )
		{
			delay = 0;
			process++;
		}
		break;
		case 5:
			MODE = 20;
		  if(( Y >= 357.5 || Y <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 6:
			MODE = 3;
			jilu1 = 1;
			process = 0;
			step++;	
    break;		
	}
}

void turn()
{
	switch(process)
	{
		case 0:
			wending(3,3);
		  if( SE3 == 0 )
			{		
				delay++;
				MODE = 10;
				if( delay == 8 )
				{
				kaiguan = 0;
					keepy = Y;
					delay = 0;
				  process++;
				}
			}
			break;
		case 1:
			wending(2,2);
		  if( Y<RANGE( keepy +15 ) && Y > RANGE( keepy +5 ) )
			{
				kaiguan = 0;
				tlpid = 0;
				pout = 0 ;
				I=0;
				D=0;
				keep = Z;
				process++;
			}
			break;
		case 2:
			MODE = 2;
		  if((Y<RANGE( keepy +35 )&&Y>RANGE( keepy +25 ))||OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8)
       process++;
      break;
    case 3:
			MODE = 4;
      if(Y>RANGE( keepy -2 )||Y<RANGE( keepy +2 ))
				process++;
			break;
		case 4:
			MODE = 4;
		  if ( OUTL == 0 || OUTR == 0)
			  process++ ;
       break;
			
		case 5:
			delay ++;
		  if( delay == 20 )
				{
					delay = 0;
				  process++;
				}
				break;
		case 6:
			MODE = 4;
		  if (SEL == 0 || SER == 0)
			  process = 9 ;
       break;
//    case 5:
//      delay ++ ;
//			  if( delay == 15 )
//				{
//					process ++ ;
//					delay = 0;
//				}
//      break;	
//    case	6:
//      if ( OUTL == 0 && OUTR == 0)
//					process ++;
//			break; 
//		case 7:
//      delay ++ ;
//			  if( delay == 15 )
//				{
//					process ++ ;
//					delay = 0;
//				}
//			break;
//		case 8:
//      if( SEL == 0 || SER == 0 )
//				{
//					process ++;
//				}
//			break;
    case 9:
      MODE = 10;
		  delay++;
      if( delay == 20 )
				{
					keep = RANGE( keep + 180 );
		  	if(((	keep + 2) <= 360) && (( keep - 2) >= 0))
					{
						mode1 = 1 ;
						mode2 = 0 ;
					}
					else 
					{
						mode1 = 0 ;
						mode2 = 1 ;
					}
					process ++ ;
					delay = 0 ;
				}
				break;
    case 10:
      tlpid = 1 ;
			  xuanzhuan(keep);
			  if(  mode1 == 1 && Z >=  ( keep - 2) && Z <= ( keep + 2))
				{
					delay++;
					if( delay ==50 )
					{
					 if(  Z >=  ( keep - 2) && Z <= ( keep + 2) )
					 {
						 delay = 0;
             process ++;
					 }
           else	
					 {
						 delay = 0;
              process = 10;		
					 }	
				 }					 
	      }
				if(  mode2 == 1 && (Z > RANGE ( keep - 2) || Z < RANGE ( keep + 2)))
		     {
					 delay++;
					 if( delay == 50 )
					 {
					  if(Z > RANGE ( keep - 2) || Z < RANGE ( keep + 2) )
					 {
						 delay = 0;
             process ++;
					 }
           else	
					 {
						 delay = 0;
              process = 10;
					 }
				 }					 
				}
				break;
		case 11:
			MODE = 10;
		  delay++;
		  if ( delay == 30 )
				{
					process ++ ;
					delay = 0 ;
				}
				break;
		case 12:
			MODE = 5;
			if(Y>RANGE( keepy -20)&&Y<RANGE( keepy -10 ))
			{
				for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
					tlpid = 0 ;
					process ++ ;
			}
			break;
		case 13:
			MODE = 2;
		  if ( Y <= RANGE( keepy + 5 ) || Y >= RANGE( keepy -5 ) )
			{
			    process ++;
			}
		  break;
		case 14:
			MODE = 10;
		  delay ++;
		  if( delay == 20 )
			{
				process ++;
		  delay = 0;
			}
			break;
		case 15:
			MODE = 20;
		  if(( Y >= 357 || Y <= 3) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 16:
			MODE = 3;
			jilu2 = 1;
			process = 0;
			step++;	
    break;			
}
}

void RIGHT2()
{
	switch(process)
	{
		case 0:
			wending(3,3);
		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) ))
    	{
				delay++;
				if( delay == 8 ) 
				{
					if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))))
				{
					jilu2 = 0;
					delay = 0;
			    kaiguan = 0;
		      process ++;
				}
				else 
				{
					delay = 0;
					process = 0;
				}
	     }
		 }
		  break;
		case 1:
			wending(2,2);
			if( OUTR == 0 )
			{
				kaiguan = 0;
				process++;
			}
			break;
		case 2:
			MODE = 10;
		  delay++;
		if( delay == 5 )
		{
			delay = 0;
			process ++;
		}
		break;
		case 3:
			MODE = 24;
		  if(OUTR == 0 )
			{
				process=5;
			}
			break;
//		case 4:
//			MODE = 24;
//		  if(OUTR == 1 )
//			{
//				process++;
//			}
//			break;
		case 5:
			MODE = 10;
		  delay++;
		if( delay == 5 )
		{
			delay = 0;
			process ++;
		}
		break;
		case 6:
			MODE = 12;
			if(OUT4 == 1 && OUT5 == 1 )
		  {
				process++;
			}
			break;
		case 7:
			MODE = 12;
		  if( OUT4 == 0 && OUT5 == 0  )
		  {
				process++;
			}
			break;
			case 8:
			MODE = 12;
			if( OUT4 == 1 && OUT5 == 1 )
		  {
				process++;
			}
			break;
		case 9:
			MODE = 12;
		  if( OUT4 == 0 || OUT5 == 0  )
		  {
				process++;
			}
			break;
		case 10:
			MODE = 10;
	    delay++;
				if( delay == 5 )
				{
					delay = 0;
				process ++;
				for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
				 }

			break;
		case 11:
			MODE = 20;
		  if(( Y >= 356 || Y <= 4 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
			process = 0;
			step++;	
		  }
			break;
	}
}


void zhangai()
{
	 switch(process)
	 {
		 case 0:
			 MODE = 22;
		   if( SEL == 0||SER == 0 )
			 {
				 for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
					 pid.OUT = 0 ;
					z3 = Z;
          process++;					 
			 }
			 break;
//		   if(Y<=15&&Y>= 5)
//			 {
//				  for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 process ++;
//			 }
//			 break;
		 case 1:
			 delay++;
		   tlpid  = 1;
		   if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 )
				 zaxj(z3);
			 else 
				 MODE = 22;
			 if(delay == 300)
			 {
				 delay = 0;
				 process = 0;
				 for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
				 step++;
       z3 = 0;
       pout = 0;
				I=0;
				D= 0;
				tlpid = 0;
				 }
			 break;
		 }
}

void danbian1()
{
	switch(process)
	{
		case 0:
			MODE = 22;
		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 )
			{
				MODE = 13;
			}
			else MODE = 21;
		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && (X < 356 && X > 340) && (Y > 5 && Y < 18))
			{
//        z1 = 180;				
				pout = 0;
			  I = 0;
			  D = 0;
				if(z2 == 0)
				{
					z2 = RANGE(z1 +180 -7);//7
				}
				else
					z2 = RANGE(z2-7);
				if(((	z2 + 2) <= 360) && (( z2 - 2) >= 0))
					{
						mode1 = 1 ;
						mode2 = 0 ;
					}
					else 
					{
						mode1 = 0 ;
						mode2 = 1 ;
					}
				process ++;
			}
		  break;
		
			
		case 1:
			
				if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SEL == 0 )
			{
        MODE = 14;
      }	
      else if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SER == 0 )
			{
				process ++;
        MODE = 15;
      }
			else if( SEL == 1 && SER == 1)
			{
				MODE = 13;
			}

			
		
//		  if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 )
//			{
//				process = 11;
//			}
		  break;
		case 2:
			 MODE = 5;
		   if( SER == 1)
				  process++;
			break;
	  case 3:
			MODE = 10;
		  delay ++;
		  if( delay == 10 )
			{
				process ++;
		    delay = 0;
			}
			break;
		case 4:
          MODE = 19;
		    if( SEL == 0 )
				{
					process++;
				}
			  if(( mode1 == 1 && Z >=  ( z2 - 2) && Z <= ( z2 + 2))&&SEL == 1)
				{
          process ++;						
	      }
				if ((mode2 == 1 && (Z > RANGE ( z2 - 2) || Z < RANGE ( z2 + 2)))&&SEL == 1)
		     {
		      process ++ ;

				}
				break; 

		case 5:
			MODE = 10;
			delay++;
		  if( delay == 10 )
			{
				delay = 0;
				process++;
			}
		  break;
		case 6:
						tlpid = 1;
			if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SEL == 0 )
			{
        MODE = 14;
      }	
      else if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SER == 0 )
			{
        MODE = 15;
      }
			else if( SEL == 1 && SER == 1)
			{
				xqiao(z2);
			}
			
			if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 && (X >356 || X <3)  )
			{
				pout = 0;
				I=0;
				D= 0;
				tlpid = 0;
				process ++;
			}
			break;
		case 7:
    MODE = 10;
		  delay ++;
		  if(delay ==20)
			{
				delay = 0;
				process ++;
			}
			break;			
//		case 8:
//			MODE = 20;
//		  delay ++;
//		  if( delay == 20 )
//			{
//				process ++;
//		  delay = 0;
//			}
//			break;
    			
		case 8:
			MODE = 20;
		  if(( Y >= 357 || Y <= 3 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 9:
			MODE = 10;
			process = 0;
		  z1 = 0;
			z2 = 0;
			pout = 0;
			I = 0;
		  D = 0;
		  jilu1 = 1;
			step++;	
    break;
			
			
	}
}

void ceshi()
{
	switch(process)
	{
		case 0:
			MODE = 2;
		  protect();
		if(( X >= 357.5 || X <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 1:
			MODE = 3;
		  protect();
		break;
	}
}

void xieqiao1()
{
	switch( process )
	{
		case 0:
			wending(3,3);
		if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8  )
		{
			tlpid = 0;
				pout = 0 ;
				I=0;
				D=0;
			kaiguan = 0;
			if(z2 == 0)
			{
				z2 = RANGE(z1 + 180+5);
			}
      else 
				z2 = RANGE ( z2 +5 );
			jilu2 = 0;
			process++ ;
		}
		break;
//	  case 1:
//			MODE = 20;
//		  delay ++;
//		  if( delay == 10 )
//			{
//				delay = 0; 
//				process ++ ;
//			}
//			break;
//		case 2:
//			if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SEL == 0 )
//			{
//        MODE= 17;
//      }	
//      else if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SER == 0 )
//			{
//        MODE = 16;
//      }
//			else if( SEL == 1 && SER == 1)
//			{
//				MODE = 18;
//			}
//			if(X > 10 && Y > 8)
//			{
//			  z2 = RANGE(z2+3);
//				process ++;
//			}
//			break;
//		case 3:
//			MODE = 10;
//			break;
		case 1:
			tlpid = 1;
//			if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SEL == 0 )
//			{
//        MODE = 16;
//      }	
//      else if ( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && SER == 0 )
//			{
//        MODE = 17;
//      }
//			else if( SEL == 1 && SER == 1)
//			{
				xqiao(z2);
//			}
			
		
		  if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 &&( X<3||X>357 ) )
			{ 
				tlpid = 0;
				process ++;
				pout = 0;
			  I = 0;
		  	D = 0;
			}
		  break;
		case 2:
			MODE = 10;
		  delay ++;
		  if(delay ==20)
			{
				delay = 0;
				process ++;
			}
			break;
//		case 4:
//			MODE = 20;
//		  delay ++;
//		  if(delay ==20)
//			{
//				delay = 0;
//				process ++;
//			}
//			break;
		case 3:
			MODE = 20;
		  if(( Y >= 357  || Y <= 3 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 4:
			MODE = 3;
			process = 0;
		  z1=z2=0;
			step++;	
    break;
	}}

void RIGHT()
{
	switch(process)
	{
		case 0:
			wending(3,3);
		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) ))
    	{
				delay++;
				if( delay == 8) 
				{
					if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))))
				{
					kaiguan = 0;
					tlpid = 0;
				pout = 0 ;
				I=0;
				D=0;
					jilu2 = 0;
					delay = 0;
		      process ++;
				}
				else 
				{
					delay = 0;
					process = 0;
				}
	     }
		  break;
		case 1:
			MODE = 26;
		  delay++;
		if( delay == 10 )
		{
			delay = 0;
			process = 2;
		}
		case 2:
			MODE = 12;
			if( OUT4 != 0 && OUT5 != 0 )
		  {
				process++;
			}
			break;
		case 3:
			MODE = 12;
		  if( OUT4 == 0 && OUT5 == 0 && OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6 )
		  {
				process++;
			}
			break;
		case 4:
			MODE = 27;
		  if(	Y>=355 || Y<=5 )
			{
				delay++;
				if( delay == 10 )
				{
					delay = 0;
				process ++;
				for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
				 }
			}
			break;
		case 5:
			MODE = 20;
		  if(( Y >= 357.5 || Y <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
			process = 0;
			step++;	
		  }
			break;
	}
}
}

void wu4()
{
	switch( process )
	{
		case 0:	
		  z3 = Z;
		  if((RANGE(	z3+90+ 2) <= 360) && (RANGE( z3+90- 2) >= 0))
					{
						mode1 = 1 ;
						mode2 = 0 ;
					}
					else 
					{
						mode1 = 0 ;
						mode2 = 1 ;
					}
		process=2;
		break;
		case 2:
			tlpid = 1;
		   zaxj(z3);
		delay ++;
		if( delay == 2250 )
		{
			  z3 = RANGE(z3 +90);
			  tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
			delay = 0;
			process ++;
		}
//		if( SE3 == 1 )
//		{
//			tlpid = 0;
//				pout = 0;
//			  I = 0;
//		  	D = 0;
//			delay = 0;
//			process ++;
//		}
		break;
		case 3:
			MODE = 10;
		  delay++;
		  if( delay == 10 )
			{
				delay = 0 ;
				process ++;
			}
		break;
		case 4:
			 tlpid = 1 ;
			  xuanzhuan2(z3);
			  if(  mode1 == 1 && Z >=  ( z3 - 2) && Z <= ( z3 + 2))
				{
					tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
          process ++;					 
	      }
				if(  mode2 == 1 && (Z > RANGE ( z3 - 2) || Z < RANGE ( z3 + 2)))
		     {
					 tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
		      process ++ ;
				}
				break;
		case 5:
			MODE = 10;
		  delay++;
		  if( delay == 10 )
			{
				delay = 0 ;
				process ++;
			}
			break;
		case 6:
		  if((RANGE(	z3+180+ 2) <= 360) && (RANGE( z3+180- 2) >= 0))
					{
						mode1 = 1 ;
						mode2 = 0 ;
					}
					else 
					{
						mode1 = 0 ;
						mode2 = 1 ;
					}
		process++;
					break;
		case 7:
			tlpid = 1;
		   zaxj(z3);
		delay ++;
		if( delay == 1100 )
		{
			  z3 = RANGE(z3 +180);
			  tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
			delay = 0;
			process ++;
		}
		break;
		case 8:
			MODE = 10;
		  delay++;
		  if( delay == 10 )
			{			
				delay = 0 ;
				process ++;
			}
			break;
		case 9:
			tlpid = 1 ;
			  xuanzhuan(z3);
			  if(  mode1 == 1 && Z >=  ( z3 - 2) && Z <= ( z3 + 2))
				{
					tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
          process ++;					 
	      }
				if(  mode2 == 1 && (Z > RANGE ( z3 - 2) || Z < RANGE ( z3 + 2)))
		     {
					 tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
		      process ++ ;
				}
				break;
		case 10:
			MODE = 10;
		  delay++;
		  if( delay == 10 )
			{			
				delay = 0 ;
				process ++;
			}
			break;
		case 11:
			if((RANGE(	z3+90+ 2) <= 360) && (RANGE( z3+90- 2) >= 0))
					{
						mode1 = 1 ;
						mode2 = 0 ;
					}
					else 
					{
						mode1 = 0 ;
						mode2 = 1 ;
					}
		process++;
					break;
		case 12:
			tlpid = 1;
		   zaxj(z3);
		delay ++;
		if( delay == 1100 )
		{
			  z3 = RANGE(z3+90);
			  tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
			delay = 0;
			process ++;
		}
		break;
		case 13:
			MODE = 10;
		  delay++;
		  if( delay == 10 )
			{			
				delay = 0 ;
				process ++;
			}
			break;
		case 14:
//      tlpid = 1 ;
//			  xuanzhuan2(z3);
		MODE = 19;
			  if(  mode1 == 1 && Z >=  ( z3 - 2) && Z <= ( z3 + 2))
				{
					tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
          process ++;					 
	      }
				if(  mode2 == 1 && (Z > RANGE ( z3 - 2) || Z < RANGE ( z3 + 2)))
		     {
					 tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
		      process ++ ;
				}
				break;
		case 15:
       MODE = 10;
		  delay++;
		  if( delay == 10 )
			{			
				delay = 0 ;
				process ++;
			}
			break;
    case 16:
      tlpid = 1;
		   zaxj(z3);
		delay ++;
		if( delay == 2050 )
		{
			MODE = 10;
			  tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
			delay = 0;
			process = 0;
			step++;
		}
		break; 			
		
	}
}

void door()
{
	switch(process)
	{
		case 0:
			MODE = 2;
		  if( SEL == 0||SER == 0 )
			 {
				 for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
					 pid.OUT = 0 ;
					 if( z1 == 0 )
					z3 = Z;
					 else 
						 z3 = z1;
          process++;			
	     }
			 break;
		case 1:
			delay ++;
		   tlpid  = 1;
		   if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 )
				 zaxj(z3);
			 else 
				 MODE = 2;
			 if(delay == 400)
			 {
				 delay = 0;
				 process ++;
				tlpid = 0;
				 }
			 break;
		case 2:
			MODE = 10;
		  delay++;
		if( delay == 5 )
		{
			for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
       z1 = 0;
       pout = 0;
				I=0;
				D= 0;
			delay = 0;
			process ++;
		}
		break;
		case 3:
			MODE = 20;
		  if(( Y >= 356 || Y <= 4 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				process ++;
		  }
			break;
		case 4:
			wending(3,3);
			jilu2 = 1;
			process = 0;
			step++;	
    break;		
}}

void RIGHT3()
{
	switch(process)
	{
		case 0:
			wending(3,3);
		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) ))
    	{
				delay++;
				if( delay == 8 ) 
				{
					if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))))
				{
					kaiguan = 0;
					jilu2 = 0;
					delay = 0;
		      process ++;
				}
				else 
				{
					delay = 0;
					process = 0;
				}
	     }
		 }
		  break;
//		case 1:
//			wending(2,2);
//			if( OUTR == 0 )
//				process++;
//			break;
		case 1:
			MODE = 10;
		  delay++;
		if( delay == 5 )
		{
			delay = 0;
			process ++;
		}
		break;
//		case 3:
//			MODE = 24;
//		  if( OUT8 == 0 || OUT7 == 0 )
//			{
//				process++;
//			}
//			break;
//		case 4:
//			MODE = 10;
//		  delay++;
//		if( delay == 5 )
//		{
//			delay = 0;
//			process ++;
//		}
//		break;
		case 2:
			MODE = 12;
			if(OUT4 == 1 && OUT5 == 1 )
		  {
				process++;
			}
			break;
		case 3:
			MODE = 12;
		  if( OUT4 == 0 || OUT5 == 0  )
		  {
				process++;
			}
			break;
//			case 7:
//			MODE = 12;
//			if( OUT4 == 0 || OUT5 == 0 )
//		  {
//				process++;
//			}
//			break;
//		case 8:
//			MODE = 12;
//		  if( OUT4 == 0 && OUT5 == 0  )
//		  {
//				process++;
//			}
//			break;
		case 4:
			MODE = 10;
	delay++;
				if( delay == 5 )
				{
					delay = 0;
				process ++;
				for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
				 }

			break;
		case 5:
			MODE = 20;
		  if(( Y >= 356 || Y <= 4 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
			{
				jilu1 = 1;
			process = 0;
			step++;	
		  }
			break;
	}
}


void quan()
{
	switch(process)
	{
		case 0:
			jilu1 = 1;
		  wending(3,3);
		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) ))
    	{
				delay++;
				if( delay == 8 ) 
				{
					if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))))
				{
					kaiguan = 0;
					jilu1 = 0;
					delay = 0;
		      process ++;
				}
				else 
				{
					delay = 0;
					process = 0;
				}
	     }
		 }
			case 1:
			wending(2,2);
			if( OUTR == 0 )
			{
				kaiguan = 0 ;
				process++;
			}
			break;
		case 2:
			MODE = 10;
		  delay++;
		if( delay == 10 )
		{
			delay = 0;
			process ++;
		}
		break;
		case 3:
			MODE = 12;
			if( OUT4 != 0 && OUT5 != 0 )
		  {
				process++;
			}
			break;
		case 4:
			MODE = 12;
		  if( OUT4 == 0 && OUT5 == 0 )
		  {
				process++;
			}
			break;
		case 5:
			MODE = 10;
		delay ++;
		if( delay == 5 )
		{
			for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
			delay = 0;
			process ++;
		}
		break;
		case 6:
			MODE = 2;
		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 )
			{
				process ++;
			}
      break;
 		case 7:
      MODE = 18;
      if(( Y>=20 && Y<= 30 )||(SEL == 0 && Y>=5 && Y<= 10))
			{
        process++;
				if( z2 == 0 )
				z3 = RANGE( z3+180 +10 );
				else 
					z3 = RANGE( z2+180 +10);
			}
      break;
    case 8:
			tlpid = 1;
      if ( SEL == 0 )
			{
        MODE = 7;
      }	
      else if ( SER == 0 )
			{
        MODE = 8;
      }
			else if( SEL == 1 && SER == 1)
			{
				zaxj(z3);
			}
			if( ANY == 0 && Y>=20 && Y<= 30)
			{
				tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
				process++;
			}
			break;
		case 9:
//			MODE = 10;
//			tlpid = 1;
//      if ( SEL == 0 )
//			{
//        MODE = 7;
//      }	
//      else if ( SER == 0 )
//			{
//        MODE = 8;
//      }
//			else if( SEL == 1 && SER == 1)
//			{
//				MODE = ;
//			}
		   MODE = 25;
			if(  ANY == 1 )
			{
				tlpid = 0;
				pout = 0;
			  I = 0;
		  	D = 0;
				process++;
			}
			break;
		case 10:
			MODE = 28;
		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 && Y>= -355 && Y<=5 )
			{
				process++;
			}
			break;
		case 11:
			MODE = 10;
		delay++;
		if( delay == 10 )
		{
			for ( q=0 ; q<=7 ; q++ )
	         {
		         i [q] = 1 ;
		         temp[q] = 1 ;
	         }
	        pid.OUT = 0 ;
					 delay = 0;
			process++;
		}
		break;
		case 12:
			MODE = 2;
		  if( OUTL == 0 )
			process++;
			break;
		case 13:
			MODE = 10;
		break;
	}
}

//void lukou( )
//{
//	switch(process)
//	{
//		case 0:
//		  wending(3,3);
//		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
//			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
//			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
//		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
//		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) ))
//    	{
//				delay++;
//				if( delay == 8 ) 
//				{
//					if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
//			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
//			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
//		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
//		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))))
//				{
//					kaiguan = 0;
//					delay = 0;
//		      process ++;
//				}
//				else 
//				{
//					delay = 0;
//					process = 0;
//				}
//	     }
//		 }
//		case 1:

//		  if ( (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6 && OUT4 == 0 && OUT5 ==0 )|| (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 7 && (OUT4 == 0 || OUT5 ==0 )))
//			{
//				process = 2;
//			}
//			break;
//		case 2:

//		  delay++;
//		  if(delay == 40)
//			{
//				delay = 0;
//				if( (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6 && OUT4 == 0 && OUT5 ==0 )|| (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 7 && (OUT4 == 0 || OUT5 ==0 )))
//				{
//					process = 0;
//					step++;
//				}
//				else
//					process = 1;
//	    }
//			
//		}
//	}

//	}
//}

//void youzhuan( int n )
//{
//  float k; 
//	switch(process)
//	{
//		case 0:
//			MODE = 3;
//		  if (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
//			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
//			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
//		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
//		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) )
//			{	
//				
//				jilu2 = 0;
//				k = Z;
//			  process++;
//			}
//			break;
//		case 1:
//		  if ( OUTR == 0)
//			{	
//				process++;
//			}
//			break;
//		case 2:
//			MODE= 10;
//		  delay++;
//		if( delay == 200 )
//		{
//			delay = 0;
//			process ++;
//		}
//		break;
//		case 3:
//		MODE = 12;
//		 if ( RANGE( k - n) >5  && RANGE( k - n) < 355)
//		 {
//			 if ( Z > RANGE(RANGE( k - n) - 4) && Z < RANGE(RANGE( k - n) + 4))
//			 { process ++;
//			   for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 }
//		 }
//			else
//		 {
//			 if ( Z >  RANGE(RANGE( k - n) - 4) || Z <  RANGE(RANGE( k - n) + 4))
//			 { process ++;
//			 for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 }
//		 }
//    break;
//    case 4:
//     MODE = 10;
//		if( )
//		{
//    delay ++;
//    if( delay == 150 )		
//		{
//			delay = 0;
//			process ++;
//			for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//		}
//	}
//		break;
//    case 5:
//    MODE = 2;
//		  if(( X >= 357.5 || X <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
//			{
//				process ++;
//		  }
//			break;
//		case 6:
//			MODE = 3;
//			jilu2 = 1;
//			process = 0;
//			step++;	
//    break;
//}
//}
//void zuozhuan( int n )
//{
//  float k; 
//	switch(process)
//	{
//		case 0:
//			MODE = 3;
//		  if (OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8<6||((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 6)&&((OUT1==0&&OUT3==0)||(OUT1==0&&OUT3==0)
//			 ||(OUT1==0&&OUT4==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT5==0)||(OUT1==0&&OUT6==0)||(OUT1==0&&OUT7==0)
//			 ||(OUT1==0&&OUT8==0)||(OUT2==0&&OUT4==0)||(OUT2==0&&OUT5==0)||(OUT2==0&&OUT6==0)||(OUT2==0&&OUT7==0)||(OUT2==0&&OUT8==0)||
//		 (OUT3==0&&OUT5==0)||(OUT3==0&&OUT6==0)||(OUT3==0&&OUT7==0)||(OUT3==0&&OUT8==0)||(OUT4==0&&OUT6==0)||(OUT4==0&&OUT7==0)||(OUT4==0&&OUT8==0)||
//		 (OUT5==0&&OUT7==0)||(OUT5==0&&OUT8==0)||(OUT6==0&&OUT8==0))) )
//			{	
//				
//				jilu2 = 0;
//				k = Z;
//			  process++;
//			}
//			break;
//		case 1:
//		  if ( OUTL == 0)
//			{	
//				process++;
//			}
//			break;
//		case 2:
//			MODE= 10;
//		  delay++;
//		if( delay == 200 )
//		{
//			delay = 0;
//			process ++;
//		}
//		break;
//		case 3:
//		MODE = 12;
//		 if ( RANGE( k - n) >5  && RANGE( k - n) < 355)
//		 {
//			 if ( Z > RANGE(RANGE( k - n) - 4) && Z < RANGE(RANGE( k - n) + 4))
//			 { process ++;
//			   for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 }
//		 }
//			else
//		 {
//			 if ( Z >  RANGE(RANGE( k - n) - 4) || Z <  RANGE(RANGE( k - n) + 4))
//			 { process ++;
//			 for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 }
//		 }
//    break;
//    case 4:
//     MODE = 10;
//		if( )
//		{
//    delay ++;
//    if( delay == 150 )		
//		{
//			delay = 0;
//			process ++;
//			for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//		}
//	}
//		break;
//    case 5:
//    MODE = 2;
//		  if(( X >= 357.5 || X <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
//			{
//				process ++;
//		  }
//			break;
//		case 6:
//			MODE = 3;
//			jilu2 = 1;
//			process = 0;
//			step++;	
//    break;
//}
//}
//void door()
//{
//	switch(process)
//	{
//		case 0:
//			MODE = 3;
//		  protect();
//		  if(angle[1] <= -8)
//			{
//				safe = 1;
//				process=1;
//			}
//		  break;
//		case 1:
//			MODE = 1;
//		  delay++;
//		if( delay == 4400 )
//		{
//			for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//			delay = 0;
//			process = 0;
//			step++;
//		}
//			break;
//	}

//void xieqiao2()
//{
//	switch( process )
//	{
//			
//		case 0:
//			MODE = 3;
//		  if( OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 )
//			{
//				MODE = 10;
//				if( angle[1] >= -5 && angle[1] <=5 )
//				{
//					delay++;
//					if( delay == 100 )
//					{
//						delay = 0;
//						for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//					 process  = 1;
//					}
//				}
//			}
//			break;
//		case 1 :
//			MODE = 3;
//		  if((OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 == 8 && ( SEL ==0 || SER == 0 )))
//			{
//				jilu3=jilu1 =0;
//				pout = 0;
//			  I = 0;
//			  D = 0;
//        if( chuandi3 == 0 )
//				{
//					if(chuandi2 != 0)
//					{
//						chuandi3 = RANGE( chuandi2 + 180 -2);
//					}
//					if( chuandi2 == 0)
//						chuandi3 = RANGE(chuandi1 - 2);
//				}
//				else chuandi3 = RANGE(chuandi3 + 90 - 2);
//        process = 2;
//			}
//		  break;

//		case 2:
//			MODE = 10;
//		  delay++;
//		  if( delay == 300 )
//			{
//				delay = 0;
//				process = 3;
//			}
//			break;
//		case 3:
//			tlpid = 1;
//		xqiao(chuandi3);
//	
//		  if(OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8 != 8 )
//			{
//				tlpid = 0;
//				process = 6;
//				pout = 0;
//			  I = 0;
//		  	D = 0;
//			}
//			break;
//		case 6:
//			delay ++;
//		  MODE = 1;
//		  if(delay == 1000)
//			{
//				for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				  process = 7;
//					delay = 0;
//			}
//		 break;
//		case 7:
//			MODE = 2;
//		  if(( X >= 357.5 || X <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
//			{
//				process ++;
//		  }
//			break;
//		case 8:
//			chuandi1 = 0;
//			chuandi2 = 0;
//			MODE = 3;
//			jilu1 = 1;
//			process = 0;
//			step++;	

//			break;
//	}
//}
//void zhangai2()
//{
//	 switch(process)
//	 {
//		 case 0:
//			 MODE = 23;
//       
//		   if( angle[1] <= -5)
//			 {
//				 jilu1 = 0;
//				 process = 1;
//				 
//			 }
//			 break;
//		 case 1:
//       MODE = 1;
//			 delay++;
//			 if(delay == 6500 )
//			 {
//				 delay = 0;
//				 process ++;
//			 }
//       
//			 break;
//		 case 2:
//			 MODE = 2;
//		  if(( X >= 357.5 || X <= 2.5 ) && (ANZ==1) && (OUT4 == 0 && OUT5 == 0))
//			{
//				process ++;
//		  }
//			break;
//		case 3:
//			MODE = 3;
//			jilu1 = 1;
//			process = 0;
//			step++;	
//    break;
//		 }
//}
//void turn2(void)
//{
// int mode1=0,mode2=0;
// float keep=0;
//	//OLED_ShowNum( 8,4,keep,6,16);
//	
//	switch(process)
//		{
//			case 1 :
//				pout = 0;
//				MODE = 1;
//			  I = 0;
//			  D = 0;
//			  if( angle[1] <=-5)
//				{
//					if( chuandi1 == 0 )
//					{
//						chuandi1 = Z;
//					}
//					jilu1 = 0;
//					keep = Z;
//					process = 2;
//				}
//				  break;
//			case 2 :    
//			  if ( angle [1] <= -10 )
//				{
//			    process = 3 ;
//				}
//				  break;
//			case 3 :
//    			MODE = 3;

//			  if ( angle [1] >= -10 && angle [1] <= 10 )
//			    process = 5 ;
//				  break;
//			case 5 :
//				line(12) ;
//			  if ( OUT9 == 0 && OUT10 == 0)
//					process = 6;
//				
//				 break;
//			case 6 :
//				line(12);
//			  delay ++ ;
//			  if( delay == 150 )
//				{
//					process = 7 ;
//					delay = 0;
//				}
//			  break;
//			case 7 :
//				line(12) ;
//			  if ( OUT9 == 0 && OUT10 == 0)
//					process = 9;
//				
//				 break;
////			case 8 :
////				line(2);
////				if ( OUT9 == 0 && OUT10 == 0 )
////					process = 9;
////				break;
//			case 9:
//				line(12);
//			  delay ++ ;
//			  if( delay == 150 )
//				{
//					process = 11 ;
//					delay = 0;
//				}
//				break;
//			case 10:
//				line(12);
//				if( SE1 == 0 || SE2 == 0 )
//				{
//					process = 11;
//				}
//				break;
//			case 11 :
//				line(5);
//			  delay++;
//			  if( delay == 500 )
//				{
//					process = 12 ;
//					delay = 0 ;
//				}
//				break;
//			case 12 :
//			  line(5);
//			  keep = RANGE( keep + 180 );
//		  	if(((	keep + 2) <= 360) && (( keep - 2) >= 0))
//					{
//						mode1 = 1 ;
//						mode2 = 0 ;
//					}
//					else 
//					{
//						mode1 = 0 ;
//						mode2 = 1 ;
//					}

//			  
//			  process = 13 ;
//			  break ;
//			case 13 :

//			  line(25);
//			  if(  mode1 == 1 && angle [2] >=  ( keep - 2) && angle [2] <= ( keep + 2))
//				{
//					for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;

//		      process = 14 ;
//				}
//		    if(  mode2 == 1 && (angle [2] > RANGE ( keep - 2) || angle [2] < RANGE ( keep + 2)))
//		     {
//					for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//		      process = 14 ;
//				}
//				break;
//			case 14 :
//				line(5);
//			  delay ++ ;
//			  if ( delay == 500 )
//				{
//					process = 15 ;
//					delay = 0 ;
//					safe = 1 ;
//				}
//				break;
//			case 15 :
//				line(12) ;
//			  if ( angle [1] >= 15 )
//				{
//					for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//					process = 16 ;
//					pid.tli = 0;
//			    pid.tld = 0;
//					pout = 0;
//				}
//				break;
//			case 16 :
//				line(23);
//			  an = 1 ;
//			  if(AN1 == 2)
//				{
//					an = 0 ;
//					process = 17;
//					AN1 = 2 ;
//				  AN0 = 1 ;
//				}
//				break;
//			case 17 :
//				line(23) ;			  
//			  if( angle[1] >-5 && angle[1] < 5)
//				{
//			    process =  18;
//				}
//			  break;
//			case 18:
//				line(23);
//			  delay++;
//			  if(delay == 100)
//				{
//					delay = 0;
//					process = 19;
//				}
//				break;
//			case 19:
//				line(5);
//			  if( angle[1]>=-1.5 && angle[1] <=1.5 )
//				{
//					delay++;
//					if( delay == 50 )
//					{
//						delay = 0;
//					for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         } 					
//	        pid.OUT = 0 ;
//					process = 20;
//				 }
//				}
//				break;
//			case 20:
//				line(23);
//			  delay++;
//			  if( delay == 300 )
//				{
//					chuandi2 = 0;
//					delay = 0;
//					for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         } 					
//	        pid.OUT = 0 ;
//					 process = 1;
//					 step++;
//					 jilu2 = 1;
//				}
//		
//		}
//}

//void zhangai3()
//{
//	 switch(process)
//	 {
//		 case 0:
//			 line(6);
//       
//		   if( )
//			 {
//				 process = 1;
//				 safe = 1;
//				 
//			 }
//			 break;
//		 case 1:
//       line(23);
//			 delay++;
//			 if(delay == 10000)
//			 {
//				 jilu2 = 1;
//				 delay = 0;
//				 process = 0;
//				 for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 step++;
//			 }
//       if( ( OUT1==0 && OUT2 == 0 && OUT3 == 0 && OUT4 == 0 && OUT5 == 1 && OUT6 == 1 && OUT7 ==1 && OUT8 ==1) 
//				 || ( OUT1==0 && OUT2 == 0 && OUT3 == 0 && OUT4 == 0 && OUT5 ==0 && OUT6 == 1 && OUT7 ==1 && OUT8 ==1) 
//			 || ( OUT1 == 0 && OUT2 == 0 && OUT3 == 0 && OUT4 == 0 && OUT5 ==0  && OUT6 == 0 && OUT7 == 1 && OUT8 == 1) )
//			 {
//				 jilu2 = 1;
//				 delay = 0;
//				 process = 0;
//				 for ( q=0 ; q<=7 ; q++ )
//	         {
//		         i [q] = 1 ;
//		         temp[q] = 1 ;
//	         }
//	        pid.OUT = 0 ;
//				 step++;
//			 }
//			 break;
//		 }
//}