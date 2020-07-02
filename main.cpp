#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include "Header.h"

using namespace std;

int main(int argc, char* argv[])
{
    FILE *file;
    int Width = 512;
    int Length = 512;
    int BytesPerPixel = 3;
    //int Size = Length;

    unsigned char* ImageData = new unsigned char [ Length*Width*BytesPerPixel ];
    unsigned char* DiscedImage = new unsigned char [ Length*Width*BytesPerPixel ];
    unsigned char* SquaredImage = new unsigned char [ Length*Width*BytesPerPixel ];

    //unsigned char DiscedImage3D [Length][Width][BytesPerPixel];

    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(ImageData, sizeof(unsigned char),  Length*Width*BytesPerPixel ,  file);
    fclose(file);


    unsigned char*** ImageData3D =  new unsigned char **[Length];
    for (int i = 0; i < Length; i++)
    {
        ImageData3D[i] = new unsigned char *[Width]();
        for (int j = 0; j < Width; j++)
        {
            ImageData3D[i][j] = new unsigned char[BytesPerPixel]();
            for (int k = 0; k < BytesPerPixel; k++)
            {
                ImageData3D[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                ImageData3D[i][j][k] = ImageData[i * Width * BytesPerPixel + j * BytesPerPixel + k];
                
            }
        }
    }
    //
    unsigned char*** DiscedImage3D =  new unsigned char **[Length];
       for (int i = 0; i < Length; i++)
       {
           DiscedImage3D[i] = new unsigned char *[Width]();
           for (int j = 0; j < Width; j++)
           {
               DiscedImage3D[i][j] = new unsigned char[BytesPerPixel]();
               for (int k = 0; k < BytesPerPixel; k++)
               {
                   DiscedImage3D[i][j][k] = 0;
               }
           }
       }
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            for (int k = 0; k < BytesPerPixel; k++)
            {
                DiscedImage3D[i][j][k] = DiscedImage[i * Width * BytesPerPixel + j * BytesPerPixel + k];
                //Imagedata3d[i][j][k] = Imagedata[m];
                //m = m+1;
            }
        }
    }
    //
    unsigned char*** SquaredImage3D =  new unsigned char **[Length];
    for (int i = 0; i < Length; i++)
    {
        SquaredImage3D[i] = new unsigned char *[Width]();
        for (int j = 0; j < Width; j++)
        {
            SquaredImage3D[i][j] = new unsigned char[BytesPerPixel]();
            for (int k = 0; k < BytesPerPixel; k++)
            {
                SquaredImage3D[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < Length; i++)
       {
           for (int j = 0; j < Width; j++)
           {
               for (int k = 0; k < BytesPerPixel; k++)
               {
                   SquaredImage3D[i][j][k] = SquaredImage[i * Width * BytesPerPixel + j * BytesPerPixel + k];
                   //Imagedata3d[i][j][k] = Imagedata[m];
                   //m = m+1;
               }
           }
       }
    cout<< "Flag 1"<<endl;
    

    int NewHeight = 0 ;
    int NewWidth = 0;
    for (int i = 0 ; i < Length  ; i++)
    {
        for (int j = 0 ; j < Width  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double u = double(i)/256;
                double v = double(j)/256;
//                double u = double(i);
//                double v = double(j);
                u = u-1;
                v = v-1;
                double x = 0 ;
                double y = 0 ;
//
                if(sqrt(pow(u,2)+pow(v,2))<=1)
                {
                    x = (((1.00/2.00) * (sqrt(2 + pow(u,2) - pow(v,2) + 2 * sqrt(2) * u))) - (0.5 * (sqrt(2 + pow(u,2) - pow(v,2) - 2 * sqrt (2) * u))) + 1)*256;
                    y = (((1.00/2.00) * (sqrt(2 - pow(u,2) + pow(v,2) + 2 * sqrt(2) * v))) - (0.5 * (sqrt(2 - pow(u,2) + pow(v,2) - 2 * sqrt (2) * v))) + 1)*256;
//
                    NewHeight=(x>=511)?floor(x)-1:floor(x);
                    NewWidth=(x>=511)?floor(y)-1:floor(y);
                    
//
                        
                    float DeltaHeight = x - NewHeight;
                    float DeltaWidth = y - NewWidth;
                    DiscedImage3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * ImageData3D[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * ImageData3D[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * ImageData3D[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * ImageData3D[NewHeight + 1][NewWidth + 1][k]);
                }
            }
        }
    }
    
  
//    ImageDataOp = Convert3dTo1d(ImageDataOp3D, Length, Width, BytesPerPixel);
//    unsigned char* ImageDataOp = new unsigned char[Length*Width*BytesPerPixel]();
    int m = 0;
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Width; j++)
        {
           DiscedImage [m] = DiscedImage3D[i][j][0];
           DiscedImage [m + 1] = DiscedImage3D[i][j][1];
           DiscedImage [m + 2] = DiscedImage3D[i][j][2];
            m = m + 3;
        }
    }
    
    
    
//
    NewHeight = 0 ;
    NewWidth = 0;
    for (int i = 0 ; i < Length  ; i++)
    {
        for (int j = 0 ; j < Width  ; j++)
        {
            for (int k = 0 ; k < BytesPerPixel ; k++)
            {
                double x = double (i) / 256;
                x = x - 1 ;
                double y = double (j) / 256;
                y = y - 1 ;
                //cout<<x<<"  "<<y<<endl;
                double a = 0 ;
                double b = 0 ;
                    a = (x * (sqrt(1 - pow(y,2)/2))+1)*256;
                    b = (y * (sqrt(1 - pow(x,2)/2))+1)*256;
//
                  
//
                NewHeight=(a>=511)?floor(a)-1:floor(a);
                NewWidth=(b>=511)?floor(b)-1:floor(b);
                  float DeltaHeight = a - NewHeight;
                    float DeltaWidth = b - NewWidth;
                    SquaredImage3D[i][j][k] = ((1 - DeltaHeight) * (1 - DeltaWidth) * DiscedImage3D[NewHeight][NewWidth][k] +
                                            (DeltaHeight * (1 - DeltaWidth)) * DiscedImage3D[NewHeight +1][NewWidth ][k] +
                                            ((1 - DeltaHeight) * DeltaWidth) * DiscedImage3D[NewHeight ][NewWidth + 1 ][k] +
                                            (DeltaHeight * DeltaWidth) * DiscedImage3D[NewHeight + 1][NewWidth + 1][k]);

            }
        }
    }
//    SquaredImage = Convert3dTo1d(ImageDataOp3DNew, Length, Width, BytesPerPixel);
    int n = 0;
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            SquaredImage [n] = SquaredImage3D[i][j][0];
            SquaredImage [n + 1] = SquaredImage3D[i][j][1];
            SquaredImage [n + 2] = SquaredImage3D[i][j][2];
            n= n + 3;
        }
    }

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(DiscedImage, sizeof(unsigned char), Width*Length*BytesPerPixel , file);
    fclose(file);

    if (!(file=fopen(argv[3],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(SquaredImage, sizeof(unsigned char), Width*Length*BytesPerPixel , file);
    fclose(file);
//    delete [] ImageData;
//    delete [] ImageDataOp;

    return 0 ;
}
