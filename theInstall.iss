; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "StreetsofTrogue"
#define MyAppVersion "1.5"
#define MyAppPublisher "BitCrazy"
#define MyAppURL "https://www.example.com/"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{3277F4CF-3C3B-4DA4-B0AC-C63A17077A4E}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only).
;PrivilegesRequired=lowest
OutputDir=C:\Users\ethan\Downloads
OutputBaseFilename=StreetsofTrogueInstaller
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Files]
Source: "C:\Users\ethan\Downloads\streetsoftrogue-main\streetsoftrogue-main\elevator.bat"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\ethan\Downloads\streetsoftrogue-main\streetsoftrogue-main\servicer.bat"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\ethan\Downloads\streetsoftrogue-main\streetsoftrogue-main\crazy.wav"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\ethan\Downloads\streetsoftrogue-main\streetsoftrogue-main\newMain.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\ethan\Downloads\streetsoftrogue-main\streetsoftrogue-main\disable.bat"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Run]
Filename: "{app}\elevator.bat"; Description: "Launch Setter"; Flags: nowait postinstall

