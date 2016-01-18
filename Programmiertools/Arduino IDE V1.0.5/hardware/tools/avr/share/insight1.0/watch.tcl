# Watch window for Insight.
# Copyright (C) 2002, 2003, 2006 Red Hat
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


# ----------------------------------------------------------------------
# Implements watch windows for gdb.
# ----------------------------------------------------------------------

itcl::class WatchWin {
  inherit EmbeddedWin GDBWin
  # ------------------------------------------------------------------
  #  CONSTRUCTOR - create new watch window
  # ------------------------------------------------------------------
  constructor {args} {
    debug

    gdbtk_busy
    build_win $itk_interior
    gdbtk_idle
    
    add_hook gdb_no_inferior_hook "$this no_inferior"
    add_hook gdb_clear_file_hook [code $this clear_file]
    add_hook file_changed_hook [code $this clear_file]
  }
  

  # ------------------------------------------------------------------
  #   PUBLIC METHOD:  busy - BusyEvent handler
  #           Disable all ui elements that could affect gdb's state
  # ------------------------------------------------------------------
  method busy {event} {
    debug
    set Running 1
    cursor watch
  }

  # Re-enable the UI
  method idle {event} {
    debug
    set Running 0
    cursor {}
  }

  # ------------------------------------------------------------------
  # METHOD:   no_inferior
  #           Reset this object.
  # ------------------------------------------------------------------
  method no_inferior {} {
    debug
    cursor {}
    set Running 0
    foreach var $Watched {
      $var delete
    }
    $tree remove all
  }
  
  # ------------------------------------------------------------------
  #  METHOD:  cursor - change the toplevel's cursor
  # ------------------------------------------------------------------
  method cursor {what} {
    [winfo toplevel [namespace tail $this]] configure -cursor $what
    ::update idletasks
  }
  
  
  # ------------------------------------------------------------------
  # METHOD: build_win - build window for watch. 
  # ------------------------------------------------------------------
  method build_win {f} {
    #debug "$f"
    
    set f [::frame $f.f]
    set treeFrame  [frame $f.top]
    set entryFrame [frame $f.expr]

    set tree [VarTree $treeFrame.tree]
    pack $tree -expand yes -fill both

    set Entry [entry $entryFrame.ent -font global/fixed]
    button $entryFrame.but -text "Add Watch" -command [code $this validateEntry]
    pack $f -fill both -expand yes
    grid $entryFrame.ent -row 0 -column 0 -sticky news -padx 2
    grid $entryFrame.but -row 0 -column 1 -padx 2
    grid columnconfigure $entryFrame 0 -weight 1
    grid columnconfigure $entryFrame 1

    grid $treeFrame -row 0 -column 0 -sticky news
    grid $entryFrame -row 1 -column 0 -padx 5 -pady 5 -sticky news
    grid columnconfigure $f 0 -weight 1
    grid rowconfigure $f 0 -weight 1
    window_name "Watch"
    ::update idletasks
    # Binding for the entry
    bind $entryFrame.ent <Return> "$entryFrame.but flash; $entryFrame.but invoke"
  }

  method validateEntry {} {
    if {!$Running} {
      debug "Getting entry value...."
      set variable [$Entry get]
      debug "Got $variable, going to add"
      set ok [add $variable]
      debug "Added... with ok: $ok"      
      $Entry delete 0 end
    }
  }

  # ------------------------------------------------------------------
  #  METHOD: clear_file - Clear out state so that a new executable
  #             can be loaded. For WatchWins, this means doing
  #             everything that no_inferior does.
  # ------------------------------------------------------------------
  method clear_file {} {
    debug
    no_inferior
  }

  # ------------------------------------------------------------------
  # DESTRUCTOR - delete watch window
  # ------------------------------------------------------------------
  destructor {
    debug
    set tree {}

    # Remove this window and all hooks
    remove_hook gdb_no_inferior_hook "$this no_inferior"
    remove_hook gdb_clear_file_hook [code $this clear_file]
    remove_hook file_changed_hook [code $this clear_file]

    foreach var $Watched {
      $var delete
    }
  }

  method remove {entry} {
    debug $entry

    # Remove this entry from the list of watched variables
    set Watched [lremove $Watched $entry]

    $entry remove
    $entry delete
  }


  method update {event} {
    $tree update
  }


  # ------------------------------------------------------------------
  # METHOD: add - add a variable to the watch window
  # ------------------------------------------------------------------
  method add {name} {
    debug "Trying to add \"$name\" to watch"
 
    # Strip all the junk after the first \n
    set var [split $name \n]
    set var [lindex $var 0]
    set var [split $var =]
    set var [lindex $var 0]

    # Strip out leading/trailing +, -, ;, spaces, commas
    set var [string trim $var +-\;\ \r\n,]

    # Make sure that we have a valid variable
    set err [catch {gdb_cmd "set variable $var"} errTxt]
    if {$err} {
      dbug W "ERROR adding variable: $errTxt"
      ManagedWin::open WarningDlg -transient \
	-over $this -message [list $errTxt] -ignorable "watchvar"
    } else {
      if {[string index $var 0] == "\$"} {
	# We must make a special attempt at verifying convenience
	# variables.. Specifically, these are printed as "void"
	# when they are not defined. So if a user type "$_I_made_tbis_up",
	# gdb responds with the value "void" instead of an error
	catch {gdb_cmd "p $var"} msg
	set msg [split $msg =]
	set msg [string trim [lindex $msg 1] \ \r\n]
	if {$msg == "void"} {
	  return 0
	}
      }

      debug "In add, going to add $name"
      # make one last attempt to get errors
      set err [catch {set foo($name) 1}]
      debug "err1=$err"
      set err [expr {$err + [catch {expr {$foo($name) + 1}}]}]
      debug "err2=$err"
      if {!$err} {
	set var [gdb_variable create -expr $name]
	debug "var=$var"
	$tree add $var
	lappend Watched $var
	return 1
      }
    }    
    return 0
  }

  protected variable Entry
  protected variable Watched {}
  protected variable tree
  protected variable Running
}
