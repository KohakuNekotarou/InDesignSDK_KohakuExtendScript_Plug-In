# InDesign Plug-In
## Win 64bit

I'll add various things to ExtendScript.

### // extendScript for JavaScript

// Match scroll zoom all layout.
app.matchScrollZoomAllLayout();

 // Set
app.activeDocument.layoutWindows[0].accessContentLocationAtFrameOriginX = 0;

 // Get
y = app.activeDocument.layoutWindows[0].accessContentLocationAtFrameOriginY;
