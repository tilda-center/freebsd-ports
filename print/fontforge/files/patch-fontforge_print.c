--- fontforge/print.c.orig	2014-11-27 00:40:08 UTC
+++ fontforge/print.c
@@ -1148,19 +1148,7 @@ static void dump_pdfprologue(PI *pi) {
     tm = localtime(&now);
     fprintf( pi->out, "    /CreationDate (D:%04d%02d%02d%02d%02d%02d",
 	    tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );
-#ifdef _NO_TZSET
     fprintf( pi->out, "Z)\n" );
-#else
-    if ( timezone==0 )
-	fprintf( pi->out, "Z)\n" );
-    else {
-	if ( timezone<0 ) /* fprintf bug - this is a kludge to print +/- in front of a %02d-padded value */
-	    fprintf( pi->out, "-" );
-	else
-	    fprintf( pi->out, "+" );
-	fprintf( pi->out, "%02d'%02d')\n", (int)(timezone/3600),(int)(timezone/60-(timezone/3600)*60) );
-    }
-#endif
     if ( author!=NULL )
 	fprintf( pi->out, "  /Author (%s)\n", author );
     fprintf( pi->out, ">>\n" );
