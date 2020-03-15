@echo off

mkdir ..\zx\bin-a 2> nul
del ..\zx\bin-a\*.bin /q /s
del ..\zx\bin-a\*.h /q /s

echo.
echo Building binary assets
echo ======================

echo.
echo Loading screen
echo --------------
..\utils\png2scr.exe ..\zx\gfx\loading.png ..\zx\bin-a\loading.bin > nul

echo.
echo General assets
echo --------------
..\utils\mkts_sp.exe mode=sprites in=..\zx\gfx\ssmain.png out=..\zx\bin-a\ssmain size=8,1 silent
..\utils\mkts_sp.exe mode=sprites in=..\zx\gfx\ssextra.png out=..\zx\bin-a\ssextra size=1,1 silent
..\utils\mkts_sp.exe mode=sprites in=..\zx\gfx\sssmall.png out=..\zx\bin-a\sssmall size=3,1 metasize=1,1 silent

echo.
echo Fixed screens
echo -------------
..\utils\png2scr.exe ..\zx\gfx\title.png ..\zx\bin-a\title.bin > nul
..\utils\png2scr.exe ..\zx\gfx\frameA.png ..\zx\bin-a\frame.bin > nul
..\utils\apack.exe ..\zx\bin-a\title.bin ..\zx\bin-a\title.c.bin > nul
..\utils\apack.exe ..\zx\bin-a\frame.bin ..\zx\bin-a\frame.c.bin > nul

echo.
echo Level 0 assets
echo --------------
mkdir ..\zx\bin-a\level0 2> nul
..\utils\mkts_sp.exe mode=sprites in=..\zx\gfx\ss0.png out=..\zx\bin-a\level0\ss size=8,1 silent
..\utils\packmap_sp.exe in=..\map\level0.map out=..\zx\bin-a\level0\ size=10,2 fixmappy nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level0.ene out=..\zx\bin-a\level0\ yadjust=1
..\utils\list2bin.exe  ..\zx\gfx\ts0.behs ..\zx\bin-a\level0\behs.bin

echo.
echo Level 1 assets
echo --------------
mkdir ..\zx\bin-a\level1 2> nul
..\utils\mkts_sp.exe mode=sprites in=..\zx\gfx\ss1.png out=..\zx\bin-a\level1\ss size=8,1 silent
..\utils\packmap_sp.exe in=..\map\level1.map out=..\zx\bin-a\level1\ size=10,2 fixmappy nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level1.ene out=..\zx\bin-a\level1\ yadjust=1
..\utils\list2bin.exe  ..\zx\gfx\ts1.behs ..\zx\bin-a\level1\behs.bin

echo.
echo Level 2 assets
echo --------------
mkdir ..\zx\bin-a\level2 2> nul
..\utils\packmap_sp.exe in=..\map\level2.map out=..\zx\bin-a\level2\ size=12,1 nodecos noindex
..\utils\eneexp3c_sp.exe in=..\enems\level2.ene out=..\zx\bin-a\level2\ yadjust=1
..\utils\list2bin.exe  ..\zx\gfx\ts2.behs ..\zx\bin-a\level2\behs.bin

echo.
echo Creating main pattern set and level-based tilemaps
echo --------------------------------------------------
cd ..\zx\gfx
..\..\utils\mkts_sp.exe mode=scripted in=ts-a.spt silent
cd ..\..\dev-a

echo.
echo Compressing some
echo ================
echo Level 0 assets
for %%f in (..\zx\bin-a\level0\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo Level 1 assets
for %%f in (..\zx\bin-a\level1\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo Level 2 assets
for %%f in (..\zx\bin-a\level2\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo.
echo The Librarian!
echo ==============
..\utils\librarian_48.exe list=library_zx.txt librarian=util\librarian.h library=assets\library_speccy.h pathprefix=..\zx\bin-a removebin
