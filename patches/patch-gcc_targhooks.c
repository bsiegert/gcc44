$NetBSD$

--- gcc/targhooks.c.orig	2014-07-29 19:11:00.000000000 +0000
+++ gcc/targhooks.c
@@ -500,7 +500,7 @@ default_external_stack_protect_fail (voi
 tree
 default_hidden_stack_protect_fail (void)
 {
-#ifndef HAVE_GAS_HIDDEN
+#if !defined(HAVE_GAS_HIDDEN) || defined(TARGET_LIBC_PROVIDES_SSP_NONLOCAL_ONLY)
   return default_external_stack_protect_fail ();
 #else
   tree t = stack_chk_fail_decl;
