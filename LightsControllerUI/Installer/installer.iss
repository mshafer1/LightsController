; -- 64Bit.iss --
; Demonstrates installation of a program built for the x64 (a.k.a. AMD64)
; architecture.
; To successfully run this installation and the program it installs,
; you must have a "x64" edition of Windows.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]
;SourceDir=c:\files
AppName=Lights Controller
AppVersion=1.0.0
DefaultDirName={pf}\Lights Controller
DefaultGroupName=Lights Controller
UninstallDisplayIcon={app}\LightsController.exe
Compression=lzma2
SolidCompression=yes
OutputBaseFilename=Setup
OutputDir=..\LightsController\Properties\LightsControllerInstaller\
; "ArchitecturesAllowed=x64" specifies that Setup cannot run on
; anything but x64.
ArchitecturesAllowed=x64
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
ArchitecturesInstallIn64BitMode=x64
LicenseFile="..\LightsController\References\License.rtf"

[Files]
Source: "..\LightsController\bin\Release\LightsController.exe"; DestDir: "{app}"; DestName: "LightsController.exe"
; Source: "MyProg.chm"; DestDir: "{app}"
Source: "..\LightsController\References\License.rtf"; DestDir: "{app}"; DestName: "License.rtf"
Source: "..\LightsController\References\arduino.inf"; DestDir: {app}\driver; DestName: "arduino.inf"
Source: "..\LightsController\References\arduino.cat"; DestDir: {app}\driver; DestName: "arduino.cat"
Source: "..\LightsController\References\arduino_driver.cer"; DestDir: {app}\driver; DestName: "arduino_driver.cer"
Source: "dpinst-amd64.exe"; DestDir: {app}\driver; DestName: "dpinst-amd64.exe"

[Icons]
Name: "{group}\LightsController"; Filename: "{app}\LightsController.exe"

[Run]
Filename: "{cmd}"; Parameters: "/c ""certutil -addstore ""TrustedPublisher"" ""{app}\driver\arduino_driver.cer""  "
Filename: {app}\driver\dpinst-amd64.exe; WorkingDir: {app}\driver; Flags: 64bit;