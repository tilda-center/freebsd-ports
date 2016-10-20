--- src/wutil.cpp.orig	2016-07-03 12:15:45 UTC
+++ src/wutil.cpp
@@ -2,6 +2,7 @@
   Wide character equivalents of various standard unix
   functions.
 */
+#define FISH_NO_ISW_WRAPPERS
 #include "config.h"
 
 #include <stdlib.h>
@@ -515,6 +516,84 @@ int wrename(const wcstring &old, const w
     return rename(old_narrow.c_str(), new_narrow.c_str());
 }
 
+/// Return one if the code point is in the range we reserve for internal use.
+int fish_is_reserved_codepoint(wint_t wc) {
+    if (RESERVED_CHAR_BASE <= wc && wc < RESERVED_CHAR_END) return 1;
+    if (EXPAND_RESERVED_BASE <= wc && wc < EXPAND_RESERVED_END) return 1;
+    if (WILDCARD_RESERVED_BASE <= wc && wc < WILDCARD_RESERVED_END) return 1;
+    return 0;
+}
+
+/// Return one if the code point is in a Unicode private use area.
+int fish_is_pua(wint_t wc) {
+    if (PUA1_START <= wc && wc < PUA1_END) return 1;
+    if (PUA2_START <= wc && wc < PUA2_END) return 1;
+    if (PUA3_START <= wc && wc < PUA3_END) return 1;
+    return 0;
+}
+
+/// We need this because there are too many implementations that don't return the proper answer for
+/// some code points. See issue #3050.
+int fish_iswalnum(wint_t wc) {
+    if (fish_is_reserved_codepoint(wc)) return 0;
+    if (fish_is_pua(wc)) return 0;
+    return iswalnum(wc);
+}
+
+/// We need this because there are too many implementations that don't return the proper answer for
+/// some code points. See issue #3050.
+int fish_iswalpha(wint_t wc) {
+    if (fish_is_reserved_codepoint(wc)) return 0;
+    if (fish_is_pua(wc)) return 0;
+    return iswalpha(wc);
+}
+
+/// We need this because there are too many implementations that don't return the proper answer for
+/// some code points. See issue #3050.
+int fish_iswgraph(wint_t wc) {
+    if (fish_is_reserved_codepoint(wc)) return 0;
+    if (fish_is_pua(wc)) return 1;
+    return iswgraph(wc);
+}
+
+/// Test if the given string is a valid variable name.
+///
+/// \return null if this is a valid name, and a pointer to the first invalid character otherwise.
+const wchar_t *wcsvarname(const wchar_t *str) {
+    while (*str) {
+        if ((!fish_iswalnum(*str)) && (*str != L'_')) {
+            return str;
+        }
+        str++;
+    }
+    return NULL;
+}
+
+/// Test if the given string is a valid variable name.
+///
+/// \return null if this is a valid name, and a pointer to the first invalid character otherwise.
+const wchar_t *wcsvarname(const wcstring &str) { return wcsvarname(str.c_str()); }
+
+/// Test if the given string is a valid function name.
+///
+/// \return null if this is a valid name, and a pointer to the first invalid character otherwise.
+const wchar_t *wcsfuncname(const wcstring &str) { return wcschr(str.c_str(), L'/'); }
+
+/// Test if the given string is valid in a variable name.
+///
+/// \return true if this is a valid name, false otherwise.
+bool wcsvarchr(wchar_t chr) { return fish_iswalnum(chr) || chr == L'_'; }
+
+/// Convenience variants on fish_wcwswidth().
+///
+/// See fallback.h for the normal definitions.
+int fish_wcswidth(const wchar_t *str) { return fish_wcswidth(str, wcslen(str)); }
+
+/// Convenience variants on fish_wcwswidth().
+///
+/// See fallback.h for the normal definitions.
+int fish_wcswidth(const wcstring &str) { return fish_wcswidth(str.c_str(), str.size()); }
+
 int fish_wcstoi(const wchar_t *str, wchar_t ** endptr, int base)
 {
     long ret = wcstol(str, endptr, base);
