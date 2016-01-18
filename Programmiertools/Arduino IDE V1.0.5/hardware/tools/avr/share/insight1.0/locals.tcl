# Local Variable Window for Insight.
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
# Implements local variables windows for gdb.
# ----------------------------------------------------------------------

itcl::class LocalsWin {
  inherit EmbeddedWin GDBWin
  # ------------------------------------------------------------------
  #  CONSTRUCTOR - create new locals window
  # ------------------------------------------------------------------
  constructor {args} {
    debug

    gdbtk_busy
    build_win $itk_interior
    gdbtk_idle
    
    add_hook gdb_no_inferior_hook "$this no_inferior"
    add_hook gdb_clear_file_hook [code $this clear_file]
    add_hook file_changed_hook [code $this clear_file]

    update dummy
  }
  

  # ------------------------------------------------------------------
  #   PUBLIC METHOD:  busy - BusyEvent handler
  #           Disable all ui elements that could affect gdb's state
  # ------------------------------------------------------------------
  method busy {event} {
    debug
    cursor watch
  }

  # Re-enable the UI
  method idle {event} {
    debug
    cursor {}
  }

  # ------------------------------------------------------------------
  # METHOD:   no_inferior
  #           Reset this object.
  # ------------------------------------------------------------------
  method no_inferior {} {
    debug
    cursor {}
    catch {delete object $_frame}
    set _frame {}
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
  # METHOD: build_win - build window for variables. 
  # ------------------------------------------------------------------
  method build_win {f} {
    #debug "$f"
    
    set tree [VarTree $f.tree -type "local"]
    pack $f.tree -expand yes -fill both
    pack $f -expand yes -fill both
    
    window_name "Local Variables"
    ::update idletasks
  }


  # ------------------------------------------------------------------
  #  METHOD: clear_file - Clear out state so that a new executable
  #             can be loaded. For LocalWins, this means doing
  #             everything that no_inferior does.
  # ------------------------------------------------------------------
  method clear_file {} {
    no_inferior
  }

  # ------------------------------------------------------------------
  # DESTRUCTOR - delete locals window
  # ------------------------------------------------------------------
  destructor {
    debug
    set tree {}

    # Remove this window and all hooks
    remove_hook gdb_no_inferior_hook "$this no_inferior"
    remove_hook gdb_clear_file_hook [code $this clear_file]
    remove_hook file_changed_hook [code $this clear_file]
  }

  method context_switch {} {
    debug

    set err [catch {gdb_selected_frame} current_frame]
    #debug "1: err=$err; _frame=\"$_frame\"; current_frame=\"$current_frame\""

    if {$err && $_frame != ""} {
      # No current frame
      debug "no current frame"
      catch {delete object $_frame}
      set _frame {}
      return 1
    } elseif {$current_frame == "" && $_frame == ""} {
      #debug "2"
      return 0
    } elseif {$_frame == "" || $current_frame != [$_frame address]} {
      # We've changed frames. If we knew something about
      # the stack layout, we could be more intelligent about
      # destroying variables, but we don't know that here (yet).
      debug "switching to frame at $current_frame"
      
      # Destroy the old frame and create the new one
      catch {destroy $_frame}
      set _frame [Frame ::\#auto $current_frame]
      debug "created new frame: $_frame at [$_frame address]"
      return 1
    }
    
    # Nothing changed
    #debug "3"
    return 0
  }


  method update {event} {
    debug

    # Check that a context switch has not occured
    if {[context_switch]} {
      debug "CONTEXT SWITCH"
      
      # delete variables in tree
      $tree remove all

      if {$_frame != ""} {
	$tree add [$_frame variables]
      }
    } else {
      if {$_frame == ""} {return}
      # check for any new variables in the same frame
      $tree add [$_frame new]
    }    
    after idle [code $tree update]
  }
  
  protected variable Entry
  protected variable tree
  protected variable _frame {}
}
