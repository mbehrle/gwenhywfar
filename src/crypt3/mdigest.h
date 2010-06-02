/***************************************************************************
 $RCSfile$
                             -------------------
    cvs         : $Id: crypttoken.h 1113 2007-01-10 09:14:16Z martin $
    begin       : Wed Mar 16 2005
    copyright   : (C) 2005 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef GWENHYWFAR_MDIGEST_H
#define GWENHYWFAR_MDIGEST_H

#include <gwenhywfar/list1.h>
#include <gwenhywfar/list2.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct GWEN_MDIGEST GWEN_MDIGEST;


GWEN_LIST_FUNCTION_LIB_DEFS(GWEN_MDIGEST, GWEN_MDigest, GWENHYWFAR_API)
GWEN_LIST2_FUNCTION_LIB_DEFS(GWEN_MDIGEST, GWEN_MDigest, GWENHYWFAR_API)


#include <gwenhywfar/hashalgo.h>
#include <gwenhywfar/stringlist.h>



GWENHYWFAR_API
void GWEN_MDigest_free(GWEN_MDIGEST *md);

GWENHYWFAR_API
GWEN_CRYPT_HASHALGOID GWEN_MDigest_GetHashAlgoId(const GWEN_MDIGEST *md);

GWENHYWFAR_API
uint8_t *GWEN_MDigest_GetDigestPtr(GWEN_MDIGEST *md);

GWENHYWFAR_API
unsigned int GWEN_MDigest_GetDigestSize(GWEN_MDIGEST *md);

GWENHYWFAR_API
int GWEN_MDigest_Begin(GWEN_MDIGEST *md);

GWENHYWFAR_API
int GWEN_MDigest_End(GWEN_MDIGEST *md);

GWENHYWFAR_API
int GWEN_MDigest_Update(GWEN_MDIGEST *md, const uint8_t *buf, unsigned int l);






GWENHYWFAR_API GWEN_MDIGEST *GWEN_MDigest_Md5_new();
GWENHYWFAR_API GWEN_MDIGEST *GWEN_MDigest_Rmd160_new();
GWENHYWFAR_API GWEN_MDIGEST *GWEN_MDigest_Sha1_new();
GWENHYWFAR_API GWEN_MDIGEST *GWEN_MDigest_Sha256_new();


/**
 * Generate a key from a given password and a salt according to RFC 2898.
 */
GWENHYWFAR_API int GWEN_MDigest_PKPDF2(GWEN_MDIGEST *md,
				       const char *password,
				       const uint8_t *pSalt,
				       uint32_t lSalt,
				       uint8_t *pKey,
				       uint32_t lKey,
				       uint32_t iterations);

GWENHYWFAR_API int GWEN_MDigest_HashFileTree(GWEN_MDIGEST *md,
					     const char *folder,
					     const char *ignoreFile,
					     GWEN_STRINGLIST *sl);

#ifdef __cplusplus
}
#endif


#endif


