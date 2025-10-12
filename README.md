# InDesign Plug-In
### Win 64bit

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

## extendScript for JavaScript
```
// Match scroll zoom all layout.
app.matchScrollZoomAllLayout();

// Set Top-left coordinates of the layout.
app.activeDocument.layoutWindows[0].accessContentLocationAtFrameOriginX = 0;

// Get Top-left coordinates of the layout.
y = app.activeDocument.layoutWindows[0].accessContentLocationAtFrameOriginY;

// Split / Unsplit layout.
if(app.activeWindow.constructor.name == "LayoutWindow"){
    app.activeWindow.toggleSplitLayout();
}
```
