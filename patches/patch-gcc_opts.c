$NetBSD$
$MirOS: ports/lang/egcs/gcc4.4/patches/patch-gcc_opts_c,v 1.2 2014/02/10 01:15:51 tg Exp $

--- gcc/opts.c.orig	Fri Nov 27 11:34:08 2009
+++ gcc/opts.c	Sun Dec  1 04:04:48 2013
@@ -1599,6 +1599,9 @@ common_handle_option (size_t scode, cons
       set_Wextra (value);
       break;
 
+    case OPT_Wbounded:
+      break;
+
     case OPT_Werror_:
       enable_warning_as_error (arg, value, lang_mask);
       break;
@@ -2042,6 +2045,9 @@ common_handle_option (size_t scode, cons
     case OPT_gxcoff:
     case OPT_gxcoff_:
       set_debug_level (XCOFF_DEBUG, code == OPT_gxcoff_, arg);
+      break;
+
+    case OPT_fhonour_copts:
       break;
 
     case OPT_o:
