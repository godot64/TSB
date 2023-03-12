# TSB.MON 1.04
**TSB.MON** is a machine code monitor (and also a disk monitor and a simple direct assembler) which adds to the usefulness of TSB's debugging and analyzing commands. It occupies 4 KB of memory from $7000 (to $7fff). TSB.MON is an enhanced (a little) version of **SMON**, which was first published in German **64'er Magazin** in 1984 to 1985. TSB.MON is derived from the most useful **[SMON Relocatable Source Code repository](https://github.com/LeshanDaFo/SMON-RelocatableSourceCode "Github Link")** of **Claus Schlereth** in its version 1.1.4.007 (of 2023.01.14).   

## Changes to the original SMON

When in TSB you can activate TSB.MON using the launcher program "**smon**" (on TSB system disk). Just LOAD and RUN it. It installs itself to $7000 and starts working with protecting itself by limiting the available Basic RAM. Also, the launcher redefines the text assignment of the **function key #9** (C=F1) to "SYS$7000:&lArr;", so you can activate TSB.MON with just a single keystroke.

With monitor command "**Z**" you enter the internal disk monitor which in TSB creates its 256 bytes buffer at $c000. You find a brief [manual of SMON](https://www.c64-wiki.de/wiki/SMON#Standardmodus_-_Maschinensprachemonitor "Link to SMON Manual") in German C64-Wiki.

Unlike the original SMON, you may continue the output of commands "**M**", "**D**", and "**K**" after aborting them with just the command letter again (without further parameters). 

After leaving TSB.MON (with command "**X**") ist resets TSB's text colors to the defaults (background: mid grey, border: dark grey, pen color: black).

Arndt Dettke

---
[TSB.MON]: https://github.com/LeshanDaFo/SMON-RelocatableSourceCode
[manual to SMON]: https://www.c64-wiki.de/wiki/SMON#Standardmodus_-_Maschinensprachemonitor