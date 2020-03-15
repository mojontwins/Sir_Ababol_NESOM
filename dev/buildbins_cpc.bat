@echo off

mkdir ..\ports\cpc\bin 2> nul
del ..\ports\cpc\bin\*.bin /q /s
del ..\ports\cpc\bin\*.h /q /s

echo.
echo Building binary assets
echo ======================

echo.
echo General assets
echo --------------
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssmain.png out=..\ports\cpc\bin\ssmain size=8,1 metasize=2,3 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssextra.png out=..\ports\cpc\bin\ssextra size=1,1 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ssempty.png out=..\ports\cpc\bin\ssempty size=1,1 metasize=2,3 silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\sssmall.png out=..\ports\cpc\bin\sssmall size=1,1 silent

echo.
echo Fixed screens
echo -------------
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=superbuffer in=..\ports\cpc\gfx\title.png out=..\ports\cpc\bin\title.bin silent
..\utils\apack.exe ..\ports\cpc\bin\title.bin ..\ports\cpc\bin\title.c.bin > nul
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=superbuffer in=..\ports\cpc\gfx\ending.png out=..\ports\cpc\bin\ending.bin silent
..\utils\apack.exe ..\ports\cpc\bin\ending.bin ..\ports\cpc\bin\ending.c.bin > nul
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=scr  in=..\ports\cpc\gfx\loading.png out=..\ports\cpc\bin\loading.bin silent
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=scr  in=..\ports\cpc\gfx\pre-loading.png out=..\ports\cpc\bin\pre-loading.bin silent

echo.
echo Level 0 assets
echo --------------
mkdir ..\ports\cpc\bin\level0 2> nul
..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=sprites in=..\ports\cpc\gfx\ss0.png out=..\ports\cpc\bin\level0\ss size=8,1 silent
..\utils\rle53map_sp.exe in=..\map\level0.map out=..\ports\cpc\bin\level0\ size=16,3 scrsize=16,10 tlock=15 nodecos
..\utils\eneexp3c_sp.exe in=..\enems\level0.ene out=..\ports\cpc\bin\level0\ yadjust=1 prefix=0
..\utils\list2bin.exe  ..\ports\cpc\gfx\ts0.behs ..\ports\cpc\bin\level0\behs.bin

echo.
echo Creating main pattern set and level-based tilemaps
echo --------------------------------------------------
cd ..\ports\cpc\gfx
..\..\..\utils\mkts_om.exe platform=cpc brickInput pal=..\ports\cpc\gfx\pal.png  mode=scripted in=ts-a.spt silent
cd ..\..\..\dev
..\utils\apack.exe ..\ports\cpc\bin\frame.bin ..\ports\cpc\bin\frame.c.bin > nul

echo.
echo ARKOS tracker player stuff
echo --------------------------
cd ..\lib\arkos\
echo Assembling player
..\..\utils\pasmo.exe ArkosTrackerPlayer_CPC_MSX.asm ..\..\ports\cpc\bin\arkos.bin arkos.lst
echo Compiling assets
cd ..\..\ports\cpc\ogt\
..\..\..\utils\AKSToBIN.exe -a 32250 "01 - Sir Ababol CPC - Title_.aks" ..\bin\m0.bin
..\..\..\utils\AKSToBIN.exe -a 32250 "02 - Sir Ababol CPC - Ingame.aks" ..\bin\m1.bin
..\..\..\utils\AKSToBIN.exe -a 32250 "03 - Sir Ababol CPC - Game Over.aks" ..\bin\m2.bin
..\..\..\utils\AKSToBIN.exe -s -a 60928 sfx___vol_1.aks ..\bin\sfx.bin
cd ..\..\..\dev\
..\utils\apack.exe ..\ports\cpc\bin\arkos.bin ..\ports\cpc\bin\arkos.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\sfx.bin ..\ports\cpc\bin\sfx.c.bin >nul
copy /b ..\ports\cpc\bin\arkos.c.bin + ..\ports\cpc\bin\sfx.c.bin ..\ports\cpc\arkos_sfx.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\m0.bin ..\ports\cpc\bin\m0.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\m1.bin ..\ports\cpc\bin\m1.c.bin >nul
..\utils\apack.exe ..\ports\cpc\bin\m2.bin ..\ports\cpc\bin\m2.c.bin >nul

rem echo.
rem echo Compressing some
rem echo ================
rem echo Level 0 assets
rem for %%f in (..\ports\cpc\bin\level0\*.bin) do ..\utils\apack.exe "%%~pf%%~nf.bin" "%%~pf%%~nf.c.bin"  >nul

echo.
echo The Librarian!
echo ==============
..\utils\librarian_48.exe list=library_cpc.txt librarian=util\librarian.h library=assets\library_cpc.h pathprefix=..\ports\cpc\bin removebin
