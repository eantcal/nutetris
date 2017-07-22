/*
*  This file is part of nuTetris
*
*  nuTetris is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  nuTetris is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with nuTetris; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  US
*
*  Author: <antonino.calderone@ericsson.com>, <acaldmail@gmail.com>
*
*/


/* -------------------------------------------------------------------------- */

#ifndef _TETRIS_PIECE_FACTORY_H_
#define _TETRIS_PIECE_FACTORY_H_


/* -------------------------------------------------------------------------- */

#include "tetris_concrete_piece.h"

#include <exception>
#include <memory>
#include <vector>

/* -------------------------------------------------------------------------- */

namespace tetris
{


/* -------------------------------------------------------------------------- */

//! @brief This singleton class handles the creation of piece_t objects.
//! Each piece is cloned from a 'pre-created' catalog (using prototype pattern)
class piece_factory_t
{
   friend class concrete_piece_t;

public:

   //! Piece factory exception class
   struct exception_t : public std::exception
   {
      private:
         const std::string _pcause;

      public:
         exception_t(const char* err) throw() : 
            _pcause(err) 
         {}

         const char* what() const throw() override
         {
            return _pcause.c_str();
         }
   };


   //! Returns the factory object instance
   static piece_factory_t& get_instance();


   //! Creates a new piece object instance 
   piece_t::handle_t make(size_t piece_idx);


   //! Gets number of pieces within the catalog
   size_t get_piece_catalog_size() const throw()
   {
      return _piece_catalog.size();
   }

protected:

   //! Registers a new piece into the catalog
   void add_catalog(const piece_t& piece)
   {
      _piece_catalog.push_back(piece_t::handle_t(piece.clone()));
   }

   
private:
   //! piece catalog list
   std::vector< piece_t::handle_t > _piece_catalog;

   //! ctor
   piece_factory_t() throw() {}
};


/* -------------------------------------------------------------------------- */

} // namespace tetris


/* -------------------------------------------------------------------------- */

#endif
