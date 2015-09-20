import os, re, fnmatch

pairs = [('bufnew', 'hoedown_buffer_new'),
         ('bufrelease', 'hoedown_buffer_free'),
         ('bufgrow', 'hoedown_buffer_grow'),
         ('bufput', 'hoedown_buffer_put'),
         ('bufputs', 'hoedown_buffer_puts'),
         ('stack_oinit', 'hoedown_stack_new'),
         ('stack_free', 'hoedown_stack_free'),
         ('sd_markdown_new', 'hoedown_document_new'),
         ('sd_markdown_free', 'hoedown_document_free'),
         ('sd_autolink_issafe', 'hoedown_autolink_is_safe'),
         ('sdhtml_is_tag', 'hoedown_html_is_tag'),
         ('struct buf', 'hoedown_buffer'),
         ('sd_markdown_render','hoedown_document_render'),
         ('sdhtml_renderer', 'hoedown_html_renderer'),
         ('sdhtml_toc_renderer', 'hoedown_html_toc_renderer'),
         ('sdhtml_smartypants', 'hoedown_html_smartypants'),
         ('sd_callbacks', 'hoedown_renderer'),
         ('MKDA_NOT_AUTOLINK', 'HOEDOWN_AUTOLINK_NONE'),
         ('MKDEXT_FENCED_CODE', 'HOEDOEN_EXT_FENCED_CODE'),
         ]

for i in range(len(pairs)):
  pairs[i] = ('\\b' + pairs[i][0] + '\\b', pairs[i][1])
         
def fix_file(filename):
    f = open(filename)
    lines = f.xreadlines()
    outbuf = []
    for line in lines:
        for p in pairs:
            line = re.sub(p[0], p[1], line)
        outbuf.append(line)
    f.close()
    f = open(filename, 'w')
    f.writelines(outbuf)
    
def fix_files():
    files = fnmatch.filter(os.listdir('.'), '*.[ch]')
    for f in files:
        fix_file(f)

    