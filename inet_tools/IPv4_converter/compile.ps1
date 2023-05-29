$env:CHERE_INVOKING = 'yes'
$env:MSYSTEM = 'MINGW64'

rm *.exe
C:\msys64\usr\bin\bash -lc 'make all'
./*.exe


