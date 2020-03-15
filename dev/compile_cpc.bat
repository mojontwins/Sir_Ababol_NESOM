@echo off

SET game=AbabolNESOM

..\utils\mkts_om.exe platform=cpc mode=pals in=..\ports\cpc\gfx\pal.png prefix=my_inks out=assets\pal.h silent

if [%1]==[tape] goto :tape

echo ### COMPILING ###
zcc +cpc -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c > nul 
rem zcc +cpc -vn -O3 -unsigned -m -notemp -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c

echo ### MAKING DSK ###
copy %game%.bin game.bin > nul 
copy ..\ports\cpc\base.dsk %game%.dsk > nul 
copy ..\ports\cpc\arkos_sfx.c.bin arkos.bin > nul 
copy ..\ports\cpc\bin\loading.bin loading.bin > nul
..\utils\CPCDiskXP\CPCDiskXP.exe -File game.bin -AddAmsDosHeader 400 -AddToExistingDsk %game%.dsk
..\utils\CPCDiskXP\CPCDiskXP.exe -File arkos.bin -AddAmsDosHeader 7DFA -AddToExistingDsk %game%.dsk
..\utils\CPCDiskXP\CPCDiskXP.exe -File loading.bin -AddAmsDosHeader C000 -AddToExistingDsk %game%.dsk
del game.bin  > nul 
del arkos.bin > nul 
del loading.bin > nul
del zcc_opt.def  > nul 
goto :fin

:tape
echo *** CDT version ***
echo ### COMPILING ###
zcc +cpc -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC -DTAPE -o %game%.bin tilemap_conf.asm mk3.c > nul 

echo ### MAKING TAP ###
dir %game%.bin
..\utils\apack.exe %game%.bin gamec.bin
..\utils\apack.exe ..\ports\cpc\bin\pre-loading.bin scrc0.bin
..\utils\apack.exe ..\ports\cpc\bin\loading.bin scrc1.bin

copy ..\ports\cpc\arkos_sfx.c.bin arkos_sfx.c.bin > nul 

set loader_org=$a300
rem 46848 is b700
rem 41728 is a300

..\utils\imanol.exe in=loader\loadercpc.asm-orig out=loader\loader.asm binsize=?%game%.bin scrc_size=?scrc0.bin scrc1_size=?scrc1.bin mainbin_addr=?41728-gamec.bin mainbin_size=?gamec.bin arkos_sfx_c_size=?arkos_sfx.c.bin arkos_c_size=?..\ports\cpc\bin\arkos.c.bin loader_org=%loader_org% > nul
..\utils\pasmo.exe loader\loader.asm loader.bin  > nul

dir loader.bin

..\utils\2cdt.exe -n -r %game% -s 1 -X %loader_org% -L %loader_org% loader.bin %game%.cdt 
..\utils\2cdt.exe -r scr -s 1 -m 2 scrc0.bin %game%.cdt  
..\utils\2cdt.exe -r scr -s 1 -m 2 scrc1.bin %game%.cdt  
..\utils\2cdt.exe -r game -s 1 -m 2 gamec.bin %game%.cdt  
..\utils\2cdt.exe -r arkos -s 1 -m 2 arkos_sfx.c.bin %game%.cdt  

echo ### LIMPIANDO ###
rem del loader\loader.asm > nul
rem del loader.bin > nul 
del %game%.bin  > nul 
del gamec.bin > nul
del arkos_sfx.c.bin > nul 
del loading.bin > nul 2> nul
del zcc_opt.def  > nul 
del scrc0.bin > nul
del scrc1.bin > nul

goto :fin

:error
	echo ERROR!

:fin
