$NetBSD$

--- gcc/gthr-posix.c.orig	2014-07-29 19:09:41.000000000 +0000
+++ gcc/gthr-posix.c
@@ -24,6 +24,9 @@ see the files COPYING3 and COPYING.RUNTI
 <http://www.gnu.org/licenses/>.  */
 
 #include "tconfig.h"
+#include "config.h"
+#include "system.h"
+#include "coretypes.h"
 #include "tm.h"
 # define __gthrw_pragma(pragma) _Pragma (#pragma)
 /* Define so we provide weak definitions of functions used by libobjc only.  */
