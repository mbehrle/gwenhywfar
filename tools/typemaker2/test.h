/**********************************************************
 * This file has been automatically created by "typemaker2"
 * from the file "test.tm2".
 * Please do not edit this file, all changes will be lost.
 * Better edit the mentioned source file instead.
 **********************************************************/

#ifndef TEST_H
#define TEST_H


#ifdef __cplusplus
extern "C" {
#endif

/* needed system headers */
#include <gwenhywfar/types.h>
#include <gwenhywfar/list1.h>
#include <gwenhywfar/list2.h>
#include <gwenhywfar/inherit.h>
#include <gwenhywfar/idmap.h>
#include <gwenhywfar/db.h>
#include <gwenhywfar/xml.h>

typedef struct TEST TEST;
GWEN_LIST_FUNCTION_LIB_DEFS(TEST, Test, GWENHYWFAR_API)
GWEN_LIST2_FUNCTION_LIB_DEFS(TEST, Test, GWENHYWFAR_API)
GWEN_INHERIT_FUNCTION_LIB_DEFS(TEST, GWENHYWFAR_API)
GWEN_IDMAP_FUNCTION_LIB_DEFS(TEST, Test, GWENHYWFAR_API)



/** Constructor. */
GWENHYWFAR_API TEST *Test_new();

/** Destructor. */
GWENHYWFAR_API void Test_free(TEST *p_struct);

GWENHYWFAR_API TEST *Test_dup(const TEST *p_struct);

/** Getter.
 * Use this function to get the member "charPointer"
*/
GWENHYWFAR_API const char *Test_GetCharPointer(const TEST *p_struct);

/** Getter.
 * Use this function to get the member "charArray"
*/
GWENHYWFAR_API const char *Test_GetCharArray(const TEST *p_struct);

/** Setter.
 * Use this function to set the member "charPointer"
*/
GWENHYWFAR_API void Test_SetCharPointer(TEST *p_struct, const char *p_src);

/** Setter.
 * Use this function to set the member "charArray"
*/
GWENHYWFAR_API void Test_SetCharArray(TEST *p_struct, const char *p_src);

GWENHYWFAR_API void Test_ReadDb(TEST *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API int Test_WriteDb(const TEST *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API TEST *Test_fromDb(GWEN_DB_NODE *p_db);

GWENHYWFAR_API int Test_toDb(const TEST *p_struct, GWEN_DB_NODE *p_db);

GWENHYWFAR_API void Test_ReadXml(TEST *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API void Test_WriteXml(const TEST *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API void Test_toXml(const TEST *p_struct, GWEN_XMLNODE *p_db);

GWENHYWFAR_API TEST *Test_fromXml(GWEN_XMLNODE *p_db);

#ifdef __cplusplus
}
#endif

#endif

