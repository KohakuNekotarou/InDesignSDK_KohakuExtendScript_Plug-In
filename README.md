# InDesign Plug-In
### Win 64bit

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

## extendScript for JavaScript
```
// Auto match scroll zoom all layout. 
app.autoMatchScrollZoomAllLayout = true; // Set
flg = app.autoMatchScrollZoomAllLayout; // get

// Auto match scroll zoom all layout.
app.activeDocument.queryNthLayout(0).autoMatchScrollZoomAllLayout = true; // Set

// Match scroll zoom all layout.
app.matchScrollZoomAllLayout();

// Query Nth layout. 
app.activeDocument.queryNthLayout(0);

// Access content location at frame origin.
app.activeDocument.queryNthLayout(0).accessContentLocationAtFrameOriginX = 0; // Set
y = app.activeDocument.queryNthLayout(0).accessContentLocationAtFrameOriginY;  // Get

// Is split layout view shown.
result = app.activeDocument.queryNthLayout(0).isSplitLayoutViewShown();

// Access content location at frame origin.
result = app.activeDocument.queryNthLayout(0).isSplitLayoutViewShown();
if(result){
    app.activeDocument.queryNthLayout(0).splitLayoutView.accessContentLocationAtFrameOriginX = 0; // Set
    y = app.activeDocument.queryNthLayout(0).splitLayoutView.accessContentLocationAtFrameOriginY; // get
}

// Split / Unsplit layout.
    app.activeDocument.queryNthLayout(0).toggleSplitLayout();
```
