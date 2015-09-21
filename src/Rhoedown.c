/*
 * Rmarkdown.c
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

#include "Rhoedown.h"

#define NREND 8

static struct rhd_renderer RENDERERS[NREND];

static struct rhd_renderer *renderer(const char *name);

static Rboolean render_to_html(hoedown_buffer *ib, hoedown_buffer *ob,
                                  SEXP Soptions, SEXP Sextensions)
{
   hoedown_renderer *hd_renderer = NULL;
   hoedown_extensions extensions = 0;
   hoedown_html_flags renderflags = 0;
   hoedown_document *markdown = NULL;
   hoedown_buffer *htmlbuf = NULL;
   Rboolean toc = FALSE, smarty = FALSE;

   /* Marshal extensions */
   if (isString(Sextensions))
   {
      int i;
      for (i = 0; i < LENGTH(Sextensions); i++)
      {
        if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                       "AUTOLINK") == 0)
          extensions |= HOEDOWN_EXT_AUTOLINK;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "DISABLE_INDENTED_CODE") == 0)
          extensions |= HOEDOWN_EXT_DISABLE_INDENTED_CODE;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "FENCED_CODE") == 0)
          extensions |= HOEDOWN_EXT_FENCED_CODE;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "FOOTNOTES") == 0)
          extensions |= HOEDOWN_EXT_FOOTNOTES;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "HIGHLIGHT") == 0)
          extensions |= HOEDOWN_EXT_HIGHLIGHT;
        else if ((strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                             "MATH_EXPLICIT") == 0) ||
                               (strcasecmp(CHAR(STRING_ELT(Sextensions, i)),
                                           "MATH-EXPLICIT") == 0))
          extensions |= HOEDOWN_EXT_MATH_EXPLICIT;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "MATH") == 0)
          extensions |= HOEDOWN_EXT_MATH;
        else if ((strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                             "LATEX-MATH") == 0) ||
                               (strcasecmp(CHAR(STRING_ELT(Sextensions, i)),
                                           "LATEX_MATH") == 0))
          extensions |= HOEDOWN_EXT_LATEX_MATH;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "NO_INTRA_EMPHASIS") == 0)
          extensions |= HOEDOWN_EXT_NO_INTRA_EMPHASIS;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "QUOTE") == 0)
          extensions |= HOEDOWN_EXT_QUOTE;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "SPACE_HEADERS") == 0)
          extensions |= HOEDOWN_EXT_SPACE_HEADERS;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "STRIKETHROUGH") == 0)
          extensions |= HOEDOWN_EXT_STRIKETHROUGH;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "SUPERSCRIPT") == 0)
          extensions |= HOEDOWN_EXT_SUPERSCRIPT;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "SUBSCRIPT") == 0)
          extensions |= HOEDOWN_EXT_SUBSCRIPT;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                              "TABLES") == 0)
          extensions |= HOEDOWN_EXT_TABLES;
        else if (strcasecmp(CHAR(STRING_ELT(Sextensions,i)),
                            "UNDERLINE") == 0)
          extensions |= HOEDOWN_EXT_UNDERLINE;
      }
   }

   /* Marshal HTML options */
   if (isString(Soptions))
   {
      int i;
      for (i = 0; i < LENGTH(Soptions); i++)
      {
         if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                        "SKIP_HTML") == 0)
            renderflags |= HOEDOWN_HTML_SKIP_HTML;
         else if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                             "ESCAPE") == 0)
           renderflags |= HOEDOWN_HTML_ESCAPE;
         else if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                        "HARD_WRAP") == 0)
            renderflags |= HOEDOWN_HTML_HARD_WRAP;
         else if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                        "USE_XHTML") == 0)
            renderflags |= HOEDOWN_HTML_USE_XHTML;
         else if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                        "SMARTYPANTS") == 0)
            smarty = TRUE;
         else if (strcasecmp(CHAR(STRING_ELT(Soptions,i)),
                             "TOC") == 0)
         {
           toc = TRUE;
         }
      }
   }

   htmlbuf = hoedown_buffer_new(OUTPUT_UNIT);
   if (!htmlbuf)
   {
      RHD_WARNING_NOMEM;
      return FALSE;
   }

   if (toc==TRUE)
   {
      hoedown_buffer *tocbuf = hoedown_buffer_new(OUTPUT_UNIT);

      if (!tocbuf)
      {
         RHD_WARNING_NOMEM;
         return FALSE;
      }

      hd_renderer = hoedown_html_toc_renderer_new(16);
      markdown = hoedown_document_new(hd_renderer, extensions, 16);
      if (!markdown)
      {
         RHD_WARNING_NOMEM;
         return FALSE;
      }

      hoedown_document_render(markdown, tocbuf, ib->data, ib->size);
      hoedown_document_free(markdown);

      hoedown_buffer_puts(htmlbuf,"<div id=\"toc\">\n");
      hoedown_buffer_puts(htmlbuf,"<div id=\"toc_header\">Table of Contents</div>\n");
      hoedown_buffer_put(htmlbuf,tocbuf->data,tocbuf->size);
      hoedown_buffer_puts(htmlbuf,"</div>\n");
      hoedown_buffer_puts(htmlbuf,"\n");
      hoedown_buffer_free(tocbuf);
   }

   hd_renderer = hoedown_html_renderer_new(renderflags, 16);

   markdown = hoedown_document_new(hd_renderer, extensions, 16);
   if (!markdown)
   {
      RHD_WARNING_NOMEM;
      return FALSE;
   }

   hoedown_document_render(markdown, htmlbuf, ib->data, ib->size);

   hoedown_document_free(markdown);

   if (smarty==TRUE)
   {
      hoedown_buffer *smartybuf = hoedown_buffer_new(OUTPUT_UNIT);
      if (!smartybuf)
      {
         RHD_WARNING_NOMEM;
         return FALSE;
      }
      hoedown_html_smartypants(smartybuf,htmlbuf->data,htmlbuf->size);
      hoedown_buffer_free(htmlbuf);
      htmlbuf = smartybuf;
   }

   hoedown_buffer_put(ob,htmlbuf->data,htmlbuf->size);

   hoedown_buffer_free(htmlbuf);

   return TRUE;
}

void rhd_init_renderer_list()
{
   int i;
   struct rhd_renderer *html;
   for (i=0;i<NREND;i++)
   {
      memset(&RENDERERS[i],0,sizeof(struct rhd_renderer));
   }

   /* Add HTML renderer */
   html = &RENDERERS[0];
   html->name = "HTML";
   html->render = render_to_html;
   html->output_type = "character";
}

Rboolean rhd_renderer_exists(const char *name)
{
   return (renderer(name) != NULL)? TRUE: FALSE;
}

Rboolean rhd_register_renderer(struct rhd_renderer *renderer)
{
   int i, empty_slot = -1, name_exists = -1;

   if (!renderer)
      return FALSE;

   for (i=0;i<NREND;i++)
   {
      if (RENDERERS[i].name == NULL)
      {
         if (empty_slot < 0)
            empty_slot = i;
      }
      else if (strcmp(RENDERERS[i].name,renderer->name)==0)
         name_exists = i;
   }

   /* replace old renderer without warning */
   if (name_exists>=0)
      empty_slot = name_exists;

   if (empty_slot>=0)
   {
      if (RENDERERS[empty_slot].name != NULL)
      {
         free(RENDERERS[empty_slot].name);
         free(RENDERERS[empty_slot].output_type);
      }
      RENDERERS[empty_slot].name = strdup(renderer->name);
      RENDERERS[empty_slot].render = renderer->render;
      RENDERERS[empty_slot].output_type = strdup(renderer->output_type);
   }
   else
   {
      error("Renderer list full!");
      return FALSE;
   }
   return TRUE;
}

SEXP rhd_registered_renderers(void)
{
   SEXP ans;
   SEXP names;
   char *name, *output_type;
   int i;

   PROTECT(ans = allocVector(STRSXP,NREND));
   PROTECT(names = allocVector(STRSXP,NREND));

   for (i=0;i<NREND;i++)
   {
      if (RENDERERS[i].name != NULL)
      {
         name = RENDERERS[i].name;
         output_type = RENDERERS[i].output_type;

      } else {
         name = "";
         output_type = "";
      }

      SET_STRING_ELT(ans,i,mkChar(name));
      SET_STRING_ELT(names,i,mkChar(output_type));
   }

   setAttrib(ans,R_NamesSymbol,names);
   UNPROTECT(2);

   return ans;
}

static struct rhd_renderer *renderer(const char *name)
{
   int i;
   for (i=0;i<NREND;i++)
   {
      if (RENDERERS[i].name != NULL && strcmp(RENDERERS[i].name,name)==0)
      {
         return &RENDERERS[i];
      }
   }
   return NULL;
}

Rboolean rhd_input_to_buf(SEXP Sfile, SEXP Stext, hoedown_buffer *ib)
{
   /* Setup input buffer */
   if (isNull(Sfile))
   {
      int len;
      const char *text = CHAR(STRING_ELT(Stext,0));
      len = strlen(text);
      if (len > 0)
      {
         hoedown_buffer_grow(ib,len);
         hoedown_buffer_put(ib,(const void *)text,len);
      }
      else
      {
         warning("Input text is zero length!");
         return FALSE;
      }
   }
   else
   {
      FILE *in;
      size_t ret;
      const char *file = CHAR(STRING_ELT(Sfile,0));

      in = fopen(file,"r");
      if (!in)
      {
         warning("Cannot open %s!", file);
         return FALSE;
      }
      hoedown_buffer_grow(ib, READ_UNIT);
      while ((ret = fread(ib->data + ib->size, 1, ib->asize - ib->size,
                          in)) > 0) {
         ib->size += ret;
         hoedown_buffer_grow(ib, ib->size + READ_UNIT);
      }
      fclose(in);
   }

   return TRUE;
}

Rboolean rhd_buf_to_output(hoedown_buffer *ob, SEXP Soutput, SEXP *raw_vec)
{
   /* Output */
   if (isNull(Soutput))
   {
      PROTECT(*raw_vec = allocVector(RAWSXP, ob->size));
      memcpy(RAW(*raw_vec),ob->data,ob->size);
      UNPROTECT(1);
   }
   else
   {
      const char *filename = CHAR(STRING_ELT(Soutput,0));
      FILE *out = fopen(filename,"w");
      if (!out)
      {
         warning("Cannot save output to %s!", filename);
         return FALSE;
      }

      fwrite(ob->data, 1, ob->size, out);
      fclose(out);

      if (ferror (out))
      {
         warning("Error occurred writing to %s!", filename);
         return FALSE;
      }
   }

   return TRUE;
}

/* Pandoc title blocks are prepended with percents '%'. They start on the
 * first line of the document and contain 3 elements: 'title','author',
 * and date. Both 'title' and 'author' can extend to multiple lines so
 * long as that line starts with a space, but 'date' cannot.
 */
void skip_pandoc_title_block(hoedown_buffer *ib){
	int i = 0;
   size_t pos = 0;

   /* pandoc 1.9.1.1 expects title blocks to start on the first line */
   if (ib->data[0] != '%') return;

   /* We search for at most 3 elements: title, author, and date */
   for (i = 0; i < 3; i++){
      if (ib->data[pos] != '%') break;

      /* Search for end of line */
      while (pos < ib->size && ib->data[pos] != '\n') pos++;
      if (pos < ib->size) pos++;
      else break;

      do {
         /* Only title and author can contain continuation lines,
          * e.g. i < 2
          */
         if (ib->data[pos] == ' ' && i < 2){
            while (pos < ib->size && ib->data[pos] != '\n') pos++;
            if (pos < ib->size) pos++;
            else break;
         } else {
            break;
         }
      } while(1);
   }

   /* If we've seen a title block, we'll take it off
    * the beginning of our buffer by slurping up pos bytes.
    */
   if (pos > 0) hoedown_buffer_slurp(ib,pos);
}

/* Jekyll front matter begins on the first line and the first three characters
 * of the line are '---'. Front matter ends when a line is started with '---'.
 * We skip everything in between including the ending '---'.
 */
void skip_jekyll_front_matter(hoedown_buffer *ib){
   int front_matter_found = 0;
   size_t pos = 0;

   /* Jekyll 0.12.0 expects front matter to start on the first line */
   if (ib->size < 3 || !(ib->data[0] == '-' && ib->data[1] == '-' &&
      ib->data[2] == '-') ) return;

   pos = 3;
   do {
      while (pos < ib->size && ib->data[pos] != '\n') pos++;
      if (pos == ib->size) break;
      if (pos+3 < ib->size){
         if (ib->data[pos+1] == '-' && ib->data[pos+2] == '-' && ib->data[pos+3] == '-'){
            front_matter_found = 1;
            pos += 4;
            break;
         } else {
            pos++;
         }
      } else {
         break;
      }
   } while(1);

   if (front_matter_found && pos > 0)
      hoedown_buffer_slurp(ib,pos);
}

SEXP rhd_render_markdown(SEXP Sfile, SEXP Soutput, SEXP Stext, SEXP Srenderer,
                            SEXP Soptions, SEXP Sextensions)
{
   const char *name;
   hoedown_buffer *ib, *ob;
   SEXP ret_val = R_NilValue;
   Rboolean success;

   name = CHAR(STRING_ELT(Srenderer,0));

   if (!rhd_renderer_exists(name))
   {
      error("Renderer '%s' not registered!",name);
      return R_NilValue;
   }

   ib = hoedown_buffer_new(READ_UNIT);
   if (!ib)
      error("Out of memory!");

   success = rhd_input_to_buf(Sfile,Stext,ib);
   if (!success)
   {
      hoedown_buffer_free(ib);
      error("Input error!");
   }

   skip_pandoc_title_block(ib);
   skip_jekyll_front_matter(ib);

   ob = hoedown_buffer_new(OUTPUT_UNIT);
   if (!ob)
      error("Out of memory!");

   success = renderer(name)->render(ib,ob,Soptions,Sextensions);
   if (!success)
   {
      hoedown_buffer_free(ib);
      hoedown_buffer_free(ob);
      error("Render error!");
   }

   success = rhd_buf_to_output(ob,Soutput,&ret_val);

   hoedown_buffer_free(ib);
   hoedown_buffer_free(ob);

   if (!success)
      error("Output error!");

   return ret_val;
}

SEXP rhd_render_smartypants(SEXP Sfile, SEXP Soutput, SEXP Stext)
{
   hoedown_buffer *ib, *ob;
   SEXP ret_val = R_NilValue;
   Rboolean success;

   ib = hoedown_buffer_new(READ_UNIT);
   if (!ib)
      error("Out of memory!");

   success = rhd_input_to_buf(Sfile, Stext, ib);

   if (!success)
   {
      hoedown_buffer_free(ib);
      error("Input error!");
   }

   ob = hoedown_buffer_new(OUTPUT_UNIT);
   if (!ob)
      error("Out of memory!");

   hoedown_html_smartypants(ob,ib->data,ib->size);

   success = rhd_buf_to_output(ob,Soutput,&ret_val);

   hoedown_buffer_free(ib);
   hoedown_buffer_free(ob);

   if (!success)
      error("Output error!");

   return ret_val;
}
