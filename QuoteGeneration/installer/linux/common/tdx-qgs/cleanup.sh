#!/usr/bin/env bash
#
# Copyright (C) 2011-2026 Intel Corporation. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   * Neither the name of Intel Corporation nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#


set -e 

if test $(id -u) -ne 0; then
    echo "Root privilege is required."
    exit 1
fi

# Stop the daemon before the package manager removes its binary.
if [ -d /run/systemd/system ]; then
    # Stop and disable the service before removing its configuration.
    # || true prevents set -e from aborting if qgsd was never started 
    # or already crashed — uninstallation must succeed regardless of 
    # daemon state.
    systemctl stop qgsd || true
    # Remove the boot-time symlinks so a future reinstall starts with 
    # clean enable state
    systemctl disable qgsd 2>/dev/null || true
    # Delete files created by the package and cleanup directory if empty afterwards
    rm -f /etc/systemd/system/qgsd.service.d/socket.conf
    rmdir --ignore-fail-on-non-empty /etc/systemd/system/qgsd.service.d 2>/dev/null || true
    # || true: daemon-reload is best-effort on uninstall — its only job is to tell a
    # running systemd to forget the removed unit.  In containers/chroots systemd is
    # unreachable and the command fails; that must not abort the rest of cleanup.
    systemctl daemon-reload || true
elif [ -d /etc/init/ ]; then
    # || true: keep uninstall best-effort — if Upstart tooling is missing or
    # returns non-zero, package removal must not abort (consistent with stop below).
    /sbin/initctl reload-configuration || true
    # Upstart has no drop-in to clean up, but its conf must be reloaded so initctl's 
    # view of the job matches the on-disk state before we stop it.
    /sbin/initctl stop qgsd || true
fi

# Remove the runtime socket directory if it was not already cleaned up 
# by systemd's RuntimeDirectory mechanism (e.g. on non-systemd systems 
# or if the service never started successfully).
if [ -d /run/tdx-qgs ]; then
    rmdir /run/tdx-qgs 2>/dev/null || true
fi

# Remove the dedicated service account last.
# Deleting the user while the daemon is still running would leave 
# an ownerless process. By this point the service has been stopped 
# above, so it's safe to proceed.
/usr/sbin/userdel qgsd 2> /dev/null || true
/usr/sbin/groupdel qgsd 2> /dev/null || true

exit 0
