# LinVstManager
![linvstmanager](https://github.com/Goli4thus/linvstmanager/blob/master/src/resources/linvstmanager_72.png)

LinVstManager is a companion application that allows managing VSTs
in conjunction with various VST bridges created by [osxmidi](https://github.com/osxmidi/LinVst).

## Motivation
[LinVst](https://github.com/osxmidi/LinVst) (for example) requires something like the following setup:

1. Install the bridge
2. Install your desired VST in a wine prefix
3. Copy the _linvst.so_ file template to the VST's location and rename it to _{NameOfVST}.so_
4. Optinally make a softlink to another folder (let's call it a _link folder_), so you can point your DAW to one central location for loading bridged VSTs.
5. If at some point there is an update of _LinVst_ you want to give a try, you gotta:
    1. Install the new bridge version
    2. Replace the _*.so_ files alongside all bridged VSTs (the ones bridged with _LinVst_)

Now chances are that you have bridged more than one VST and possibly even with different bridges depending on if they are VST2 or VST3 and if they need to be able to communicate with each other or not.

Handling this all manually can take time and be error prone (i.e. version conflicts when starting up your DAW and some VSTs not loading).

Some time ago this already caused me to create [linvstmanage-cli](https://github.com/Goli4thus/linvstmanage); a config file and cli-based UI that together allowed to at least manage VSTs bridge with one bridge type (initially there was only _LinVst_, not _-X_, _3_, or _3-X_).
It was sufficient if all you needed was one bridge type and maybe had something like 30 VSTs bridged.

After that, the cli-based UI quickly becomes a bit of a chore to use.
Furthermore there were requests for a _scan_ feature (like most DAWs have), which allows to scan for VSTs instead of locating each one manually.

All this and the increase of bridge types kinda made [linvstmanage-cli](https://github.com/Goli4thus/linvstmanage) somewhat lacking.

That's why _LinVstManager_ was created:
![MainWindow](https://github.com/Goli4thus/images/blob/master/images_linvstmanager/Mainwindow.png)


## Features
- currently supported bridges:
    - [LinVst](https://github.com/osxmidi/LinVst)
    - [LinVst-X](https://github.com/osxmidi/LinVst-X)
    - [LinVst3](https://github.com/osxmidi/LinVst3)
    - [LinVst3-X](https://github.com/osxmidi/LinVst3-X)
- Batch adding of VSTs:
- Scanning for VSTs (verification of _*.dll_ files actually being VSTs)
- GUI and shortcut driven user interface
- No more manual config file editing (as was the case with [linvstmanage-cli](https://github.com/Goli4thus/linvstmanage))
- Update/Create *.so files for all tracked VSTs
- Enable/Disable VSTs by adding/removing a softlink to the respective *.so file.
  All softlinks are mapped to a *link folder* which can be scanned by your preferred DAW.
- Detection and optional removal of orphaned _*.so-links/files_ in _link folder_
- Regex based search of table entries
- "Blacklisting"
- and more...


## Dependencies
If you've already managed to build [LinVst](https://github.com/osxmidi/LinVst), then pretty much only:
- Qt5 for the graphical _LinVstManager_ application

## Building the source
Nevertheless, here are some distributions and the needed packages:

1. Install required packages based on your distribution:
  * **Manjaro**:
    ```
    sudo pacman -S cmake make gcc git wine qt5-base gcc-multilib
    ```

  * **Fedora 31**:
    ```
    sudo dnf install cmake make gcc gcc-c++ git wine wine-devel wine-devel.i686 qt5-devel
    ```
    <!-- Maybe the following as well: libstdc++.i686 -->

  * **Ubuntu 19.10**:
    ```
    sudo apt install cmake make gcc git libwine-development-dev qt5-default
    
    sudo dpkg --add-architecture i386
    
    sudo apt-get install libc6-dev-i386

    sudo apt-get install gcc-multilib g++-multilib

    sudo apt-get install libwine-development-dev:i386
    ```
    <!-- Regarding the 32 things: only copy/paste from LinVst README atm. -->
2. Clone this repository
  ```
  git clone https://github.com/goli4thus/linvstmanager
  ```

5. Change into the downloaded repository folder and run the following in a terminal:
  ```
  mkdir build && cd build
  cmake ..
  make -j4
  sudo make install
  ```

6. Now you should be able to launch _LinVstManager_ like any other graphical application.

## Usage
### First start
After having acknowledged that there can't be a config file on the first start of the application,
there's another message regarding closing your DAW before proceeding.
This is more important later on when you've already added some VSTs, because removing existing bridges
(*.so files) that a running DAW has loaded, will most certainly crash the DAW.

### Setting all up
Now the first thing should be to open _Option -> Preferences_:

![Preferences](https://github.com/Goli4thus/images/blob/master/images_linvstmanager/Preferences.png)

#### Bridges
Here you can setup one or more of the mentioned bridges. Specifically the location of the _*.so_ template files.

#### Defaults
When it comes to adding VSTs, choices got to be made which bridge should be used.
Here some default values can be specified.

#### General
- _Link folder_: The folder where all softlink will be created in and therefore the only location your DAW needs to be pointed at to "scan".
- _'VstDllCheck.exe'_: This is a small utility program which, if selected here, can be activated during _scanning_ for VSTs in order to verify encountered _*.dll_ files actually being VST2 files. After install it is located in _{repo-folder}/src/VstDllCheck/_


After all that, take a moment and explore the menu bar. Some operations are also available via right mouse click. Furthermore every operation can be done using a keyboard shortcut as well.

### If you've been using [linvstmanage-cli](https://github.com/Goli4thus/linvstmanage) previously...
... you're in luck. Try _File -> Import legacy config_ and locate the previous config file _linvstmanage.ini_ (by default located in _'~/.config/linvst/manage/'_.
Once selected, it will be parsed and all previously set up VSTs will be added into _LinVstManager_.

### Manually adding VSTs
Choose _Edit -> Add VST_ and locate one or more VSTs which shall be added.

### Scanning for VSTs
Choose _Edit -> Scan_ and give the text on top of the dialog an initial read.
Everything is explained there.

During the scan a progress indicator is shown which represents the actual scan progress.
Furthermore there are three counters indicating in realtime what is being found.

![ScanProgress](https://github.com/Goli4thus/images/blob/master/images_linvstmanager/ScanProgress.png)

Hint: Once a scan is done and the results are shown in the dialog's table, the entries can be filtered the same way as in the main table. Entries need to be selected (see right click menu) before they can be added. This allows to make a sub-selection of what was found (or just Ctrl-a, select, add).

#### Scan verification
Compared to simply adding VSTs via the respective menu actions, scanning can actually make use of a verification feature.
This requires that the within _LinVstManager_ included utilities _VstDllCheck64.exe" and _VstDllCheck32.exe_ have been set up in _Preferences.

In general, _*.vst3_ files are not being verified, as they are obviously VST files.

Here's what will happen depending on the "verify" selections you make within the scan dialog.

##### No verification method selected
All encountered _*.dll_ files will be considered a match and be shown in the results table.

##### One verification selected
Only encountered _*.dll_ files that pass the "64 bit VST" test (or "32 bit test" depending on selection) will be shown in the results table.
The opposite type will not be checked and therefore be ignored.

##### Both verification methods selected
All encountered _*.dll_ files that pass at least one of the two tests will be shown in the results table.


### Once VSTs are added,...
... their status will be _No *.so_ initially.

Performing an _update_ will create accompaning VST-so files for each VST.dll.
This results in the status of all VSTs becoming _Disabled_.

After that the VSTs can be _Enabled_, which creates softlinks within the _link folder_ referencing the previously created VST-so files.

This central _link folder_ can be scanned by whatever DAW you are using.


### Changing the bridge type
Select all VSTs you want to change to another bridge and use _Edit -> Change bridge_ (also accessible via right click menu) and select the desired one.


A tip in general:
There are lots of tooltips spread across labels, text fields, table headers, etc.
Just hover your mouse over things that don't quite make sense and chances are there is some additional information.

### Resolving naming conflicts
VSTs are being identified by their absolute path.
This means that if two different VSTs are named the same (i.e. "EQ.dll"), they both can be added to _LinVstManager_. Consequently this results in a naming conflict, indicated by status _Conflict_.
This can be resolved by using the _rename_ feature:

![Rename](https://github.com/Goli4thus/images/blob/master/images_linvstmanager/Rename.png)

#### Wait, are you really renaming my VST?
Well, not exactly.
The renaming affects the name shown within _LinVstManager_.
Apart from within the application, this name is used as the basis for creating the softlinks inside the _link folder_.

For example:
Let's say we have two VSTs by two different vendors, both named "EQ".
One of them will show up as a conflict once added to _LinVstManager_.
This conflict can be resolved by renaming the indicated VST. Let's say to "EQ_VendorX".
Once both of these VSTs are being _Enabled_, the _link folder_ will contain two softlinks:

- EQ.so
- EQ_VendorX.so

If you are pointing your DAW to scan the _link folder_, both VSTs will be picked up.

But depending on your DAW, the result will be different.
Some DAWs (i.e. Reaper) don't care what the filename of a VST is. The name (and vendor) shown in the FX browser are actually derived from what is set _within_ the VST itself.

Other DAWs in contrast do actually care about the filename and will display "EQ" and "EQ_VendorX" in their FX browser.

Overall this won't affect functionality of a VST, but might actually allow you to elegantly resolve naming conflicts without having to alter the naming of _*.dll_ or _*.vst3_ files.

## Further notes
### VST states

| State       | Meaning                                                                    |
| ----------- | -------------------------------------------------------------------------- |
| Enabled     | VST is enabled via active softlink                                         |
| Disabled    | VST is disabled due to missing softlink                                    |
| Mismatch    | Mismatch between linvst.so template and *.so file associated with VST file |
| No *.so     | VST-dll has no accompaning VST-so file next to it                          |
| NoBridge    | No suitable bridge has been enabled in preferences.                        |
| Conflict    | VST with the same name already exists                                      |
| Notfound    | VST-dll can't be found using the specified path                            |
| Orphan      | The so-file seems orphaned as it doesn't refer to an existing VST-dll      |
| Blacklisted | VST is blacklisted from being handled                                      |

Notes: 
- Only _Enabled_ VSTs can be seen by your DAW scanning the _link folder_.
- States _Mismatch_ and _No *.so_ can both be resolved by performing _Edit -> Update_.
- If a VST is 'Blacklisted', operations like _enable_, _disable_, _update_ all will have no effect on.
it until that VST is 'unblacklisted' once again

### Where is it all saved?
Everthing is being stored in a central config file:

    ~/.config/linvst/manager/linvstmanager_config.xml

As opposed to [linvstmanage-cli](https://github.com/Goli4thus/linvstmanage), there's no need to edit this file manually. Everything is done via the graphical interface.
    
    
### Further usability features
#### Filter bar
Apart from familiar table sorting features one can use _View -> Filter_ to open up a search bar. This search consideres all columns and is regex based (case insensitive).

Hint: Imagine all columns of a row being combined to one long string with rows being separated by one space character (cause that's how it's implemented).
This means you can perform searches like:

| Search                         | Effect                                                                                 |
| ------------------------------ | -------------------------------------------------------------------------------------  |
| eq                             | Matches rows containing "EQ"                                                           |
| eq&#124;comp                   | Matches rows containing "EQ" OR "Comp".                                                |
| vst2.*linvst3                  | Matches rows that contain "vst2" AND "linvst3" with anything in between in that order. |
| (?=.*linvst )(?=.*blacklisted) | Matches rows that contain "linvst " and "blacklisted" in any order.                    |
    
#### Sidebar
The sidebar on the right handside of the main window shows the amount of VSTs per status.
Furthermore the colored rectangles are actuall buttons and once clicked on will setup the filter bar to filter for the respective status (same effect as if entered manually in filter bar).

Hint: Clicking the same button again will cancel the filter.

### Further usecases
#### Updating or trying out different versions of a bridge
In case of updating or changing versions of LinVst (or another bridge), all that needs to be done is:
1. Install the respective bridge
2. Start _LinVstManager_ and select the newly installed _*.so_ template file with _Option -> Preferences_
3. Notice the resulting <i>No_So</i>; perform and _Edit -> Update_; all done

### Blacklisting VSTs: Why?
Let's say you've narrowed down to a subfolder within a wine prefix, but there still seem to be
many dll files that aren't VST files.

You could perform a scan *without* the 'verify' option. That would result in all non-VST-dll files
being detected as VST2 files in addition to the "real" VST2 files.
After that you could add/filter and _blacklist_ those.

During subsequent scans these dll files would be ignored due to already being "tracked".
In addition, _'blacklisted'_ VSTs won't interfere during other operations (i.e. enable all,...) and can optionally even be hidden via _View -> Hide blacklisted_.


