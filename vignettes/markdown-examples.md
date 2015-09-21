<!--
%\VignetteEngine{knitr::knitr}
%\VignetteIndexEntry{Some Markdown Examples}
-->

This vignette shows some examples for different Markdown extensions and HTML options.




```r
library(rhoedown)
```

# Markdown Extensions


```r
# The following examples are short, so we set the HTML option 'fragment_only'

options(rhoedown.HTML.options = "fragment_only")

# no_intra_emphasis example
cat(markdownToHTML(text = "foo_bar_function", extensions = c()))
```

```
## <p>foo<em>bar</em>function</p>
```

```r
cat(markdownToHTML(text = "foo_bar_function", extensions = c("no_intra_emphasis")))
```

```
## <p>foo_bar_function</p>
```

```r
# tables example (need 4 spaces at beginning of line here)
cat(markdownToHTML(text = "
    First Header  | Second Header
    ------------- | -------------
    Content Cell  | Content Cell
    Content Cell  | Content Cell
", extensions = c()))
```

```
## <pre><code>First Header  | Second Header
## ------------- | -------------
## Content Cell  | Content Cell
## Content Cell  | Content Cell
## </code></pre>
```

```r
# but not here
cat(markdownToHTML(text = "
First Header  | Second Header
------------- | -------------
Content Cell  | Content Cell
Content Cell  | Content Cell
", extensions = c("tables")))
```

```
## <table>
## <thead>
## <tr>
## <th>First Header</th>
## <th>Second Header</th>
## </tr>
## </thead>
## 
## <tbody>
## <tr>
## <td>Content Cell</td>
## <td>Content Cell</td>
## </tr>
## <tr>
## <td>Content Cell</td>
## <td>Content Cell</td>
## </tr>
## </tbody>
## </table>
```

```r
# fenced_code example (need at least three leading ~ or `)
fenced_block <- function(text, x = "`", n = 3) {
  fence <- paste(rep(x, n), collapse = "")
  paste(fence, text, fence, sep = "")
}
cat(markdownToHTML(text = fenced_block("
preformatted text here without having to indent
first line.
"), extensions = c()))
```

```
## <p><code>
## preformatted text here without having to indent
## first line.
## </code></p>
```

```r
cat(markdownToHTML(text = fenced_block("
preformatted text here without having to indent
first line.
"), extensions = c("fenced_code")))
```

```
## <pre><code>preformatted text here without having to indent
## first line.
## </code></pre>
```

```r
# autolink example
cat(markdownToHTML(text = "http://www.r-project.org/", extensions = c()))
```

```
## <p>http://www.r-project.org/</p>
```

```r
cat(markdownToHTML(text = "http://www.r-project.org/", extensions = c("autolink")))
```

```
## <p><a href="http://www.r-project.org/">http://www.r-project.org/</a></p>
```

```r
# strikethrough example
cat(markdownToHTML(text = "~~awesome~~", extensions = c()))
```

```
## <p>~~awesome~~</p>
```

```r
cat(markdownToHTML(text = "~~awesome~~", extensions = c("strikethrough")))
```

```
## <p><del>awesome</del></p>
```

```r
# lax_spacing
cat(markdownToHTML(text = "
Embedding html without surrounding with empty newline.
<div>_markdown_</div>
extra text.
", extensions = c("")))
```

```
## <p>Embedding html without surrounding with empty newline.
## <div><em>markdown</em></div>
## extra text.</p>
```

```r
cat(markdownToHTML(text = "
Embedding html without surrounding with empty newline.
<div>_markdown_</div>
extra text.
", extensions = c("lax_spacing")))
```

```
## <p>Embedding html without surrounding with empty newline.
## <div><em>markdown</em></div>
## extra text.</p>
```

```r
# space_headers example
cat(markdownToHTML(text = "#A Header\neven though there is no space between # and A",
                   extensions = c("")))
```

```
## <h1 id="toc_0">A Header</h1>
## 
## <p>even though there is no space between # and A</p>
```

```r
cat(markdownToHTML(text = "#Not A Header\nbecause there is no space between # and N",
                   extensions = c("space_headers")))
```

```
## <p>#Not A Header
## because there is no space between # and N</p>
```

```r
# superscript example
cat(markdownToHTML(text = "2^10", extensions = c()))
```

```
## <p>2^10</p>
```

```r
cat(markdownToHTML(text = "2^10", extensions = c("superscript")))
```

```
## <p>2<sup>10</sup></p>
```

```r
cat(markdownToHTML(text = "2~10", extensions = c("subscript")))
```

```
## <p>2<sub>10</sub></p>
```

# HTML Options


```r
# HTML OPTIONS

# The following examples are short, so we allways add the HTML option 'fragment_only'
tOpt <- "fragment_only"

# skip_html example
mkd = '<style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a>'
cat(markdownToHTML(text = mkd, options = c(tOpt)))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_html")))
```

```
## <p>Hello</p>
```

```r
# skip_style example
cat(markdownToHTML(text = mkd, options = c(tOpt)))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_style")))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
# skip_images example
cat(markdownToHTML(text = mkd, options = c(tOpt)))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_images")))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
# skip_links example
cat(markdownToHTML(text = mkd, options = c(tOpt)))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_links")))
```

```
## <p><style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a></p>
```

```r
# safelink example
cat(markdownToHTML(text = '[foo](http://google.com "baz")', options = c(tOpt)))
```

```
## <p><a href="http://google.com" title="baz">foo</a></p>
```

```r
cat(markdownToHTML(text = '[foo](http://google.com "baz")', options = c(tOpt, "safelink")))
```

```
## <p><a href="http://google.com" title="baz">foo</a></p>
```

```r
# toc example
mkd <- paste(c("# Header 1", "p1", "## Header 2", "p2"), collapse = "\n")

cat(markdownToHTML(text = mkd, options = c(tOpt)))
```

```
## <h1 id="toc_0">Header 1</h1>
## 
## <p>p1</p>
## 
## <h2 id="toc_1">Header 2</h2>
## 
## <p>p2</p>
```

```r
cat(markdownToHTML(text = mkd, options = c(tOpt, "toc")))
```

```
## <div id="toc">
## <div id="toc_header">Table of Contents</div>
## <ul>
## <li>
## <a href="#toc_0">Header 1</a>
## <ul>
## <li>
## Header 2</a>
## </li>
## </ul>
## </li>
## </ul>
## </div>
## 
## 
## <h1 id="toc_0">Header 1</h1>
## 
## <p>p1</p>
## 
## <h2 id="toc_1">Header 2</h2>
## 
## <p>p2</p>
```

```r
# hard_wrap example
cat(markdownToHTML(text = "foo\nbar\n", options = c(tOpt)))
```

```
## <p>foo
## bar</p>
```

```r
cat(markdownToHTML(text = "foo\nbar\n", options = c(tOpt, "hard_wrap")))
```

```
## <p>foo<br>
## bar</p>
```

```r
# use_xhtml example
cat(markdownToHTML(text = "foo\nbar\n", options = c(tOpt, "hard_wrap")))
```

```
## <p>foo<br>
## bar</p>
```

```r
cat(markdownToHTML(text = "foo\nbar\n", options = c(tOpt, "hard_wrap", "use_xhtml")))
```

```
## <p>foo<br/>
## bar</p>
```

```r
# escape example
mkd = '<style></style><img src="http://cran.rstudio.com/Rlogo.jpg"><a href="#">Hello</a>'
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_html")))
```

```
## <p>Hello</p>
```

```r
# overrides all 'skip_*' options
cat(markdownToHTML(text = mkd, options = c(tOpt, "skip_html", "escape")))
```

```
## <p>&lt;style&gt;&lt;/style&gt;&lt;img src=&quot;http://cran.rstudio.com/Rlogo.jpg&quot;&gt;&lt;a href=&quot;#&quot;&gt;Hello&lt;/a&gt;</p>
```

```r
# smartypants example
cat(markdownToHTML(text = "1/2 (c)", options = c(tOpt)))
```

```
## <p>1/2 (c)</p>
```

```r
cat(markdownToHTML(text = "1/2 (c)", options = c(tOpt, "smartypants")))
```

```
## <p>&frac12; &copy;</p>
```

```r
cat(smartypants(text = "1/2 (c)\n"))
```

```
## &frac12; &copy;
```



