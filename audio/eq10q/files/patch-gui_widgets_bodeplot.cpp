--- gui/widgets/bodeplot.cpp.orig	2017-01-26 21:42:26 UTC
+++ gui/widgets/bodeplot.cpp
@@ -194,14 +194,14 @@ void PlotEQCurve::resetCenterSpan()
 {
   //Compute center and span for the full range spectrum
   double sp = log10(MAX_FREQ/MIN_FREQ);
-  double cn = MIN_FREQ * sqrt(pow10(sp));
+  double cn = MIN_FREQ * sqrt(pow(10, sp));
   setCenterSpan(cn, sp);
 }
 
 void PlotEQCurve::setCenterSpan(double center, double span)
 { 
-  m_minFreq = center / sqrt(pow10(span));
-  m_maxFreq = center * sqrt(pow10(span));
+  m_minFreq = center / sqrt(pow(10, span));
+  m_maxFreq = center * sqrt(pow(10, span));
     
   //Initalize the grid
   const double f_grid[GRID_VERTICAL_LINES] = {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0,
@@ -246,8 +246,8 @@ void PlotEQCurve::setCenter(double cente
 {
   //Limit center to the possible range according the current span
   double sp = log10(m_maxFreq/m_minFreq);
-  double cmin = MIN_FREQ * sqrt(pow10(sp));
-  double cmax = MAX_FREQ / sqrt(pow10(sp));
+  double cmin = MIN_FREQ * sqrt(pow(10, sp));
+  double cmax = MAX_FREQ / sqrt(pow(10, sp));
   
   double cn = center;
   cn = cn > cmax ? cmax : cn;
@@ -259,7 +259,7 @@ void PlotEQCurve::setSpan(double span)
 {
   //Limit center to the possible range according the current span
   double sp_act = log10(m_maxFreq/m_minFreq);
-  double cn = m_minFreq * sqrt(pow10(sp_act));
+  double cn = m_minFreq * sqrt(pow(10, sp_act));
   double smax1 = 2.0*log10(cn/MIN_FREQ);
   double smax2= 2.0*log10(MAX_FREQ/cn);
   double smax = smax1 < smax2 ? smax1 : smax2;
@@ -306,7 +306,7 @@ void PlotEQCurve::recomputeCenterFreq(do
   double fmax = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x2 + 3.5)/((double)m_zoom_surface_ptr->get_width())));
   
   double sp_act = log10(fmax/fmin);
-  double cn = fmin * sqrt(pow10(sp_act));
+  double cn = fmin * sqrt(pow(10, sp_act));
   setCenter(cn);
 }
 
