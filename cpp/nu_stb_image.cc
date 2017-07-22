/*
*  This file is part of nutetris
*
*  nutetris is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  nutetris is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with nutetris; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  US
*
*  Author: <antonino.calderone@ericsson.com>, <acaldmail@gmail.com>
*
*/

#include "nu_stb_image.h"
#include "stb_image.h"


// -----------------------------------------------------------------------------

namespace nu
{


// -----------------------------------------------------------------------------

    unsigned char *image_load(char const *filename, int &x, int &y)
    {
        int comp = 0;
        stbi_uc * image = stbi_load(filename, &x, &y, &comp, 4);

        return image;
    }


// -----------------------------------------------------------------------------

    void image_free( unsigned char * image )
    {
        if ( image )
        {
            stbi_image_free( image );
        }
    }


// -----------------------------------------------------------------------------

} // namespace nu
