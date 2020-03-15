Idea: usar solo 3 bytes para la persistencia de los enemigos. El tema se basa en que tanto mx como my solo pueden valer 1, -1, 2, -2, 4, -4. Así puedo usar un nibble para cada componente:

`SVVV SVVV`, donde S = signo (0 positivo, 1 negativo) y VVV el valor, en binario.

Para recuperar:

```c
	mx = myx & 0x07; if (myx & 0x08) mx = -mx;
	my = (myx >> 4) & 0x07; if (myx & 0x80) my = -my;
```

Para almacenar:

```c
	if (mx >= 0) myx = mx; else myx = 0x08 | (-mx);
	if (my >= 0) myx |= (my << 4); else myx |= (((-my) << 4) | 0x80);
```

Creo que con esto lo tengo resuelto.

