/*
 * Rmarkdown.h
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

#include <R.h>
#include <Rinternals.h>
#include "html.h"

#define READ_UNIT 1024
#define OUTPUT_UNIT 64
#define RHD_WARNING_NOMEM warning("Out of memory!")

/* 
 * output_type should be either "raw" or "character"
 */
struct rhd_renderer {
   char *name;
   Rboolean (*render)(hoedown_buffer *,hoedown_buffer *, SEXP, SEXP);
   char *output_type;
};

extern void rhd_init_renderer_list();

extern Rboolean rhd_buf_to_output(hoedown_buffer *, SEXP, SEXP *);

extern Rboolean rhd_input_to_buf(SEXP, SEXP, hoedown_buffer *);

extern Rboolean rhd_register_renderer(struct rhd_renderer *);

extern Rboolean rhd_renderer_exists(const char *name);

extern SEXP rhd_registered_renderers(void);

extern SEXP rhd_render_markdown(SEXP Sfile, SEXP Soutput, SEXP Stext,
                            SEXP Srenderer, SEXP Srender_options,
                            SEXP Soptions);

extern SEXP rhd_render_smartypants(SEXP Sfile, SEXP Soutput, SEXP Stext);

extern SEXP rhd_b64encode_data( SEXP Sdata);
