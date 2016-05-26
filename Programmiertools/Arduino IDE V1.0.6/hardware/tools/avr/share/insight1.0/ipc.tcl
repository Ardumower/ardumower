# ipc.tcl
# Copyright (C) 2004 Red Hat, Inc.
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
# Implements IPC for multiple Insight instances, allowing any Insight
# to send commands to all other Insights on the same host.
#
#   PUBLIC METHODS:
#
#     send $cmd - sends $cmd to all Insights
#
# ----------------------------------------------------------------------

itcl::class Iipc {

  private variable socklist
  private variable portnum 9909
  private variable serversock

  constructor {} {
    init
  }

  destructor {
    debug
    foreach sock $socklist {
      catch {::close $sock}
    }

    if {$serversock != "0"} {
      catch {::close $serversock}
    }
    set ::iipc 0
  }
  
  private method init {} {
    debug "iipc init"
    set socklist {}
    set serversock 0
    set portnum [pref get gdb/ipc/port]
    if {[catch {socket -server [code $this accept] $portnum} serversock]} {
      debug "server already exists.  Connecting to it."
      set socklist [socket localhost $portnum]
      fconfigure $socklist -buffering line -blocking 0
      fileevent $socklist readable [code $this read $socklist]
    }
    set ::iipc 1
  }

  # accept new connection to server
  private method accept {sock addr port} {
    debug "accepting connecting from $sock -> $addr:$port"
    fconfigure $sock -buffering line -blocking 0
    lappend socklist $sock
    fileevent $sock readable [code $this sread $sock]
  }

  private method read {s} {
    if [eof $s] {
      debug "The server died on $s!!"
      catch {::close $s}
      init
      return
    }
    gets $s res
    debug "Server: $res"
    switch $res {
      quit { gdb_force_quit }
      stop { gdbtk_stop }
      run { gdbtk_run }
      default {
	catch {gdb_immediate "$res"}
      }
    }
  }

  # server read method.  Reads data then forwards
  # it to all listening sockets.
  private method sread {s} {
    if [eof $s] {
      close $s
      return
    }
    gets $s res
    if {$res != ""} {
      debug "Got: $res"
      foreach sock $socklist {
	if {$s != $sock} {
	  if {[catch {puts $sock $res}]} {
	    close $sock
	  }
	}
      }
      switch $res {
	quit { gdb_force_quit }
	stop { gdbtk_stop }
	run { gdbtk_run }
	default {
	  catch {gdb_immediate "$res"}
	}
      }
    }
  }

  # send data to all sockets.
  public method send {cmd} {
    debug "send $cmd"
    foreach sock $socklist {
      if {[catch {puts $sock $cmd}]} {
	close $sock
      }
    }
  }

  private method close {s} {
    debug "closing socket $s"
    set socklist [lremove $socklist $s]
    catch {::close $s}
  }
}





