#ifndef IMAGEGENERATION_H
#define IMAGEGENERATION_H
#include<iostream>
#include<fstream>

struct RGB
{
	double r;
	double g;
	double b;
};

//Tone reproduction
int TRmodel = 2;
//ward
double Lwa = 0.0;
double delta = 0.001;
int Lmax = 1;
int Ldmax = 100;

//reinhard
double a = 0.18;

//Adaptive Logarithmic
double Lwmax;
double b = 0.85;


void createBMP ( const char *filename, int w, int h, int dpi, RGB *data )
{
	FILE *f;
	int k = w*h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>( factor );
	int ppm = dpi*m;
	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
	bmpfileheader[2] = (unsigned char) ( filesize );
	bmpfileheader[3] = (unsigned char) ( filesize >> 8 );
	bmpfileheader[4] = (unsigned char) ( filesize >> 16 );
	bmpfileheader[5] = (unsigned char) ( filesize >> 24 );

	bmpinfoheader[4] = (unsigned char) ( w );
	bmpinfoheader[5] = (unsigned char) ( w >> 8 );
	bmpinfoheader[6] = (unsigned char) ( w >> 16 );
	bmpinfoheader[7] = (unsigned char) ( w >> 24 );

	bmpinfoheader[8] = (unsigned char) ( h );
	bmpinfoheader[9] = (unsigned char) ( h >> 8 );
	bmpinfoheader[10] = (unsigned char) ( h >> 16 );
	bmpinfoheader[11] = (unsigned char) ( h >> 24 );

	bmpinfoheader[21] = (unsigned char) ( s );
	bmpinfoheader[22] = (unsigned char) ( s >> 8 );
	bmpinfoheader[23] = (unsigned char) ( s >> 16 );
	bmpinfoheader[24] = (unsigned char) ( s >> 24 );

	bmpinfoheader[25] = (unsigned char) ( ppm );
	bmpinfoheader[26] = (unsigned char) ( ppm >> 8 );
	bmpinfoheader[27] = (unsigned char) ( ppm >> 16 );
	bmpinfoheader[28] = (unsigned char) ( ppm >> 24 );

	bmpinfoheader[29] = (unsigned char) ( ppm );
	bmpinfoheader[30] = (unsigned char) ( ppm >> 8 );
	bmpinfoheader[31] = (unsigned char) ( ppm >> 16 );
	bmpinfoheader[32] = (unsigned char) ( ppm >> 24 );

	f = fopen ( filename, "wb" );

	fwrite ( bmpfileheader, 1, 14, f );
	fwrite ( bmpinfoheader, 1, 40, f );
	double red;
	double green;
	double blue;
	for ( int i = 0; i < k; i++ )
	{

		red = data[i].r * Lmax;
		green = data[i].g * Lmax;
		blue = data[i].b * Lmax;

		double L = 0.27*red + 0.67*green + 0.06*blue;

		Lwa += log ( delta + L );
	}
	Lwa = exp ( Lwa / k );
	double sf = ( 1.219 + pow ( Ldmax / 2, 0.4 ) ) / ( 1.219 + pow ( Lwa, 0.4 ) );
	sf = pow ( sf, 2.5 );
	double Ld = sf / Ldmax;
	Lwmax = Lmax / Lwa;
	for ( int i = 0; i < k; i++ )
	{
		double max = -99999;

		double R, Rs, Rr;
		double G, Gs, Gr;
		double B, Bs, Br;


		R = data[i].r * Lmax;
		G = data[i].g * Lmax;
		B = data[i].b * Lmax;

		double L = 0.27*R + 0.67*G + 0.06*B;
		double Lw = L / Lwa;

		if ( TRmodel == 2 )
		{
			double exponent = log ( b ) / log ( 0.5 );
			double first = 1 / log10 ( Lwmax + 1 );
			double second = log ( Lw + 1 ) / log ( 2 + 0.8*( pow ( Lw / Lwmax, exponent ) ) );
			Ld = first * second;
		}

		Rs = R * a / Lwa;
		Gs = G * a / Lwa;
		Bs = B * a / Lwa;

		Rr = Rs*( 1 + Rs );
		Gr = Gs*( 1 + Gs );
		Br = Bs*( 1 + Bs );

		double wred;
		double wgreen;
		double wblue;

		if ( TRmodel == 0 || TRmodel == 2 )
		{
			wred = Ld*R;
			wgreen = Ld*G;
			wblue = Ld*B;
		}
		else if ( TRmodel == 1 )
		{
			wred = Ldmax*Rr;
			wgreen = Ldmax*Gr;
			wblue = Ldmax*Br;
		}

		if ( wred > max )
		{
			max = wred;
		}
		if ( wgreen > max )
		{
			max = wgreen;
		}
		if ( wblue > max )
		{
			max = wblue;
		}

		if ( max > 1.0 )
		{
			wred = ( wred ) / max;
			wgreen = ( wgreen ) / max;
			wblue = ( wblue ) / max;
		}

		red = (wred) * 255;
		blue = (wblue) * 255;
		green = (wgreen) * 255;

		unsigned char color[3] = { (int) floor ( blue ), (int) floor ( green ), (int) floor ( red ) };
		fwrite ( color, 1, 3, f );
	}
	fclose ( f );
}

#endif // !1
