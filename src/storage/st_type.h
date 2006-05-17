/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id: csv_p.h 120 2003-12-03 23:29:33Z aquamaniac $
 begin       : Thu Oct 30 2003
 copyright   : (C) 2003 by Martin Preuss
 email       : martin@libchipcard.de

 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef GWEN_STO_TYPE_H
#define GWEN_STO_TYPE_H

#include <gwenhywfar/list2.h>


typedef struct GWEN_STO_TYPE GWEN_STO_TYPE;

GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_STO_TYPE, GWEN_StoType, GWENHYWFAR_API)


#include <gwenhywfar/st_storage.h>
#include <gwenhywfar/st_vardef.h>


GWENHYWFAR_API
GWEN_STO_STORAGE *GWEN_StoType_GetStorage(const GWEN_STO_TYPE *ty);

GWENHYWFAR_API
GWEN_TYPE_UINT32 GWEN_StoType_GetId(const GWEN_STO_TYPE *ty);

GWENHYWFAR_API
const char *GWEN_StoType_GetTypeName(const GWEN_STO_TYPE *ty);

GWENHYWFAR_API
const char *GWEN_StoType_GetName(const GWEN_STO_TYPE *ty);

GWENHYWFAR_API
const GWEN_STO_VARDEF_LIST *GWEN_StoType_GetVarList(const GWEN_STO_TYPE *ty);

GWENHYWFAR_API
int GWEN_StoType_AddVar(GWEN_STO_TYPE *ty, const GWEN_STO_VARDEF *vdef);



#endif


