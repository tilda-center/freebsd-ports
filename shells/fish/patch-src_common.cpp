--- src/common.cpp.orig	2016-07-03 12:15:45 UTC
+++ src/common.cpp
@@ -482,45 +482,6 @@ void append_format(wcstring &str, const 
     va_end(va);
 }
 
-const wchar_t *wcsvarname(const wchar_t *str)
-{
-    while (*str)
-    {
-        if ((!iswalnum(*str)) && (*str != L'_'))
-        {
-            return str;
-        }
-        str++;
-    }
-    return NULL;
-}
-
-const wchar_t *wcsvarname(const wcstring &str)
-{
-    return wcsvarname(str.c_str());
-}
-
-const wchar_t *wcsfuncname(const wcstring &str)
-{
-    return wcschr(str.c_str(), L'/');
-}
-
-
-bool wcsvarchr(wchar_t chr)
-{
-    return iswalnum(chr) || chr == L'_';
-}
-
-int fish_wcswidth(const wchar_t *str)
-{
-    return fish_wcswidth(str, wcslen(str));
-}
-
-int fish_wcswidth(const wcstring& str)
-{
-    return fish_wcswidth(str.c_str(), str.size());
-}
-
 wchar_t *quote_end(const wchar_t *pos)
 {
     wchar_t c = *pos;
