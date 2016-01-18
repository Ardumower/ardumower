# Open a viewer for HTML help info
# Copyright (C) 2002, 2008, Red Hat, Inc.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License (GPL) as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# ------------------------------------------------------------------------------
# NAME:		public proc open_help
# SYNOPSIS:	open_help file
# DESC:		Opens html help file using an appropriate
#		browser.
# ------------------------------------------------------------------------------

proc open_help {hfile} {
  debug $hfile
  # create full pathname link
  set link file://[file join $::GDBTK_LIBRARY help $hfile]

  # windows is easy
  if {$::gdbtk_platform(platform) == "windows"} {
    ide_shell_execute open $link
    return
  }

  #
  # for Unix, we never know what is installed
  #

  # set list of viewer apps to try
  switch [pref get gdb/compat] {
    "KDE" {
      set apps {htmlview khelpcenter firefox opera mozilla}
    }
    "GNOME" {
      set apps {htmlview firefox opera mozilla gnome-help khelpcenter}
    }      
    default {
      set apps {htmlview firefox opera mozilla gnome-help khelpcenter netscape}
    }
  }

  # If the user has previously entered a browser name, append it
  # to the list. Should it go first or last? 
  set bname [pref get gdb/help/browsername]
  if {$bname != ""} {
    lappend apps $bname
  }
  
  # now loop through list checking each application
  foreach app $apps {
    debug "app=$app"
    if {[catch "exec $app $link &" result]} {
      debug "$app failed: $result"
    } else {
      return
    }
  }
  
  # if we reached here, nothing worked, so prompt for a name
  set text "No help browser was found on your system.\n\
Please enter the name of an HTML viewer application."
  while {[set app [prompt_helpname  $text]] != "0"} {
    if {$app != ""} {
      if {[catch "exec $app $link &" result]} {
	dbug W "$app failed: $result"
	set text "Could not run application $app.\n\
Please enter the name of an HTML viewer application."
      } else {
	pref set gdb/help/browsername $app
	return
      }
    }
  }
}

# displays an entry dialog and asks for the name of an application
# returns 0 on cancel
#         name on success
proc prompt_helpname {text} {
  iwidgets::promptdialog .pd -title "Browser Query" -modality application \
    -labeltext  $text
  if {[.pd activate]} {
    set app [string trim [.pd get]]
    destroy .pd
    return $app
  }
  destroy .pd
  debug "cancelled"
  return 0
}

