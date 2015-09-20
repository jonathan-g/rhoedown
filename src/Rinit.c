/*
 * Rinit.c
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
            
#include <R_ext/Rdynload.h>
#include "Rhoedown.h"
#include "buffer.h"
#include "autolink.h"
#include "html.h"
#include "hoedown_version.h"

#define CALLDEF(name, n) {#name,(DL_FUNC) &name, n}
static R_CallMethodDef CallEntries[] = {
   CALLDEF(rhd_render_markdown,6),
   CALLDEF(rhd_registered_renderers,0),
   CALLDEF(rhd_render_smartypants,3),
   CALLDEF(rhd_b64encode_data,1),
   {NULL,NULL,0}
};

void R_init_rhoedown(DllInfo *dll)
{
   R_registerRoutines(dll,NULL,CallEntries, NULL, NULL);
   R_useDynamicSymbols(dll, FALSE);

   rhd_init_renderer_list();

   /* Callable functions from other packages' C code */
#define RREGDEF(name) R_RegisterCCallable("rhoedown", #name, (DL_FUNC) name)
   RREGDEF(hoedown_buffer_cstr);
   RREGDEF(hoedown_buffer_free);
   RREGDEF(hoedown_buffer_grow);
   RREGDEF(hoedown_buffer_new);
   RREGDEF(hoedown_buffer_prefix);
   RREGDEF(hoedown_buffer_put);
   RREGDEF(hoedown_buffer_puts);
   RREGDEF(hoedown_buffer_printf);
   RREGDEF(hoedown_buffer_putc);
   RREGDEF(hoedown_buffer_reset);
   RREGDEF(hoedown_buffer_slurp);
   RREGDEF(hoedown_autolink_is_safe);
   RREGDEF(hoedown_autolink__www);
   RREGDEF(hoedown_autolink__email);
   RREGDEF(hoedown_autolink__url);
   RREGDEF(hoedown_document_new);
   RREGDEF(hoedown_document_render);
   RREGDEF(hoedown_document_free);
   RREGDEF(hoedown_version);

   /* markdown C calls */
   RREGDEF(rhd_register_renderer);
   RREGDEF(rhd_renderer_exists);
   RREGDEF(rhd_input_to_buf);
   RREGDEF(rhd_buf_to_output);
}
