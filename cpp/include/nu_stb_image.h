/*
*  This file is part of nuTetris
*
*  nuTetris is free software; you can redistribute it and/or modify
*  it under the terms of the MIT License.
*
*  nuTetris is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  MIT License for more details.
*
*  Author: <antonino.calderone@gmail.com>
*
*/

#ifndef __NU_STB_IMAGE_H__
#define __NU_STB_IMAGE_H__

namespace nu
{
   unsigned char *image_load(char const *filename, int &x, int &y);
   void image_free( unsigned char * image );
}

#endif // ! __NU_STB_IMAGE_H__
