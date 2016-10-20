--- src/wutil.h.orig	2016-07-03 12:15:45 UTC
+++ src/wutil.h
@@ -130,6 +130,31 @@ int wmkdir(const wcstring &dir, int mode
 */
 int wrename(const wcstring &oldName, const wcstring &newName);
 
+#define PUA1_START 0xE000
+#define PUA1_END 0xF900
+#define PUA2_START 0xF0000
+#define PUA2_END 0xFFFFE
+#define PUA3_START 0x100000
+#define PUA3_END 0x10FFFE
+
+// We need this because there are too many implementations that don't return the proper answer for
+// some code points. See issue #3050.
+#ifndef FISH_NO_ISW_WRAPPERS
+#define iswalnum fish_iswalnum
+#define iswalpha fish_iswalpha
+#define iswgraph fish_iswgraph
+#endif
+int fish_iswalnum(wint_t wc);
+int fish_iswalpha(wint_t wc);
+int fish_iswgraph(wint_t wc);
+
+const wchar_t *wcsvarname(const wchar_t *str);
+const wchar_t *wcsvarname(const wcstring &str);
+const wchar_t *wcsfuncname(const wcstring &str);
+bool wcsvarchr(wchar_t chr);
+int fish_wcswidth(const wchar_t *str);
+int fish_wcswidth(const wcstring &str);
+
 /** Like wcstol(), but fails on a value outside the range of an int */
 int fish_wcstoi(const wchar_t *str, wchar_t ** endptr, int base);
 
