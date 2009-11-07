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

int x264_pixel_sad_16x16(uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_16x8 (uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_8x16 (uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_8x8  (uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_8x4  (uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_4x8  (uint8_t *, int , uint8_t *, int);
int x264_pixel_sad_4x4  (uint8_t *, int , uint8_t *, int);

int x264_pixel_satd_16x16(uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_16x8 (uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_8x16 (uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_8x8  (uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_8x4  (uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_4x8  (uint8_t *, int, uint8_t *, int);
int x264_pixel_satd_4x4  (uint8_t *, int, uint8_t *, int);

void x264_pixel_sub_wxh(int16_t *, int, uint8_t *, int, uint8_t *, int);
