library(rhoedown)
f = tempfile()
if (file.create(f)) {
   markdownToHTML(f, fragment.only = TRUE)
   markdownToHTML(f)
   unlink(f)
}
