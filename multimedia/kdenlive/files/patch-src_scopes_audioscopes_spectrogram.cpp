--- src/scopes/audioscopes/spectrogram.cpp.orig	2016-10-30 07:58:30 UTC
+++ src/scopes/audioscopes/spectrogram.cpp
@@ -241,7 +241,7 @@ QImage Spectrogram::renderHUD(uint)
                 x = leftDist + (m_innerScopeRect.width()-1) * ((float)hz)/m_freqMax;
 
                 // Hide text if it would overlap with the text drawn at the mouse position
-                hideText = m_aTrackMouse->isChecked() && m_mouseWithinWidget && abs(x-(leftDist + mouseX + 20)) < (int) minDistX + 16
+                hideText = m_aTrackMouse->isChecked() && m_mouseWithinWidget && abs(x-((int)leftDist + mouseX + 20)) < (int) minDistX + 16
                         && mouseX < m_innerScopeRect.width() && mouseX >= 0;
 
                 if (x <= rightBorder) {
@@ -269,7 +269,7 @@ QImage Spectrogram::renderHUD(uint)
             }
             // Draw the line at the very right (maximum frequency)
             x = leftDist + m_innerScopeRect.width()-1;
-            hideText = m_aTrackMouse->isChecked() && m_mouseWithinWidget && abs(x-(leftDist + mouseX + 30)) < (int) minDistX
+            hideText = m_aTrackMouse->isChecked() && m_mouseWithinWidget && abs(x-((int)leftDist + mouseX + 30)) < (int) minDistX
                     && mouseX < m_innerScopeRect.width() && mouseX >= 0;
             davinci.drawLine(x, topDist, x, topDist + m_innerScopeRect.height()+6);
             if (!hideText) {
