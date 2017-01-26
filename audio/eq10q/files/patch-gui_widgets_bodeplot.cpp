--- gui/widgets/bodeplot.cpp.orig	2017-01-26 12:12:00 UTC
+++ gui/widgets/bodeplot.cpp
@@ -41,7 +41,7 @@
 PlotEQCurve::PlotEQCurve(int iNumOfBands, int channels)
 :width(PLOT_WIDTH),
 height(PLOT_HIGHT),
-m_TotalBandsCount(iNumOfBands), 
+m_TotalBandsCount(iNumOfBands),
 m_NumChannels(channels),
 m_Bypass(false),
 bMotionIsConnected(false),
@@ -49,7 +49,7 @@ bBandFocus(false),
 m_BandRedraw(false),
 m_fullRedraw(false),
 m_justRedraw(false),
-SampleRate(0), //Initially zero to force the freq vectors initialization 
+SampleRate(0), //Initially zero to force the freq vectors initialization
 m_FftActive(false),
 m_minFreq(MIN_FREQ),
 m_maxFreq(MAX_FREQ),
@@ -58,25 +58,25 @@ fft_gain(0.0),
 fft_range(80.0),
 m_bIsSpectrogram(false),
 m_bFftHold(false)
-{    
+{
   //Allocate memory for filter data strcuts
   m_filters = new FilterBandParams*[m_TotalBandsCount];
   for (int i = 0; i<m_TotalBandsCount; i++)
   {
     m_filters[i] = new FilterBandParams;
   }
-  
+
   //Allocate memory for f and pixels arrays
   f = new double[CURVE_NUM_OF_POINTS];
   xPixels = new int[CURVE_NUM_OF_POINTS];
-  
+
   //Allocate memory for Y axes arrays
   main_y = new double*[m_NumChannels];
   for (int i = 0; i<m_NumChannels; i++)
   {
     main_y[i] = new double[CURVE_NUM_OF_POINTS];
   }
-  
+
   band_y = new double*[m_TotalBandsCount];
   band_state = new MSState[m_TotalBandsCount];
   for (int i = 0; i<m_TotalBandsCount; i++)
@@ -91,7 +91,7 @@ m_bFftHold(false)
       band_state[i] = MONO;
     }
   }
-  
+
   //init curves to zero state
   for(int i = 0; i<CURVE_NUM_OF_POINTS; i++)
   {
@@ -104,23 +104,23 @@ m_bFftHold(false)
             band_y[j][i] = 0.0;
     }
   }
-  
+
   //Allocate memory for band redraw vector
   m_Bands2Redraw = new bool[m_TotalBandsCount];
   m_curve_surface_ptr = new  Cairo::RefPtr<Cairo::ImageSurface> [m_TotalBandsCount];
-  
-  //Allocate memory for FFT data 
-  xPixels_fft = new double[(FFT_N/2) + 1]; 
-  xPixels_fft_bins = new double[(FFT_N/2) + 1]; 
+
+  //Allocate memory for FFT data
+  xPixels_fft = new double[(FFT_N/2) + 1];
+  xPixels_fft_bins = new double[(FFT_N/2) + 1];
   fft_pink_noise = new double[(FFT_N/2) + 1];
   fft_plot = new double[(FFT_N/2) + 1];
   fft_ant_data = new double [(FFT_N/2) + 1];
-  
+
   fft_log_lut = GenerateLog10LUT();
   resetCurve();
 
   set_size_request(width, height);
-  
+
   //Init zoom widget
   m_zoom_widget.center_focus = false;
   m_zoom_widget.center_press = false;
@@ -131,14 +131,14 @@ m_bFftHold(false)
   m_zoom_widget.x1 = 0;
   m_zoom_widget.x2 = 0;
   m_zoom_widget.x_ant = 0;
-  
-  
+
+
   //Connect mouse signals
   add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK | Gdk::SCROLL_MASK | Gdk::LEAVE_NOTIFY_MASK);
   signal_button_press_event().connect(sigc::mem_fun(*this, &PlotEQCurve::on_button_press_event),true);
   signal_button_release_event().connect(sigc::mem_fun(*this, &PlotEQCurve::on_button_release_event),true);
   signal_scroll_event().connect(sigc::mem_fun(*this, &PlotEQCurve::on_scrollwheel_event),true);
-  
+
   //The timeout signal used to refresh the display is now connected at first run of on_expose_event to run it with freq vector correctly initialized
   signal_motion_notify_event().connect(sigc::mem_fun(*this, &PlotEQCurve::on_mouse_motion_event),true);
   signal_leave_notify_event().connect(sigc::mem_fun(*this, &PlotEQCurve::on_mouse_leave_widget),true);
@@ -146,7 +146,7 @@ m_bFftHold(false)
 
   //Init FFT vectors
   setSampleRate(44.1e3);
-      
+
   //Allow this widget to get keyboard focus
   set_can_focus(true);
 }
@@ -160,26 +160,26 @@ PlotEQCurve::~PlotEQCurve()
   }
   delete[] m_filters;
   delete[] m_Bands2Redraw;
-  
+
   //Delete freq and pixels pointers
   delete[] f;
   delete[] xPixels;
-  
+
   //Delete Y array pointers
   for (int i = 0; i<m_NumChannels; i++)
   {
     delete[] main_y[i];
   }
-  delete[] main_y; 
-  
+  delete[] main_y;
+
   for (int i = 0; i<m_TotalBandsCount; i++)
   {
     delete[] band_y[i];
   }
   delete[] band_y;
-  
+
   delete[] band_state;
-  
+
   //Delete FFT plots
   delete[] fft_pink_noise;
   delete[] xPixels_fft;
@@ -194,50 +194,50 @@ void PlotEQCurve::resetCenterSpan()
 {
   //Compute center and span for the full range spectrum
   double sp = log10(MAX_FREQ/MIN_FREQ);
-  double cn = MIN_FREQ * sqrt(pow10(sp));
+  double cn = MIN_FREQ * sqrt(pow(10, sp));
   setCenterSpan(cn, sp);
 }
 
 void PlotEQCurve::setCenterSpan(double center, double span)
-{ 
-  m_minFreq = center / sqrt(pow10(span));
-  m_maxFreq = center * sqrt(pow10(span));
-    
+{
+  m_minFreq = center / sqrt(pow(10, span));
+  m_maxFreq = center * sqrt(pow(10, span));
+
   //Initalize the grid
   const double f_grid[GRID_VERTICAL_LINES] = {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0,
                         100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0,
                         1000.0, 2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0, 8000.0, 9000.0,
                         10000.0, 20000.0};
-                                             
+
   for(int i=0; i < GRID_VERTICAL_LINES; i++)
   {
     xPixels_Grid[i] = freq2Pixels(f_grid[i]);
   }
-  
+
   //Initialize freq vector and pixels for the new limits
   for(int i=0; i < CURVE_NUM_OF_POINTS; i++)
-  {   
+  {
     xPixels[i] = (double)(i)*(((double)(width - 2*CURVE_MARGIN-CURVE_TEXT_OFFSET_X))/((double)(CURVE_NUM_OF_POINTS - 1)));
     f[i] = Pixels2freq(xPixels[i]);
   }
-  
+
   //Recalc freq bins to fit fft into widget size
   const double wrangePx = (freq2Pixels(MAX_FREQ) - freq2Pixels(MIN_FREQ));
   for(int i = 0; i <= (FFT_N/2); i++)
   {
     xPixels_fft_bins[i] =  round(xPixels_fft[i] * wrangePx)/(wrangePx);
   }
-  
+
   //Clear spectrogram to fit the new zoom windows
   if(m_fft_surface_ptr)
   {
-    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);  
+    Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
   }
-  
+
   //Redraw all by timer
   m_fullRedraw = true;
 }
@@ -246,9 +246,9 @@ void PlotEQCurve::setCenter(double cente
 {
   //Limit center to the possible range according the current span
   double sp = log10(m_maxFreq/m_minFreq);
-  double cmin = MIN_FREQ * sqrt(pow10(sp));
-  double cmax = MAX_FREQ / sqrt(pow10(sp));
-  
+  double cmin = MIN_FREQ * sqrt(pow(10, sp));
+  double cmax = MAX_FREQ / sqrt(pow(10, sp));
+
   double cn = center;
   cn = cn > cmax ? cmax : cn;
   cn = cn < cmin ? cmin : cn;
@@ -259,11 +259,11 @@ void PlotEQCurve::setSpan(double span)
 {
   //Limit center to the possible range according the current span
   double sp_act = log10(m_maxFreq/m_minFreq);
-  double cn = m_minFreq * sqrt(pow10(sp_act));
+  double cn = m_minFreq * sqrt(pow(10, sp_act));
   double smax1 = 2.0*log10(cn/MIN_FREQ);
   double smax2= 2.0*log10(MAX_FREQ/cn);
   double smax = smax1 < smax2 ? smax1 : smax2;
-  
+
   double sp = span > smax ? smax : span;
   sp = sp < MIN_SPAN_DEC ? MIN_SPAN_DEC : sp;
   setCenterSpan(cn, sp);
@@ -271,13 +271,13 @@ void PlotEQCurve::setSpan(double span)
 
 void PlotEQCurve::recomputeMinFreq_fromX1Pixel(double x1)
 {
-  
+
   if( m_zoom_widget.x2 - x1 < 30) return; //To avoid crossing control points
-  
+
   double desp = x1 -  m_zoom_widget.x1;
-  double local_x1 =  m_zoom_widget.x1 + desp; 
-  double local_x2 =  m_zoom_widget.x2 - desp; 
-  
+  double local_x1 =  m_zoom_widget.x1 + desp;
+  double local_x2 =  m_zoom_widget.x2 - desp;
+
   double fmin = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x1 - 3.5)/((double)m_zoom_surface_ptr->get_width())));
   double fmax = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x2 + 3.5)/((double)m_zoom_surface_ptr->get_width())));
   setSpan(log10(fmax/fmin));
@@ -286,11 +286,11 @@ void PlotEQCurve::recomputeMinFreq_fromX
 void PlotEQCurve::recomputeMaxFreq_fromX2Pixel(double x2)
 {
    if( x2 - m_zoom_widget.x1 < 30) return; //To avoid crossing control points
-  
+
   double desp = x2 -  m_zoom_widget.x2;
-  double local_x1 =  m_zoom_widget.x1 - desp; 
-  double local_x2 =  m_zoom_widget.x2 + desp; 
-  
+  double local_x1 =  m_zoom_widget.x1 - desp;
+  double local_x2 =  m_zoom_widget.x2 + desp;
+
   double fmin = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x1 - 3.5)/((double)m_zoom_surface_ptr->get_width())));
   double fmax = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x2 + 3.5)/((double)m_zoom_surface_ptr->get_width())));
   setSpan(log10(fmax/fmin));
@@ -301,12 +301,12 @@ void PlotEQCurve::recomputeCenterFreq(do
 
   double local_x1 = m_zoom_widget.x1 - CURVE_MARGIN - CURVE_TEXT_OFFSET_X + xDiff;
   double local_x2 = m_zoom_widget.x2 - CURVE_MARGIN - CURVE_TEXT_OFFSET_X + xDiff;
-  
+
   double fmin = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x1 - 3.5)/((double)m_zoom_surface_ptr->get_width())));
   double fmax = MIN_FREQ*pow((MAX_FREQ/MIN_FREQ),((local_x2 + 3.5)/((double)m_zoom_surface_ptr->get_width())));
-  
+
   double sp_act = log10(fmax/fmin);
-  double cn = fmin * sqrt(pow10(sp_act));
+  double cn = fmin * sqrt(pow(10, sp_act));
   setCenter(cn);
 }
 
@@ -319,7 +319,7 @@ void PlotEQCurve::resetCurve()
       main_y[j][i] = 0.0;
     }
   }
-  
+
   for (int i = 0; i<m_TotalBandsCount; i++)
   {
     m_filters[i]->bIsOn = false;
@@ -327,7 +327,7 @@ void PlotEQCurve::resetCurve()
     m_filters[i]->fType = PEAK;
     m_filters[i]->Gain = 0.0;
     m_filters[i]->Q = 2.0;
-    
+
     //Reset band_y to zero
     for(int j = 0; j < CURVE_NUM_OF_POINTS; j++)
     {
@@ -337,12 +337,12 @@ void PlotEQCurve::resetCurve()
 }
 
 void PlotEQCurve::ComputeFilter(int bd_ix)
-{  
+{
   if(m_filters[bd_ix]->fType != NOT_SET)
   {
     CalcBand_DigitalFilter(bd_ix);
   }
-  
+
   //Compute Shape
   for(int i = 0; i < CURVE_NUM_OF_POINTS; i++)
   {
@@ -359,20 +359,20 @@ void PlotEQCurve::ComputeFilter(int bd_i
           case MONO:
             main_y[0][i] += band_y[j][i];
             break;
-            
+
           case DUAL:
             main_y[0][i] += band_y[j][i];
             main_y[1][i] += band_y[j][i];
             break;
-            
+
           case ML:
             main_y[0][i] += band_y[j][i];
             break;
-            
+
           case SR:
             main_y[1][i] += band_y[j][i];
             break;
-            
+
         }
       }
     }
@@ -409,7 +409,7 @@ void  PlotEQCurve::setBandEnable(int bd_
   m_filters[bd_ix]->bIsOn = bIsEnabled;
   cueBandRedraws(bd_ix);
 }
-    
+
 void PlotEQCurve::setBypass(bool bypass)
 {
   m_Bypass = bypass;
@@ -419,9 +419,9 @@ void PlotEQCurve::setBypass(bool bypass)
 //==========================SIGNAL SLOTS===========================================================
 //Mouse grab signal handlers
 bool PlotEQCurve::on_button_press_event(GdkEventButton* event)
-{       
+{
   grab_focus();
-  
+
   //Check if is a double click or simple
   if(event->button == 1 && bBandFocus)
   {
@@ -461,16 +461,16 @@ bool PlotEQCurve::on_button_release_even
   m_zoom_widget.center_press = false;
   m_zoom_widget.f1_press = false;
   m_zoom_widget.f2_press = false;
-  return true; 
+  return true;
 }
 
 bool PlotEQCurve::on_scrollwheel_event(GdkEventScroll* event)
 {
    //Check if is over some control pointer
-  
+
   const double x = event->x - CURVE_MARGIN - CURVE_TEXT_OFFSET_X;
   const double y = event->y - CURVE_MARGIN;
-  
+
   for(int i = 0; i < m_TotalBandsCount; i++)
   {
     if( x > freq2Pixels(m_filters[i]->Freq) - BALL_DETECTION_PIXELS &&
@@ -478,36 +478,36 @@ bool PlotEQCurve::on_scrollwheel_event(G
 	y > dB2Pixels(m_filters[i]->Gain) - BALL_DETECTION_PIXELS &&
 	y < dB2Pixels(m_filters[i]->Gain) + BALL_DETECTION_PIXELS )
     {
-      if (event->direction == GDK_SCROLL_UP) 
-      { 
+      if (event->direction == GDK_SCROLL_UP)
+      {
 	// up code
 	m_filters[i]->Q += SCROLL_EVENT_INCREMENT*m_filters[i]->Q;
 	m_filters[i]->Q = m_filters[i]->Q > PEAK_Q_MAX ? PEAK_Q_MAX : m_filters[i]->Q;
-      } 
-      else if (event->direction == GDK_SCROLL_DOWN) 
-      { 
-	// down code 
+      }
+      else if (event->direction == GDK_SCROLL_DOWN)
+      {
+	// down code
 	m_filters[i]->Q -= SCROLL_EVENT_INCREMENT*m_filters[i]->Q;
 	m_filters[i]->Q = m_filters[i]->Q < PEAK_Q_MIN ? PEAK_Q_MIN : m_filters[i]->Q;
       }
-    
+
     //Redraw with timeout
     cueBandRedraws(m_iBandSel);
-        
+
     // emit the signal
     m_BandChangedSignal.emit( i, m_filters[i]->Gain, m_filters[i]->Freq, m_filters[i]->Q);
     break;
     }
   }
-  
+
   return true;
 }
 
 bool PlotEQCurve::on_mouse_motion_event(GdkEventMotion* event)
-{ 
+{
   const double x = event->x - CURVE_MARGIN - CURVE_TEXT_OFFSET_X;
   const double y = event->y - CURVE_MARGIN;
-      
+
   if(bMotionIsConnected)
   {
     //Recompute curve on current band and redraw
@@ -516,7 +516,7 @@ bool PlotEQCurve::on_mouse_motion_event(
     m_filters[m_iBandSel]->Freq = Pixels2freq(xclipped);
     m_filters[m_iBandSel]->Freq = m_filters[m_iBandSel]->Freq > FREQ_MAX ? FREQ_MAX : m_filters[m_iBandSel]->Freq;
     m_filters[m_iBandSel]->Freq = m_filters[m_iBandSel]->Freq < FREQ_MIN ? FREQ_MIN : m_filters[m_iBandSel]->Freq;
-    
+
     if (m_filters[m_iBandSel]->fType == PEAK ||
 	m_filters[m_iBandSel]->fType == HIGH_SHELF ||
 	m_filters[m_iBandSel]->fType == LOW_SHELF )
@@ -525,14 +525,14 @@ bool PlotEQCurve::on_mouse_motion_event(
       m_filters[m_iBandSel]->Gain = m_filters[m_iBandSel]->Gain > GAIN_MAX ? GAIN_MAX : m_filters[m_iBandSel]->Gain;
       m_filters[m_iBandSel]->Gain = m_filters[m_iBandSel]->Gain < GAIN_MIN ? GAIN_MIN : m_filters[m_iBandSel]->Gain;
     }
-    
+
     else
     {
       m_filters[m_iBandSel]->Gain = 0.0;
     }
-    
+
     redraw_cursor(xclipped,  dB2Pixels(m_filters[m_iBandSel]->Gain));
-    
+
     //Redraw with timeout
     cueBandRedraws(m_iBandSel);
 
@@ -544,12 +544,12 @@ bool PlotEQCurve::on_mouse_motion_event(
   else
   {
     redraw_cursor(event->x -CURVE_MARGIN - CURVE_TEXT_OFFSET_X, event->y  - CURVE_MARGIN);
-    
+
     //Check if is over Zoom widget
     if((event->x > m_zoom_widget.x1 - 10 &&
         event->x < m_zoom_widget.x2 + 10 &&
         event->y > height -CURVE_MARGIN - CURVE_TEXT_OFFSET_Y + ZOOM_WIDGET_BORDER_Y &&
-        event->y < height -CURVE_MARGIN ) || 
+        event->y < height -CURVE_MARGIN ) ||
         m_zoom_widget.center_press || m_zoom_widget.f1_press || m_zoom_widget.f2_press)
     {
       if(m_zoom_widget.center_press)
@@ -569,7 +569,7 @@ bool PlotEQCurve::on_mouse_motion_event(
         m_zoom_widget.f1_focus = true;
         m_zoom_widget.f2_focus = false;
         m_zoom_widget.center_focus = false;
-        recomputeMinFreq_fromX1Pixel(event->x); 
+        recomputeMinFreq_fromX1Pixel(event->x);
         m_fullRedraw = true;
       }
       else if(m_zoom_widget.f2_press)
@@ -577,10 +577,10 @@ bool PlotEQCurve::on_mouse_motion_event(
         m_zoom_widget.f2_focus = true;
         m_zoom_widget.f1_focus = false;
         m_zoom_widget.center_focus = false;
-        recomputeMaxFreq_fromX2Pixel(event->x); 
+        recomputeMaxFreq_fromX2Pixel(event->x);
         m_fullRedraw = true;
       }
-      
+
       else if(event->x > m_zoom_widget.x1 + 10 &&
               event->x  < m_zoom_widget.x2 - 10 )
       {
@@ -621,7 +621,7 @@ bool PlotEQCurve::on_mouse_motion_event(
       redraw_zoom_widget();
       m_justRedraw = true;
     }
-    
+
     //Check if is over some control pointer
     bBandFocus = false;
     bool vFocus[m_TotalBandsCount];
@@ -636,7 +636,7 @@ bool PlotEQCurve::on_mouse_motion_event(
 	  x < width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X &&
 	  y > 0 &&
           y < height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y )
-      
+
       {
 	m_iBandSel = i;
 	bBandFocus = true;
@@ -658,7 +658,7 @@ bool PlotEQCurve::on_mouse_motion_event(
 	}
       }
     }
-    
+
     if(bBandFocus)
     {
       m_BandSelectedSignal.emit(m_iBandSel);
@@ -667,10 +667,10 @@ bool PlotEQCurve::on_mouse_motion_event(
     {
       m_BandUnselectedSignal.emit();
     }
-    
+
     m_BandRedraw = true; //Force a redraw of curve in next timer without computing bands
   }
-  
+
   if( event->x > CURVE_MARGIN + CURVE_TEXT_OFFSET_X &&
       event->x < width - CURVE_MARGIN  &&
       event->y > CURVE_MARGIN &&
@@ -695,7 +695,7 @@ bool PlotEQCurve::on_mouse_leave_widget(
   m_zoom_widget.f2_focus = false;
   redraw_zoom_widget();
   m_justRedraw = true;
-  
+
   if(!bMotionIsConnected)
   {
     redraw_cursor(event->x - CURVE_MARGIN - CURVE_TEXT_OFFSET_X, event->y - CURVE_MARGIN);
@@ -708,9 +708,9 @@ bool PlotEQCurve::on_mouse_leave_widget(
 
 //Timer callback for auto redraw and graph math
 bool PlotEQCurve::on_timeout_redraw()
-{  
+{
   bool bRedraw = false;
-  
+
   //Full redraw request
   if(m_fullRedraw)
   {
@@ -723,11 +723,11 @@ bool PlotEQCurve::on_timeout_redraw()
       m_Bands2Redraw[i] = true;
     }
     m_BandRedraw = true;
-    
+
     m_fullRedraw = false;
     bRedraw = true;
   }
-  
+
   //Redraw if curve changed
   if(m_BandRedraw)
   {
@@ -744,8 +744,8 @@ bool PlotEQCurve::on_timeout_redraw()
     m_BandRedraw = false;
     bRedraw = true;
   }
-  
-  
+
+
   if(bRedraw || m_justRedraw)
   {
     m_justRedraw = false;
@@ -755,7 +755,7 @@ bool PlotEQCurve::on_timeout_redraw()
       Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
       win->invalidate_rect(r, false);
     }
-  } 
+  }
   return true;
 }
 
@@ -766,108 +766,108 @@ bool PlotEQCurve::on_expose_event(GdkEve
   Glib::RefPtr<Gdk::Window> window = get_window();
   if(window)
   {
-  
+
     Gtk::Allocation allocation = get_allocation();
     width = allocation.get_width();
     height = allocation.get_height();
-  
+
     if( !(m_background_surface_ptr || m_fft_surface_ptr || m_zoom_surface_ptr || m_maincurve_surface_ptr || m_grid_surface_ptr  || m_xAxis_surface_ptr || m_yAxis_surface_ptr || m_cursor_surface_ptr))
-    {      
+    {
       m_background_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width, height);
       m_fft_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
       m_zoom_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, CURVE_TEXT_OFFSET_Y - ZOOM_WIDGET_BORDER_Y);
-      
+
       //Set initial x1 and x2
       redraw_zoom_widget();
-        
+
       m_maincurve_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
       for(int i = 0; i < m_TotalBandsCount; i++)
       {
         m_curve_surface_ptr[i] = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
       }
       m_grid_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
-      m_xAxis_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, CURVE_TEXT_OFFSET_Y);    
+      m_xAxis_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, CURVE_TEXT_OFFSET_Y);
       m_yAxis_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, CURVE_TEXT_OFFSET_X, height - CURVE_TEXT_OFFSET_Y);
       m_cursor_surface_ptr = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,  width - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X, height - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
       redraw_background_widget();
       resetCenterSpan();
       Glib::signal_timeout().connect( sigc::mem_fun(*this, &PlotEQCurve::on_timeout_redraw), AUTO_REFRESH_TIMEOUT_MS ); //Connectin timer here to avoid using plot with unitialized freq vector
     }
-    
+
     Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
 
     //Draw the background
     if(m_background_surface_ptr)
     {
-      cr->save();          
-      cr->set_source(m_background_surface_ptr, 0, 0);    
+      cr->save();
+      cr->set_source(m_background_surface_ptr, 0, 0);
       cr->paint();
       cr->restore();
     }
-    
-    //Draw zoom widget 
+
+    //Draw zoom widget
     if(m_zoom_surface_ptr)
     {
-      cr->save();          
-      cr->set_source(m_zoom_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, height -  CURVE_MARGIN - CURVE_TEXT_OFFSET_Y + ZOOM_WIDGET_BORDER_Y);    
+      cr->save();
+      cr->set_source(m_zoom_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, height -  CURVE_MARGIN - CURVE_TEXT_OFFSET_Y + ZOOM_WIDGET_BORDER_Y);
       cr->paint();
       cr->restore();
     }
-        
+
     //Draw FFT data
     if(m_FftActive && m_fft_surface_ptr)
-    {     
-      cr->save();          
-      cr->set_source(m_fft_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);    
+    {
+      cr->save();
+      cr->set_source(m_fft_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);
       cr->paint();
       cr->restore();
     }
-       
-    //Draw the grid 
+
+    //Draw the grid
     if(m_grid_surface_ptr)
     {
-      cr->save();         
-      cr->set_source(m_grid_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);    
+      cr->save();
+      cr->set_source(m_grid_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);
       cr->paint();
       cr->restore();
     }
-        
+
     //Db Scale Axis
     if(m_yAxis_surface_ptr)
-    {     
-      cr->save();          
-      cr->set_source(m_yAxis_surface_ptr, CURVE_MARGIN, 0);    
+    {
+      cr->save();
+      cr->set_source(m_yAxis_surface_ptr, CURVE_MARGIN, 0);
       cr->paint();
       cr->restore();
     }
-    
+
     //Hz scale Axis
     if(m_xAxis_surface_ptr)
-    {     
-      cr->save();          
-      cr->set_source(m_xAxis_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, height -  CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);    
+    {
+      cr->save();
+      cr->set_source(m_xAxis_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, height -  CURVE_MARGIN - CURVE_TEXT_OFFSET_Y);
       cr->paint();
       cr->restore();
     }
-    
+
     //Draw the cursor position
     if(m_cursor_surface_ptr)
     {
-      cr->save();          
-      cr->set_source(m_cursor_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);    
+      cr->save();
+      cr->set_source(m_cursor_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);
       cr->paint();
       cr->restore();
     }
 
     //Draw the curve
     if(m_maincurve_surface_ptr)
-    {     
-      cr->save();          
+    {
+      cr->save();
       cr->set_source(m_maincurve_surface_ptr, CURVE_MARGIN + CURVE_TEXT_OFFSET_X, CURVE_MARGIN);
       cr->paint();
       cr->restore();
     }
-    
+
     //draw de outer grind box
     cr->save();
     cr->set_source_rgb(0.3, 0.3, 0.3);
@@ -876,7 +876,7 @@ bool PlotEQCurve::on_expose_event(GdkEve
     cr->stroke();
     cr->restore();
   }
-  return true;    
+  return true;
 }
 
 void PlotEQCurve::glowBand(int band)
@@ -915,7 +915,7 @@ double PlotEQCurve::Pixels2dB(double pix
 
 double PlotEQCurve::Pixels2freq(double pixels)
 {
-  return m_minFreq*pow(10, ((pixels  /*- CURVE_MARGIN- CURVE_TEXT_OFFSET_X */)/((((double)width) - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X)/(log10(m_maxFreq/m_minFreq))))); 
+  return m_minFreq*pow(10, ((pixels  /*- CURVE_MARGIN- CURVE_TEXT_OFFSET_X */)/((((double)width) - 2*CURVE_MARGIN - CURVE_TEXT_OFFSET_X)/(log10(m_maxFreq/m_minFreq)))));
 }
 
 
@@ -952,10 +952,10 @@ void PlotEQCurve::CalcBand_DigitalFilter
   m_fil.fs = SampleRate;
   m_fil.InterK = 0.0f;
   m_fil.useInterpolation = 0.0f;
-  
+
   //Calc coefs
   calcCoefs(&m_fil, m_fil.gain, m_fil.freq, m_fil.q, m_fil.iType, m_fil.enable);
-  
+
   //Digital filter magnitude response
   double w, A, B, C, D, sinW, cosW;
   //Precalculables
@@ -963,11 +963,11 @@ void PlotEQCurve::CalcBand_DigitalFilter
   double BK = m_fil.b0 - m_fil.b2;
   double CK = 1 + m_fil.a2;
   double DK = 1 - m_fil.a2;
-  
-  
+
+
   for(int i=0; i<CURVE_NUM_OF_POINTS; i++)
   {
-    w=2*PI*f[i] / m_fil.fs; 
+    w=2*PI*f[i] / m_fil.fs;
     sinW = sin(w);
     cosW = cos(w);
     A = m_fil.b1 + AK*cosW;
@@ -976,7 +976,7 @@ void PlotEQCurve::CalcBand_DigitalFilter
     D = DK*sinW;
     band_y[bd_ix][i]=(double)20*log10(sqrt(pow(A*C + B*D, 2) + pow(B*C - A*D, 2))/(C*C + D*D));
   }
-  
+
   //Compute 3 and 4 order m_filters
   if(m_fil.filter_order)
   {
@@ -985,10 +985,10 @@ void PlotEQCurve::CalcBand_DigitalFilter
     double BK = m_fil.b1_0 - m_fil.b1_2;
     double CK = 1 + m_fil.a1_2;
     double DK = 1 - m_fil.a1_2;
-    
+
     for(int i=0; i<CURVE_NUM_OF_POINTS; i++)
     {
-      w=2*PI*f[i] / m_fil.fs; 
+      w=2*PI*f[i] / m_fil.fs;
       sinW = sin(w);
       cosW = cos(w);
       A = m_fil.b1_1 + AK*cosW;
@@ -1001,25 +1001,25 @@ void PlotEQCurve::CalcBand_DigitalFilter
 }
 
 void PlotEQCurve::setSampleRate(double samplerate)
-{ 
+{
   if(samplerate != SampleRate)
   {
     SampleRate = samplerate;
-    
+
     if( !(m_background_surface_ptr || m_fft_surface_ptr || m_zoom_surface_ptr || m_maincurve_surface_ptr || m_grid_surface_ptr  || m_xAxis_surface_ptr || m_yAxis_surface_ptr))
     {
       //Init FFT vectors using real sampleRate
       double fft_raw_freq;
       for(int i = 0; i <= (FFT_N/2); i++)
-      {     
+      {
         fft_raw_freq = (SampleRate * (double)i) /  ((double)(FFT_N));
-        xPixels_fft[i] = log10(fft_raw_freq/MIN_FREQ)/log10(MAX_FREQ/MIN_FREQ);        
+        xPixels_fft[i] = log10(fft_raw_freq/MIN_FREQ)/log10(MAX_FREQ/MIN_FREQ);
         fft_pink_noise[i] =  3.0*(log10(fft_raw_freq/20.0)/log10(2));
         fft_plot[i]= 0.0;
         fft_ant_data[i] = 0.0;
         //std::cout<<"freq["<<i<<"] = "<<  fft_raw_freq[i]<< "Pixels = "<< xPixels_fft[i] <<std::endl;
       }
-      
+
       //Redraw all by timer
       m_fullRedraw = true;
     }
@@ -1042,13 +1042,13 @@ void PlotEQCurve::setFftActive(bool acti
   m_bIsSpectrogram = isSpectrogram;
 
   //Clear plot screen
-  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);   
+  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);
   cr->save();
   cr->set_operator(Cairo::OPERATOR_CLEAR);
   cr->paint();
   cr->restore();
-  
-  
+
+
   m_justRedraw = true;
 }
 
@@ -1071,7 +1071,7 @@ void PlotEQCurve::setFftRange(double r)
 void PlotEQCurve::setPlotdBRange(double range)
 {
   m_dB_plot_range = 2.0*range;
-  
+
   //Redraw all by timer
   m_fullRedraw = true;
 }
@@ -1079,19 +1079,19 @@ void PlotEQCurve::setPlotdBRange(double 
 void PlotEQCurve::redraw_background_widget()
 {
   if(m_background_surface_ptr)
-  {  
+  {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_background_surface_ptr);
-  
+
     //Paint backgroud
     cr->save();
     cr->set_source_rgb(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B);
     cr->paint(); //Fill all with background color
     cr->restore();
-    
-    
+
+
     //Draw an interesting frame
-    cr->save();         
+    cr->save();
     double radius = height / 50.0;
     double degrees = M_PI / 180.0;
     cr->begin_new_sub_path();
@@ -1099,34 +1099,34 @@ void PlotEQCurve::redraw_background_widg
     cr->arc (width - CURVE_BORDER - radius, height - CURVE_BORDER - radius, radius, 0 * degrees, 90 * degrees);
     cr->arc (CURVE_BORDER + radius, height- CURVE_BORDER - radius, radius, 90 * degrees, 180 * degrees);
     cr->arc ( CURVE_BORDER + radius, CURVE_BORDER + radius, radius, 180 * degrees, 270 * degrees);
-    cr->close_path();  
-    Cairo::RefPtr<Cairo::LinearGradient> bkg_gradient_ptr = Cairo::LinearGradient::create(width/2, CURVE_BORDER, width/2, height - CURVE_BORDER);   
-    bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.1, 0.1, 0.1, 0.6 ); 
-    bkg_gradient_ptr->add_color_stop_rgba (0.5, 0.2, 0.3, 0.3, 0.3 ); 
-    bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.1, 0.1, 0.1, 0.6 ); 
+    cr->close_path();
+    Cairo::RefPtr<Cairo::LinearGradient> bkg_gradient_ptr = Cairo::LinearGradient::create(width/2, CURVE_BORDER, width/2, height - CURVE_BORDER);
+    bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.1, 0.1, 0.1, 0.6 );
+    bkg_gradient_ptr->add_color_stop_rgba (0.5, 0.2, 0.3, 0.3, 0.3 );
+    bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.1, 0.1, 0.1, 0.6 );
     cr->set_source(bkg_gradient_ptr);
     cr->fill_preserve();
     cr->set_line_width(1.0);
     cr->set_source_rgb(0.3, 0.3, 0.4);
-    cr->stroke(); 
+    cr->stroke();
     cr->restore();
   }
-  
+
 }
 
 void PlotEQCurve::redraw_zoom_widget()
-{  
+{
   if(m_zoom_surface_ptr)
-  {  
+  {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_zoom_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-  
+
     //Draw a box
     cr->save();
     cr->begin_new_sub_path();
@@ -1141,7 +1141,7 @@ void PlotEQCurve::redraw_zoom_widget()
     cr->set_source_rgba(0.6, 0.6, 0.6, 0.6);
     cr->stroke();
     cr->restore();
-    
+
     //Draw a freq axis
     cr->save();
     cr->set_source_rgb(0.6, 0.6, 0.6);
@@ -1149,21 +1149,21 @@ void PlotEQCurve::redraw_zoom_widget()
     Pango::FontDescription font_desc("sans 8px");
     pangoLayout->set_font_description(font_desc);
     pangoLayout->set_alignment(Pango::ALIGN_RIGHT);
-    
-    //Initalize the grid 
+
+    //Initalize the grid
     const double f_grid[4] = {20.0, 100.0, 1000.0, 10000.0};
     int gridPix[4];
     for(int i=0; i < 4; i++)
     {
       gridPix[i] = round(((double)m_zoom_surface_ptr->get_width())/(log10(MAX_FREQ/MIN_FREQ))*log10(f_grid[i]/MIN_FREQ)) +  CURVE_MARGIN + CURVE_TEXT_OFFSET_X;
     }
-    
+
     //Hz scale 20 Hz
     cr->move_to( gridPix[0] - 5  - CURVE_MARGIN - CURVE_TEXT_OFFSET_X, 0.5*m_zoom_surface_ptr->get_height() - 4);
     pangoLayout->set_text("20");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 100 Hz
     cr->move_to( gridPix[1] - 5  - CURVE_MARGIN - CURVE_TEXT_OFFSET_X, 0.5*m_zoom_surface_ptr->get_height() - 4);
     pangoLayout->set_text("100");
@@ -1174,16 +1174,16 @@ void PlotEQCurve::redraw_zoom_widget()
     cr->move_to( gridPix[2] - 5  - CURVE_MARGIN - CURVE_TEXT_OFFSET_X, 0.5*m_zoom_surface_ptr->get_height() - 4);
     pangoLayout->set_text("1k");
     pangoLayout->show_in_cairo_context(cr);
-    cr->stroke(); 
-    
+    cr->stroke();
+
     //Hz scale 10 kHz
     cr->move_to( gridPix[3] - 5  - CURVE_MARGIN - CURVE_TEXT_OFFSET_X, 0.5*m_zoom_surface_ptr->get_height() - 4);
     pangoLayout->set_text("10k");
     pangoLayout->show_in_cairo_context(cr);
-    cr->stroke(); 
+    cr->stroke();
     cr->restore();
-            
-    //Get pixel position in surface acording max freq span range (freq2pixels function is not valid here!) 
+
+    //Get pixel position in surface acording max freq span range (freq2pixels function is not valid here!)
     m_zoom_widget.x1 = round(((double)m_zoom_surface_ptr->get_width())/(log10(MAX_FREQ/MIN_FREQ))*log10(m_minFreq/MIN_FREQ)) + 3.5;
     m_zoom_widget.x2 = round(((double)m_zoom_surface_ptr->get_width())/(log10(MAX_FREQ/MIN_FREQ))*log10(m_maxFreq/MIN_FREQ)) - 3.5;
 
@@ -1193,48 +1193,48 @@ void PlotEQCurve::redraw_zoom_widget()
       cr->save();
       cr->rectangle(m_zoom_widget.x1 - 5, 2, 10, m_zoom_surface_ptr->get_height() - 4);
       cr->set_source_rgb(0,0.9,0.9);
-      cr->fill();  
+      cr->fill();
       cr->restore();
-      
+
       cr->save();
       cr->rectangle(m_zoom_widget.x2 - 5, 2, 10, m_zoom_surface_ptr->get_height() - 4);
       cr->set_source_rgb(0,0.9,0.9);
-      cr->fill();  
+      cr->fill();
       cr->restore();
     }
-    
-    
-    //Draw the button   
+
+
+    //Draw the button
     cr->save();
-    cr->begin_new_sub_path();    
+    cr->begin_new_sub_path();
     cr->arc( m_zoom_widget.x1, 6.5, 3, M_PI, -0.5*M_PI);
     cr->arc( m_zoom_widget.x2, 6.5, 3, -0.5*M_PI, 0);
     cr->arc( m_zoom_widget.x2,  m_zoom_surface_ptr->get_height() - 6.5, 3, 0.0,  0.5*M_PI);
     cr->arc( m_zoom_widget.x1, m_zoom_surface_ptr->get_height() - 6.5, 3, 0.5*M_PI, M_PI);
     cr->close_path();
-    
-    Cairo::RefPtr<Cairo::LinearGradient> bkg_gradient_ptr = Cairo::LinearGradient::create(0, 0, 0,  m_zoom_surface_ptr->get_height()); 
+
+    Cairo::RefPtr<Cairo::LinearGradient> bkg_gradient_ptr = Cairo::LinearGradient::create(0, 0, 0,  m_zoom_surface_ptr->get_height());
     if(m_zoom_widget.center_focus)
     {
-      bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.2, 0.3, 0.3, 0.7);  
+      bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.2, 0.3, 0.3, 0.7);
       bkg_gradient_ptr->add_color_stop_rgba (0.4, 0.2, 0.4, 0.5, 1 );
-      bkg_gradient_ptr->add_color_stop_rgba (0.6, 0.2, 0.4, 0.5, 1 );  
-      bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.2, 0.3, 0.3, 0.7 );  
+      bkg_gradient_ptr->add_color_stop_rgba (0.6, 0.2, 0.4, 0.5, 1 );
+      bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.2, 0.3, 0.3, 0.7 );
     }
     else
     {
-      bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.2, 0.2, 0.2, 0.7 );  
+      bkg_gradient_ptr->add_color_stop_rgba (0.0, 0.2, 0.2, 0.2, 0.7 );
       bkg_gradient_ptr->add_color_stop_rgba (0.4, 0.3, 0.3, 0.3, 1 );
-      bkg_gradient_ptr->add_color_stop_rgba (0.6, 0.3, 0.3, 0.3, 1 );  
-      bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.2, 0.2, 0.2, 0.7 );  
+      bkg_gradient_ptr->add_color_stop_rgba (0.6, 0.3, 0.3, 0.3, 1 );
+      bkg_gradient_ptr->add_color_stop_rgba (1.0, 0.2, 0.2, 0.2, 0.7 );
     }
-    cr->set_source(bkg_gradient_ptr);                       
+    cr->set_source(bkg_gradient_ptr);
     cr->fill_preserve();
     cr->set_line_width(1);
     cr->set_source_rgba(1,1,1, 0.7);
     cr->stroke();
     cr->restore();
-    
+
     //Draw text on button
     cr->save();
     cr->set_source_rgb(0.6, 0.6, 0.6);
@@ -1253,7 +1253,7 @@ void PlotEQCurve::redraw_zoom_widget()
         ss1<<divider;
       }
     }
-    
+
     cr->move_to( m_zoom_widget.x1 + 5,  m_zoom_surface_ptr->get_height()/2 - 4);
     pangoLayout->set_text( ss1.str() );
     pangoLayout->show_in_cairo_context(cr);
@@ -1261,7 +1261,7 @@ void PlotEQCurve::redraw_zoom_widget()
     pangoLayout->set_text("~Zoom~");
     pangoLayout->show_in_cairo_context(cr);
     cr->move_to( m_zoom_widget.x2 - 25,  m_zoom_surface_ptr->get_height()/2 - 4);
-    
+
     std::stringstream ss2;
     if(m_maxFreq<1000)
     {
@@ -1276,12 +1276,12 @@ void PlotEQCurve::redraw_zoom_widget()
         ss2<<divider;
       }
     }
-    
+
     pangoLayout->set_text( ss2.str() );
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
     cr->restore();
-    
+
     //Update coords including global offsets
     m_zoom_widget.x1 += CURVE_MARGIN + CURVE_TEXT_OFFSET_X;
     m_zoom_widget.x2 += CURVE_MARGIN + CURVE_TEXT_OFFSET_X;
@@ -1289,21 +1289,21 @@ void PlotEQCurve::redraw_zoom_widget()
 }
 
 void PlotEQCurve::redraw_curve_widgets(int band)
-{ 
+{
   if(m_curve_surface_ptr[band])
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_curve_surface_ptr[band]);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-  
+
     //Draw curve area in band color
     cr->save();
-    double Y_fil0, Y_fil1;    
+    double Y_fil0, Y_fil1;
     switch(m_filters[band]->fType)
     {
       case PEAK:
@@ -1312,7 +1312,7 @@ void PlotEQCurve::redraw_curve_widgets(i
 	Y_fil0 = dB2Pixels( m_filters[band]->Gain);
 	Y_fil1 = dB2Pixels((-1.0)* m_filters[band]->Gain);
 	break;
-	
+
       case NOTCH:
 	Y_fil0 = (double)m_curve_surface_ptr[band]->get_height();
 	Y_fil1 = 0;
@@ -1322,11 +1322,11 @@ void PlotEQCurve::redraw_curve_widgets(i
 	Y_fil0 = 0.75*(double)m_curve_surface_ptr[band]->get_height();
 	Y_fil1 = 0.25*(double)m_curve_surface_ptr[band]->get_height();
     }
-    
-    Cairo::RefPtr<Cairo::LinearGradient> bd_gradient_ptr = Cairo::LinearGradient::create(0, Y_fil0, 0, Y_fil1);  
+
+    Cairo::RefPtr<Cairo::LinearGradient> bd_gradient_ptr = Cairo::LinearGradient::create(0, Y_fil0, 0, Y_fil1);
     if(m_filters[band]->bIsOn and !m_Bypass) //If band is enabled and not bypass
     {
-      Gdk::Color color(bandColorLUT[band]); 
+      Gdk::Color color(bandColorLUT[band]);
       bd_gradient_ptr->add_color_stop_rgba(0, color.get_red_p(), color.get_green_p(), color.get_blue_p(), 0.3);
       bd_gradient_ptr->add_color_stop_rgba(0.5, color.get_red_p(), color.get_green_p(), color.get_blue_p(), 0.01);
       bd_gradient_ptr->add_color_stop_rgba(1, color.get_red_p(), color.get_green_p(), color.get_blue_p(), 0.3);
@@ -1356,8 +1356,8 @@ void PlotEQCurve::redraw_main_curve()
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_maincurve_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
@@ -1367,19 +1367,19 @@ void PlotEQCurve::redraw_main_curve()
     {
       //Draw the curve color area for each band
       if(m_curve_surface_ptr[i])
-      {     
-        cr->save();          
+      {
+        cr->save();
         cr->set_source(m_curve_surface_ptr[i], 0, 0);
         cr->paint();
         cr->restore();
       }
     }
-    
+
     if (!m_Bypass)
     {
       //Draw the main curve
       cr->save();
-      
+
       cr->set_line_width(1);
       for(int j = 0; j < m_NumChannels; j++)
       {
@@ -1395,20 +1395,20 @@ void PlotEQCurve::redraw_main_curve()
         cr->move_to(xPixels[0], dB2Pixels(main_y[j][0]) + 0.5);
         for (int i = 1; i < CURVE_NUM_OF_POINTS; i++)
         {
-          cr->line_to(xPixels[i], dB2Pixels(main_y[j][i]) + 0.5); 
+          cr->line_to(xPixels[i], dB2Pixels(main_y[j][i]) + 0.5);
         }
         cr->stroke();
       }
       cr->restore();
-      
+
       //Draw curve control ball
-      cr->save();    
+      cr->save();
       double ball_x, ball_y;
       Cairo::RefPtr< Cairo::RadialGradient > ball_gradient_ptr;
       for(int i = 0; i < m_TotalBandsCount; i++) //for each band
       {
           ball_x = (double)freq2Pixels(m_filters[i]->Freq);
-          if( m_filters[i]->fType == PEAK || 
+          if( m_filters[i]->fType == PEAK ||
               m_filters[i]->fType == LOW_SHELF ||
               m_filters[i]->fType == HIGH_SHELF )
           {
@@ -1419,26 +1419,26 @@ void PlotEQCurve::redraw_main_curve()
             ball_y =  (double)dB2Pixels(0.0);
             m_filters[i]->Gain = 0.0;
           }
-          
+
           Gdk::Color color(bandColorLUT[i]);
           ball_gradient_ptr = Cairo::RadialGradient::create( ball_x - 2, ball_y - 2, 0,  ball_x - 2, ball_y - 2, 8);
           ball_gradient_ptr->add_color_stop_rgba (0.0, 1.0, 1.0, 1.0, 0.7);
-          ball_gradient_ptr->add_color_stop_rgba (1.0, 0.0, 0.0, 0.0, 0.0);           
+          ball_gradient_ptr->add_color_stop_rgba (1.0, 0.0, 0.0, 0.0, 0.0);
           cr->arc(ball_x, ball_y, 5.0, 0.0, 6.28318530717958647693);
           cr->set_source_rgb(color.get_red_p(), color.get_green_p(), color.get_blue_p());
           cr->fill_preserve();
-          cr->set_source(ball_gradient_ptr);    
+          cr->set_source(ball_gradient_ptr);
           cr->fill_preserve();
           cr->set_line_width(1);
           cr->set_source_rgb(0.1,0.1,0.1);
           cr->stroke();
       }
-      
+
       //Draw Focused band
       if(bMotionIsConnected || bBandFocus)
       {
           ball_x = (double)freq2Pixels(m_filters[m_iBandSel]->Freq);
-          if( m_filters[m_iBandSel]->fType == PEAK || 
+          if( m_filters[m_iBandSel]->fType == PEAK ||
               m_filters[m_iBandSel]->fType == LOW_SHELF ||
               m_filters[m_iBandSel]->fType == HIGH_SHELF )
           {
@@ -1449,7 +1449,7 @@ void PlotEQCurve::redraw_main_curve()
             ball_y =  (double)dB2Pixels(0.0);
             m_filters[m_iBandSel]->Gain = 0.0;
           }
-            
+
           Gdk::Color color("#00FFFF");
           cr->set_line_width(1);
           cr->set_source_rgb(color.get_red_p(), color.get_green_p(), color.get_blue_p());
@@ -1457,7 +1457,7 @@ void PlotEQCurve::redraw_main_curve()
           cr->stroke();
       }
       cr->restore();
-      
+
     }// end Bypass check
   }
 }
@@ -1469,14 +1469,14 @@ void PlotEQCurve::redraw_grid_widget()
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_grid_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-    
-    cr->save();  
+
+    cr->save();
     cr->set_source_rgb(0.3, 0.3, 0.3);
     cr->set_line_width(1);
     for(int i = 0; i < GRID_VERTICAL_LINES; i++)
@@ -1485,7 +1485,7 @@ void PlotEQCurve::redraw_grid_widget()
       cr->line_to(xPixels_Grid[i] + 0.5,  m_grid_surface_ptr->get_height());
       cr->stroke();
     }
-    
+
     for(int i = -m_dB_plot_range/2; i <= m_dB_plot_range/2; i+=(int)(m_dB_plot_range/10.0))
     {
       cr->move_to(0, dB2Pixels(i) + 0.5);
@@ -1502,13 +1502,13 @@ void PlotEQCurve::redraw_xAxis_widget()
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_xAxis_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-    
+
     //Draw text with pango to grid
     cr->save();
     cr->set_source_rgb(0.6, 0.6, 0.6);
@@ -1516,54 +1516,54 @@ void PlotEQCurve::redraw_xAxis_widget()
     Pango::FontDescription font_desc("sans 9px");
     pangoLayout->set_font_description(font_desc);
     pangoLayout->set_alignment(Pango::ALIGN_RIGHT);
-    
+
     cr->move_to( xPixels_Grid[0] - 5, 3.5);
     pangoLayout->set_text("20");
     pangoLayout->show_in_cairo_context(cr);
-    cr->stroke(); 
-    
+    cr->stroke();
+
     //Hz scale 50 Hz
     cr->move_to( xPixels_Grid[3] - 5, 3.5);
     pangoLayout->set_text("50");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 100 Hz
     cr->move_to( xPixels_Grid[8] - 10, 3.5);
     pangoLayout->set_text("100");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 200 Hz
     cr->move_to( xPixels_Grid[9] - 10, 3.5);
     pangoLayout->set_text("200");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 500 Hz
     cr->move_to( xPixels_Grid[12] - 10, 3.5);
     pangoLayout->set_text("500");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 1 KHz
     cr->move_to( xPixels_Grid[17] - 5, 3.5);
     pangoLayout->set_text("1k");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 2 KHz
     cr->move_to( xPixels_Grid[18] - 5, 3.5);
     pangoLayout->set_text("2k");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 5 KHz
     cr->move_to( xPixels_Grid[21] - 5, 3.5);
     pangoLayout->set_text("5k");
     pangoLayout->show_in_cairo_context(cr);
     cr->stroke();
-    
+
     //Hz scale 10 KHz
     cr->move_to( xPixels_Grid[26] - 5, 3.5);
     pangoLayout->set_text("10k");
@@ -1585,13 +1585,13 @@ void PlotEQCurve::redraw_yAxis_widget()
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_yAxis_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-    
+
     //Draw text with pango to grid
     cr->save();
     cr->set_source_rgb(0.6, 0.6, 0.6);
@@ -1607,38 +1607,38 @@ void PlotEQCurve::redraw_yAxis_widget()
       cr->move_to( 0, dB2Pixels(i) - 3.5 + CURVE_MARGIN);
       pangoLayout->set_text(ss.str());
       pangoLayout->show_in_cairo_context(cr);
-      cr->stroke();  
+      cr->stroke();
     }
-    
+
   }
 }
 
 void PlotEQCurve::redraw_cursor(double x, double y)
-{   
+{
   if(m_cursor_surface_ptr)
   {
     //Create cairo context using the buffer surface
     Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_cursor_surface_ptr);
-    
-    //Clear current context  
+
+    //Clear current context
     cr->save();
     cr->set_operator(Cairo::OPERATOR_CLEAR);
     cr->paint();
     cr->restore();
-            
+
     //Draw text with pango to grid
     if( x > 0 &&
         x < m_cursor_surface_ptr->get_width()  &&
         y > 0 &&
         y < m_cursor_surface_ptr->get_height() )
     {
-      
+
       if(bBandFocus)
       {
 	x = freq2Pixels(m_filters[m_iBandSel]->Freq);
 	y = dB2Pixels( m_filters[m_iBandSel]->Gain );
       }
-      
+
       cr->save();
       cr->set_source_rgba(0.9, 0.9, 0.9, 1.0);
       cr->set_line_width(1);
@@ -1651,13 +1651,13 @@ void PlotEQCurve::redraw_cursor(double x
       cr->move_to(x + 0.5*BALL_DETECTION_PIXELS, y + 0.5);
       cr->line_to(m_cursor_surface_ptr->get_width(), y + 0.5);
       cr->stroke();
-       
+
       Glib::RefPtr<Pango::Layout> pangoLayout = Pango::Layout::create(cr);
       Pango::FontDescription font_desc("sans 9px");
-      pangoLayout->set_font_description(font_desc);     
+      pangoLayout->set_font_description(font_desc);
       std::stringstream ss;
-      double freq = Pixels2freq(x); 
-      double gain = Pixels2dB(y);   
+      double freq = Pixels2freq(x);
+      double gain = Pixels2dB(y);
       int precision = 1;
       if(freq < 100 || (freq >= 1e3 && freq < 1e4)) precision = 2;
       if(freq >= 1000)
@@ -1670,11 +1670,11 @@ void PlotEQCurve::redraw_cursor(double x
       }
       if( x > (m_cursor_surface_ptr->get_width() - 45))
       {
-	cr->move_to( x - 45, m_cursor_surface_ptr->get_height() - 10); 
+	cr->move_to( x - 45, m_cursor_surface_ptr->get_height() - 10);
       }
       else
       {
-	cr->move_to( x + 2, m_cursor_surface_ptr->get_height() - 10); 
+	cr->move_to( x + 2, m_cursor_surface_ptr->get_height() - 10);
       }
       pangoLayout->set_text(ss.str());
       pangoLayout->show_in_cairo_context(cr);
@@ -1683,16 +1683,16 @@ void PlotEQCurve::redraw_cursor(double x
       ss<< std::setprecision(2) << std::fixed << gain  << " dB" ;
       if(gain > 0)
       {
-	cr->move_to( 2, y +1 ); 
+	cr->move_to( 2, y +1 );
       }
       else
       {
-	cr->move_to( 2, y - 10); 
+	cr->move_to( 2, y - 10);
       }
       pangoLayout->set_text(ss.str());
       pangoLayout->show_in_cairo_context(cr);
-      cr->stroke();  
-      cr->restore(); 
+      cr->stroke();
+      cr->restore();
     }
   }
 }
@@ -1702,17 +1702,17 @@ void PlotEQCurve::redraw_fft_widget()
 {
   const double m = (-1.0)/(fft_range);
   float val;
-   
-  Cairo::RefPtr<Cairo::LinearGradient> fft_gradient_ptr = Cairo::LinearGradient::create(0, 0, 1.0, 0);    
+
+  Cairo::RefPtr<Cairo::LinearGradient> fft_gradient_ptr = Cairo::LinearGradient::create(0, 0, 1.0, 0);
 
   double binMax = 1e6;
   double binX[(FFT_N/2) + 1];
   double binY[(FFT_N/2) + 1];
-  int binCount = 0; 
+  int binCount = 0;
   fft_plot[0] = 1e6; //I don't care about DC
-  
-  for (int i = 1; i <= (FFT_N/2); i++) 
-  {     
+
+  for (int i = 1; i <= (FFT_N/2); i++)
+  {
     if(m_bIsSpectrogram)
     {
       val = sqrt((float)fft_raw_data[i]);
@@ -1723,40 +1723,40 @@ void PlotEQCurve::redraw_fft_widget()
       val = sqrt((float)fft_ant_data[i]);
     }
     fft_plot[i] = m*(20.0f*fastLog10((int*)(&val), fft_log_lut) + fft_gain + fft_pink_noise[i]);
-    
+
     if(xPixels_fft_bins[i] == xPixels_fft_bins[i-1])
     {
       //Inside bin code
       binMax = fft_plot[i] < binMax ? fft_plot[i] : binMax; //Yes it is reversed because binMax is really a pixel min
     }
     else
-    { 
+    {
       binX[binCount] = xPixels_fft_bins[i-1];
       binY[binCount] = binMax;
-      fft_gradient_ptr->add_color_stop_rgba (binX[binCount], 0.5, -1.0*binMax + 1.0,  1.0,  -1.0*binMax + 1.0); 
+      fft_gradient_ptr->add_color_stop_rgba (binX[binCount], 0.5, -1.0*binMax + 1.0,  1.0,  -1.0*binMax + 1.0);
       binCount++;
       binMax =  fft_plot[i];
-      
+
     }
-  } 
-  
+  }
+
   //Create cairo context using the buffer surface
-  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);  
-  
+  Cairo::RefPtr<Cairo::Context> cr = Cairo::Context::create(m_fft_surface_ptr);
+
   //Store a copy of the image
   Cairo::RefPtr<Cairo::ImageSurface> img_ant = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,  m_fft_surface_ptr->get_width(),  m_fft_surface_ptr->get_height());
-  Cairo::RefPtr<Cairo::Context> cr_ant = Cairo::Context::create(img_ant);  
+  Cairo::RefPtr<Cairo::Context> cr_ant = Cairo::Context::create(img_ant);
   cr_ant->save();
   cr_ant->set_source (m_fft_surface_ptr, 0, 0);
   cr_ant->paint();
   cr_ant->restore();
-  
-  //Clear current context  
+
+  //Clear current context
   cr->save();
   cr->set_operator(Cairo::OPERATOR_CLEAR);
   cr->paint();
   cr->restore();
-  
+
   if(m_bIsSpectrogram)
   {
     //Draw the FFT spectrogram
@@ -1765,29 +1765,29 @@ void PlotEQCurve::redraw_fft_widget()
     cr->rectangle(0, SPECTROGRAM_LINE_THICKNESS, m_fft_surface_ptr->get_width(), m_fft_surface_ptr->get_height() - SPECTROGRAM_LINE_THICKNESS);
     cr->fill();
     cr->restore();
-    
-    cr->save();   
+
+    cr->save();
     cr->translate(freq2Pixels(MIN_FREQ), 0);
     cr->scale(freq2Pixels(MAX_FREQ) - freq2Pixels(MIN_FREQ),  m_fft_surface_ptr->get_height());
     cr->rectangle(0, 0, 1.0, SPECTROGRAM_LINE_THICKNESS/( m_fft_surface_ptr->get_height()));
     cr->set_source(fft_gradient_ptr);
     cr->fill();
     cr->restore();
-  }   
+  }
   else
   {
-    
+
     //Draw the FFT plot Curve
-    cr->save();   
+    cr->save();
     cr->translate(freq2Pixels(MIN_FREQ), 0);
     cr->scale(freq2Pixels(MAX_FREQ) - freq2Pixels(MIN_FREQ),  m_fft_surface_ptr->get_height());
-    
+
     cr->move_to(0.0, 1.0);
-            
-    //Curve smooth version 
+
+    //Curve smooth version
     double Ax, Ay, Bx, By;
     for(int i = 1; i<binCount; i++)
-    {          
+    {
       if(i == 1)
       {
         //Limit left A = Pk-1
@@ -1796,11 +1796,11 @@ void PlotEQCurve::redraw_fft_widget()
       }
       else
       {
-        //Calc ctl point A       
+        //Calc ctl point A
         Ax = binX[i - 1] + SPLINE_TENSION * ( binX[i] -  binX[i - 2] );
-        Ay = binY[i - 1] + SPLINE_TENSION * ( binY[i] -  binY[i - 2] );          
+        Ay = binY[i - 1] + SPLINE_TENSION * ( binY[i] -  binY[i - 2] );
       }
-      
+
       if(i == (binCount - 1))
       {
         //Limit rigth A = Pk
@@ -1811,19 +1811,19 @@ void PlotEQCurve::redraw_fft_widget()
       {
         //Calc ctl point A
         Bx = binX[i] - SPLINE_TENSION * ( binX[i + 1] -  binX[i - 1] );
-        By = binY[i] - SPLINE_TENSION * ( binY[i + 1] -  binY[i - 1] );          
+        By = binY[i] - SPLINE_TENSION * ( binY[i + 1] -  binY[i - 1] );
       }
       cr->curve_to(Ax, Ay, Bx, By, binX[i], binY[i]);
-    }      
+    }
 
     cr->line_to(1.0, 1.0);
-    cr->line_to(0.0, 1.0);    
+    cr->line_to(0.0, 1.0);
     cr->set_source_rgba(0.21, 0.15, 0.78, 0.7);
     cr->fill_preserve();
     cr->set_source(fft_gradient_ptr);
-    cr->fill();  
+    cr->fill();
     cr->restore();
-  } 
+  }
 }
 
 void PlotEQCurve::setStereoState(int band, PlotEQCurve::MSState state)
@@ -1834,4 +1834,3 @@ void PlotEQCurve::setStereoState(int ban
     cueBandRedraws(band);
   }
 }
-
