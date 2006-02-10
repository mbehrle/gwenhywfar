/***************************************************************************
 $RCSfile$
 -------------------
 cvs         : $Id$
 begin       : Thu Nov 06 2003
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


#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/* Define this if you are extending the "class" CryptKey */
#define GWEN_EXTEND_CRYPTKEY


#include "cryptssl_rsa_p.h"
#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>
#include <gwenhywfar/text.h> /* DEBUG ! */
#include <gwenhywfar/waitcallback.h>

#include <openssl/rsa.h>
#include <openssl/objects.h>
#include <openssl/err.h>

#include "cryptssl_p.h"


void GWEN_CryptKeyRSA_FreeKeyData(GWEN_CRYPTKEY *key){
  RSA *kd;

  kd=(RSA*)GWEN_CryptKey_GetKeyData(key);
  if (kd)
    RSA_free(kd);
}



void GWEN_CryptKeyRSA_DumpPubKey(const GWEN_CRYPTKEY *key){
  GWEN_DB_NODE *dbDebug;
  GWEN_ERRORCODE lerr;

  dbDebug=GWEN_DB_Group_new("key");
  lerr=GWEN_CryptKey_toDb(key, dbDebug, 1);
  if (!GWEN_Error_IsOk(lerr)) {
    DBG_ERROR_ERR(GWEN_LOGDOMAIN, lerr);
  }
  else {
    const void *p;
    unsigned int len;

    p=GWEN_DB_GetBinValue(dbDebug, "data/n", 0, 0, 0, &len);
    DBG_ERROR(GWEN_LOGDOMAIN,
              "Key data follows (%d bytes):", len);
    GWEN_DB_Dump(dbDebug, stderr, 2);
    if (p && len)
      GWEN_Text_DumpString((const char*)p, len, stderr, 2);
  }
  GWEN_DB_Group_free(dbDebug);
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Encrypt(const GWEN_CRYPTKEY *key,
                                        GWEN_BUFFER *src,
                                        GWEN_BUFFER *dst){
  unsigned int srclen;
  int dstlen;
  unsigned char *psrc;
  unsigned char *pdst;

  assert(key);
  assert(src);
  assert(dst);

  srclen=GWEN_Buffer_GetUsedBytes(src);
  if (srclen!=GWEN_CryptKey_GetChunkSize(key)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Size %d!=%d",
              srclen, GWEN_CryptKey_GetChunkSize(key));
    if (1) {
      DBG_ERROR(GWEN_LOGDOMAIN,
                "Offending key follows");
      GWEN_CryptKeyRSA_DumpPubKey(key);
    }

    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BAD_SIZE);
  }
  if (GWEN_Buffer_AllocRoom(dst, srclen)) {
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BUFFER_FULL);
  }
  psrc=(unsigned char*)GWEN_Buffer_GetStart(src);
  pdst=(unsigned char*)GWEN_Buffer_GetPosPointer(dst);

  dstlen=RSA_public_encrypt(srclen, psrc, pdst,
                            GWEN_CryptKey_GetKeyData(key),
                            RSA_NO_PADDING);
  if (dstlen==-1) {
    char errbuf[256];

    ERR_error_string_n(ERR_get_error(), errbuf, sizeof(errbuf));
    DBG_ERROR(GWEN_LOGDOMAIN,
              "OpenSSL error: %s", errbuf);
    ERR_print_errors_fp(stderr);
    if (1) {
      DBG_ERROR(GWEN_LOGDOMAIN,
                "Offending key follows");
      GWEN_CryptKeyRSA_DumpPubKey(key);
    }
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_ENCRYPT);
  }
  if ((unsigned int)dstlen!=srclen) {
    DBG_ERROR(GWEN_LOGDOMAIN,
              "ERROR: Unexpected dstlen (%d != %u)\n",
              dstlen, srclen);
    if (1) {
      DBG_ERROR(GWEN_LOGDOMAIN,
                "Offending key follows");
      GWEN_CryptKeyRSA_DumpPubKey(key);
    }
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_ENCRYPT);
  }
  GWEN_Buffer_IncrementPos(dst, dstlen);
  GWEN_Buffer_AdjustUsedBytes(dst);
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Decrypt(const GWEN_CRYPTKEY *key,
                                        GWEN_BUFFER *src,
                                        GWEN_BUFFER *dst){
  unsigned int srclen;
  unsigned int dstlen;
  unsigned char *psrc;
  unsigned char *pdst;

  assert(key);
  assert(src);
  assert(dst);

  srclen=GWEN_Buffer_GetUsedBytes(src);
  if (srclen!=GWEN_CryptKey_GetChunkSize(key)) {
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BAD_SIZE);
  }
  if (GWEN_Buffer_AllocRoom(dst, srclen)) {
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BUFFER_FULL);
  }
  psrc=(unsigned char*)GWEN_Buffer_GetStart(src);
  pdst=(unsigned char*)GWEN_Buffer_GetPosPointer(dst);

  dstlen=RSA_private_decrypt(srclen, psrc, pdst,
                             GWEN_CryptKey_GetKeyData(key),
                             RSA_NO_PADDING);
  if (dstlen!=srclen) {
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_ENCRYPT);
  }
  GWEN_Buffer_IncrementPos(dst, dstlen);
  GWEN_Buffer_AdjustUsedBytes(dst);
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Sign(const GWEN_CRYPTKEY *key,
                                     GWEN_BUFFER *src,
                                     GWEN_BUFFER *dst){
  unsigned int srclen;
  unsigned char *pdst;
  unsigned char *psrc;
  int firstPos;
  RSA *kd;
  BN_CTX *bnctx;
  BIGNUM *bnresult1;
  BIGNUM *bnresult2;
  BIGNUM *bnSignature;
  BIGNUM *bnhash;
  int res;

  assert(key);
  assert(src);
  assert(dst);

  kd=(RSA*)GWEN_CryptKey_GetKeyData(key);
  assert(kd);

  firstPos=GWEN_Buffer_GetPos(dst);

  bnctx=BN_CTX_new();
  BN_CTX_start(bnctx);

  bnhash=BN_CTX_get(bnctx);
  bnresult1=BN_CTX_get(bnctx);
  bnresult2=BN_CTX_get(bnctx);

  srclen=GWEN_Buffer_GetUsedBytes(src);
  if (srclen!=GWEN_CryptKey_GetChunkSize(key)) {
    DBG_INFO(GWEN_LOGDOMAIN, "Bad size of source data (%d!=%d)",
             srclen, GWEN_CryptKey_GetChunkSize(key));
    BN_CTX_end(bnctx);
    BN_CTX_free(bnctx);
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BAD_SIZE);
  }
  if (GWEN_Buffer_AllocRoom(dst, srclen)) {
    DBG_INFO(GWEN_LOGDOMAIN, "Could not allocate room for %d bytes", srclen);
    BN_CTX_end(bnctx);
    BN_CTX_free(bnctx);
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_BUFFER_FULL);
  }

  /* sign the src */
  psrc=(unsigned char*)GWEN_Buffer_GetStart(src);
  bnhash=BN_bin2bn(psrc, srclen, bnhash);
  /* result1=(hash^privateExponent) % modulus */
  res=BN_mod_exp(bnresult1, bnhash, kd->d, kd->n, bnctx);

  /* the iso9796-appendix is as follows:
   * if ((the modulus - the calculated signature) <
   *    (the calculated signature))
   * then use (the modulus - the calculated signature) as signature
   */

  /* result2=modulus-result1 */
  if (!BN_sub(bnresult2, kd->n, bnresult1)) {
    DBG_ERROR(GWEN_LOGDOMAIN, "Math error");
    BN_CTX_end(bnctx);
    BN_CTX_free(bnctx);
    return GWEN_Error_new(0,
                          GWEN_ERROR_SEVERITY_ERR,
                          GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                          GWEN_CRYPT_ERROR_SIGN);
  }

  bnSignature=bnresult1;

  if (!(GWEN_CryptKey_GetFlags(key) &
        GWEN_CRYPT_FLAG_DISABLE_SMALLER_SIGNATURE)) {
    if (BN_cmp(bnresult2, bnresult1) < 0) {
      /* GWEN_WaitCallback_Log(0, "Using smaller signature"); */
      DBG_INFO(GWEN_LOGDOMAIN, "Using smaller signature");
      bnSignature=bnresult2;
    }
    else {
      /* GWEN_WaitCallback_Log(0, "Using normal signature"); */
    }
  }
  else {
    /* GWEN_WaitCallback_Log(0, "Always using normal signature"); */
  }

  if (GWEN_Buffer_GetPos(dst)!=0) {
    DBG_WARN(GWEN_LOGDOMAIN,
             "Not at start pos, we could otherwise be much faster");
  }

  pdst=(unsigned char*)GWEN_Buffer_GetPosPointer(dst);
  res=BN_bn2bin(bnSignature, pdst);
  GWEN_Buffer_IncrementPos(dst, res);
  GWEN_Buffer_AdjustUsedBytes(dst);

  GWEN_Buffer_SetPos(dst, firstPos);

  /* padd to multiple of 8 bytes */
  if (res % 8) {
    unsigned int j;
    unsigned int k;

    j=8-((unsigned int)res%8);
    if (GWEN_Buffer_ReserveBytes(dst, j)) {
      DBG_INFO(GWEN_LOGDOMAIN, "Could not reserve %d bytes", j);
      BN_CTX_end(bnctx);
      BN_CTX_free(bnctx);
      return GWEN_Error_new(0,
                            GWEN_ERROR_SEVERITY_ERR,
                            GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                            GWEN_CRYPT_ERROR_BUFFER_FULL);
    }
    for (k=0; k<j; k++) {
      GWEN_Buffer_InsertByte(dst, 0);
    }
  }

  BN_CTX_end(bnctx);
  BN_CTX_free(bnctx);
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Verify(const GWEN_CRYPTKEY *key,
                                       GWEN_BUFFER *src,
                                       GWEN_BUFFER *signature){
  unsigned int srclen;
  unsigned int siglen;
  unsigned char *psrc;
  unsigned char *psig;
  RSA *kd;
  BN_CTX *bnctx;
  BIGNUM *bnsig1;
  BIGNUM *bnsig2;
  BIGNUM *bndecsig1;
  BIGNUM *bndecsig2;
  BIGNUM *bnhash;

  assert(key);
  assert(src);
  assert(signature);

  kd=(RSA*)GWEN_CryptKey_GetKeyData(key);
  assert(kd);

  bnctx=BN_CTX_new();
  BN_CTX_start(bnctx);

  bnsig1=BN_CTX_get(bnctx);
  bnsig2=BN_CTX_get(bnctx);
  bndecsig1=BN_CTX_get(bnctx);
  bndecsig2=BN_CTX_get(bnctx);
  bnhash=BN_CTX_get(bnctx);

  srclen=GWEN_Buffer_GetUsedBytes(src);
  psrc=(unsigned char*)GWEN_Buffer_GetStart(src);
  siglen=GWEN_Buffer_GetUsedBytes(signature);
  psig=(unsigned char*)GWEN_Buffer_GetStart(signature);

  /* decrypt the institutes signature */
  bnsig1=BN_bin2bn(psig, siglen, bnsig1);
  BN_sub(bnsig2, kd->n, bnsig1);
  bnhash=BN_bin2bn(psrc, srclen, bnhash);

  BN_mod_exp(bndecsig1, bnsig1, kd->e, kd->n, bnctx);
  BN_mod_exp(bndecsig2, bnsig2, kd->e, kd->n, bnctx);

  if (BN_cmp(bndecsig1, bnhash)!=0) {
    DBG_INFO(GWEN_LOGDOMAIN, "Trying other signature variant");
    if (BN_cmp(bndecsig2, bnhash)!=0) {
      DBG_ERROR(GWEN_LOGDOMAIN, "Signature does not match");
      BN_CTX_end(bnctx);
      BN_CTX_free(bnctx);
      return GWEN_Error_new(0,
                            GWEN_ERROR_SEVERITY_ERR,
                            GWEN_Error_FindType(GWEN_CRYPT_ERROR_TYPE),
                            GWEN_CRYPT_ERROR_VERIFY);
    }
  }

  BN_CTX_end(bnctx);
  BN_CTX_free(bnctx);

  return 0;
}



unsigned int GWEN_CryptKeyRSA_GetChunkSize(const GWEN_CRYPTKEY *key){
  RSA *kd;
  unsigned int i;

  assert(key);
  kd=(RSA*)GWEN_CryptKey_GetKeyData(key);
  assert(kd);
  i=RSA_size(kd);
  return i;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_FromDb(GWEN_CRYPTKEY *key,
                                       GWEN_DB_NODE *db){
  int pub;
  const void *p;
  unsigned int len;
  RSA *kd;
  BIGNUM *bn;
  int keylen;

  kd=RSA_new();
  assert(kd);

  DBG_DEBUG(GWEN_LOGDOMAIN, "Reading this key:");
  if (GWEN_Logger_GetLevel(GWEN_LOGDOMAIN)>=GWEN_LoggerLevel_Debug)
    GWEN_DB_Dump(db, stderr, 2);

  /* needed because older versions of GWEN did not store the keylength */
  keylen=GWEN_CryptKey_GetKeyLength(key);
  if (keylen==0) {
    keylen=768;
    GWEN_CryptKey_SetKeyLength(key, keylen);
  }

  pub=GWEN_DB_GetIntValue(db, "public", 0, 1);
  GWEN_CryptKey_SetPublic(key, pub);

  p=GWEN_DB_GetBinValue(db, "e", 0, 0, 0, &len);
  if (p) {
    bn=BN_new();
    kd->e=BN_bin2bn((unsigned char*) p, len, bn);
  }
  else {
    /* OpenSSL might be using blinding, so we MUST set e even if it is not
     * otherwise used for private keys */
    kd->e=BN_new();
    BN_set_word(kd->e, GWEN_CRYPT_RSA_DEFAULT_EXPONENT);
  }

  p=GWEN_DB_GetBinValue(db, "n", 0, 0, 0, &len);
  if (p) {
    bn=BN_new();
    kd->n=BN_bin2bn((unsigned char*) p, len, bn);
  }
  else
    kd->n=BN_new();

  if (!pub) {
    p=GWEN_DB_GetBinValue(db, "p", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->p=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->p=BN_new();

    p=GWEN_DB_GetBinValue(db, "q", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->q=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->q=BN_new();

    p=GWEN_DB_GetBinValue(db, "dmp1", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->dmp1=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->dmp1=BN_new();

    p=GWEN_DB_GetBinValue(db, "dmq1", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->dmq1=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->dmq1=BN_new();

    p=GWEN_DB_GetBinValue(db, "iqmp", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->iqmp=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->iqmp=BN_new();

    p=GWEN_DB_GetBinValue(db, "d", 0, 0, 0, &len);
    if (p) {
      bn=BN_new();
      kd->d=BN_bin2bn((unsigned char*) p, len, bn);
    }
    else
      kd->d=BN_new();
  }

  GWEN_CryptKey_SetKeyData(key, kd);

  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_ToDb(const GWEN_CRYPTKEY *key,
                                     GWEN_DB_NODE *db,
                                     int pub){
  char buffer[GWEN_CRYPT_RSA_MAX_KEY_LENGTH/8];
  int l;
  RSA *kd;

  kd=GWEN_CryptKey_GetKeyData(key);
  assert(kd);
  GWEN_DB_SetIntValue(db,
                      GWEN_DB_FLAGS_DEFAULT |
                      GWEN_DB_FLAGS_OVERWRITE_VARS,
                      "public", pub);
  if (kd->n) {
    l=BN_bn2bin(kd->n, (unsigned char*) &buffer);
    GWEN_DB_SetBinValue(db,
                        GWEN_DB_FLAGS_DEFAULT |
                        GWEN_DB_FLAGS_OVERWRITE_VARS,
                        "n", buffer, l);
  }

  if (kd->e) {
    l=BN_bn2bin(kd->e, (unsigned char*) &buffer);
    GWEN_DB_SetBinValue(db,
                        GWEN_DB_FLAGS_DEFAULT |
                        GWEN_DB_FLAGS_OVERWRITE_VARS,
                        "e", buffer, l);
  }

  if (pub==0) {
    if (kd->p) {
      l=BN_bn2bin(kd->p, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "p", buffer, l);
    }

    if (kd->q) {
      l=BN_bn2bin(kd->q, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "q", buffer, l);
    }

    if (kd->dmp1) {
      l=BN_bn2bin(kd->dmp1, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "dmp1", buffer, l);
    }

    if (kd->dmq1) {
      l=BN_bn2bin(kd->dmq1, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "dmq1", buffer, l);
    }

    if (kd->iqmp) {
      l=BN_bn2bin(kd->iqmp, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "iqmp", buffer, l);
    }

    if (kd->d) {
      l=BN_bn2bin(kd->d, (unsigned char*) &buffer);
      GWEN_DB_SetBinValue(db,
                          GWEN_DB_FLAGS_DEFAULT |
                          GWEN_DB_FLAGS_OVERWRITE_VARS,
                          "d", buffer, l);
    }
  }
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Generate(GWEN_CRYPTKEY *key,
                                         unsigned int keylength){
  RSA *newKey;

  assert(key);
  if (keylength==0)
    keylength=GWEN_CRYPT_RSA_DEFAULT_KEY_LENGTH;

  newKey=RSA_generate_key(keylength, GWEN_CRYPT_RSA_DEFAULT_EXPONENT,
                          NULL, NULL);
  assert(newKey);
  GWEN_CryptKey_SetKeyData(key, newKey);
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Open(GWEN_CRYPTKEY *key){
  GWEN_CryptKey_IncrementOpenCount(key);
  return 0;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Close(GWEN_CRYPTKEY *key){
  GWEN_CryptKey_DecrementOpenCount(key);
  return 0;
}



GWEN_CRYPTKEY *GWEN_CryptKeyRSA_new(){
  GWEN_CRYPTKEY *key;
  RSA *keyData;

  key=GWEN_CryptKey_new();
  keyData=RSA_new();
  assert(keyData);
  GWEN_CryptKey_SetKeyData(key, keyData);

  GWEN_CryptKey_SetEncryptFn(key, GWEN_CryptKeyRSA_Encrypt);
  GWEN_CryptKey_SetDecryptFn(key, GWEN_CryptKeyRSA_Decrypt);
  GWEN_CryptKey_SetSignFn(key, GWEN_CryptKeyRSA_Sign);
  GWEN_CryptKey_SetVerifyFn(key, GWEN_CryptKeyRSA_Verify);
  GWEN_CryptKey_SetGetChunkSizeFn(key, GWEN_CryptKeyRSA_GetChunkSize);
  GWEN_CryptKey_SetFromDbFn(key, GWEN_CryptKeyRSA_FromDb);
  GWEN_CryptKey_SetToDbFn(key, GWEN_CryptKeyRSA_ToDb);
  GWEN_CryptKey_SetGenerateKeyFn(key, GWEN_CryptKeyRSA_Generate);
  GWEN_CryptKey_SetFreeKeyDataFn(key, GWEN_CryptKeyRSA_FreeKeyData);
  GWEN_CryptKey_SetOpenFn(key, GWEN_CryptKeyRSA_Open);
  GWEN_CryptKey_SetCloseFn(key, GWEN_CryptKeyRSA_Close);
  GWEN_CryptKey_SetDupFn(key, GWEN_CryptKeyRSA_dup);
  return key;
}



GWEN_CRYPTKEY *GWEN_CryptKeyRSA_dup(const GWEN_CRYPTKEY *key){
  GWEN_CRYPTKEY *newKey;
  RSA *keyData;
  RSA *newKeyData;

  keyData=(RSA*)GWEN_CryptKey_GetKeyData(key);
  assert(keyData);
  newKey=GWEN_CryptKey_new();
  newKeyData=RSA_new();
  assert(newKeyData);
  newKeyData->n=BN_dup(keyData->n);
  newKeyData->e=BN_dup(keyData->e);
  newKeyData->p=BN_dup(keyData->p);
  newKeyData->q=BN_dup(keyData->q);
  newKeyData->dmp1=BN_dup(keyData->dmp1);
  newKeyData->dmq1=BN_dup(keyData->dmq1);
  newKeyData->iqmp=BN_dup(keyData->iqmp);
  newKeyData->d=BN_dup(keyData->d);
  GWEN_CryptKey_SetKeyData(newKey, newKeyData);
  return newKey;
}



GWEN_ERRORCODE GWEN_CryptKeyRSA_Register(){
  GWEN_CRYPTKEY_PROVIDER *pr;
  GWEN_ERRORCODE err;

  pr=GWEN_CryptProvider_new();
  GWEN_CryptProvider_SetNewKeyFn(pr, GWEN_CryptKeyRSA_new);
  GWEN_CryptProvider_SetName(pr, GWEN_CRYPT_RSA_NAME);
  err=GWEN_Crypt_RegisterProvider(pr);
  if (!GWEN_Error_IsOk(err)) {
    GWEN_CryptProvider_free(pr);
    DBG_INFO(GWEN_LOGDOMAIN, "called from here");
    return err;
  }
  return 0;
}






