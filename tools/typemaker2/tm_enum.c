/**********************************************************
 * This file has been automatically created by "typemaker2"
 * from the file "tm_enum.xml".
 * Please do not edit this file, all changes will be lost.
 * Better edit the mentioned source file instead.
 **********************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "tm_enum_p.h"

#include <gwenhywfar/misc.h>
#include <gwenhywfar/debug.h>

/* code headers */

/* macro functions */
GWEN_LIST_FUNCTIONS(TYPEMAKER2_ENUM, Typemaker2_Enum)


TYPEMAKER2_ENUM *Typemaker2_Enum_new() {
  TYPEMAKER2_ENUM *p_struct;

  GWEN_NEW_OBJECT(TYPEMAKER2_ENUM, p_struct)
  GWEN_LIST_INIT(TYPEMAKER2_ENUM, p_struct)
  /* members */
  p_struct->id=NULL;
  p_struct->prefix=NULL;
  p_struct->type=NULL;
  p_struct->items=Typemaker2_Item_List_new();
  p_struct->toStringFn=NULL;
  p_struct->fromStringFn=NULL;

  return p_struct;
}

void Typemaker2_Enum_free(TYPEMAKER2_ENUM *p_struct) {
  if (p_struct) {
    GWEN_LIST_FINI(TYPEMAKER2_ENUM, p_struct)
  /* members */
    free(p_struct->id);
    free(p_struct->prefix);
    free(p_struct->type);
    Typemaker2_Item_List_free(p_struct->items);
    free(p_struct->toStringFn);
    free(p_struct->fromStringFn);
    GWEN_FREE_OBJECT(p_struct);
  }
}

TYPEMAKER2_ENUM *Typemaker2_Enum_dup(const TYPEMAKER2_ENUM *p_src) {
  TYPEMAKER2_ENUM *p_struct;

  assert(p_src);
  p_struct=Typemaker2_Enum_new();
  /* member "id" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->id) {
    free(p_struct->id);
    p_struct->id=NULL;
  }
  if (p_src->id) {
    p_struct->id=strdup(p_src->id);
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "prefix" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->prefix) {
    free(p_struct->prefix);
    p_struct->prefix=NULL;
  }
  if (p_src->prefix) {
    p_struct->prefix=strdup(p_src->prefix);
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "type" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->type) {
    free(p_struct->type);
    p_struct->type=NULL;
  }
  if (p_src->type) {
    p_struct->type=strdup(p_src->type);
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "items" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->items) {
    Typemaker2_Item_List_free(p_struct->items);
    p_struct->items=NULL;
  }
  if (p_src->items) {
    { if (p_src->items) { TYPEMAKER2_ITEM_LIST *t; TYPEMAKER2_ITEM *elem; t=Typemaker2_Item_List_new(); elem=Typemaker2_Item_List_First(p_src->items); while(elem) { TYPEMAKER2_ITEM *cpy; cpy=Typemaker2_Item_dup(elem); Typemaker2_Item_List_Add(cpy, t); elem=Typemaker2_Item_List_Next(elem); } p_struct->items=t; } else p_struct->items=NULL; }
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON

  /* member "toStringFn" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->toStringFn) {
    free(p_struct->toStringFn);
    p_struct->toStringFn=NULL;
  }
  if (p_src->toStringFn) {
    p_struct->toStringFn=strdup(p_src->toStringFn);
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON

  /* member "fromStringFn" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->fromStringFn) {
    free(p_struct->fromStringFn);
    p_struct->fromStringFn=NULL;
  }
  if (p_src->fromStringFn) {
    p_struct->fromStringFn=strdup(p_src->fromStringFn);
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON

  return p_struct;
}

const char *Typemaker2_Enum_GetId(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  return p_struct->id;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

const char *Typemaker2_Enum_GetPrefix(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  return p_struct->prefix;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

const char *Typemaker2_Enum_GetType(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  return p_struct->type;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

TYPEMAKER2_ITEM_LIST *Typemaker2_Enum_GetItems(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  return p_struct->items;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

const char *Typemaker2_Enum_GetToStringFn(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  return p_struct->toStringFn;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

const char *Typemaker2_Enum_GetFromStringFn(const TYPEMAKER2_ENUM *p_struct) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  return p_struct->fromStringFn;
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

void Typemaker2_Enum_SetId(TYPEMAKER2_ENUM *p_struct, const char *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  if (p_struct->id) {
    free(p_struct->id);
  }
  if (p_src) {
    p_struct->id=strdup(p_src);
  }
  else {
    p_struct->id=NULL;
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

void Typemaker2_Enum_SetPrefix(TYPEMAKER2_ENUM *p_struct, const char *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  if (p_struct->prefix) {
    free(p_struct->prefix);
  }
  if (p_src) {
    p_struct->prefix=strdup(p_src);
  }
  else {
    p_struct->prefix=NULL;
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

void Typemaker2_Enum_SetType(TYPEMAKER2_ENUM *p_struct, const char *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  assert(p_struct);
  if (p_struct->type) {
    free(p_struct->type);
  }
  if (p_src) {
    p_struct->type=strdup(p_src);
  }
  else {
    p_struct->type=NULL;
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
}

void Typemaker2_Enum_SetItems(TYPEMAKER2_ENUM *p_struct, const TYPEMAKER2_ITEM_LIST *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  if (p_struct->items) {
    Typemaker2_Item_List_free(p_struct->items);
  }
  if (p_src) {
    { if (p_src) { TYPEMAKER2_ITEM_LIST *t; TYPEMAKER2_ITEM *elem; t=Typemaker2_Item_List_new(); elem=Typemaker2_Item_List_First(p_src); while(elem) { TYPEMAKER2_ITEM *cpy; cpy=Typemaker2_Item_dup(elem); Typemaker2_Item_List_Add(cpy, t); elem=Typemaker2_Item_List_Next(elem); } p_struct->items=t; } else p_struct->items=NULL; }
  }
  else {
    p_struct->items=Typemaker2_Item_List_new();
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

void Typemaker2_Enum_SetToStringFn(TYPEMAKER2_ENUM *p_struct, const char *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  if (p_struct->toStringFn) {
    free(p_struct->toStringFn);
  }
  if (p_src) {
    p_struct->toStringFn=strdup(p_src);
  }
  else {
    p_struct->toStringFn=NULL;
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

void Typemaker2_Enum_SetFromStringFn(TYPEMAKER2_ENUM *p_struct, const char *p_src) {
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  assert(p_struct);
  if (p_struct->fromStringFn) {
    free(p_struct->fromStringFn);
  }
  if (p_src) {
    p_struct->fromStringFn=strdup(p_src);
  }
  else {
    p_struct->fromStringFn=NULL;
  }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

void Typemaker2_Enum_ReadXml(TYPEMAKER2_ENUM *p_struct, GWEN_XMLNODE *p_db) {
  assert(p_struct);
  /* member "id" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->id) {
    free(p_struct->id);
  }
  p_struct->id=NULL;
  { const char *s; 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 s=GWEN_XMLNode_GetProperty(p_db, "id", NULL); 
#else
 s=GWEN_XMLNode_GetCharValue(p_db, "id", NULL); 
#endif
 if (s) p_struct->id=strdup(s); }

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  /* member "prefix" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->prefix) {
    free(p_struct->prefix);
  }
  p_struct->prefix=NULL;
  { const char *s; 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 s=GWEN_XMLNode_GetProperty(p_db, "prefix", NULL); 
#else
 s=GWEN_XMLNode_GetCharValue(p_db, "prefix", NULL); 
#endif
 if (s) p_struct->prefix=strdup(s); }

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  /* member "type" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->type) {
    free(p_struct->type);
  }
  p_struct->type=NULL;
  { const char *s; 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 s=GWEN_XMLNode_GetProperty(p_db, "type", NULL); 
#else
 s=GWEN_XMLNode_GetCharValue(p_db, "type", NULL); 
#endif
 if (s) p_struct->type=strdup(s); }

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  /* member "items" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->items) {
    Typemaker2_Item_List_free(p_struct->items);
  }
  p_struct->items=Typemaker2_Item_List_new();
  /* member "items" is volatile, not reading from xml */

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  /* member "toStringFn" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->toStringFn) {
    free(p_struct->toStringFn);
  }
  p_struct->toStringFn=NULL;
  /* member "toStringFn" is volatile, not reading from xml */

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  /* member "fromStringFn" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
  if (p_struct->fromStringFn) {
    free(p_struct->fromStringFn);
  }
  p_struct->fromStringFn=NULL;
  /* member "fromStringFn" is volatile, not reading from xml */

#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_VOLATILE_ON
}

void Typemaker2_Enum_WriteXml(const TYPEMAKER2_ENUM *p_struct, GWEN_XMLNODE *p_db) {
  assert(p_struct);
  /* member "id" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->id) { 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 GWEN_XMLNode_SetProperty(p_db, "id", p_struct->id); 
#else
 GWEN_XMLNode_SetCharValue(p_db, "id", p_struct->id); 
#endif
 } else { /* TODO: remove element */ }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "prefix" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->prefix) { 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 GWEN_XMLNode_SetProperty(p_db, "prefix", p_struct->prefix); 
#else
 GWEN_XMLNode_SetCharValue(p_db, "prefix", p_struct->prefix); 
#endif
 } else { /* TODO: remove element */ }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "type" */
#define TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#define TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
  if (p_struct->type) { 
#ifdef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON
 GWEN_XMLNode_SetProperty(p_db, "type", p_struct->type); 
#else
 GWEN_XMLNode_SetCharValue(p_db, "type", p_struct->type); 
#endif
 } else { /* TODO: remove element */ }
#undef TYPEMAKER2_MEMBER_FLAGS_OWN_ON
#undef TYPEMAKER2_MEMBER_FLAGS_ATTRIBUTE_ON

  /* member "items" is volatile, not writing to xml */

  /* member "toStringFn" is volatile, not writing to xml */

  /* member "fromStringFn" is volatile, not writing to xml */

}

void Typemaker2_Enum_toXml(const TYPEMAKER2_ENUM *p_struct, GWEN_XMLNODE *p_db) {
  Typemaker2_Enum_WriteXml(p_struct, p_db);
}

TYPEMAKER2_ENUM *Typemaker2_Enum_fromXml(GWEN_XMLNODE *p_db) {
  TYPEMAKER2_ENUM *p_struct;
  p_struct=Typemaker2_Enum_new();
  Typemaker2_Enum_ReadXml(p_struct, p_db);
  return p_struct;
}

