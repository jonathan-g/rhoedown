roxygen:
	cd .. && rm -f rhoedown_*.tar.gz && R -e "library(Rd2roxygen)" \
		-e "rab('rhoedown', install=TRUE)"

tests: tests/tests.Rout.save

tests/tests.Rout.save: tests/tests.R inst/examples/markdownExtensions.R inst/examples/HTMLOptions.R
	cd tests && R CMD BATCH --no-save --no-restore --no-timing tests.R tests.Rout.save

check:
	cd .. && R CMD check rhoedown_*.tar.gz --as-cran --no-manual
