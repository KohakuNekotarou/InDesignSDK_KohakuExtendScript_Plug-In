# InDesign Plug-In

**I'll add various things to ExtendScript.**
<br>**Let's learn the InDesign SDK together.**

On Mac, you cannot use downloaded plug-ins directly.<br>
https://helpx.adobe.com/jp/indesign/kb/indesign-and-macos-catalina.html<br>
Refer to the above and use Terminal to<br>
sudo xattr -r -d com.apple.quarantine /Applications/Adobe\ Indesign\ 2025/Plug-ins/KohakuExtendScript.InDesignPlugin<br>
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

## Build Method
**Mac Edition**

1. Download the SDK<br>
https://developer.adobe.com/indesign/

2. Downloading the programming software, Xcode<br>
SDK/docs/html/index.html<br>
Download the Xcode version compatible with your InDesign version as a reference.<br>
https://developer.apple.com/download/all/?q=xcode

3. Create a PlugIn template<br>
Search for and install Java to use dolly.jar<br>
SDK/devtools/dolly/dolly.jar<br>
use<br>
![DollyXs1](https://github.com/user-attachments/assets/1f2e1f85-45e5-4b55-b471-66a96a79d35e)<br>
![DollyXs2](https://github.com/user-attachments/assets/5feaf568-000f-4ce8-bc11-bed5820689ae)<br>
![DollyXs3](https://github.com/user-attachments/assets/92de3c44-2a62-4181-91a9-15d06b6388e3)<br>
![DollyXs4](https://github.com/user-attachments/assets/46114f15-ab2c-4f05-bd17-4a54686b5040)<br>
The project directory is located at<br>
SDK/build/mac/prj<br>
Set up and create as follows

4. Download the source from Git<br>
![gitDownload](https://github.com/user-attachments/assets/d096440d-13a1-4106-98a9-7f2469086d09)<br>
Place the source files in the<br>
SDK/source/sdksamples/KohakuExtendScript<br>
folder

5. Build in Xcode<br>
Load KohakuExtendScript project in Xcode<br>

Add only source files not displayed in the project<br>
It is important to add only source files not displayed in the project<br>

Set the build configuration to Release<br>
Product > Build

6. Load PlugIn
SDK/build/mac/release_cocoa64/KohakuExtendScript.InDesignPlugin<br>
Place it in the plugin folder
