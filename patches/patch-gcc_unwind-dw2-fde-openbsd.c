$NetBSD$

DWARF2 unwind support for OpenBSD/MirBSD, from mgcc

--- gcc/unwind-dw2-fde-openbsd.c.orig	Sat Dec  5 14:28:24 2009
+++ gcc/unwind-dw2-fde-openbsd.c	Sat Dec  5 14:28:24 2009
@@ -0,0 +1,11 @@
+/* $MirOS: ports/lang/egcs/gcc4.4/patches/patch-gcc_unwind-dw2-fde-openbsd_c,v 1.1 2009/12/05 15:38:54 tg Exp $ */
+
+/* XXX This file provides a few defines such that we can compile the
+   source from unwind-dw2-fde-glibc.c on OpenBSD.  Hopefully we can
+   integrate these defines in that file and rename it to something
+   like unwind-de2-fde-phdr.c in the up-stream sources.  */
+
+#define ElfW(type) Elf_##type
+
+#define __GLIBC__ 3		/* Fool unwind-dw2-fde-glibc.c.  */
+#include "unwind-dw2-fde-glibc.c"
