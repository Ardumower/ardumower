#!/usr/bin/wish
# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 42) (by Poul-Henning Kamp):
# Joerg Wunsch <j.gnu@uriah.heep.sax.de> wrote this file.  As long as you
# retain this notice you can do whatever you want with this stuff. If we meet
# some day, and you think this stuff is worth it, you can buy me a beer
# in return.
# ----------------------------------------------------------------------------
#
# Simple Makefile generator for AVR-GCC
#
# $Id: mfile.tcl,v 2.12 2008/11/06 03:35:52 arcanum Exp $

# Full path name where various files will be found

if {[info exists env(MFILE_HOME)]} {
    set prefix $env(MFILE_HOME)
} else {
    if {$tcl_platform(platform) == "unix"} {
	set prefix "/usr/local/share/mfile"
    } else {
	set prefix "."
    }
}

set templatename "$prefix/makefile_template"
set helpfile "$prefix/help.html"
set mainicon "$prefix/mfile.xbm"
set helpicon "$prefix/htmlview.xbm"

global helpfile mainicon helpicon

# color to highlight changed items with
global highlight
set highlight "\#ffff80"

#
# end of configurable section
#

global devicelist
set devicelist \
    { {at90can32 0x800900} \
      {at90can64 0x801100} \
      {at90can128 0x801100} \
      at90pwm1 \
      at90pwm2 \
      at90pwm216 \
      at90pwm2b \
      at90pwm3 \
      at90pwm316 \
      at90pwm3b \
      at90s1200 \
      at90s2313 \
      at90s2323 \
      at90s2333 \
      at90s2343 \
      {at90s4414 0x800160} \
      at90s4433 \
      at90s4434 \
      {at90s8515 0x800260} \
      at90s8535 \
      at90usb1286 \
      at90usb1287 \
      at90usb162 \
      at90usb646 \
      at90usb647 \
      at90usb82 \
      {atmega103 0x801000} \
      {atmega128 0x801100} \
      {atmega1280 0x802200} \
      {atmega1281 0x802200} \
      atmega1284p \
      atmega16 \
      {atmega161 0x800460} \
      {atmega162 0x800500} \
      atmega163 \
      atmega164p \
      atmega165 \
      atmega165p \
      atmega168 \
      atmega168p \
      atmega169 \
      atmega169p \
      atmega2560 \
      atmega2561 \
      atmega32 \
      atmega323 \
      atmega324p \
      atmega325 \
      atmega325p \
      atmega3250 \
      atmega328p \
      atmega329 \
      atmega329p \
      atmega3290 \
      atmega3290p \
      atmega32c1 \
      atmega32m1 \
      atmega32u4 \
      atmega32u6 \
      atmega406 \
      atmega48 \
      atmega48p \
      {atmega64 0x801100} \
      {atmega640 0x802200} \
      atmega644 \
      atmega644p \
      atmega645 \
      atmega6450 \
      atmega649 \
      atmega6490 \
      atmega8 \
      {atmega8515 0x800260} \
      atmega8535 \
      atmega88
      atmega88p
      attiny11 \
      attiny12 \
      attiny13 \
      attiny13a \
      attiny15 \
      attiny167 \
      attiny22 \
      attiny2313 \
      attiny24 \
      attiny25 \
      attiny26 \
      attiny261 \
      attiny28 \
      attiny43u \
      attiny44 \
      attiny45 \
      attiny461 \
      attiny48 \
      attiny84 \
      attiny85 \
      attiny861 \
      attiny88 \
      at94K \
      at76c711 \
      at43usb320 \
      at43usb355 \
      at86rf401 \
      atxmega64a1 \
      atxmega64a3 \
      atxmega128a1 \
      atxmega128a3 \
      atxmega256a3 \
      atxmega256a3b }

global makefile

global filename
set filename "Makefile"
global basename
set basename $filename

global backupsuffix
if {$tcl_platform(platform) == "unix"} {
    set backupsuffix "~"
} else {
    set backupsuffix ".bak"
}

global extmemparts
foreach m $devicelist {
    if {[llength $m] > 1} {
	set extmemparts([lindex $m 0]) [lindex $m 1]
    }
}

global extmemmax memoffset
set extmemmax [expr 0x80ffff]
set memoffset [expr 0x800000]

proc parsetemplate {fname} {
    global makefile

    set fh [open $fname]
    set template [read $fh]
    close $fh

    global mainfile mcutype oformat optlevel stdlevel src mainfilesrc
    global asrc printfopts scanfopts deftarget avrdudeprog avrdudeport
    global dformat
    global extmemsize extmemstart extmemopts
    global extmemmax extmemparts memoffset

    foreach v { mainfile mcutype oformat optlevel stdlevel src \
		    mainfilesrc asrc printfopts scanfopts deftarget \
		    avrdudeprog avrdudeport dformat \
		    extmemsize extmemstart extmemopts} {
	if {[info exists $v]} {
	    unset $v
	}
    }

    # Now parse what we've got, and allocate our
    # internal variables
    if {[regexp {(?n)^MCU\s*=\s*(\S+)} $template dummy x]} {
	set mcutype $x
    }

    if {[regexp {(?n)^TARGET\s*=\s*(\S+)} $template dummy x]} {
	set mainfile $x
    }

    if {[regexp {(?n)^FORMAT\s*=\s*(\S+)} $template dummy x]} {
	set oformat $x
    }

    if {[regexp {(?n)^OPT\s*=\s*(\S+)} $template dummy x]} {
	set optlevel $x
    }

    if {[regexp {(?n)^DEBUG\s*=\s*(\S+)} $template dummy x]} {
	set dformat $x
    }

    if {[regexp {(?n)^CSTANDARD\s*=\s*-std=(\S+)} $template dummy x]} {
	set stdlevel $x
    }

    if {[regexp {(?n)^SRC\s*=\s*(.*)$} $template dummy x]} {
	if {[regexp {(.*)\$[(]TARGET[)].c(.*)} $x dummy y z]} {
	    # replace multiple consecutive spaces by just one
	    regsub -all {\s+} "$y$z" " " y
	    set src $y
	    # mainfilesrc == 1 means include $(TARGET).c into SRC
	    set mainfilesrc 1
	} else {
	    set src $x
	    # mainfilesrc == 0 means do not include $(TARGET).c into SRC
	    set mainfilesrc 0
	}
    }

    if {[regexp {(?n)^ASRC\s*=\s*(\S+)} $template dummy x]} {
	set asrc ""
    }

    if {[regexp {(?n)^PRINTF_LIB\s*=\s*(\S+)} $template dummy x]} {
	if {$x == {$(PRINTF_LIB_MIN)}} {
	    set printfopts "min"
	} elseif {$x == {$(PRINTF_LIB_FLOAT)}} {
	    set printfopts "flt"
	} else {
	    set printfopts "none"
	}
    }

    if {[regexp {(?n)^SCANF_LIB\s*=\s*(\S+)} $template dummy x]} {
	if {$x == {$(SCANF_LIB_MIN)}} {
	    set scanfopts "min"
	} elseif {$x == {$(SCANF_LIB_FLOAT)}} {
	    set scanfopts "flt"
	} else {
	    set scanfopts "none"
	}
    }

    if {[regexp {(?n)^EXTMEMOPTS\s*=(.*)$} $template dummy x]} {
	if {[regexp -- {--section-start[,=]\.data=([0-9a-fA-Fx]+).*__heap_end=([0-9a-fA-Fx]+)} \
		$x dummy y1 y2]} {
	    # variables & heap are in external RAM
	    set extmemopts "vars"
	} elseif {[regexp \
		{__heap_start=([0-9a-fA-Fx]+).*__heap_end=([0-9a-fA-Fx]+)} \
		$x dummy y1 y2]} {
	    # only heap in external RAM
	    set extmemopts "heap"
	} else {
	    set extmemopts "none"
	    if {$x != ""} {
		complain "Unknown EXTMEMOPTS $x, ignored"
	    }
	}
	if {$extmemopts != "none"} {
	    set extmemstart [expr $y1]
	    if {[expr $y2 == $extmemmax]} {
		set extmemsize [expr $extmemmax + 1]
	    } else {
		set extmemsize [expr $y2 - $y1 + 1]
	    }
	    if {[info exists mcutype]} {
		if {[info exists extmemparts($mcutype)]} {
		    if {[expr $extmemparts($mcutype) == $y1]} {
			# extmemstart == 0 means "lowest possible value"
			set extmemstart 0
		    }
		}
	    }
	}
    }

    if {[regexp {(?n)^build:\s*(.*)$} $template dummy x]} {
	if {[regexp {\sextcoff\s*$} $x]} {
	    set deftarget "extcoff"
	} elseif {[regexp {\scoff\s*$} $x]} {
	    set deftarget "coff"
	} else {
	    set deftarget "none"
	}
    }

    if {[regexp {(?n)^AVRDUDE_PROGRAMMER\s*=\s*(\S+)} $template dummy x]} {
	set avrdudeprog $x
    }

    if {[regexp {(?n)^AVRDUDE_PORT\s*=\s*(\S+)} $template dummy x]} {
	set avrdudeport $x
    }

    set makefile $template
}

proc makemfilemenu {} {
    global tcl_platform
    global devicelist xram
    global mainfile mcutype oformat optlevel stdlevel src mainfilesrc
    global asrc printfopts scanfopts deftarget avrdudeprog avrdudeport
    global dformat debugidx
    global extmemsize extmemstart extmemopts
    global extmemmax extmemparts extmemmentry memoffset

    .f1.f1.mb2.m1 delete 0 last
    foreach w [winfo children .f1.f1.mb2.m1] {
	destroy $w
    }

    .f1.f1.mb2.m1 add command -label {Code generation} -state disabled
    if {[info exists mainfile]} {
	.f1.f1.mb2.m1 add command -command {setmainfile} \
	    -label "Main file name..." -underline 0
    }
    if {[info exists mcutype]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c1 \
	    -label "MCU type" \
	    -underline 2
    }
    if {[info exists oformat]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c2 \
	    -label "Output format" \
	    -underline 7
    }
    if {[info exists optlevel]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c3 \
	    -label "Optimization level" \
	    -underline 0
    }
    if {[info exists dformat]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c30 \
	    -label "Debug format" \
	    -underline 0
    }
    if {[info exists stdlevel]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c31 \
	    -label "C standard level" \
	    -underline 2
    }
    if {[info exists src]} {
	.f1.f1.mb2.m1 add command -command {asksrc} \
	    -label "C/C++ source file(s)..." -underline 0
    }
    if {[info exists asrc]} {
	.f1.f1.mb2.m1 add command -command {setasrc} \
	    -label "Assembler source file(s)..." -underline 0
    }
    if {[info exists printfopts]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c4 \
	    -label "printf() options" \
	    -underline 0
    }
    if {[info exists scanfopts]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c41 \
	    -label "scanf() options" \
	    -underline 3
    }
    if {[info exists extmemopts]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c42 \
	    -label "External RAM options" \
	    -underline 1 -state disabled
	set extmemmentry [.f1.f1.mb2.m1 index end]
	if {[info exists mcutype]} {
	    if {[info exists extmemparts($mcutype)]} {
		.f1.f1.mb2.m1 entryconfigure $extmemmentry \
			-state normal
	    }
	}
    }
    if {[info exists deftarget] && ! [info exists dformat]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c5 \
	    -label "Default \"make\" target" \
	    -underline 15
    }

    .f1.f1.mb2.m1 add separator
    .f1.f1.mb2.m1 add command -label {AVRdude} -state disabled

    switch $tcl_platform(platform) {
	"windows" {
	    set portlist {usb com1 com2 com3 com4 lpt1 lpt2 lpt3}
	}
	"unix" {
	    switch $tcl_platform(os) {
		"Linux" {
		    set portlist {usb /dev/ttyS0 /dev/ttyS1 /dev/ttyS2 /dev/ttyS3 \
				      /dev/parport0 /dev/parport1 /dev/parport2}
		}
		"FreeBSD" {
		    set portlist {usb dev/cuaa0 /dev/cuaa1 /dev/cuaa2 /dev/cuaa3 \
				      /dev/ppi0 /dev/ppi1 /dev/ppi2}
		}
		"Solaris" {
		    set portlist {usb /dev/term/a /dev/term/b /dev/printers/0}
		}
	    }
	}
    }

    if {[info exists avrdudeprog]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c6 \
	    -label {Programmer} \
	    -underline 3
    }
    if {[info exists portlist] && [info exists avrdudeport]} {
	.f1.f1.mb2.m1 add cascade -menu .f1.f1.mb2.m1.c7 \
	    -label {Port} \
	    -underline 2
    }

    .f1.f1.mb2.m1 add separator
    .f1.f1.mb2.m1 add command -label {Miscellaneous} -state disabled
    .f1.f1.mb2.m1 add checkbutton -variable editwidget \
	-label "Enable Editing of Makefile" \
	-command changeeditable \
	-onvalue normal -offvalue disabled

    .f1.f1.mb2 configure -menu .f1.f1.mb2.m1

    if {[info exists mcutype]} {
	menu .f1.f1.mb2.m1.c1 -tearoff 0
	.f1.f1.mb2.m1.c1 add cascade -menu .f1.f1.mb2.m1.c1.at90 \
	    -label "AT90" -underline 2
	.f1.f1.mb2.m1.c1 add cascade -menu .f1.f1.mb2.m1.c1.atmega \
	    -label "ATmega" -underline 2
	.f1.f1.mb2.m1.c1 add cascade -menu .f1.f1.mb2.m1.c1.attiny \
	    -label "ATtiny" -underline 2
	.f1.f1.mb2.m1.c1 add cascade -menu .f1.f1.mb2.m1.c1.other \
	    -label "Other" -underline 0

	menu .f1.f1.mb2.m1.c1.at90 -tearoff 0
	menu .f1.f1.mb2.m1.c1.atmega -tearoff 0
	menu .f1.f1.mb2.m1.c1.attiny -tearoff 0
	menu .f1.f1.mb2.m1.c1.other -tearoff 0

	foreach m $devicelist {
	    set mcu [lindex $m 0]
	    if {[llength $mcu] > 1} {
		set xram($mcu) [lindex $m 1]
	    }
	    switch -glob $mcu {
		"at90*" {
		    .f1.f1.mb2.m1.c1.at90 add radiobutton -variable mcutype \
			-label $mcu -command setmcu
		}
		"atmega*" {
		    .f1.f1.mb2.m1.c1.atmega add radiobutton -variable mcutype \
			-label $mcu -command setmcu
		}
		"attiny*" {
		    .f1.f1.mb2.m1.c1.attiny add radiobutton -variable mcutype \
			-label $mcu -command setmcu
		}
		"*" {
		    .f1.f1.mb2.m1.c1.other add radiobutton -variable mcutype \
			-label $mcu -command setmcu
		}
	    }
	}
    }

    if {[info exists oformat]} {
	menu .f1.f1.mb2.m1.c2 -tearoff 0

	foreach f {srec ihex binary} {
	    .f1.f1.mb2.m1.c2 add radiobutton -variable oformat \
		-label $f -command setoformat
	}
    }

    if {[info exists optlevel]} {
	menu .f1.f1.mb2.m1.c3 -tearoff 0

	foreach f {0 1 s 2 3} {
	    .f1.f1.mb2.m1.c3 add radiobutton -variable optlevel \
		-label $f -command setoptlevel
	}
    }

    if {[info exists dformat]} {
	menu .f1.f1.mb2.m1.c30 -tearoff 0

	if {[info exists deftarget]} {
	    # We've got both, DEBUG and the default target selection.
	    # Join them into a single menu entry.
	    if {$dformat == "dwarf-2"} {
		set debugidx 3
	    } elseif {$deftarget == "none"} {
		set debugidx 0
	    } elseif {$deftarget == "coff"} {
		set debugidx 1
	    } elseif {$deftarget == "extcoff"} {
		set debugidx 2
	    } else {
		set debugidx 0
	    }
	    # Note that the order of the setdeftarget and setdformat
	    # calls below determines which of the edited fields will
	    # be displayed highlighted to the user.  The last one
	    # wins.  Thus, we highlight the stabs vs. dwarf-2 decision
	    # for the ELF formats, or the default build target for the
	    # COFF formats.
	    .f1.f1.mb2.m1.c30 add radiobutton \
		-variable debugidx -value 0 \
		-label "ELF/stabs (GDB/Insight)" \
		-command {set dformat "stabs"; set deftarget "none"; \
			      setdeftarget; setdformat }
	    .f1.f1.mb2.m1.c30 add radiobutton \
		-variable debugidx -value 1 \
		-label {AVR-COFF (AVR Studio 3.x, VMLAB < 3.10 [obsolete])} \
		-command {set dformat "stabs"; set deftarget "coff"; \
			      setdformat; setdeftarget }
	    .f1.f1.mb2.m1.c30 add radiobutton \
		-variable debugidx -value 2 \
		-label {AVR-ext-COFF (AVR Studio 4.07+, VMLAB 3.10+ [obsolete])} \
		-command {set dformat "stabs"; set deftarget "extcoff"; \
			      setdformat; setdeftarget }
	    .f1.f1.mb2.m1.c30 add radiobutton \
		-variable debugidx -value 3 \
		-label {ELF/DWARF-2 (AVR Studio 4.11+)} \
		-command {set dformat "dwarf-2"; set deftarget "none"; \
			      setdeftarget; setdformat }
	} else {
	    foreach f {stabs dwarf-2} {
		.f1.f1.mb2.m1.c30 add radiobutton -variable dformat \
		    -label $f -command setdformat
	    }
	}
    }

    if {[info exists stdlevel]} {
	menu .f1.f1.mb2.m1.c31 -tearoff 0

	foreach f {c89 gnu89 c99 gnu99} {
	    .f1.f1.mb2.m1.c31 add radiobutton -variable stdlevel \
		-label $f -command setstdlevel
	}
    }

    if {[info exists printfopts]} {
	menu .f1.f1.mb2.m1.c4 -tearoff 0

	.f1.f1.mb2.m1.c4 add radiobutton -variable printfopts \
	    -label "none/standard" -underline 0 -value "none" -command setprintfopts
	.f1.f1.mb2.m1.c4 add radiobutton -variable printfopts \
	    -label "minimalistic" -underline 0 -value "min" -command setprintfopts
	.f1.f1.mb2.m1.c4 add radiobutton -variable printfopts \
	    -label "floating point" -underline 0 -value "flt" -command setprintfopts
    }

    if {[info exists scanfopts]} {
	menu .f1.f1.mb2.m1.c41 -tearoff 0

	.f1.f1.mb2.m1.c41 add radiobutton -variable scanfopts \
	    -label "none/standard" -underline 0 -value "none" -command setscanfopts
	.f1.f1.mb2.m1.c41 add radiobutton -variable scanfopts \
	    -label "minimalistic" -underline 0 -value "min" -command setscanfopts
	.f1.f1.mb2.m1.c41 add radiobutton -variable scanfopts \
	    -label "floating point + %\[" -underline 0 -value "flt" -command setscanfopts
    }

    if {[info exists extmemopts]} {
	menu .f1.f1.mb2.m1.c42 -tearoff 0

	.f1.f1.mb2.m1.c42 add radiobutton -variable extmemopts \
	    -label "none" -underline 0 -value "none" -command setextmemopts
	.f1.f1.mb2.m1.c42 add radiobutton -variable extmemopts \
	    -label "variables & heap" -underline 0 -value "vars" -command setextmemopts
	.f1.f1.mb2.m1.c42 add radiobutton -variable extmemopts \
	    -label "heap only" -underline 0 -value "heap" -command setextmemopts
	.f1.f1.mb2.m1.c42 add cascade -menu .f1.f1.mb2.m1.c42.c1 \
		-label "Ext. memory start" -underline 5
	.f1.f1.mb2.m1.c42 add cascade -menu .f1.f1.mb2.m1.c42.c2 \
		-label "Ext. memory size" -underline 14

	menu .f1.f1.mb2.m1.c42.c1 -tearoff 0
	foreach m {0 1024 2048 4096 8192 16384 32768} {
	    if {$m == 0} {
		set s "lowest possible"
		set v 0
	    } else {
		set s [format {%d KB} [expr $m / 1024]]
		set v [expr $m + $memoffset]
	    }
	    .f1.f1.mb2.m1.c42.c1 add radiobutton -variable extmemstart \
		    -label $s -value $v \
		    -command setextmemopts
	}

	menu .f1.f1.mb2.m1.c42.c2 -tearoff 0
	foreach m {1024 2048 4096 8192 16384 32768 65536} {
	    set s [format {%d KB} [expr $m / 1024]]
	    .f1.f1.mb2.m1.c42.c2 add radiobutton -variable extmemsize \
		    -label $s -value [expr $m] \
		    -command setextmemopts
	}
    }

    if {[info exists deftarget] && ! [info exists dformat]} {
	menu .f1.f1.mb2.m1.c5 -tearoff 0

	.f1.f1.mb2.m1.c5 add radiobutton -variable deftarget \
	    -label "standard (ELF + ihex/srec/binary)" -underline 0 \
	    -value "none" -command setdeftarget
	.f1.f1.mb2.m1.c5 add radiobutton -variable deftarget \
	    -label "AVR \"Extended\" COFF (AVR Studio 4.07+, VMLAB 3.10+)" -underline 6 \
	    -value "extcoff" -command setdeftarget
	.f1.f1.mb2.m1.c5 add radiobutton -variable deftarget -underline 4 \
	    -label "AVR COFF (AVR Studio 3.x, VMLAB < 3.10)" \
	    -value "coff" -command setdeftarget
    }

    if {[info exists avrdudeprog]} {
	menu .f1.f1.mb2.m1.c6 -tearoff 0

	foreach p [lsort {dasa3 dasa ponyser dapa xil futurlec \
		       abcmini picoweb sp12 alf bascom dt006 \
		       pony-stk200 stk200 pavr jtag2 jtag2fast \
		       jtag2slow jtagmkII jtagmkI avr911 avr109 \
		       butterfly avr910 stk500v2 stk500 avrisp2 \
		       avrispv2 avrisp bsd }] {
	    .f1.f1.mb2.m1.c6 add radiobutton -variable avrdudeprog \
		-label $p -command setavrdudeprog
	}
    }

    if {[info exists portlist] && [info exists avrdudeport]} {
	menu .f1.f1.mb2.m1.c7 -tearoff 0

	foreach p $portlist {
	    .f1.f1.mb2.m1.c7 add radiobutton -variable avrdudeport \
		-label $p -command setavrdudeport
	}
    }

}

proc writefile {fname} {
    global backupsuffix makefile modified

    if {[file exists $fname]} {
	file rename -force $fname "$fname$backupsuffix"
    }
    set makefile [.f1.f2.f1.t1 get 1.0 end]
    set f [open $fname "w"]
    puts $f $makefile
    close $f
    set modified 0
}

proc about {} {
    toplevel .about

    set x [winfo pointerx .]
    set y [winfo pointery .]
    if {$x != -1 && $y != -1} {
	wm geometry .about "+[expr $x - 250]+[expr $y - 100]"
    }
    wm title .about {About Mfile}
    wm resizable .about 0 0

    frame .about.f1
    message .about.f1.m1 \
	-relief sunken \
	-width 500 \
	-text \
{Mfile - Simple Makefile generator for AVR-GCC

Copyright © 2003,2004 Jörg Wunsch

$Revision: 2.12 $ $Date: 2008/11/06 03:35:52 $

"THE BEER-WARE LICENSE" (Revision 42) (by Poul-Henning Kamp):
Joerg Wunsch <j.gnu@uriah.heep.sax.de> wrote this file.  As long as you
retain this notice you can do whatever you want with this stuff. If we meet
some day, and you think this stuff is worth it, you can buy me a beer
in return.}
    button .about.f1.ok -command {destroy .about} -text {OK}

    pack configure .about.f1.m1 -side top
    pack configure .about.f1.ok -side bottom
    pack configure .about.f1

    tkwait window .about
}

proc setmcu {} {
    global mcutype
    global editwidget
    global highlight modified
    global extmemmentry extmemparts extmemstart extmemopts

    set r1 [.f1.f2.f1.t1 search -regexp "^MCU = " 1.0]
    if {$r1 == ""} {
	complain "Oops, MCU not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, MCU not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "MCU = $mcutype"
    .f1.f2.f1.t1 configure -state $editwidget
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, MCU not found"
	return
    }

    if {[info exists extmemopts]} {
	if {[info exists extmemparts($mcutype)]} {
	    .f1.f1.mb2.m1 entryconfigure $extmemmentry -state normal
	    if {$extmemstart == ""} {
		set extmemstart 0
	    }
	    if {$extmemstart == 0 || \
		    [expr $extmemparts($mcutype) == $extmemstart]} {
		# extmemstart == 0 means "lowest possible value"
		set extmemstart 0
		setextmemopts
	    }
	} else {
	    .f1.f1.mb2.m1 entryconfigure $extmemmentry -state disabled
	}
    }

    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
    .f1.f2.f1.t1 see $r1
}

proc setoformat {} {
    global oformat
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^FORMAT = " 1.0]
    if {$r1 == ""} {
	complain "Oops, FORMAT not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, FORMAT not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "FORMAT = $oformat"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, FORMAT not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setoptlevel {} {
    global optlevel
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^OPT = " 1.0]
    if {$r1 == ""} {
	complain "Oops, OPT not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, OPT not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "OPT = $optlevel"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, OPT not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setdformat {} {
    global dformat
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^DEBUG = " 1.0]
    if {$r1 == ""} {
	complain "Oops, DEBUG not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, DEBUG not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "DEBUG = $dformat"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, DEBUG not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setstdlevel {} {
    global stdlevel
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^CSTANDARD = " 1.0]
    if {$r1 == ""} {
	complain "Oops, CSTANDARD not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, CSTANDARD not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "CSTANDARD = -std=$stdlevel"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, CSTANDARD not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setdeftarget {} {
    global deftarget
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^build:" 1.0]
    if {$r1 == ""} {
	complain "Oops, default target not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, default target not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    set line [.f1.f2.f1.t1 get $r1 $r2]
    if {[regexp {^(.*) (ext)?coff} $line dummy d]} {
	set line $d
    } else {
	regsub {^(.*)} $line {\1} line
    }
    switch $deftarget {
	"coff" {
	    set line "$line coff"
	}
	"extcoff" {
	    set line "$line extcoff"
	}
	"none" {
	    set line "$line"
	}
    }
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "$line"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, default target not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setprintfopts {} {
    global printfopts
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^PRINTF_LIB = " 1.0]
    if {$r1 == ""} {
	complain "Oops, PRINTF_LIB not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, PRINTF_LIB not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    switch $printfopts {
	"none" {
	    set line "PRINTF_LIB = "
	}
	"min" {
	    set line "PRINTF_LIB = \$(PRINTF_LIB_MIN)"
	}
	"flt" {
	    set line "PRINTF_LIB = \$(PRINTF_LIB_FLOAT)"
	}
    }
    .f1.f2.f1.t1 insert $r2 "$line"
    
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, PRINTF_LIB not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setscanfopts {} {
    global scanfopts
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^SCANF_LIB = " 1.0]
    if {$r1 == ""} {
	complain "Oops, SCANF_LIB not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, SCANF_LIB not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    switch $scanfopts {
	"none" {
	    set line "SCANF_LIB = "
	}
	"min" {
	    set line "SCANF_LIB = \$(SCANF_LIB_MIN)"
	}
	"flt" {
	    set line "SCANF_LIB = \$(SCANF_LIB_FLOAT)"
	}
    }
    .f1.f2.f1.t1 insert $r2 "$line"
    
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, SCANF_LIB not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setextmemopts {} {
    global extmemsize extmemstart extmemopts
    global extmemmax extmemparts extmemmentry memoffset
    global mcutype
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^EXTMEMOPTS *=" 1.0]
    if {$r1 == ""} {
	complain "Oops, EXTMEMOPTS not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, EXTMEMOPTS not found"
	return
    }
    if {$extmemopts != "none"} {
	if {![info exists extmemsize]} {
	    set extmemsize [expr $extmemmax + 1 - $memoffset]
	} elseif {$extmemsize == 0 || $extmemsize == ""} {
	    set extmemsize [expr $extmemmax + 1 - $memoffset]
	}
	if {![info exists extmemstart]} {
	    set extmemstart 0
	} elseif {$extmemstart == 0 || $extmemstart == ""} {
	    set extmemstart 0
	}
	if {[expr $extmemstart] == 0} {
	    set m $extmemparts($mcutype)
	} else {
	    set m [expr $extmemstart]
	}
	set xstart [format {0x%x} [expr $m]]
	if {[expr $memoffset + $extmemsize] == [expr $extmemmax + 1]} {
	    set xend [format {0x%x} [expr $extmemmax]]
	} else {
	    set xend [format {0x%x} [expr $m + $extmemsize - 1]]
	}
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    switch $extmemopts {
	"none" {
	    set line "EXTMEMOPTS = "
	}
	"vars" {
	    set line "EXTMEMOPTS = -Wl,--section-start,.data=$xstart,--defsym=__heap_end=$xend"
	}
	"heap" {
	    set line "EXTMEMOPTS = -Wl,--defsym=__heap_start=$xstart,--defsym=__heap_end=$xend"
	}
    }
    .f1.f2.f1.t1 insert $r2 "$line"
    
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, EXTMEMOPTS not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setmainfile {} {
    global mainfile
    global editwidget
    global highlight modified

    set mainfile [ask $mainfile "Main file"]

    set r1 [.f1.f2.f1.t1 search -regexp "^TARGET = " 1.0]
    if {$r1 == ""} {
	complain "Oops, TARGET not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, TARGET not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "TARGET = $mainfile"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, TARGET not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setmakefile {} {
    global basename
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^MAKEFILE\\s*=" 1.0]
    if {$r1 == ""} {
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, MAKEFILE not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "MAKEFILE = $basename"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, MAKEFILE not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setasrc {} {
    global asrc
    global editwidget
    global highlight modified

    set asrc [ask $asrc "Assembler source file(s)"]

    set r1 [.f1.f2.f1.t1 search -regexp "^ASRC = " 1.0]
    if {$r1 == ""} {
	complain "Oops, ASRC not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, ASRC not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "ASRC = $asrc"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, ASRC not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setavrdudeprog {} {
    global avrdudeprog
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^AVRDUDE_PROGRAMMER = " 1.0]
    if {$r1 == ""} {
	complain "Oops, AVRDUDE_PROGRAMMER not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, AVRDUDE_PROGRAMMER not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "AVRDUDE_PROGRAMMER = $avrdudeprog"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, AVRDUDE_PROGRAMMER not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc setavrdudeport {} {
    global avrdudeport
    global editwidget
    global highlight modified

    set r1 [.f1.f2.f1.t1 search -regexp "^AVRDUDE_PORT = " 1.0]
    if {$r1 == ""} {
	complain "Oops, AVRDUDE_PORT not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, AVRDUDE_PORT not found"
	return
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "AVRDUDE_PORT = $avrdudeport"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, AVRDUDE_PORT not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc complain {text} {
    if {[winfo exists .complain]} {
	return
    }
    toplevel .complain
    set x [winfo pointerx .]
    set y [winfo pointery .]
    if {$x != -1 && $y != -1} {
	wm geometry .complain "+$x+$y"
    }
    wm title .complain {Error}
    wm resizable .complain 0 0
    
    message .complain.m1 -text $text
    button .complain.ok -text {OK} -command {destroy .complain}

    pack .complain.m1
    pack .complain.ok

    tkwait window .complain
}

proc ask {val text} {
    global askval

    if {[winfo exists .ask]} {
	return
    }

    toplevel .ask
    set x [winfo pointerx .]
    set y [winfo pointery .]
    if {$x != -1 && $y != -1} {
	wm geometry .ask "+$x+$y"
    }
    wm title .ask $text
    wm resizable .ask 0 0

    set askval $val

    frame .ask.f1
    label .ask.f1.l1 -text "$text:"
    entry .ask.f1.e1 -width 20 -relief sunken -textvariable askval

    frame .ask.f2
    button .ask.f2.b1 -text {OK} -command {destroy .ask}

    pack configure .ask.f1.l1 -side left
    pack configure .ask.f1.e1 -side left
    pack configure .ask.f1
    pack configure .ask.f2.b1 -side top
    pack configure .ask.f2

    bind .ask.f1.e1 <Key-Return> {destroy .ask}

    tkwait window .ask

    return $askval
}

proc asksrc {} {
    global src mainfilesrc mainfile
    global editwidget
    global highlight modified

    if {[winfo exists .ask]} {
	return
    }

    toplevel .ask
    set x [winfo pointerx .]
    set y [winfo pointery .]
    if {$x != -1 && $y != -1} {
	wm geometry .ask "+$x+$y"
    }
    wm title .ask {Source files}
    wm resizable .ask 1 0

    frame .ask.f1
    frame .ask.f1.f1
    label .ask.f1.f1.l1 -text "C/C++ source file(s):"
    entry .ask.f1.f1.e1 -width 20 -relief sunken -textvariable src
    button .ask.f1.f1.b1 -text "Choose file..." \
	-command {
	    global src
	    set x [tk_getOpenFile -filetypes {
		{{C source files} {.c}}
		{{C++ source files} {.C .cc .cxx}}
		{{All files} *}
	    }]
	    if {$x != ""} {
		set rootname [lindex [file split [pwd]] 0]
		if {[string range $x 0 [expr [string length $rootname] - 1]] \
			== $rootname} {
		    # Try finding common path name components to the
		    # current working directory.  If found, eliminate
		    # them.
		    set y [pwd]
		    set prefix "."
		    while {[expr [string first $y $x] == -1]} {
			set y [file dirname $y]
			if {$prefix == "."} {
			    set prefix ".."
			} else {
			    set prefix "../${prefix}"
			}
		    }
		    if {$y != $rootname} {
			# If more than the root directory name
			# remained, replace it.
			set commonlen [string length $y]
			set x [string range $x $commonlen end]
			set x "${prefix}${x}"
		    }
		}
		set src "$src $x"
	    }
	    focus .ask
	    wm deiconify .ask
	    if {[string length $src]} {
		# let the entry widget auto-size
		.ask.f1.f1.e1 configure -width 0
	    }
	}
    frame .ask.f1.f2
    checkbutton .ask.f1.f2.cb1 -variable mainfilesrc
    label .ask.f1.f2.l1 -text "Include ${mainfile}.c"
    button .ask.f1.f2.b1 -text {OK} -command {destroy .ask}

    pack configure .ask.f1.f1.l1 -side left
    pack configure .ask.f1.f1.e1 -side left -expand y -fill x
    pack configure .ask.f1.f1.b1 -side left
    pack configure .ask.f1.f1 -side top -anchor nw -expand y -fill x
    pack configure .ask.f1.f2.cb1 -side left
    pack configure .ask.f1.f2.l1 -side left
    pack configure .ask.f1.f2.b1 -side right
    pack configure .ask.f1.f2 -side top -anchor nw -expand y -fill x
    pack configure .ask.f1 -expand y -fill x

    bind .ask.f1.f1.e1 <Key-Return> {destroy .ask}
    focus .ask

    tkwait window .ask

    set r1 [.f1.f2.f1.t1 search -regexp "^SRC = " 1.0]
    if {$r1 == ""} {
	complain "Oops, SRC not found"
	return
    }
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, SRC not found"
	return
    }

    if {$mainfilesrc != 0} {
	set s "\$(TARGET).c $src"
    } else {
	set s "$src"
    }
    set modified 1
    .f1.f2.f1.t1 configure -state normal
    .f1.f2.f1.t1 delete $r1 $r2
    .f1.f2.f1.t1 insert $r2 "SRC = $s"
    .f1.f2.f1.t1 configure -state $editwidget
    .f1.f2.f1.t1 see $r1
    set r2 [.f1.f2.f1.t1 search -regexp {$} $r1]
    if {$r2 == ""} {
	complain "Oops, SRC not found"
	return
    }
    .f1.f2.f1.t1 tag delete highlight
    .f1.f2.f1.t1 tag add highlight $r1 $r2
    .f1.f2.f1.t1 tag configure highlight -background $highlight
}

proc changeeditable {} {
    global editwidget modified

    if {$editwidget == "normal"} {
	set modified 1
    }
    .f1.f2.f1.t1 configure -state $editwidget
}

proc openfile {} {
    global filename basename
    global modified
    global asksavereply
    global makefile editwidget

    if {$modified} {
	if {[winfo exists .asksave]} {
	    return
	}
	toplevel .asksave
	message .asksave.l1 -width 400 \
	    -text "The current buffer has been modified.\n\nDiscard changes?"
	frame .asksave.f1
	button .asksave.f1.ok -text {Yes} -command {
	    global asksavereply
	    set asksavereply 1
	    destroy .asksave
	}
	button .asksave.f1.cancel -text {No} -command {
	    global asksavereply
	    set asksavereply 0
	    destroy .asksave
	}

	pack configure .asksave.l1 -side top
	pack configure .asksave.f1.ok -side left
	pack configure .asksave.f1.cancel -side left
	pack configure .asksave.f1 -side top

	set x [winfo pointerx .]
	set y [winfo pointery .]
	if {$x != -1 && $y != -1} {
	    wm geometry .asksave "+$x+$y"
	}

	tkwait window .asksave

	if {$asksavereply == 0} {
	    return
	}

	set modified 0
    }

    set fn [tk_getOpenFile -initialfile $filename]
    if {[string length $fn] > 0} {
	parsetemplate $fn
	makemfilemenu

	set filename $fn
	catch "regsub {^.*/} $fn {} basename"
	wm title . $basename

	.f1.f2.f1.t1 configure -state normal
	.f1.f2.f1.t1 delete 1.0 end
	.f1.f2.f1.t1 insert end $makefile
	.f1.f2.f1.t1 configure -state $editwidget

	setmakefile
    }
}

proc saveas {} {
    global filename basename
    set fn [tk_getSaveFile -initialfile $filename]
    if {[string length $fn] > 0} {
	set filename $fn
	catch "regsub {^.*/} $fn {} basename"
	wm title . $basename
	setmakefile
	writefile $fn
    }
}

proc quit {force} {
    global modified filename

    if {$modified} {
	if {$force} {
	    # called from WM_SAVE_YOURSELF handler only -- no time
	    # to ask the luser back
	    wm protocol . WM_SAVE_YOURSELF {}
	    set modified 0
	    writefile "${filename}.saved"
	    exit 0
	}

	if {[winfo exists .askquit]} {
	    return
	}
	toplevel .askquit
	message .askquit.l1 -width 400 \
	    -text "The current buffer has been modified.\n\nExit anyway?"
	frame .askquit.f1
	button .askquit.f1.ok -text {Yes} -command {
	    wm protocol . WM_DELETE_WINDOW {}
	    wm protocol . WM_SAVE_YOURSELF {}
	    exit 0
	}
	button .askquit.f1.cancel -text {No} -command {destroy .askquit}

	pack configure .askquit.l1 -side top
	pack configure .askquit.f1.ok -side left
	pack configure .askquit.f1.cancel -side left
	pack configure .askquit.f1 -side top

	set x [winfo pointerx .]
	set y [winfo pointery .]
	if {$x != -1 && $y != -1} {
	    wm geometry .askquit "+$x+$y"
	}

	tkwait window .askquit
    } else {
	exit 0
    }
}

source "$prefix/htmlview.tcl"

parsetemplate $templatename

global editwidget
set editwidget disabled

global modified
set modified 0

frame .f1

frame .f1.f1

# "File" menu
menubutton .f1.f1.mb1 -text File -underline 0

menu .f1.f1.mb1.m1 -tearoff 1
.f1.f1.mb1.m1 add command -command {writefile $filename} \
    -label Save -underline 0
.f1.f1.mb1.m1 add command -command {saveas} \
    -label {Save As...} -underline 5
.f1.f1.mb1.m1 add command -command {openfile} \
    -label {Open...} -underline 0
.f1.f1.mb1.m1 add separator
.f1.f1.mb1.m1 add command -command {quit 0} -label Exit -underline 1

.f1.f1.mb1 configure -menu .f1.f1.mb1.m1

# "Help" menu
menubutton .f1.f1.mbH -text Help -underline 0

menu .f1.f1.mbH.m1 -tearoff 1
.f1.f1.mbH.m1 add command -command {htmlview $helpfile} \
    -label "Help..." -underline 0
.f1.f1.mbH.m1 add separator
.f1.f1.mbH.m1 add command -command {about} -label "About..." -underline 0

.f1.f1.mbH configure -menu .f1.f1.mbH.m1

# "Makefile" menu
menubutton .f1.f1.mb2 -text Makefile -underline 0
menu .f1.f1.mb2.m1 -tearoff 1 -disabledforeground blue3
makemfilemenu

frame .f1.f2
frame .f1.f2.f1
text .f1.f2.f1.t1 -height 25 -width 80 -wrap none \
    -yscrollcommand {.f1.f2.f1.s1 set} \
    -xscrollcommand {.f1.f2.s2 set} \
    -state $editwidget
scrollbar .f1.f2.f1.s1 -command {.f1.f2.f1.t1 yview}
scrollbar .f1.f2.s2 -orient horizontal -command {.f1.f2.f1.t1 xview}

pack configure .f1.f1.mbH -side right
pack configure .f1.f1.mb1 -side left
pack configure .f1.f1.mb2 -side left
pack configure .f1.f1 -fill x -side top -anchor nw

pack configure .f1.f2.f1.t1 -side left -expand y -fill both -anchor nw
pack configure .f1.f2.f1.s1 -side left -fill y -anchor nw
pack configure .f1.f2.f1 -side top -expand y -fill both -anchor nw
pack configure .f1.f2.s2 -side left -expand y -fill x -anchor nw
pack configure .f1.f2 -side top -expand y -fill both -anchor nw

pack configure .f1 -side left -expand y -fill both -anchor nw

update
set x [winfo width .]
set y [winfo height .]
wm minsize . $x $y

# XBM icons look fairly stupid on Windows since the background will
# be rendered in black.  Rather keep the standar Tk icon there.
if {$tcl_platform(platform) == "unix" && [file exists $mainicon]} {
    wm iconbitmap . @$mainicon
}

.f1.f2.f1.t1 configure -state normal
.f1.f2.f1.t1 insert end $makefile
.f1.f2.f1.t1 configure -state $editwidget

bind . <Key-F1> {htmlview $helpfile}

# When the text widget is in normal state, <Key-Prior> and <Key-Next>
# already work as expected, but they don't when it is in disabled
# state (since the widget doesn't get any focus then) so we override
# it globally here.  While we are at it, bind <Key-Home> and <Key-End>
# as well.

bind . <Key-Prior> ".f1.f2.f1.t1 yview scroll -10 units"
bind . <Key-Next> ".f1.f2.f1.t1 yview scroll 10 units"
bind . <Key-Home> ".f1.f2.f1.t1 yview moveto 0"
bind . <Key-End> ".f1.f2.f1.t1 yview moveto 1"

wm protocol . WM_DELETE_WINDOW {quit 0}
wm protocol . WM_SAVE_YOURSELF {quit 1}
