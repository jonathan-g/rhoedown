## ----read-code, include=FALSE--------------------------------------------
library(knitr)
opts_chunk$set(tidy = FALSE)  # otherwise \n will cause problems
read_chunk(system.file('examples', 'markdownExtensions.R', package = 'rhoedown'),
           labels = 'md-extensions')
read_chunk(system.file('examples', 'HTMLOptions.R', package = 'rhoedown'),
           labels = 'html-options')

## ------------------------------------------------------------------------
library(rhoedown)

