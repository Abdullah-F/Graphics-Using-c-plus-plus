#include <Windows.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>

using namespace std;


#define ID_Edit  104
#define ID_DDA 201
#define ID_Parametric 301
#define ID_cartesian 402
#define ID_Bresenham 302
#define ID_Exit 101
#define ID_mid 403
#define ID_save 404
#define ID_load 405
#define ID_Polar 500
#define ID_Cartesian_Circle 501
#define ID_Iterative_Circle 502
#define ID_Midpoint_Circle 503
#define ID_DDA_Circle 504
class LineInfo
{
	public:
		LineInfo()
		{
			x1 = y1 =  x2 =  y2 = algorithmNumber  = 0;
			color = RGB(255,0,150);
		}
		
		LineInfo(int v1 ,int v2 ,int v3 ,int v4 ,int v5 ,COLORREF v6 )
		{
			x1 = v1;
			y1 = v2;
			x2 =v3;
			y2 = v4;
			algorithmNumber  = v5;
			color = v6;
		}
		
		
		int x1;
		int y1;
		int x2;
		int y2;
		int algorithmNumber;
		COLORREF  color;
		
		
		
		void write(ofstream &myfile)
		{
			
        myfile << x1 << " "<<y1 << " "<<x2 << " "<<y2 << " "<< algorithmNumber<< " "<< color<< " ";
		
		}
		
		
		void read(ifstream &read)
		{
		 
		 read >> x1 >> y1 >> x2 >> y2 >> algorithmNumber >> color;
        
		}
};

/****************************************************************/
void B_V_multiplication(int B[] [4], int V[] , int* alpha)
{
	int sum;
	
	
	for(int i = 0 ; i < 4 ; i++)
	{
		sum =0;
		for(int j = 0 ; j < 4 ; j++)
		{
			sum += B[i][j] * V[j];
			
		}
		
		*(alpha+i)= sum;
		
		
	}
		
	
	
}

/**************************************************************/

void swap(int &x, int &y)
{
    int tmp=x;
    x=y;
    y=tmp;
}

//**************************************************************************************

int R(int x , int y , int x1 , int y1)
{
	if(x == x1 && y!=y1)
	return y > y1?y-y1:y1-y;
	else if(x !=x1 && y == y1)
	return x>x1?x-x1:x1-x;
	else
	return round( sqrt((pow(x-x1,2)-pow(y-y1,2)) ) );
}





void DrawLine(HDC hdc, int xs, int ys, int xe, int ye,COLORREF color)
{
    double deltaX,deltaY,step,x,y,maxOf_XandY = xe>=ye?xe:ye;
    int numberOfRepetions = 10 ;

    if(xs > xe)
    {
        swap(xs,xe);
        swap(ys,ye);
    }
    deltaX = xe-xs;
    deltaY = ye-ys;

    step = deltaX>=deltaY?1.0/(deltaX >0?deltaX:1) : 1.0/(deltaY>0?deltaY:1);
    while(1)
    {
        maxOf_XandY = maxOf_XandY/10;
        if(maxOf_XandY < 1)
        {
            break;
        }
        else
            numberOfRepetions*=10;
    }


    step = step*numberOfRepetions;
    step = round(step);
    for(int i = 0 ; i <=numberOfRepetions ; i+=step)
    {
        double stp = (double)i/numberOfRepetions;
        x = xs+stp*deltaX;

        y = ys+stp*deltaY;

        SetPixel(hdc,round(x),round(y),color);

    }
}



//**************************************************************************************
void Drow8point(HDC hdc,int xc,int yc,int x,int y)
      {
 
                     
        SetPixel(hdc,xc+x,yc+y,RGB(255,0,150));              
         SetPixel(hdc,xc+x,yc-y,RGB(255,0,150));
           DrawLine( hdc,xc+x,yc-y,xc+x,yc+y ,RGB(255,0,150))  ; 
          SetPixel(hdc,xc-x,yc+y,RGB(255,0,150)); 
         SetPixel(hdc,xc-x,yc-y,RGB(255,0,150)); 
         DrawLine( hdc,xc-x,yc-y,xc-x,yc+y ,RGB(255,0,150))  ; 
        SetPixel(hdc,xc+y,yc+x,RGB(255,0,150)); 
         SetPixel(hdc,xc+y,yc-x,RGB(255,0,150));
          DrawLine( hdc,xc+y,yc-x,xc+y,yc+x ,RGB(255,0,150))  ; 
          SetPixel(hdc,xc-y,yc+x,RGB(255,0,150));  
         SetPixel(hdc,xc-y,yc-x,RGB(255,0,150)); 
         DrawLine( hdc,xc-y,yc-x,xc-y,yc+x ,RGB(255,0,150))  ; 
     }
     
//*****************************************************************************************     
void polar(HDC hdc,int r,int xc , int yc)
{
	double x = r , y = 0;
	Drow8point(hdc,xc, yc,  round(x), round(y));
	
	double theta = 0;
	double deltaTheta = 1.0/r;
	
	while(x>y)
	{
		theta = theta +deltaTheta;
		y = r * sin(theta);
		x = r * cos(theta);
		 Drow8point(hdc,xc, yc,  round(x), round(y));
	}
	
	
}


//***************************************************************************************
void DrowCrtisianCircle(HDC hdc,int xc,int yc,int R)
{
      int x=0;
    double y=R;
     
     Drow8point( hdc, xc, yc, x,round(y));
     while(x<y)
     {
          x=x+1;
          y = sqrt(R*R-x*x);
         Drow8point( hdc, xc, yc, x,round(y));
                
       }
	        
     }


//****************************************************************************************
void iterative  (HDC hdc,int xc,int yc,double r){
double x=r,y=0;
double delta_theta=1.0/r;

  Drow8point(hdc,xc,yc,x,y);
  double CT=cos(delta_theta);
    double st=sin(delta_theta);
     while(x>y){
          double x1=  x*CT- y*st;
           y = x*st + y*CT;
           x=x1;
            Drow8point(hdc,xc,yc,round(x),round(y));
            }
     
     }

//*******************************************************************************************
void DrowCircleByMidpoint(HDC hdc,int xc,int yc,double R)
{
    int x=0;
    double y=R;
    double d=1-R;
    double change1=3;
  double change2=5-(2*R);
    Drow8point( hdc,xc,yc,x,y);
     while(x<y){
            x=x+1;
         if(d>=0){
                  d=d+change2+4;
                  change2= change2+4;
                  y=y-1; 
                  
                  } 
             else
             {
             d=d+change1;
              change2= change2+2;
              }
             change1=change1+2;
              Drow8point( hdc,xc,yc,x,y);
             }
             }

//*******************************************************************************************
 void DrowCircleByDDA(HDC hdc,int xc,int yc,double R)
    {
    int x=0;
    double y=R;
     double d=(5/4)-R;
     Drow8point( hdc, xc, yc, x, y);
     while(x<y)
     {
            x=x+1;
           if (d>=0 )
           {
                 d=d+2*(x-y)+3;
                  y=y-1;
           }   
                else
                {
                   d=d+(2*x)+1;
                }
               Drow8point( hdc, xc, yc, x, y);
      }    
                
   }

//*******************************************************************************************
///DDA
void drawlineByDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{

 
 int dx=xe-xs;
 int dy=ye-ys;
 
 double x=xs;
 double y=ys;

 if(abs(dy)<=abs(dx))//ching in x greater of y
    {
        double m=(double)dy/dx;
        if(xs>xe)
        {
          swap(xs,xe);
          swap(ys,ye);
        }
        for(int x=xs;x<=xe;x++)
        {
            int y=round(ys+(x-xs)*m);
            SetPixel(hdc,x,y,color);
            
        }
    }
    else//ching in y greater of x
    {
        double slope=(double)dx/dy;
        if(ys>ye)
        {
            swap(xs,xe);
            swap(ys,ye);
        }
        for(int y=ys;y<=ye;y++)
        {
           int x=round(xs+(y-ys)*slope);
            SetPixel(hdc,x,y,color);
          
        }
    }
}



//***********************************************************
///paramatric

//*************************************************************************************

///midpoint
void drawLineMidpoint(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    if(xe<xs)
        {
            swap(xs,xe);
            swap(ys,ye);
        }

    int dx=xe-xs;
    int dy=ye-ys;

    double d=dx-(2*dy);

    double change1 =2*(dx-dy);
    double change2= -2*dy;

    double x=xs;
    double y=ys;

    SetPixel(hdc,x,y,color);

    while(x<xe)
    {
        x=x+1;
        if(d<0)
        {
            y=y+1;
            d=d+change1;

        }
        else
        {
            d=d+change2;
        }


        SetPixel(hdc,x,y,color);
    }



}


//***************************************************************************************
///simple DDA
void drawlineBYSDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
     
    
    int dx=xe-xs;
    int dy=ye-ys;
    
	double m=(double)dy/dx;
    
	double x= xs;
    double y=ys;
   
   
     SetPixel(hdc,xs,ys,color);
     
	 if(m<1){
          y=ys;
          for ( x = xs ; x<=xe ; x++){
              SetPixel(hdc,x,y,color);
		       y += m;
               x=x+1;
          }   
	 
	 }
   
   else
   {
        x = xs ;
	    
		for ( y = ys ; y<=ye ; y++){
		       SetPixel(hdc,x,y,color);
		       x += 1/m ;
		       y=y+1;
         }

   }

}

/****************************************************************************************/

//*** bezier curve

void bezier(HDC hdc, int x0, int y0, int x1, int y1, int x2,
 int y2, int x3 , int y3 , COLORREF color)
{
	float x,y;
	int B[4][4] =
	{
		{  1,0 ,0 ,0  },
		{ -3,3 ,0 ,0  },
		{  3,-6 ,3 ,0 },
		{ -1,3 ,-3 ,1 },
		
	};
	
	int vx[] = {x0, x1, x2 , x3}; 
	int vy[] = {y0, y1, y2 , y3};
	
	int cx[4] , cy[4];
	
	B_V_multiplication(B,vx,cx);
	B_V_multiplication(B,vy,cy);
	
	for(float t = 0 ; t < 1 ; t = t + (1.0/500))
	{
		x = 0 ; 
		y = 0;
		
		for(int i = 0  ; i < 4 ; i++)
		x += cx[i] * pow(t,i);
		
		for(int i = 0  ; i < 4 ; i++)
		y += cy[i] * pow(t,i);
		
		SetPixel(hdc ,round(x) , round(y) , color);
	}
	
	
}
//***************************************************************************************


LRESULT WINAPI MyWindowProc(HWND hwnd,UINT m,WPARAM wp,LPARAM lp)
{
	
    HDC hdc;
    hdc=GetDC(hwnd);
    static int x  = -1,y = -1,x1  = -1 , y1 = -1 , useMouse = 0 ;
	static vector<LineInfo> data;
	
	bezier(hdc,500,300,300,450,200,150,100,400,RGB(20,0,150));
    switch(m)
    {
    case WM_CREATE:
    {

        HMENU mainMenu=CreateMenu();
        HMENU subMenu1=CreateMenu();
        HMENU subMenu2=CreateMenu();
        HMENU subMenu3=CreateMenu();
        HMENU subMenu4=CreateMenu();
        


        InsertMenu(mainMenu,ID_Edit,MF_POPUP,(UINT_PTR) subMenu1,"Line");

        AppendMenu(subMenu1,MF_STRING,ID_DDA,"&DDA");
        AppendMenu(subMenu1,MF_SEPARATOR,0,"");

        AppendMenu(subMenu1,MF_STRING,ID_mid,"&midpoint");
        AppendMenu(subMenu1,MF_SEPARATOR,0,"");

        AppendMenu(subMenu1,MF_STRING,ID_Parametric,"&parametric");
        AppendMenu(subMenu1,MF_SEPARATOR,0,"");

        AppendMenu(subMenu1,MF_STRING,ID_cartesian,"&SDDA_cartesian");

        AppendMenu(subMenu1,MF_SEPARATOR,0,"");


        ///////////////////////////////////////////////////////////////////////
        InsertMenu(mainMenu,ID_Edit,MF_POPUP,(UINT_PTR)subMenu4,"circle");
        AppendMenu(subMenu4,MF_STRING,ID_Polar,"&polar");
        AppendMenu(subMenu4,MF_STRING,ID_Cartesian_Circle,"&cartesian");
        AppendMenu(subMenu4,MF_STRING,ID_Iterative_Circle,"&iterative");
        AppendMenu(subMenu4,MF_STRING,ID_Midpoint_Circle,"&MidPoint");
        AppendMenu(subMenu4,MF_STRING,ID_DDA_Circle,"&DDA");
        
        ///////////////////////////////////////////////////////////////////////

        InsertMenu(mainMenu,ID_Edit,MF_POPUP,(UINT_PTR)subMenu2,"Exit");
        AppendMenu(subMenu2,MF_STRING,ID_Exit,"&Exit");

       //////////////////////////////////////////////////////////////////////////////
        InsertMenu(mainMenu,ID_Edit,MF_POPUP,(UINT_PTR)subMenu3,"Data");
        AppendMenu(subMenu3,MF_STRING,ID_save,"&save");
        
        
        AppendMenu(subMenu1,MF_SEPARATOR,0,"");
        AppendMenu(subMenu3,MF_STRING,ID_load,"&load");


        SetMenu(hwnd,mainMenu);
        
        



        break;
    }

    case WM_COMMAND :
        switch(LOWORD(wp))
        {
            case ID_DDA:
              useMouse = 1;
              break;
            case ID_cartesian:
              useMouse = 4;
              break;
            case ID_Parametric:
              useMouse = 3;
              break;
            case ID_mid:
              useMouse = 2;
              break;
            case ID_Polar:
            	useMouse = 5;
            	break;
            case ID_Cartesian_Circle:
            useMouse = 6;
            break;
            case ID_Iterative_Circle:
            	useMouse = 7;
            	break;
            case ID_Midpoint_Circle :
            		useMouse = 8;
            		break;
            case ID_DDA_Circle:
            	useMouse = 9;
            	break;
            case ID_Exit:
        	  CloseWindow(hwnd);
        	break;
            
			case ID_save:
        	{
        		ofstream write("data.txt",ios::app);
        		
				for(int i = 0 ; i < data.size() ; i++)
        		{
        			
        		data.at(i).write(write);	
        			
				}
				
				write.close();
				
				data.clear();
				
			}
			
			break;
			
		   case ID_load:
			{
				LineInfo line;
				ifstream read("data.txt");
        		while(!read.eof())
        		{
				
        			line.read(read);
        			
        	      if(line.algorithmNumber == ID_cartesian)
                   {
                

                        drawlineBYSDDA(hdc, line.x1, line.y1, line.x2,line.y2,line.color);
                
            
                   }
                 else if(line.algorithmNumber == ID_mid)
                   {
                
                        drawLineMidpoint(hdc, line.x1, line.y1, line.x2,line.y2,line.color);
                

                   }

                 else if(line.algorithmNumber ==ID_Parametric)
                   {
                
                        DrawLine(hdc, line.x1, line.y1, line.x2,line.y2,line.color);
                   }
            
                 else if(line.algorithmNumber ==ID_DDA)
                    {
            
                       drawlineByDDA(hdc, line.x1, line.y1, line.x2,line.y2,line.color);
                     
                    }
                    
                    else if(line.algorithmNumber ==ID_Polar)
                    {
            
                       polar(hdc,line.x2, line.x1, line.y1);
                     
                    }
                    else if(line.algorithmNumber ==ID_Cartesian_Circle)
                    {
            
                       DrowCrtisianCircle(hdc, line.x1, line.y1,line.x2);
                     
                    }
                    else if(line.algorithmNumber ==ID_Iterative_Circle)
                    {
                    	
            
                       iterative(hdc, line.x1, line.y1,line.x2);
                     
                    }
                    else if(line.algorithmNumber ==ID_Midpoint_Circle)
                    {
                    	
            
                       DrowCircleByMidpoint(hdc, line.x1, line.y1,line.x2);
                     
                    }
                    else if(line.algorithmNumber ==ID_DDA_Circle)
                    {
                    	
            
                       DrowCircleByDDA(hdc, line.x1, line.y1,line.x2);
                     
                    }


                    
                    


        			
        			
				}
				read.close();
				break;
				
			}
        	



        }

        break;

    case WM_LBUTTONUP:


        if(x ==-1 )
        {

            x = LOWORD(lp);
            y = HIWORD(lp);

        }
        else if(x != -1)
        {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            

            if(useMouse == 4)
            {
                

                drawlineBYSDDA(hdc, x, y, x1,y1,RGB(20,0,150));
                LineInfo line(x, y, x1,y1,ID_cartesian,RGB(20,0,150));
                data.push_back(line);
                
            
            }
            else if(useMouse == 2)
            {
                
                drawLineMidpoint(hdc,x,y,x1,y1,RGB(100,0,80));
                LineInfo line(x, y, x1,y1,ID_mid,RGB(20,0,150));
                data.push_back(line);

            }

            else if(useMouse == 3)
            {
                
                DrawLine(hdc,x,y,x1,y1,RGB(0.6,90,0));
                LineInfo line(x, y, x1,y1,ID_Parametric,RGB(20,0,150));
                data.push_back(line);
            }
              else if(useMouse == 1)
            {
            
                drawlineByDDA(hdc,x,y,x1,y1,RGB(255,0,150));
                LineInfo line(x, y, x1,y1,ID_DDA,RGB(255,0,150));
                data.push_back(line);
            
            }
              else if(useMouse == 5)
            {
            
                polar(hdc, R(x,y,x1,y1), x , y);
                LineInfo line(x, y, R(x,y,x1,y1),0,ID_Polar,RGB(255,0,150));
                data.push_back(line);
            
            }
            else if(useMouse  == 6)
            {
            	DrowCrtisianCircle(hdc,x,y,R(x,y,x1,y1));
            	LineInfo line(x, y, R(x,y,x1,y1),0,ID_Cartesian_Circle,RGB(255,0,150));
                data.push_back(line);
			}
			else if(useMouse  == 7)
            {
            	iterative(hdc,x,y,R(x,y,x1,y1));
            	LineInfo line(x, y, R(x,y,x1,y1),0,ID_Iterative_Circle,RGB(255,0,150));
                data.push_back(line);
			}
			else if(useMouse  == 8)
            {
            	DrowCircleByMidpoint(hdc,x,y,R(x,y,x1,y1));
            	LineInfo line(x, y, R(x,y,x1,y1),0,ID_Midpoint_Circle,RGB(255,0,150));
                data.push_back(line);
			}else if(useMouse  == 9)
            {
            	DrowCircleByDDA(hdc,x,y,R(x,y,x1,y1));
            	LineInfo line(x, y, R(x,y,x1,y1),0,ID_DDA_Circle,RGB(255,0,150));
                data.push_back(line);
			}
			





            ReleaseDC(hwnd,hdc);
            x =-1 ;
            y =-1;

        }




        break;


       case WM_DESTROY:
        PostQuitMessage(0);
        break;

       default:
        return DefWindowProc(hwnd,m,wp,lp);
    }
    return 0;
}



int APIENTRY WinMain(HINSTANCE h,HINSTANCE, LPSTR,int n)
{
    HWND hwnd;
    WNDCLASS wc;
    wc.cbClsExtra=wc.cbWndExtra=0;
    wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    wc.hIcon=LoadIcon(NULL,IDI_WINLOGO);
    wc.hInstance=h;
    wc.lpfnWndProc=MyWindowProc;
    wc.lpszClassName="MyClass";
    wc.lpszMenuName=NULL;
    wc.style=CS_VREDRAW | CS_HREDRAW;
    RegisterClass(&wc);
    hwnd=CreateWindow(wc.lpszClassName,"Drowing Line",WS_OVERLAPPEDWINDOW,0,0,1200,600,NULL,NULL,h,NULL);
    ShowWindow(hwnd,n);
    UpdateWindow(hwnd);
    MSG m;
    
    while(GetMessage(&m, hwnd,0,0)>0)
    {
        TranslateMessage(&m);
        DispatchMessage(&m);
    }
    return 0;
}

