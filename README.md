# InDesign Plug-In
### Win 64bit

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

On Mac, you cannot use downloaded plug-ins directly.
https://helpx.adobe.com/jp/indesign/kb/indesign-and-macos-catalina.html
Refer to the above and use Terminal to
sudo xattr -r -d com.apple.quarantine /Applications/Adobe\ Indesign\ 2025/Plug-ins/KohakuExtendScript.InDesignPlugin
Please execute.

## extendScript for JavaScript
```
// Auto match scroll zoom all layout. 
app.autoMatchScrollZoomAllLayout = true; // Set
flg = app.autoMatchScrollZoomAllLayout; // get

// Match scroll zoom all layout.
app.matchScrollZoomAllLayout();

// Query Nth layout. 
app.activeDocument.queryNthLayout(0);

// Auto match scroll zoom all layout.
app.activeDocument.queryNthLayout(0).autoMatchScrollZoomAllLayout = true; // Set

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
