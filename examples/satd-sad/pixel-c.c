/* Copyright (c) 2006 Henri-Pierre Charles. Tous droits reserves */

/***
   NOM
     pixel-c
   UTILITE
     
   NOTES
     $Revision$
     
   HISTOIRE
          hpc - Jul 5, 2006: Created.
     $Log$
***/

#ifdef HAVE_STDINT_H
#include <stdint.h>
#else
#include <inttypes.h>
#endif
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "pixel-c.h"

#define PIXEL_SAD_C( name, lx, ly ) \
int name( uint8_t *pix1, int i_stride_pix1,  \
                 uint8_t *pix2, int i_stride_pix2 ) \
{                                                   \
    int i_sum = 0;                                  \
    int x, y;                                       \
    for( y = 0; y < ly; y++ )                       \
    {                                               \
        for( x = 0; x < lx; x++ )                   \
        {                                           \
            i_sum += abs( pix1[x] - pix2[x] );      \
        }                                           \
        pix1 += i_stride_pix1;                      \
        pix2 += i_stride_pix2;                      \
    }                                               \
    return i_sum;                                   \
}



#if 1
PIXEL_SAD_C( x264_pixel_sad_16x16, 16, 16 )
PIXEL_SAD_C( x264_pixel_sad_16x8,  16,  8 )
PIXEL_SAD_C( x264_pixel_sad_8x16,   8, 16 )
PIXEL_SAD_C( x264_pixel_sad_8x8,    8,  8 )
PIXEL_SAD_C( x264_pixel_sad_8x4,    8,  4 )
PIXEL_SAD_C( x264_pixel_sad_4x8,    4,  8 )
PIXEL_SAD_C( x264_pixel_sad_4x4,    4,  4 )
#endif


/****************************************************************************
 * pixel_satd_WxH: sum of 4x4 Hadamard transformed differences
 ****************************************************************************/
inline void x264_pixel_sub_wxh( int16_t *diff, int i_size,
                                uint8_t *pix1, int i_pix1, uint8_t *pix2, int i_pix2 )
{
    int y, x;

    for( y = 0; y < i_size; y++ )
    {
        for( x = 0; x < i_size; x++ )
        {
            diff[x + y*i_size] = pix1[x] - pix2[x];
        }
        pix1 += i_pix1;
        pix2 += i_pix2;
    }
}

static int pixel_satdref_wxh( uint8_t *pix1, int i_pix1, uint8_t *pix2, int i_pix2, int i_width, int i_height )
{
    int16_t tmp[4][4];
    int16_t diff[4][4];
    int x, y;
    int i_satd = 0;

    for( y = 0; y < i_height; y += 4 )
    {
        for( x = 0; x < i_width; x += 4 )
        {
            int d;

            x264_pixel_sub_wxh( (int16_t*)diff, 4, &pix1[x], i_pix1, &pix2[x], i_pix2 );

            for( d = 0; d < 4; d++ )
            {
                int s01, s23;
                int d01, d23;

                s01 = diff[d][0] + diff[d][1]; s23 = diff[d][2] + diff[d][3];
                d01 = diff[d][0] - diff[d][1]; d23 = diff[d][2] - diff[d][3];

                tmp[d][0] = s01 + s23;
                tmp[d][1] = s01 - s23;
                tmp[d][2] = d01 - d23;
                tmp[d][3] = d01 + d23;
            }
            for( d = 0; d < 4; d++ )
            {
                int s01, s23;
                int d01, d23;

                s01 = tmp[0][d] + tmp[1][d]; s23 = tmp[2][d] + tmp[3][d];
                d01 = tmp[0][d] - tmp[1][d]; d23 = tmp[2][d] - tmp[3][d];

                i_satd += abs( s01 + s23 ) + abs( s01 - s23 ) + abs( d01 - d23 ) + abs( d01 + d23 );
            }

        }
        pix1 += 4 * i_pix1;
        pix2 += 4 * i_pix2;
    }

    return i_satd / 2;
}

/****************************************************************************
 * pixel_satd_WxH: sum of 4x4 Hadamard transformed differences
 ****************************************************************************/
static int pixel_satd2_wxh( uint8_t *pix1, int i_pix1, uint8_t *pix2, int i_pix2, int i_width, int i_height )
{
    int16_t tmp[4][4];
    int16_t diff[4][4];
    int16_t m[4][4] = {{+1, +1, +1, +1}, 
		       {+1, +1, -1, -1}, 
		       {+1, -1, -1, +1}, 
		       {+1, -1, +1, -1}};
    int x, y, subx, suby, e, f;
    int i_satd = 0;

    for( y = 0; y < i_height; y += 4 )
    {
        for( x = 0; x < i_width; x += 4 )
        {
            int d;

	    /* pixel_sub_wxh( (int16_t*)diff, 4, &pix1[x], i_pix1, &pix2[x], i_pix2 ); */
	    for( suby = 0; suby < 4; suby++ )
	      {
		for( subx = 0; subx < 4; subx++ )
		  {
		    diff[suby][subx] = pix1[subx] - pix2[subx];
		  }
		pix1 += i_pix1;
		pix2 += i_pix2;
	      }

            for( d = 0; d < 4; d++ )
            {
		for (e = 0; e < 4; e++)
		  { 
		    tmp[d][e] = 0;
		    for (f = 0; f < 4 ; f++)
		      {
			tmp[d][e] += m[f][e]*diff[d][f];
		      }
		  }
            }
            for( d = 0; d < 4; d++ )
            {
                int s01, s23;
                int d01, d23;

                s01 = tmp[0][d] + tmp[1][d]; 
		s23 = tmp[2][d] + tmp[3][d];
                d01 = tmp[0][d] - tmp[1][d]; 
		d23 = tmp[2][d] - tmp[3][d];
                i_satd += abs( s01 + s23 ) + abs( s01 - s23 ) + abs( d01 - d23 ) + abs( d01 + d23 );
            }

        }
        pix1 += 4 * i_pix1;
        pix2 += 4 * i_pix2;
    }

    return i_satd / 2;
}

#define PIXEL_SATD_C( name, width, height ) \
int name( uint8_t *pix1, int i_stride_pix1, \
                 uint8_t *pix2, int i_stride_pix2 ) \
{ \
    return pixel_satdref_wxh( pix1, i_stride_pix1, pix2, i_stride_pix2, width, height ); \
}
PIXEL_SATD_C( x264_pixel_satd_16x16, 16, 16 )
PIXEL_SATD_C( x264_pixel_satd_16x8,  16, 8 )
PIXEL_SATD_C( x264_pixel_satd_8x16,  8, 16 )
PIXEL_SATD_C( x264_pixel_satd_8x8,   8, 8 )
PIXEL_SATD_C( x264_pixel_satd_8x4,   8, 4 )
PIXEL_SATD_C( x264_pixel_satd_4x8,   4, 8 )
PIXEL_SATD_C( x264_pixel_satd_4x4,   4, 4 )
