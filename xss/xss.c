/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.19
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#define SWIGPYTHON

#include "Python.h"

/***********************************************************************
 * common.swg
 *
 *     This file contains generic SWIG runtime support for pointer
 *     type checking as well as a few commonly used macros to control
 *     external linkage.
 *
 * Author : David Beazley (beazley@cs.uchicago.edu)
 *
 * Copyright (c) 1999-2000, The University of Chicago
 * 
 * This file may be freely redistributed without license or fee provided
 * this copyright message remains intact.
 ************************************************************************/

#include <string.h>

#if defined(_WIN32) || defined(__WIN32__)
#       if defined(_MSC_VER)
#               if defined(STATIC_LINKED)
#                       define SWIGEXPORT(a) a
#                       define SWIGIMPORT(a) extern a
#               else
#                       define SWIGEXPORT(a) __declspec(dllexport) a
#                       define SWIGIMPORT(a) extern a
#               endif
#       else
#               if defined(__BORLANDC__)
#                       define SWIGEXPORT(a) a _export
#                       define SWIGIMPORT(a) a _export
#               else
#                       define SWIGEXPORT(a) a
#                       define SWIGIMPORT(a) a
#               endif
#       endif
#else
#       define SWIGEXPORT(a) a
#       define SWIGIMPORT(a) a
#endif

#ifdef SWIG_GLOBAL
#define SWIGRUNTIME(a) SWIGEXPORT(a)
#else
#define SWIGRUNTIME(a) static a
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*swig_converter_func)(void *);
typedef struct swig_type_info *(*swig_dycast_func)(void **);

typedef struct swig_type_info {
  const char             *name;                 
  swig_converter_func     converter;
  const char             *str;
  void                   *clientdata;	
  swig_dycast_func        dcast;
  struct swig_type_info  *next;
  struct swig_type_info  *prev;
} swig_type_info;

#ifdef SWIG_NOINCLUDE

SWIGIMPORT(swig_type_info *) SWIG_TypeRegister(swig_type_info *);
SWIGIMPORT(swig_type_info *) SWIG_TypeCheck(char *c, swig_type_info *);
SWIGIMPORT(void *)           SWIG_TypeCast(swig_type_info *, void *);
SWIGIMPORT(swig_type_info *) SWIG_TypeDynamicCast(swig_type_info *, void **);
SWIGIMPORT(const char *)     SWIG_TypeName(const swig_type_info *);
SWIGIMPORT(swig_type_info *) SWIG_TypeQuery(const char *);
SWIGIMPORT(void)             SWIG_TypeClientData(swig_type_info *, void *);

#else

static swig_type_info *swig_type_list = 0;

/* Register a type mapping with the type-checking */
SWIGRUNTIME(swig_type_info *)
SWIG_TypeRegister(swig_type_info *ti)
{
  swig_type_info *tc, *head, *ret, *next;
  /* Check to see if this type has already been registered */
  tc = swig_type_list;
  while (tc) {
    if (strcmp(tc->name, ti->name) == 0) {
      /* Already exists in the table.  Just add additional types to the list */
      if (tc->clientdata) ti->clientdata = tc->clientdata;	
      head = tc;
      next = tc->next;
      goto l1;
    }
    tc = tc->prev;
  }
  head = ti;
  next = 0;

  /* Place in list */
  ti->prev = swig_type_list;
  swig_type_list = ti;

  /* Build linked lists */
 l1:
  ret = head;
  tc = ti + 1;
  /* Patch up the rest of the links */
  while (tc->name) {
    head->next = tc;
    tc->prev = head;
    head = tc;
    tc++;
  }
  if (next) next->prev = head;  /**/
  head->next = next;
  return ret;
}

/* Check the typename */
SWIGRUNTIME(swig_type_info *) 
SWIG_TypeCheck(char *c, swig_type_info *ty)
{
  swig_type_info *s;
  if (!ty) return 0;        /* Void pointer */
  s = ty->next;             /* First element always just a name */
  do {
    if (strcmp(s->name,c) == 0) {
      if (s == ty->next) return s;
      /* Move s to the top of the linked list */
      s->prev->next = s->next;
      if (s->next) {
	s->next->prev = s->prev;
      }
      /* Insert s as second element in the list */
      s->next = ty->next;
      if (ty->next) ty->next->prev = s;
      ty->next = s;
      s->prev = ty;  /**/
      return s;
    }
    s = s->next;
  } while (s && (s != ty->next));
  return 0;
}

/* Cast a pointer up an inheritance hierarchy */
SWIGRUNTIME(void *) 
SWIG_TypeCast(swig_type_info *ty, void *ptr) 
{
  if ((!ty) || (!ty->converter)) return ptr;
  return (*ty->converter)(ptr);
}

/* Dynamic pointer casting. Down an inheritance hierarchy */
SWIGRUNTIME(swig_type_info *) 
SWIG_TypeDynamicCast(swig_type_info *ty, void **ptr) 
{
  swig_type_info *lastty = ty;
  if (!ty || !ty->dcast) return ty;
  while (ty && (ty->dcast)) {
     ty = (*ty->dcast)(ptr);
     if (ty) lastty = ty;
  }
  return lastty;
}

/* Return the name associated with this type */
SWIGRUNTIME(const char *)
SWIG_TypeName(const swig_type_info *ty) {
  return ty->name;
}

/* Search for a swig_type_info structure */
SWIGRUNTIME(swig_type_info *)
SWIG_TypeQuery(const char *name) {
  swig_type_info *ty = swig_type_list;
  while (ty) {
    if (ty->str && (strcmp(name,ty->str) == 0)) return ty;
    if (ty->name && (strcmp(name,ty->name) == 0)) return ty;
    ty = ty->prev;
  }
  return 0;
}

/* Set the clientdata field for a type */
SWIGRUNTIME(void)
SWIG_TypeClientData(swig_type_info *ti, void *clientdata) {
  swig_type_info *tc, *equiv;
  if (ti->clientdata == clientdata) return;
  ti->clientdata = clientdata;
  equiv = ti->next;
  while (equiv) {
    if (!equiv->converter) {
      tc = swig_type_list;
      while (tc) {
	if ((strcmp(tc->name, equiv->name) == 0))
	  SWIG_TypeClientData(tc,clientdata);
	tc = tc->prev;
      }
    }
    equiv = equiv->next;
  }
}
#endif

#ifdef __cplusplus
}

#endif

/***********************************************************************
 * python.swg
 *
 *     This file contains the runtime support for Python modules
 *     and includes code for managing global variables and pointer
 *     type checking.
 *
 * Author : David Beazley (beazley@cs.uchicago.edu)
 ************************************************************************/

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SWIG_PY_INT     1
#define SWIG_PY_FLOAT   2
#define SWIG_PY_STRING  3
#define SWIG_PY_POINTER 4
#define SWIG_PY_BINARY  5

/* Flags for pointer conversion */

#define SWIG_POINTER_EXCEPTION     0x1
#define SWIG_POINTER_DISOWN        0x2

/* Exception handling in wrappers */
#define SWIG_fail   goto fail

/* Constant information structure */
typedef struct swig_const_info {
    int type;
    char *name;
    long lvalue;
    double dvalue;
    void   *pvalue;
    swig_type_info **ptype;
} swig_const_info;

#ifdef SWIG_NOINCLUDE

SWIGEXPORT(PyObject *)        SWIG_newvarlink(void);
SWIGEXPORT(void)              SWIG_addvarlink(PyObject *, char *, PyObject *(*)(void), int (*)(PyObject *));
SWIGEXPORT(int)               SWIG_ConvertPtr(PyObject *, void **, swig_type_info *, int);
SWIGEXPORT(int)               SWIG_ConvertPacked(PyObject *, void *, int sz, swig_type_info *, int);
SWIGEXPORT(char *)            SWIG_PackData(char *c, void *, int);
SWIGEXPORT(char *)            SWIG_UnpackData(char *c, void *, int);
SWIGEXPORT(PyObject *)        SWIG_NewPointerObj(void *, swig_type_info *,int own);
SWIGEXPORT(PyObject *)        SWIG_NewPackedObj(void *, int sz, swig_type_info *);
SWIGEXPORT(void)              SWIG_InstallConstants(PyObject *d, swig_const_info constants[]);
#else

/* -----------------------------------------------------------------------------
 * global variable support code.
 * ----------------------------------------------------------------------------- */

typedef struct swig_globalvar {   
  char       *name;                  /* Name of global variable */
  PyObject *(*get_attr)(void);       /* Return the current value */
  int       (*set_attr)(PyObject *); /* Set the value */
  struct swig_globalvar *next;
} swig_globalvar;

typedef struct swig_varlinkobject {
  PyObject_HEAD
  swig_globalvar *vars;
} swig_varlinkobject;

static PyObject *
swig_varlink_repr(swig_varlinkobject *v) {
  v = v;
  return PyString_FromString("<Global variables>");
}

static int
swig_varlink_print(swig_varlinkobject *v, FILE *fp, int flags) {
  swig_globalvar  *var;
  flags = flags;
  fprintf(fp,"Global variables { ");
  for (var = v->vars; var; var=var->next) {
    fprintf(fp,"%s", var->name);
    if (var->next) fprintf(fp,", ");
  }
  fprintf(fp," }\n");
  return 0;
}

static PyObject *
swig_varlink_getattr(swig_varlinkobject *v, char *n) {
  swig_globalvar *var = v->vars;
  while (var) {
    if (strcmp(var->name,n) == 0) {
      return (*var->get_attr)();
    }
    var = var->next;
  }
  PyErr_SetString(PyExc_NameError,"Unknown C global variable");
  return NULL;
}

static int
swig_varlink_setattr(swig_varlinkobject *v, char *n, PyObject *p) {
  swig_globalvar *var = v->vars;
  while (var) {
    if (strcmp(var->name,n) == 0) {
      return (*var->set_attr)(p);
    }
    var = var->next;
  }
  PyErr_SetString(PyExc_NameError,"Unknown C global variable");
  return 1;
}

statichere PyTypeObject varlinktype = {
  PyObject_HEAD_INIT(0)              
  0,
  (char *)"swigvarlink",                      /* Type name    */
  sizeof(swig_varlinkobject),         /* Basic size   */
  0,                                  /* Itemsize     */
  0,                                  /* Deallocator  */ 
  (printfunc) swig_varlink_print,     /* Print        */
  (getattrfunc) swig_varlink_getattr, /* get attr     */
  (setattrfunc) swig_varlink_setattr, /* Set attr     */
  0,                                  /* tp_compare   */
  (reprfunc) swig_varlink_repr,       /* tp_repr      */    
  0,                                  /* tp_as_number */
  0,                                  /* tp_as_mapping*/
  0,                                  /* tp_hash      */
};

/* Create a variable linking object for use later */
SWIGRUNTIME(PyObject *)
SWIG_newvarlink(void) {
  swig_varlinkobject *result = 0;
  result = PyMem_NEW(swig_varlinkobject,1);
  varlinktype.ob_type = &PyType_Type;    /* Patch varlinktype into a PyType */
  result->ob_type = &varlinktype;
  result->vars = 0;
  result->ob_refcnt = 0;
  Py_XINCREF((PyObject *) result);
  return ((PyObject*) result);
}

SWIGRUNTIME(void)
SWIG_addvarlink(PyObject *p, char *name,
	   PyObject *(*get_attr)(void), int (*set_attr)(PyObject *p)) {
  swig_varlinkobject *v;
  swig_globalvar *gv;
  v= (swig_varlinkobject *) p;
  gv = (swig_globalvar *) malloc(sizeof(swig_globalvar));
  gv->name = (char *) malloc(strlen(name)+1);
  strcpy(gv->name,name);
  gv->get_attr = get_attr;
  gv->set_attr = set_attr;
  gv->next = v->vars;
  v->vars = gv;
}

/* Pack binary data into a string */
SWIGRUNTIME(char *)
SWIG_PackData(char *c, void *ptr, int sz) {
  static char hex[17] = "0123456789abcdef";
  int i;
  unsigned char *u = (unsigned char *) ptr;
  register unsigned char uu;
  for (i = 0; i < sz; i++,u++) {
    uu = *u;
    *(c++) = hex[(uu & 0xf0) >> 4];
    *(c++) = hex[uu & 0xf];
  }
  return c;
}

/* Unpack binary data from a string */
SWIGRUNTIME(char *)
SWIG_UnpackData(char *c, void *ptr, int sz) {
  register unsigned char uu = 0;
  register int d;
  unsigned char *u = (unsigned char *) ptr;
  int i;
  for (i = 0; i < sz; i++, u++) {
    d = *(c++);
    if ((d >= '0') && (d <= '9'))
      uu = ((d - '0') << 4);
    else if ((d >= 'a') && (d <= 'f'))
      uu = ((d - ('a'-10)) << 4);
    d = *(c++);
    if ((d >= '0') && (d <= '9'))
      uu |= (d - '0');
    else if ((d >= 'a') && (d <= 'f'))
      uu |= (d - ('a'-10));
    *u = uu;
  }
  return c;
}

/* Convert a pointer value */
SWIGRUNTIME(int)
SWIG_ConvertPtr(PyObject *obj, void **ptr, swig_type_info *ty, int flags) {
  swig_type_info *tc;
  char  *c;
  static PyObject *SWIG_this = 0;
  int    newref = 0;
  PyObject  *pyobj = 0;

  if (!obj) return 0;
  if (obj == Py_None) {
    *ptr = 0;
    return 0;
  }
#ifdef SWIG_COBJECT_TYPES
  if (!(PyCObject_Check(obj))) {
    if (!SWIG_this)
      SWIG_this = PyString_FromString("this");
    pyobj = obj;
    obj = PyObject_GetAttr(obj,SWIG_this);
    newref = 1;
    if (!obj) goto type_error;
    if (!PyCObject_Check(obj)) {
      Py_DECREF(obj);
      goto type_error;
    }
  }  
  *ptr = PyCObject_AsVoidPtr(obj);
  c = (char *) PyCObject_GetDesc(obj);
  if (newref) Py_DECREF(obj);
  goto cobject;
#else
  if (!(PyString_Check(obj))) {
    if (!SWIG_this)
      SWIG_this = PyString_FromString("this");
    pyobj = obj;
    obj = PyObject_GetAttr(obj,SWIG_this);
    newref = 1;
    if (!obj) goto type_error;
    if (!PyString_Check(obj)) {
      Py_DECREF(obj);
      goto type_error;
    }
  } 
  c = PyString_AsString(obj);
  /* Pointer values must start with leading underscore */
  if (*c != '_') {
    *ptr = (void *) 0;
    if (strcmp(c,"NULL") == 0) {
      if (newref) { Py_DECREF(obj); }
      return 0;
    } else {
      if (newref) { Py_DECREF(obj); }
      goto type_error;
    }
  }
  c++;
  c = SWIG_UnpackData(c,ptr,sizeof(void *));
  if (newref) { Py_DECREF(obj); }
#endif

#ifdef SWIG_COBJECT_TYPES
cobject:
#endif

  if (ty) {
    tc = SWIG_TypeCheck(c,ty);
    if (!tc) goto type_error;
    *ptr = SWIG_TypeCast(tc,(void*) *ptr);
  }

  if ((pyobj) && (flags & SWIG_POINTER_DISOWN)) {
      PyObject *zero = PyInt_FromLong(0);
      PyObject_SetAttrString(pyobj,(char*)"thisown",zero);
      Py_DECREF(zero);
  }
  return 0;

type_error:
  if (flags & SWIG_POINTER_EXCEPTION) {
    if (ty) {
      char *temp = (char *) malloc(64+strlen(ty->name));
      sprintf(temp,"Type error. Expected %s", ty->name);
      PyErr_SetString(PyExc_TypeError, temp);
      free((char *) temp);
    } else {
      PyErr_SetString(PyExc_TypeError,"Expected a pointer");
    }
  }
  return -1;
}

/* Convert a packed value value */
SWIGRUNTIME(int)
SWIG_ConvertPacked(PyObject *obj, void *ptr, int sz, swig_type_info *ty, int flags) {
  swig_type_info *tc;
  char  *c;

  if ((!obj) || (!PyString_Check(obj))) goto type_error;
  c = PyString_AsString(obj);
  /* Pointer values must start with leading underscore */
  if (*c != '_') goto type_error;
  c++;
  c = SWIG_UnpackData(c,ptr,sz);
  if (ty) {
    tc = SWIG_TypeCheck(c,ty);
    if (!tc) goto type_error;
  }
  return 0;

type_error:

  if (flags) {
    if (ty) {
      char *temp = (char *) malloc(64+strlen(ty->name));
      sprintf(temp,"Type error. Expected %s", ty->name);
      PyErr_SetString(PyExc_TypeError, temp);
      free((char *) temp);
    } else {
      PyErr_SetString(PyExc_TypeError,"Expected a pointer");
    }
  }
  return -1;
}

/* Create a new pointer object */
SWIGRUNTIME(PyObject *)
SWIG_NewPointerObj(void *ptr, swig_type_info *type, int own) {
  PyObject *robj;
  if (!ptr) {
    Py_INCREF(Py_None);
    return Py_None;
  }
#ifdef SWIG_COBJECT_TYPES
  robj = PyCObject_FromVoidPtrAndDesc((void *) ptr, (char *) type->name, NULL);
#else
  {
    char result[1024];
    char *r = result;
    *(r++) = '_';
    r = SWIG_PackData(r,&ptr,sizeof(void *));
    strcpy(r,type->name);
    robj = PyString_FromString(result);
  }
#endif
  if (!robj || (robj == Py_None)) return robj;
  if (type->clientdata) {
    PyObject *inst;
    PyObject *args = Py_BuildValue((char*)"(O)", robj);
    Py_DECREF(robj);
    inst = PyObject_CallObject((PyObject *) type->clientdata, args);
    Py_DECREF(args);
    if (inst) {
      if (own) {
	PyObject *n = PyInt_FromLong(1);
	PyObject_SetAttrString(inst,(char*)"thisown",n);
	Py_DECREF(n);
      }
      robj = inst;
    }
  }
  return robj;
}

SWIGRUNTIME(PyObject *)
SWIG_NewPackedObj(void *ptr, int sz, swig_type_info *type) {
  char result[1024];
  char *r = result;
  if ((2*sz + 1 + strlen(type->name)) > 1000) return 0;
  *(r++) = '_';
  r = SWIG_PackData(r,ptr,sz);
  strcpy(r,type->name);
  return PyString_FromString(result);
}

/* Install Constants */
SWIGRUNTIME(void)
SWIG_InstallConstants(PyObject *d, swig_const_info constants[]) {
  int i;
  PyObject *obj;
  for (i = 0; constants[i].type; i++) {
    switch(constants[i].type) {
    case SWIG_PY_INT:
      obj = PyInt_FromLong(constants[i].lvalue);
      break;
    case SWIG_PY_FLOAT:
      obj = PyFloat_FromDouble(constants[i].dvalue);
      break;
    case SWIG_PY_STRING:
      obj = PyString_FromString((char *) constants[i].pvalue);
      break;
    case SWIG_PY_POINTER:
      obj = SWIG_NewPointerObj(constants[i].pvalue, *(constants[i]).ptype,0);
      break;
    case SWIG_PY_BINARY:
      obj = SWIG_NewPackedObj(constants[i].pvalue, constants[i].lvalue, *(constants[i].ptype));
      break;
    default:
      obj = 0;
      break;
    }
    if (obj) {
      PyDict_SetItemString(d,constants[i].name,obj);
      Py_DECREF(obj);
    }
  }
}

#endif

#ifdef __cplusplus
}
#endif








/* -------- TYPES TABLE (BEGIN) -------- */

#define  SWIGTYPE_p_Display swig_types[0] 
#define  SWIGTYPE_p_Window swig_types[1] 
#define  SWIGTYPE_p_XScreenSaverInfo swig_types[2] 
static swig_type_info *swig_types[4];

/* -------- TYPES TABLE (END) -------- */


/*-----------------------------------------------
              @(target):= _xss.so
  ------------------------------------------------*/
#define SWIG_init    init_xss

#define SWIG_name    "_xss"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>


#define  SWIG_MemoryError    1
#define  SWIG_IOError        2
#define  SWIG_RuntimeError   3
#define  SWIG_IndexError     4
#define  SWIG_TypeError      5
#define  SWIG_DivisionByZero 6
#define  SWIG_OverflowError  7
#define  SWIG_SyntaxError    8
#define  SWIG_ValueError     9
#define  SWIG_SystemError   10
#define  SWIG_UnknownError  99


static void _SWIG_exception(int code, const char *msg) {
  switch(code) {
  case SWIG_MemoryError:
    PyErr_SetString(PyExc_MemoryError,msg);
    break;
  case SWIG_IOError:
    PyErr_SetString(PyExc_IOError,msg);
    break;
  case SWIG_RuntimeError:
    PyErr_SetString(PyExc_RuntimeError,msg);
    break;
  case SWIG_IndexError:
    PyErr_SetString(PyExc_IndexError,msg);
    break;
  case SWIG_TypeError:
    PyErr_SetString(PyExc_TypeError,msg);
    break;
  case SWIG_DivisionByZero:
    PyErr_SetString(PyExc_ZeroDivisionError,msg);
    break;
  case SWIG_OverflowError:
    PyErr_SetString(PyExc_OverflowError,msg);
    break;
  case SWIG_SyntaxError:
    PyErr_SetString(PyExc_SyntaxError,msg);
    break;
  case SWIG_ValueError:
    PyErr_SetString(PyExc_ValueError,msg);
    break;
  case SWIG_SystemError:
    PyErr_SetString(PyExc_SystemError,msg);
    break;
  default:
    PyErr_SetString(PyExc_RuntimeError,msg);
    break;
  }
}

#define SWIG_exception(a,b) { _SWIG_exception(a,b); SWIG_fail; }



int event_base, error_base;
static XScreenSaverInfo *mit_info;

Display *dpy;
int screen;
Window root;

XScreenSaverInfo* get_info(void) {
    if (XScreenSaverQueryExtension(dpy, &event_base, &error_base)) {
            mit_info = XScreenSaverAllocInfo();
            XScreenSaverQueryInfo(dpy, root, mit_info);
            return mit_info;
    } else {
        return NULL;
    }
}


#ifdef __cplusplus
extern "C" {
#endif
static PyObject *_wrap_XScreenSaverInfo_window_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    Window arg2 ;
    Window *argp2 ;
    PyObject * obj0 = 0 ;
    PyObject * obj1 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"OO:XScreenSaverInfo_window_set",&obj0,&obj1)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    if ((SWIG_ConvertPtr(obj1,(void **) &argp2, SWIGTYPE_p_Window,SWIG_POINTER_EXCEPTION) == -1)) SWIG_fail;
    arg2 = *argp2; 
    if (arg1) (arg1)->window = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_window_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    Window result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_window_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result =  ((arg1)->window);
    
    {
        Window * resultptr;
        resultptr = (Window *) malloc(sizeof(Window));
        memmove(resultptr, &result, sizeof(Window));
        resultobj = SWIG_NewPointerObj((void *) resultptr, SWIGTYPE_p_Window, 1);
    }
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_state_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    int arg2 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oi:XScreenSaverInfo_state_set",&obj0,&arg2)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    if (arg1) (arg1)->state = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_state_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_state_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int) ((arg1)->state);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_kind_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    int arg2 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"Oi:XScreenSaverInfo_kind_set",&obj0,&arg2)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    if (arg1) (arg1)->kind = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_kind_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    int result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_kind_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (int) ((arg1)->kind);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_til_or_since_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long arg2 ;
    PyObject * obj0 = 0 ;
    PyObject * obj1 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"OO:XScreenSaverInfo_til_or_since_set",&obj0,&obj1)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    arg2 = (unsigned long) PyInt_AsLong(obj1);
    if (PyErr_Occurred()) SWIG_fail;
    if (arg1) (arg1)->til_or_since = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_til_or_since_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_til_or_since_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (unsigned long) ((arg1)->til_or_since);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_idle_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long arg2 ;
    PyObject * obj0 = 0 ;
    PyObject * obj1 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"OO:XScreenSaverInfo_idle_set",&obj0,&obj1)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    arg2 = (unsigned long) PyInt_AsLong(obj1);
    if (PyErr_Occurred()) SWIG_fail;
    if (arg1) (arg1)->idle = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_idle_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_idle_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (unsigned long) ((arg1)->idle);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_eventMask_set(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long arg2 ;
    PyObject * obj0 = 0 ;
    PyObject * obj1 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"OO:XScreenSaverInfo_eventMask_set",&obj0,&obj1)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    arg2 = (unsigned long) PyInt_AsLong(obj1);
    if (PyErr_Occurred()) SWIG_fail;
    if (arg1) (arg1)->eventMask = arg2;
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_XScreenSaverInfo_eventMask_get(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    unsigned long result;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:XScreenSaverInfo_eventMask_get",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    result = (unsigned long) ((arg1)->eventMask);
    
    resultobj = PyInt_FromLong((long)result);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_new_XScreenSaverInfo(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *result;
    
    if(!PyArg_ParseTuple(args,(char *)":new_XScreenSaverInfo")) goto fail;
    result = (XScreenSaverInfo *)(XScreenSaverInfo *) calloc(1, sizeof(XScreenSaverInfo));
    
    resultobj = SWIG_NewPointerObj((void *) result, SWIGTYPE_p_XScreenSaverInfo, 1);
    return resultobj;
    fail:
    return NULL;
}


static PyObject *_wrap_delete_XScreenSaverInfo(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *arg1 = (XScreenSaverInfo *) 0 ;
    PyObject * obj0 = 0 ;
    
    if(!PyArg_ParseTuple(args,(char *)"O:delete_XScreenSaverInfo",&obj0)) goto fail;
    if ((SWIG_ConvertPtr(obj0,(void **) &arg1, SWIGTYPE_p_XScreenSaverInfo,SWIG_POINTER_EXCEPTION | 0 )) == -1) SWIG_fail;
    free((char *) arg1);
    
    Py_INCREF(Py_None); resultobj = Py_None;
    return resultobj;
    fail:
    return NULL;
}


static PyObject * XScreenSaverInfo_swigregister(PyObject *self, PyObject *args) {
    PyObject *obj;
    if (!PyArg_ParseTuple(args,(char*)"O", &obj)) return NULL;
    SWIG_TypeClientData(SWIGTYPE_p_XScreenSaverInfo, obj);
    Py_INCREF(obj);
    return Py_BuildValue((char *)"");
}
static int _wrap_event_base_set(PyObject *_val) {
    {
        long temp = PyInt_AsLong(_val);
        if (PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "C variable 'event_base (int)'");
            return 1;
        }
        event_base = (int) temp;
    }
    return 0;
}


static PyObject *_wrap_event_base_get() {
    PyObject *pyobj;
    
    pyobj = PyInt_FromLong((long)event_base);
    return pyobj;
}


static int _wrap_error_base_set(PyObject *_val) {
    {
        long temp = PyInt_AsLong(_val);
        if (PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "C variable 'error_base (int)'");
            return 1;
        }
        error_base = (int) temp;
    }
    return 0;
}


static PyObject *_wrap_error_base_get() {
    PyObject *pyobj;
    
    pyobj = PyInt_FromLong((long)error_base);
    return pyobj;
}


static int _wrap_mit_info_set(PyObject *_val) {
    {
        void *temp;
        if ((SWIG_ConvertPtr(_val,(void **) &temp, SWIGTYPE_p_XScreenSaverInfo, SWIG_POINTER_EXCEPTION | SWIG_POINTER_DISOWN)) == -1) {
            PyErr_SetString(PyExc_TypeError, "C variable 'mit_info (XScreenSaverInfo *)'");
            return 1;
        }
        mit_info = (XScreenSaverInfo *) temp;
    }
    return 0;
}


static PyObject *_wrap_mit_info_get() {
    PyObject *pyobj;
    
    pyobj = SWIG_NewPointerObj((void *) mit_info, SWIGTYPE_p_XScreenSaverInfo, 0);
    return pyobj;
}


static int _wrap_dpy_set(PyObject *_val) {
    {
        void *temp;
        if ((SWIG_ConvertPtr(_val,(void **) &temp, SWIGTYPE_p_Display, SWIG_POINTER_EXCEPTION | SWIG_POINTER_DISOWN)) == -1) {
            PyErr_SetString(PyExc_TypeError, "C variable 'dpy (Display *)'");
            return 1;
        }
        dpy = (Display *) temp;
    }
    return 0;
}


static PyObject *_wrap_dpy_get() {
    PyObject *pyobj;
    
    pyobj = SWIG_NewPointerObj((void *) dpy, SWIGTYPE_p_Display, 0);
    return pyobj;
}


static int _wrap_screen_set(PyObject *_val) {
    {
        long temp = PyInt_AsLong(_val);
        if (PyErr_Occurred()) {
            PyErr_SetString(PyExc_TypeError, "C variable 'screen (int)'");
            return 1;
        }
        screen = (int) temp;
    }
    return 0;
}


static PyObject *_wrap_screen_get() {
    PyObject *pyobj;
    
    pyobj = PyInt_FromLong((long)screen);
    return pyobj;
}


static int _wrap_root_set(PyObject *_val) {
    {
        Window * temp;
        if ((SWIG_ConvertPtr(_val, (void **) &temp, SWIGTYPE_p_Window, SWIG_POINTER_EXCEPTION)) == -1) {
            PyErr_SetString(PyExc_TypeError, "C variable 'root (Window)'");
            return 1;
        }
        root = *((Window *) temp);
    }
    return 0;
}


static PyObject *_wrap_root_get() {
    PyObject *pyobj;
    
    pyobj = SWIG_NewPointerObj((void *) &root, SWIGTYPE_p_Window, 0);
    return pyobj;
}


static PyObject *_wrap_get_info(PyObject *self, PyObject *args) {
    PyObject *resultobj;
    XScreenSaverInfo *result;
    
    if(!PyArg_ParseTuple(args,(char *)":get_info")) goto fail;
    {
        result = (XScreenSaverInfo *)get_info();
        
        if (!result) {
            SWIG_exception(SWIG_RuntimeError, "Couldn't query screensaver extension.");
            return NULL;
        }
    }
    resultobj = SWIG_NewPointerObj((void *) result, SWIGTYPE_p_XScreenSaverInfo, 0);
    return resultobj;
    fail:
    return NULL;
}


static PyMethodDef SwigMethods[] = {
	 { (char *)"XScreenSaverInfo_window_set", _wrap_XScreenSaverInfo_window_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_window_get", _wrap_XScreenSaverInfo_window_get, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_state_set", _wrap_XScreenSaverInfo_state_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_state_get", _wrap_XScreenSaverInfo_state_get, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_kind_set", _wrap_XScreenSaverInfo_kind_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_kind_get", _wrap_XScreenSaverInfo_kind_get, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_til_or_since_set", _wrap_XScreenSaverInfo_til_or_since_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_til_or_since_get", _wrap_XScreenSaverInfo_til_or_since_get, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_idle_set", _wrap_XScreenSaverInfo_idle_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_idle_get", _wrap_XScreenSaverInfo_idle_get, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_eventMask_set", _wrap_XScreenSaverInfo_eventMask_set, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_eventMask_get", _wrap_XScreenSaverInfo_eventMask_get, METH_VARARGS },
	 { (char *)"new_XScreenSaverInfo", _wrap_new_XScreenSaverInfo, METH_VARARGS },
	 { (char *)"delete_XScreenSaverInfo", _wrap_delete_XScreenSaverInfo, METH_VARARGS },
	 { (char *)"XScreenSaverInfo_swigregister", XScreenSaverInfo_swigregister, METH_VARARGS },
	 { (char *)"get_info", _wrap_get_info, METH_VARARGS },
	 { NULL, NULL }
};


/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (BEGIN) -------- */

static swig_type_info _swigt__p_Display[] = {{"_p_Display", 0, "Display *", 0},{"_p_Display"},{0}};
static swig_type_info _swigt__p_Window[] = {{"_p_Window", 0, "Window *", 0},{"_p_Window"},{0}};
static swig_type_info _swigt__p_XScreenSaverInfo[] = {{"_p_XScreenSaverInfo", 0, "XScreenSaverInfo *", 0},{"_p_XScreenSaverInfo"},{0}};

static swig_type_info *swig_types_initial[] = {
_swigt__p_Display, 
_swigt__p_Window, 
_swigt__p_XScreenSaverInfo, 
0
};


/* -------- TYPE CONVERSION AND EQUIVALENCE RULES (END) -------- */

static swig_const_info swig_const_table[] = {
{ SWIG_PY_INT,     (char *)"ScreenSaverOff", (long) 0, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverOn", (long) 1, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverCycle", (long) 2, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverDisabled", (long) 3, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverBlanked", (long) 0, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverInternal", (long) 1, 0, 0, 0},
{ SWIG_PY_INT,     (char *)"ScreenSaverExternal", (long) 2, 0, 0, 0},
{0}};

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C"
#endif
SWIGEXPORT(void) SWIG_init(void) {
    static PyObject *SWIG_globals = 0; 
    static int       typeinit = 0;
    PyObject *m, *d;
    int       i;
    if (!SWIG_globals) SWIG_globals = SWIG_newvarlink();
    m = Py_InitModule((char *) SWIG_name, SwigMethods);
    d = PyModule_GetDict(m);
    
    if (!typeinit) {
        for (i = 0; swig_types_initial[i]; i++) {
            swig_types[i] = SWIG_TypeRegister(swig_types_initial[i]);
        }
        typeinit = 1;
    }
    SWIG_InstallConstants(d,swig_const_table);
    
    PyDict_SetItemString(d,(char*)"cvar", SWIG_globals);
    SWIG_addvarlink(SWIG_globals,(char*)"event_base",_wrap_event_base_get, _wrap_event_base_set);
    SWIG_addvarlink(SWIG_globals,(char*)"error_base",_wrap_error_base_get, _wrap_error_base_set);
    SWIG_addvarlink(SWIG_globals,(char*)"mit_info",_wrap_mit_info_get, _wrap_mit_info_set);
    SWIG_addvarlink(SWIG_globals,(char*)"dpy",_wrap_dpy_get, _wrap_dpy_set);
    SWIG_addvarlink(SWIG_globals,(char*)"screen",_wrap_screen_get, _wrap_screen_set);
    SWIG_addvarlink(SWIG_globals,(char*)"root",_wrap_root_get, _wrap_root_set);
    
    dpy = XOpenDisplay("");
    screen = DefaultScreen(dpy);
    root = RootWindow(dpy, screen);
    
}

