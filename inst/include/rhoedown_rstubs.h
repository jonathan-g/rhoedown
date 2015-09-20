/*
 * markdown_rstubs.h
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

#ifndef HOEDOWN_RSTUBS
#define HOEDOWN_RSTUBS

#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include "hoedown.h"

#ifdef __cplusplus
extern "C" {
#endif

/* bufnullterm: NUL-termination of the string array (making a C-string) */
  const char *rstub_hoedown_buffer_cstr(hoedown_buffer *);
#define hoedown_buffer_cstr rstub_hoedown_buffer_cstr
  
/* hoedown_buffer_free: decrease the reference count and free the buffer if needed */
void rstub_hoedown_buffer_free(hoedown_buffer *);
#define hoedown_buffer_free rstub_hoedown_buffer_free
  
/* hoedown_buffer_grow: increasing the allocated size to the given value */
int rstub_hoedown_buffer_grow(hoedown_buffer *, size_t);
#define hoedown_buffer_grow rstub_hoedown_buffer_grow

/* hoedown_buffer_new: allocation of a new buffer */
hoedown_buffer *rstub_hoedown_buffer_new(size_t) __attribute__ ((malloc));
#define hoedown_buffer_new rstub_hoedown_buffer_new

/* hoedown_buffer_prefix: compare the beginning of a buffer with a string */
int rstub_hoedown_buffer_prefix(const hoedown_buffer *buf, const char *prefix);
#define hoedown_buffer_prefix rstub_hoedown_buffer_prefix

/* hoedown_buffer_printf: formatted printing to a buffer */
void rstub_hoedown_buffer_printf(hoedown_buffer *, const char *, ...) __attribute__ ((format (printf, 2, 3)));
#define hoedown_buffer_printf rstub_hoedown_buffer_printf

/* hoedown_buffer_put: appends raw data to a buffer */
void rstub_hoedown_buffer_put(hoedown_buffer *, const void *, size_t);
#define hoedown_buffer_put rstub_hoedown_buffer_put

/* hoedown_buffer_putc: appends a single char to a buffer */
void rstub_hoedown_buffer_putc(hoedown_buffer *, int);
#define hoedown_buffer_putc rstub_hoedown_buffer_putc

/* hoedown_buffer_puts: appends a NUL-terminated string to a buffer */
void rstub_hoedown_buffer_puts(hoedown_buffer *, const char *);
#define hoedown_buffer_puts rstub_hoedown_buffer_puts

/* hoedown_buffer_reset: frees internal data of the buffer */
void rstub_hoedown_buffer_reset(hoedown_buffer *);
#define hoedown_buffer_reset rstub_hoedown_buffer_reset

/* bufslurp: removes a given number of bytes from the head of the array */
void rstub_bufslurp(hoedown_buffer *, size_t);
#define bufslurp rstub_bufslurp

extern int
rstub_hoedown_autolink_issafe(const uint8_t *link, size_t link_len);
#define hoedown_autolink_issafe rstub_hoedown_autolink_issafe

extern size_t
rstub_hoedown_autolink__www(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                     size_t offset, size_t size, hoedown_autolink_flags flags);
#define hoedown_autolink__www rstub_hoedown_autolink__www

extern size_t
rstub_hoedown_autolink__email(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                       size_t offset, size_t size, hoedown_autolink_flags flags);
#define hoedown_autolink__email rstub_hoedown_autolink__email

extern size_t
rstub_hoedown_autolink__url(size_t *rewind_p, hoedown_buffer *link, uint8_t *data,
                     size_t offset, size_t size, hoedown_autolink_flags flags);
#define hoedown_autolink__url rstub_hoedown_autolink__url

extern struct hoedown_document *
rstub_hoedown_document_new(hoedown_renderer * renderer,	unsigned int extensions,
	size_t max_nesting);
#define hoedown_document_new rstub_hoedown_document_new

extern void
rstub_hoedown_document_render(struct hoedown_document *doc, hoedown_buffer *ob, 
                              const uint8_t *data, size_t doc_size);
#define hoedown_document_render rstub_hoedown_document_render

extern void
rstub_hoedown_document_free(struct hoedown_document *doc);
#define hoedown_document_free rstub_hoedown_document_free

extern void
rstub_sd_version(int *major, int *minor, int *revision);
#define sd_version rstub_sd_version

struct rhd_renderer {
   char *name;
   Rboolean (*render)(hoedown_buffer *,hoedown_buffer *, SEXP, SEXP);
};

Rboolean rstub_rhd_register_renderer(struct rhd_renderer *);
#define rhd_register_renderer rstub_rhd_register_renderer

SEXP rstub_rhd_registered_renderers(void);
#define rhd_registered_renderers rstub_rhd_registered_renderers

Rboolean rstub_rhd_renderer_exists(const char *);
#define rhd_renderer_exists rstub_rhd_renderer_exists

Rboolean rstub_rhd_buf_to_output(hoedown_buffer *, SEXP, SEXP *);
#define rhd_buf_to_output rstub_rhd_buf_to_output

Rboolean rstub_rhd_input_to_buf(SEXP, SEXP, hoedown_buffer *);
#define rhd_input_to_buf rstub_rhd_input_to_buf

#ifdef __cplusplus
}
#endif

#endif // HOEDOWN_RSTUBS
