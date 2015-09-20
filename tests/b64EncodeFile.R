library(rhoedown)

## Download
url = "http://www.r-project.org/Rlogo.png"
path = tempdir()
pathname = file.path(tempdir(), basename(url))
if (!file_test("-f", pathname)) download.file(url, pathname)

## Encode
data = rhoedown:::.b64EncodeFile(pathname)
str(data)

unlink(pathname)
