--- src/common.h.orig	2016-07-03 12:15:45 UTC
+++ src/common.h
@@ -711,40 +711,6 @@ void append_format(wcstring &str, const 
 void append_formatv(wcstring &str, const wchar_t *format, va_list ap);
 
 /**
-   Test if the given string is a valid variable name.
-
-   \return null if this is a valid name, and a pointer to the first invalid character otherwise
-*/
-
-const wchar_t *wcsvarname(const wchar_t *str);
-const wchar_t *wcsvarname(const wcstring &str);
-
-
-/**
-   Test if the given string is a valid function name.
-
-   \return null if this is a valid name, and a pointer to the first invalid character otherwise
-*/
-
-const wchar_t *wcsfuncname(const wcstring &str);
-
-/**
-   Test if the given string is valid in a variable name
-
-   \return true if this is a valid name, false otherwise
-*/
-
-bool wcsvarchr(wchar_t chr);
-
-/**
-   Convenience variants on fish_wcwswidth().
-
-   See fallback.h for the normal definitions.
-*/
-int fish_wcswidth(const wchar_t *str);
-int fish_wcswidth(const wcstring& str);
-
-/**
    This functions returns the end of the quoted substring beginning at
    \c in. The type of quoting character is detemrined by examining \c
    in. Returns 0 on error.
