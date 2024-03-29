$NetBSD$

--- gcc/config/mirbsd.h.orig	Thu May 29 22:36:32 2014
+++ gcc/config/mirbsd.h	Thu May 29 22:55:47 2014
@@ -0,0 +1,400 @@
+/* $MirOS: ports/lang/egcs/gcc4.4/patches/patch-gcc_config_mirbsd_h,v 1.8 2014/05/29 22:58:50 tg Exp $ */
+
+/* Base configuration file for all MirOS BSD targets.
+   Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2005, 2006, 2007,
+   2008, 2009, 2014
+   Free Software Foundation, Inc.
+   Contributed by Thorsten “mirabilos” Glaser <tg@mirbsd.org>
+
+This file is part of GCC.
+
+GCC is free software; you can redistribute it and/or modify
+it under the terms of the GNU General Public License as published by
+the Free Software Foundation; version 2.
+
+GCC is distributed in the hope that it will be useful,
+but WITHOUT ANY WARRANTY; without even the implied warranty of
+MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
+GNU General Public License for more details.
+
+You should have received a copy of the GNU General Public License
+along with GCC; see the file COPYING.  If not, write to
+the Free Software Foundation, 59 Temple Place - Suite 330,
+Boston, MA 02111-1307, USA.  */
+
+#include <sys/types.h>
+#include <sys/mman.h>
+#include <stdint.h>
+#include <stdio.h>
+#include <unistd.h>
+
+/* TARGET_OS_CPP_BUILTINS() common to all MirOS BSD targets.  */
+#define MIRBSD_OS_CPP_BUILTINS()			\
+  do							\
+    {							\
+      builtin_define ("__MirBSD__");			\
+      builtin_define ("__OpenBSD__");			\
+      builtin_define ("__unix__");			\
+      builtin_define ("__STDC_ISO_10646__=200009L");	\
+      builtin_assert ("system=unix");			\
+      builtin_assert ("system=bsd");			\
+      builtin_assert ("system=MirBSD");			\
+    }							\
+  while (0)
+
+/* CPP_SPEC parts common to all MirOS BSD targets.  */
+#ifdef CPP_CPU_SPEC
+#define MIRBSD_CPP_SPEC			\
+  "%(cpp_cpu) 				\
+   %{posix:-D_POSIX_SOURCE}		\
+   %{pthread:-D_POSIX_THREADS}"
+#else
+#define MIRBSD_CPP_SPEC			\
+  "%{posix:-D_POSIX_SOURCE}		\
+   %{pthread:-D_POSIX_THREADS}"
+#endif
+
+#undef CPP_SPEC
+#define CPP_SPEC			MIRBSD_CPP_SPEC
+
+/* Since we use gas, stdin -> - is a good idea.  */
+#define AS_NEEDS_DASH_FOR_PIPED_INPUT
+
+
+/* Look for the include files in the system-defined places.  */
+
+#undef INCLUDE_DEFAULTS
+#define INCLUDE_DEFAULTS {					\
+	{ GPLUSPLUS_INCLUDE_DIR, "G++", 1, 1, 0 },		\
+	{ GPLUSPLUS_TOOL_INCLUDE_DIR, "G++", 1, 1, 0 },		\
+	{ GPLUSPLUS_BACKWARD_INCLUDE_DIR, "G++", 1, 1, 0 },	\
+	{ GCC_INCLUDE_DIR, "GCC", 0, 0, 0 },			\
+	{ "/usr/include", NULL, 0, 0, 1 },			\
+	{ NULL, NULL, 0, 0, 0 }					\
+}
+
+/* MirOS provides most *crt*.o files in the /usr/lib directory.  */
+
+#undef STANDARD_STARTFILE_PREFIX
+#define STANDARD_STARTFILE_PREFIX	"/usr/lib/"
+
+
+/* Provide a LIB_SPEC appropriate for MirOS BSD.  */
+
+#define MIRBSD_LIB_SPEC		\
+  "%{pthread:-lpthread}		\
+   %{!shared:			\
+     %{!symbolic:-lc}}"
+
+#undef LIB_SPEC
+#define LIB_SPEC		MIRBSD_LIB_SPEC
+
+/* Provide a LIBGCC_SPEC stub for shared libgcc use.  */
+
+#define MIRBSD_LIBGCC_SPEC	"-lgcc"
+
+#undef LIBGCC_SPEC
+#define LIBGCC_SPEC		MIRBSD_LIBGCC_SPEC
+
+/* When building shared libraries, the initialization and finalization
+   functions for the library are .init and .fini respectively.  */
+
+#define COLLECT_SHARED_INIT_FUNC(STREAM,FUNC)				\
+  do {									\
+    fprintf ((STREAM), "void __init() __asm__ (\".init\");");		\
+    fprintf ((STREAM), "void __init() {\n\t%s();\n}\n", (FUNC));	\
+  } while (0)
+
+#define COLLECT_SHARED_FINI_FUNC(STREAM,FUNC)				\
+  do {									\
+    fprintf ((STREAM), "void __fini() __asm__ (\".fini\");");		\
+    fprintf ((STREAM), "void __fini() {\n\t%s();\n}\n", (FUNC));	\
+  } while (0)
+
+#undef TARGET_HAS_F_SETLKW
+#define TARGET_HAS_F_SETLKW
+
+/* Handle #pragma weak and #pragma pack.  */
+
+#define HANDLE_SYSV_PRAGMA 1
+
+/* Define this so we can compile MS code for use with WINE.  */
+#define HANDLE_PRAGMA_PACK_PUSH_POP 1
+
+/* Don't use the 'xsTAG;' construct in DBX output; BSD systems that
+   use DBX don't support it.  */
+#define DBX_NO_XREFS
+
+
+/* Define some types that are the same on all MirOS BSD platforms,
+   making them agree with <machine/ansi.h>.  */
+
+#undef WCHAR_TYPE
+#define WCHAR_TYPE "short unsigned int"
+
+#undef WCHAR_TYPE_SIZE
+#define WCHAR_TYPE_SIZE 16
+
+#undef WINT_TYPE
+#define WINT_TYPE "unsigned int"
+
+#undef SIZE_TYPE
+#define SIZE_TYPE "long unsigned int"
+
+#undef PTRDIFF_TYPE
+#define PTRDIFF_TYPE "long int"
+
+/* This defines which switch letters take arguments.  On MirOS, most
+   of the normal cases (defined by gcc.c) apply.  */
+
+#undef SWITCH_TAKES_ARG
+#define SWITCH_TAKES_ARG(CHAR)			\
+  (DEFAULT_SWITCH_TAKES_ARG (CHAR)		\
+   || (CHAR) == 'R')
+
+
+/* Provide a STARTFILE_SPEC appropriate for MirOS BSD.  Here we
+   provide support for the special GCC option -static.  On ELF
+   targets, we also add the crtbegin.o file, which provides part
+   of the support for getting C++ file-scope static objects
+   constructed before entering "main".  */
+
+#define MIRBSD_STARTFILE_SPEC	\
+  "%:if-exists(crti%O%s)	\
+   %{!shared:crt0%O%s}		\
+   %{static:			\
+     %:if-exists-else(crtbeginT%O%s crtbegin%O%s)} \
+   %{!static:			\
+     %{!shared:crtbegin%O%s}	\
+     %{shared:crtbeginS%O%s}}"
+
+#undef STARTFILE_SPEC
+#define STARTFILE_SPEC MIRBSD_STARTFILE_SPEC
+
+
+/* Provide an ENDFILE_SPEC appropriate for MirOS BSD.  Here we
+   add crtend.o, which provides part of the support for getting
+   C++ file-scope static objects deconstructed after exiting "main".  */
+
+#define MIRBSD_ENDFILE_SPEC	\
+  "%{!shared:crtend%O%s}	\
+   %{shared:crtendS%O%s}	\
+   %:if-exists(crtn%O%s)"
+
+#undef ENDFILE_SPEC
+#define ENDFILE_SPEC MIRBSD_ENDFILE_SPEC
+
+/*
+ * Work around gcc version-specific library vs rpath problem.
+ * Components are:
+ *	%R = sysroot præfix (empty except if cross-compiling)
+ *	STANDARD_EXEC_PREFIX = “${PREFIX}/lib/gcc/”
+ *	DEFAULT_TARGET_MACHINE = “${OStriplet}”
+ *	DEFAULT_TARGET_VERSION = “4.4.7”
+ */
+#undef MIRBSD_RDIR
+#define MIRBSD_RDIR	STANDARD_EXEC_PREFIX DEFAULT_TARGET_MACHINE "/" \
+			DEFAULT_TARGET_VERSION
+
+/* Provide a LINK_SPEC appropriate for MirOS BSD.  Here we provide
+   support for the special GCC options -assert, -R, -rpath, -shared,
+   -nostdlib, -static, -rdynamic, and -dynamic-linker.
+
+   Target-specific code can use this in conjunction with any other
+   target-specific LINK_SPEC options.  */
+
+#define MIRBSD_LINK_SPEC			\
+  "%{assert*} %{R*} %{rpath*}			\
+   -L%R" MIRBSD_RDIR " -rpath " MIRBSD_RDIR "	\
+   %{!shared:					\
+     -dc -dp					\
+     %{!nostdlib:%{!r*:%{!e*:-e __start}}}	\
+     %{!static:					\
+       %{rdynamic:-export-dynamic}		\
+       %{!dynamic-linker:			\
+	 -dynamic-linker /usr/libexec/ld.so}}	\
+     %{static:-Bstatic}}			\
+   %{!static:-Bdynamic}				\
+   %{shared:-shared}"
+
+#undef LINK_SPEC
+#define LINK_SPEC MIRBSD_LINK_SPEC
+
+/* This is to address issues with libgcc: some of the functions are
+   also provided by libc, and we prefer these due to them being less
+   buggy.  Since we always use GNU ld, we can use the libs grouping
+   feature to prevent listing the libraries two or three times each.  */
+#undef LINK_GCC_C_SEQUENCE_SPEC
+#define LINK_GCC_C_SEQUENCE_SPEC "--start-group %L %G --end-group"
+
+/* Don't assume anything about the header files.  Needed for libjava.  */
+#undef NO_IMPLICIT_EXTERN_C
+#define NO_IMPLICIT_EXTERN_C 1
+
+/* MirOS BSD targets need to make the stack executable.  */
+
+#undef ENABLE_EXECUTE_STACK
+#define ENABLE_EXECUTE_STACK						\
+extern void __enable_execute_stack (void *);				\
+void									\
+__enable_execute_stack (void *addr)					\
+{									\
+  static intptr_t size = 0;						\
+  static intptr_t mask;							\
+  intptr_t page = (intptr_t)addr;					\
+  size_t end = (intptr_t)addr + TRAMPOLINE_SIZE;			\
+									\
+  if (size == 0)							\
+    {									\
+      size = sysconf(_SC_PAGESIZE);					\
+      mask = ~(size - 1);						\
+    }									\
+									\
+  page &= mask;								\
+  end = (end & mask) + size - page;					\
+									\
+  if (mprotect ((char *)page, end,					\
+   PROT_READ | PROT_WRITE | PROT_EXEC) < 0)				\
+    perror ("mprotect of trampoline code");				\
+}
+
+/* Disable the use of unsafe builtin functions (strcat, strcpy), making
+   them easier to be spotted in the object files.  */
+
+#define NO_UNSAFE_BUILTINS
+
+/* Support of shared libraries, mostly imported from svr4.h through netbsd.  */
+/* Two differences from svr4.h:
+   - we use . - _func instead of a local label,
+   - we put extra spaces in expressions such as
+     .type _func , @function
+     This is more readable for a human being and confuses cxxfilt less.  */
+
+/* Assembler format: output and generation of labels.  */
+
+/* Define the strings used for the .type and .size directives.
+   These strings generally do not vary from one system running BSD
+   to another, but if a given system needs to use different pseudo-op
+   names for these, they may be overridden in the arch specific file.  */
+
+#undef TYPE_ASM_OP
+#undef SIZE_ASM_OP
+#undef SET_ASM_OP
+#undef GLOBAL_ASM_OP
+
+#define TYPE_ASM_OP	"\t.type\t"
+#define SIZE_ASM_OP	"\t.size\t"
+#define SET_ASM_OP	"\t.set\t"
+#define GLOBAL_ASM_OP	"\t.globl\t"
+
+/* The following macro defines the format used to output the second
+   operand of the .type assembler directive.  */
+#undef TYPE_OPERAND_FMT
+#define TYPE_OPERAND_FMT	"@%s"
+
+/* Provision if extra assembler code is needed to declare a function's result
+   (taken from svr4, not needed yet actually).  */
+#ifndef ASM_DECLARE_RESULT
+#define ASM_DECLARE_RESULT(FILE, RESULT)
+#endif
+
+/* These macros generate the special .type and .size directives which
+   are used to set the corresponding fields of the linker symbol table
+   entries under MirOS.  These macros also have to output the starting
+   labels for the relevant functions/objects.  */
+
+/* Extra assembler code needed to declare a function properly.
+   Some assemblers may also need to also have something extra said
+   about the function's return value.  We allow for that here.  */
+#undef ASM_DECLARE_FUNCTION_NAME
+#define ASM_DECLARE_FUNCTION_NAME(FILE, NAME, DECL)			\
+  do {									\
+	fprintf (FILE, "%s", TYPE_ASM_OP);				\
+	assemble_name (FILE, NAME);					\
+	fputs (" , ", FILE);						\
+	fprintf (FILE, TYPE_OPERAND_FMT, "function");			\
+	putc ('\n', FILE);						\
+	ASM_DECLARE_RESULT (FILE, DECL_RESULT (DECL));			\
+	ASM_OUTPUT_LABEL(FILE, NAME);					\
+  } while (0)
+
+/* Declare the size of a function.  */
+#undef ASM_DECLARE_FUNCTION_SIZE
+#define ASM_DECLARE_FUNCTION_SIZE(FILE, FNAME, DECL)			\
+  do {									\
+	if (!flag_inhibit_size_directive) {				\
+		fprintf (FILE, "%s", SIZE_ASM_OP);			\
+		assemble_name (FILE, (FNAME));				\
+		fputs (" , . - ", FILE);				\
+		assemble_name (FILE, (FNAME));				\
+		putc ('\n', FILE);					\
+	}								\
+  } while (0)
+
+/* Extra assembler code needed to declare an object properly.  */
+#undef ASM_DECLARE_OBJECT_NAME
+#define ASM_DECLARE_OBJECT_NAME(FILE, NAME, DECL)			\
+  do {									\
+	fprintf (FILE, "%s", TYPE_ASM_OP);				\
+	assemble_name (FILE, NAME);					\
+	fputs (" , ", FILE);						\
+	fprintf (FILE, TYPE_OPERAND_FMT, "object");			\
+	putc ('\n', FILE);						\
+	size_directive_output = 0;					\
+	if (!flag_inhibit_size_directive && (DECL) &&			\
+	    DECL_SIZE (DECL)) {						\
+		size_directive_output = 1;				\
+		fprintf (FILE, "%s", SIZE_ASM_OP);			\
+		assemble_name (FILE, NAME);				\
+		fprintf (FILE, " , %ld\n",				\
+		    int_size_in_bytes (TREE_TYPE (DECL)));		\
+	}								\
+	ASM_OUTPUT_LABEL (FILE, NAME);					\
+  } while (0)
+
+/* Output the size directive for a decl in rest_of_decl_compilation
+   in the case where we did not do so before the initializer.
+   Once we find the error_mark_node, we know that the value of
+   size_directive_output was set by ASM_DECLARE_OBJECT_NAME
+   when it was run for the same decl.  */
+#undef ASM_FINISH_DECLARE_OBJECT
+#define ASM_FINISH_DECLARE_OBJECT(FILE, DECL, TOP_LEVEL, AT_END)	\
+do {									\
+	const char *name = XSTR (XEXP (DECL_RTL (DECL), 0), 0);		\
+	if (!flag_inhibit_size_directive && DECL_SIZE (DECL)		\
+	    && ! AT_END && TOP_LEVEL					\
+	    && DECL_INITIAL (DECL) == error_mark_node			\
+	    && !size_directive_output) {				\
+		size_directive_output = 1;				\
+		fprintf (FILE, "%s", SIZE_ASM_OP);			\
+		assemble_name (FILE, name);				\
+		fprintf (FILE, " , %ld\n",				\
+		    int_size_in_bytes (TREE_TYPE (DECL)));		\
+	}								\
+   } while (0)
+
+/* Those are 'generic' ways to weaken/globalize a label. We shouldn't need
+   to override a processor specific definition. Hence, #ifndef ASM_*
+   In case overriding turns out to be needed, one can always #undef ASM_*
+   before including this file.  */
+
+/* Tell the assembler that a symbol is weak.  */
+/* Note: netbsd arm32 assembler needs a .globl here. An override may
+   be needed when/if we go for arm32 support.  */
+#ifndef ASM_WEAKEN_LABEL
+#define ASM_WEAKEN_LABEL(FILE,NAME) \
+  do { fputs ("\t.weak\t", FILE); assemble_name (FILE, NAME); \
+       fputc ('\n', FILE); } while (0)
+#endif
+
+/* Exception handling.  */
+
+/* Use --as-needed -lgcc_s for eh support.  */
+#ifdef HAVE_LD_AS_NEEDED
+#define USE_LD_AS_NEEDED 1
+#endif
+
+/* Disable emitting __stack_chk_fail_local */
+#ifdef TARGET_LIBC_PROVIDES_SSP
+#define TARGET_LIBC_PROVIDES_SSP_NONLOCAL_ONLY
+#endif
