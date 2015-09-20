Markdown rendering for R
=============================================================================

[![Build Status](https://travis-ci.org/jonathan-g/rhoedown.svg)](https://travis-ci.org/jonathan-g/rhoedown)

Overview
-----------------------------------------------------------------------------

*Markdown* is a plain-text formatting syntax that can be converted
to XHTML or other formats. This package provides R bindings to the
[Hoedown](https://github.com/hoedown/hoedown) markdown rendering library.

The R function `markdownToHTML` renders a markdown file to HTML. Options
controlling HTML output and supported markdown extensions can be optionally
specified.

The package also exports the underlying Hoedown C extension API which
enables creating and calling custom renderers using the `renderMarkdown`
function.

To learn more about markdown syntax see: <http://en.wikipedia.org/wiki/Markdown>

License
-----------------------------------------------------------------------------

The rhoedown package is licensed under the GPLv2. See these files for
additional details:

- inst/COPYING - Markdown package license (GPLv2)
- inst/NOTICE  - Copyright notices for additional included software
