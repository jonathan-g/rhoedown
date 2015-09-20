/*
 * markdown_rstubs.c
 * 
 * Copyright (C) 2009-2013 by RStudio, Inc.
 * 
 * This program is licensed to you under the terms of version 2 of the
 * GNU General Public License. This program is distributed WITHOUT ANY
 * EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * GPL (http://www.gnu.org/licenses/gpl-2.0.txt) for more details.
 *
 */

/* Inspird by Matrix/inst/include/Matrix_stubs.c */

#include "rhoedown_rstubs.h"

const char *rstub_hoedown_buffer_cstr(hoedown_buffer *buf)
{
  static const char *(*fun)(hoedown_buffer *) = NULL;
  if (fun==NULL)
    fun = (const char *(*)(hoedown_buffer *))R_GetCCallable("rhoedown","hoedown_buffer_cstr");
  return fun(buf);
}

void rstub_hoedown_buffer_free(hoedown_buffer *buf)
{
  static void (*fun)(hoedown_buffer *) = NULL;
  if (fun==NULL)
    fun = (void (*)(hoedown_buffer *t))R_GetCCallable("rhoedown","hoedown_buffer_free");
  return fun(buf);
}

int rstub_hoedown_buffer_grow(hoedown_buffer *buf, size_t sz)
{
   static int (*fun)(hoedown_buffer *, size_t) = NULL;
   if (fun==NULL)
      fun = (int (*)(hoedown_buffer *,size_t))R_GetCCallable("rhoedown","hoedown_buffer_grow");
   return fun(buf,sz);
}

hoedown_buffer *rstub_hoedown_buffer_new(size_t sz)
{
   static hoedown_buffer *(*fun)(size_t) = NULL;
   if (fun==NULL)
      fun = (hoedown_buffer *(*)(size_t))R_GetCCallable("rhoedown","hoedown_buffer_new");
   return fun(sz);
}

int rstub_hoedown_buffer_prefix(const hoedown_buffer *buf, const char *prefix)
{
   static int (*fun)(const hoedown_buffer *, const char *) = NULL;
   if (fun==NULL)
      fun = (int (*)(const hoedown_buffer *, const char *))R_GetCCallable("rhoedown","hoedown_buffer_prefix");
   return fun(buf,prefix);
}

void rstub_hoedown_buffer_printf(hoedown_buffer *buf, const char *fmt, ...)
{
  va_list ap;
  static int (*fun)(hoedown_buffer *, const char *, ...) = NULL;
  if (fun==NULL)
    fun = (int (*)(hoedown_buffer *,const char *, ...))
    R_GetCCallable("rhoedown","hoedown_buffer_printf");
  
  va_start(ap, fmt);
  fun(buf,fmt,ap);
  va_end(ap);
}

void rstub_hoedown_buffer_put(hoedown_buffer *buf, const void *v, size_t sz)
{
   static void (*fun)(hoedown_buffer *, const void *, size_t) = NULL;
   if (fun==NULL)
      fun = (void (*)(hoedown_buffer *, const void *, size_t))R_GetCCallable("rhoedown","hoedown_buffer_put");
   return fun(buf,v,sz);
}

void rstub_hoedown_buffer_putc(hoedown_buffer *buf, int i)
{
  static void (*fun)(hoedown_buffer *, int) = NULL;
  if (fun==NULL)
    fun = (void (*)(hoedown_buffer *, int))R_GetCCallable("rhoedown","hoedown_buffer_putc");
  return fun(buf,i);
}

void rstub_hoedown_buffer_puts(hoedown_buffer *buf, const char *c)
{
   static void (*fun)(hoedown_buffer *, const char *) = NULL;
   if (fun==NULL)
      fun = (void (*)(hoedown_buffer *, const char *))R_GetCCallable("rhoedown","hoedown_buffer_puts");
   return fun(buf,c);
}

void rstub_hoedown_buffer_reset(hoedown_buffer *buf)
{
   static void (*fun)(hoedown_buffer *) = NULL;
   if (fun==NULL)
      fun = (void (*)(hoedown_buffer *t))R_GetCCallable("rhoedown","hoedown_buffer_reset");
   return fun(buf);
}

void rstub_hoedown_buffer_slurp(hoedown_buffer *buf, size_t sz)
{
   static int (*fun)(hoedown_buffer *, size_t) = NULL;
   if (fun==NULL)
      fun = (int (*)(hoedown_buffer *,size_t))R_GetCCallable("rhoedown","hoedown_buffer_slurp");
   fun(buf,sz);
}

int
rstub_hoedown_autolink_issafe(const uint8_t *link, size_t link_len){
   static int (*fun)(const uint8_t *, size_t) = NULL;
   if (fun==NULL)
      fun = (int (*)(const uint8_t *, size_t))
         R_GetCCallable("rhoedown","hoedown_autolink_issafe");
   return fun(link,link_len);
}

size_t
rstub_hoedown_autolink__www(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                     size_t offset, size_t size, hoedown_autolink_flags flags)
{
   static size_t (*fun)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                        size_t offset, size_t size, hoedown_autolink_flags flags) = NULL;
   if (fun==NULL)
      fun = (size_t (*)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                           size_t offset, size_t size, hoedown_autolink_flags flags))
         R_GetCCallable("rhoedown","hoedown_autolink__www");
   return fun(rewind_p,link,data,offset,size, flags);
}

size_t
rstub_hoedown_autolink__email(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                       size_t offset, size_t size, hoedown_autolink_flags flags)
{
   static size_t (*fun)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                        size_t offset, size_t size, hoedown_autolink_flags flags) = NULL;
   if (fun==NULL)
      fun = (size_t (*)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                           size_t offset, size_t size, hoedown_autolink_flags flags))
         R_GetCCallable("rhoedown","hoedown__autolink__email");
   return fun(rewind_p,link,data,offset,size, flags);
}

size_t
rstub_hoedown_autolink__url(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                     size_t offset, size_t size, hoedown_autolink_flags flags)
{
   static size_t (*fun)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                        size_t offset, size_t size, hoedown_autolink_flags flags) = NULL;
   if (fun==NULL)
      fun = (size_t (*)(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                           size_t offset, size_t size, hoedown_autolink_flags flags))
         R_GetCCallable("rhoedown","hoedown__autolink__url");
   return fun(rewind_p,link,data,offset,size, flags);
}

struct hoedown_document *
rstub_hoedown_markdown_new(const hoedown_renderer * renderer, hoedown_extensions extensions, size_t max_nesting)
{
   static struct hoedown_markdown *(*fun)(hoedown_renderer *, hoedown_extensions *, size_t) = NULL;
   if (fun==NULL)
      fun = (struct hoedown_document *(*)(hoedown_renderer *, hoedown_extensions *, size_t))
         R_GetCCallable("rhoedown","hoedown_document_new");
   return fun(renderer, extensions, max_nesting);
}

void
rstub_hoedown_markdown_render(hoedown_document *doc, hoedown_buffer *ob, 
                              const uint8_t *data, size_t size, )
{
   static void (*fun)(struct hoedown_document *, hoedown_buffer *, 
                const uint8_t *, size_t) = NULL;
   if (fun==NULL)
      fun = (void (*)(struct hoedown_document *, hoedown_buffer *, 
                   const uint8_t *, size_t))
         R_GetCCallable("rhoedown","hoedown_markdown_render");
   return fun(doc, ob, data, size);
}

void
rstub_hoedown_markdown_free(struct hoedown_document *doc)
{
   static void (*fun)(struct hoedown_document *) = NULL;
   if (fun==NULL)
      fun = (void (*)(struct hoedown_document *))
         R_GetCCallable("rhoedown","hoedown_markdown_free");
   return fun(doc);
}

void
rstub_hoedown_version(int *major, int *minor, int *revision)
{
   static void (*fun)(int *, int *, int *) = NULL;
   if (fun==NULL)
      fun = (void (*)(int *, int *, int *))
         R_GetCCallable("rhoedown","hoedown_version");
   return fun(major,minor,revision);
}

Rboolean rstub_rhd_register_renderer(struct rhd_renderer *renderer)
{
   static Rboolean (*fun)(struct rhd_renderer *) = NULL;
   if (fun==NULL)
      fun = (Rboolean (*)(struct rhd_renderer *))
         R_GetCCallable("rhoedown","rhd_register_renderer");
   return fun(renderer);
}

SEXP rstub_rhd_registered_renderers(void)
{
  static SEXP (*fun)(void) = NULL;
  if (fun==NULL)
    fun = (SEXP (*)(void))
    R_GetCCallable("rhoedown","rhd_registered_renderers");
  return fun();
}


Rboolean rstub_rhd_renderer_exists(const char *name)
{
   static SEXP (*fun)(SEXP) = NULL;
   if (fun==NULL)
      fun = (SEXP (*)(SEXP))
         R_GetCCallable("rhoedown","rhd_renderer_exists");
   return fun(name);
}

Rboolean rstub_rhd_buf_to_output(hoedown_buffer *ob, SEXP Soutput, 
                                        SEXP *raw_vec)
{
   static Rboolean (*fun)(hoedown_buffer *, SEXP, SEXP *) = NULL;
   if (fun==NULL)
      fun = (Rboolean (*)(hoedown_buffer *, SEXP, SEXP *))
         R_GetCCallable("rhoedown","rhd_buf_to_output");
   return fun(ob,Soutput,raw_vec);
}

Rboolean rstub_rhd_input_to_buf(SEXP Sfile, SEXP Stext, hoedown_buffer *ib)
{
   static Rboolean (*fun)(SEXP, SEXP, hoedown_buffer *) = NULL;
   if (fun==NULL)
      fun = (Rboolean (*)(SEXP, SEXP, hoedown_buffer *))
         R_GetCCallable("rhoedown","rhd_input_to_buf");
   return fun(Sfile,Stext,ib);
}
