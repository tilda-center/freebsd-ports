--- gui/widgets/bandctl.cpp.orig	2017-01-26 21:43:08 UTC
+++ gui/widgets/bandctl.cpp
@@ -949,7 +949,7 @@ bool BandCtl::parseBtnString(BandCtl::Bu
   if(str_k.length() > 0)
   {
     val_k = atof(str_k.c_str()) * 1e3;
-    val *= pow10(3.0 - str.length());
+    val *= pow(10, 3.0 - str.length());
     if(str.length() > 3)
     {
       //throw an error, imposible to match str > 3 with k
@@ -960,7 +960,7 @@ bool BandCtl::parseBtnString(BandCtl::Bu
   }
   if(str_d.length() > 0)
   {
-    val_d = atof(str_d.c_str())/ pow10((double)str_d.length());
+    val_d = atof(str_d.c_str())/ pow(10, (double)str_d.length());
   }
    
   btn->value = val + val_k + val_d;
