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

version_ge() {
    [ "$(printf '%s\n' "$1" "$2" | sort -V | tail -n1)" = "$1" ]
}

configure_qgs_transport() {
    local kernel
    local kernel_version
    local libvirtd_version=""
    local qemu_version=""

    if [ -x "$(command -v libvirtd)" ]; then
        libvirtd_version="$(libvirtd --version 2>/dev/null | grep -oE '[0-9]+(\.[0-9]+){2}' | head -n1 || true)"
    fi

    if [ -x "$(command -v qemu-system-x86_64)" ]; then
        qemu_version="$(qemu-system-x86_64 --version 2>/dev/null | head -n1 | grep -oE '[0-9]+(\.[0-9]+){2}' | head -n1 || true)"
    fi

    kernel="$(uname -r)"
    kernel_version="${kernel%%-*}"

    echo "kernel: ${kernel_version}"
    echo "libvirt: ${libvirtd_version}"
    echo "qemu: ${qemu_version}"

    if { [ -n "${libvirtd_version}" ] && version_ge "${libvirtd_version}" "11.6"; } || \
       { [ -n "${qemu_version}" ] && version_ge "${qemu_version}" "10.1.0"; } || \
       version_ge "${kernel_version}" "6.17"; then
        echo "unix socket based configuration for QGS"
        if [ -f /etc/qgs.conf ]; then
            sed -i -E 's/^([[:space:]]*port[[:space:]]*=.*)/#\1/' /etc/qgs.conf
        fi
    else
        echo "vsock based configuration for QGS"
        if [ -f /etc/qgs.conf ]; then
            sed -i -E 's/^([[:space:]]*)#([[:space:]]*port[[:space:]]*=.*)$/\1\2/' /etc/qgs.conf
        fi
    fi
}

# Create user and group if not exist
id -u qgsd &> /dev/null || \
    /usr/sbin/useradd -r -U -c "User for qgsd" \
    -d /var/opt/qgsd -s /sbin/nologin qgsd

# Configure QGS transport (vsock or socket) based on the environment
configure_qgs_transport

# Start the QGS service
mkdir -p /etc/systemd/system/qgsd.service.d
tee /etc/systemd/system/qgsd.service.d/socket.conf > /dev/null << 'EOF'
[Service]
RuntimeDirectory=tdx-qgs
UMask=0111
EOF

if [ -d /run/systemd/system ]; then
    systemctl daemon-reload
    systemctl enable qgsd
    systemctl start qgsd 
elif [ -d /etc/init/ ]; then
    /sbin/initctl reload-configuration
    /sbin/initctl start qgsd
fi

exit 0
